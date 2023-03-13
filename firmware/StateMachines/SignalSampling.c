#include "SignalSampling.h"
#include "SamplingParams.h"
#include "HAL/HAL_ADC.h"
#include "HAL/HAL_globalIntMask.h"
#include "../HelperClasses/WindowAvg.h" // todo: add ./ as include directory

/* Private variable declarations */
#define SAMPLE_BUF_SIZE 32 //256
#define FOURIER_SUM_ARRAY_LEN 64

#define TIMEBASE_MASK 0b11111100        // clears the lower 2 bits so that (readIdx & TIMEBASE_MASK) is a multiple 4

// Raw buffers for averaging/summing
static int16_t sampBuf[SAMPLE_BUF_SIZE];   // Raw ADC sample buffer
/*! \todo If math optimization is needed, int16 or int24 can be used instead of int32 */
static int16_t FourierSumSin[FOURIER_SUM_ARRAY_LEN];
static int16_t FourierSumCos[FOURIER_SUM_ARRAY_LEN];

// State machine owned by the main software thread
static struct {
    uint8_t readIdx;                    //buffer index of the next sample to be converted; copy of the volatile variable owned by the ISR, updated every task loop
    
    // Averaging/summing
    WndAvg_t avgSin;
    WndAvg_t avgCos;
    
    bool dataReady;
}SM;

// State machine owned by the ISR
static volatile struct {
    uint8_t writeIdx;            //buffer index of the next sample to be converted; read-only except by the ISR callback
    bool bufFull;
}ISRvars;

static int32_t sumSin = 0;
static int32_t sumCos = 0;

/* Private function declarations */
static void resetBuf(void);
static void ISRcallback(void);

/* Public function definitions */

void SigSamp_init()
{
    HAL_initADC(TSAMP_PRESCALER, TSAMP_POSTSCALER - 1, TSAMP_PERIOD - 1);
    HAL_globalIntEn();
    WndAvg_init(&SM.avgSin, FourierSumSin, FOURIER_SUM_ARRAY_LEN);
    WndAvg_init(&SM.avgCos, FourierSumCos, FOURIER_SUM_ARRAY_LEN);
    
    resetBuf();
    HAL_registerADCisrCallback(ISRcallback);
}

void SigSamp_start()
{
    HAL_ADCEnable();
    resetBuf();
}

void SigSamp_stop()
{
    HAL_ADCDisable();
}
void SigSamp_tasks()
{
    /* Protected section: make local copies of ISR-owned volatile variables. */
    HAL_globalIntDis();
    bool bufFull_cpy = ISRvars.bufFull;
    HAL_globalIntEn();
    
    /*
     * Data processing task description:
     * 
     * -New ADC samples are processed 4 samples at a time, since f_samp = 4 * (frequency of interest), and 4 samples = 2*pi radians
     * -Once the predetermined number of periods ("period" = 4 samples) are processed, the sine/cosine sums are saved in a buffer
     *      used for post-averaging/filtering.
     */
#if 1
    SM.dataReady = false;
    if (!bufFull_cpy) { return; }  //debugging: try summing the whole buffer all at once
    
    sumCos = 0;
    sumSin = 0;
    SM.readIdx = 0;
    for (int i = 0; i < (SAMPLE_BUF_SIZE >> 2); i++)
    {
        const int16_t* buf = &sampBuf[SM.readIdx];
        /** 2-bit sine lookup table = {0, 1, 0, -1}
         *  2-bit cosine lookup table = {1, 0, -1, 0}
         */
        sumSin += buf[1] - buf[3];
        sumCos += buf[0] - buf[2];
        
        SM.readIdx += 4;
    }
    SM.dataReady = true;
    HAL_globalIntDis();
    ISRvars.bufFull = false;
    HAL_globalIntEn();
    
#else
    /* Process new samples in groups of 4 */
    while ((uint8_t)(writeIdx_cpy - SM.readIdx) >= 4)
    {
        const int16_t* buf = &sampBuf[SM.readIdx];
        /** 2-bit sine lookup table = {0, 1, 0, -1}
         *  2-bit cosine lookup table = {1, 0, -1, 0}
         */
        int16_t sumSin = buf[1] - buf[3];
        int16_t sumCos = buf[0] - buf[2];
        
        SM.readIdx += 4;
        WndAvg_pushVal(&SM.avgSin, sumSin);     /*! \todo: what are the minimum sizes for the WndAvg_pushVal() input arguments? */
        WndAvg_pushVal(&SM.avgCos, sumCos);
    }
#endif
}

uint8_t SigSamp_getTimebase(void)
{
    return SM.readIdx & TIMEBASE_MASK;
}

bool SigSamp_dataReady(void)
{
    return SM.dataReady;
}

void SigSamp_getSigStr(int32_t* pSinOut, int32_t* pCosOut, uint8_t* numCycles)
{
#if 1
    *pSinOut = sumSin;
    *pCosOut = sumCos;
    *numCycles = SAMPLE_BUF_SIZE >> 2;
    
#else
    *pSinOut = WndAvg_getSum(&SM.avgSin);
    *pCosOut = WndAvg_getSum(&SM.avgCos);
    *numCycles = SM.readIdx >> 2;
#endif
}

/* Private function definitions */
static void resetBuf(void)
{
    // Reset indices
    SM.readIdx = 0;
    ISRvars.writeIdx = 0;
    
    // Reset Fourier sums
    WndAvg_clear(&SM.avgSin);
    WndAvg_clear(&SM.avgCos);
}

static void ISRcallback(void)
{
    /* When buffer is full, index will overflow to zero. check if main software thread is
     * finished processing the buffer.
     */
#if 1
    if (!ISRvars.bufFull)
    {
        // Push new sample to the buffer, increment buf index
        sampBuf[ISRvars.writeIdx] = HAL_ADCGetConv();
        ISRvars.writeIdx++;
        if (SAMPLE_BUF_SIZE == ISRvars.writeIdx) {
            ISRvars.bufFull = true;
            ISRvars.writeIdx = 0;
        }
    }
#else
    if ((ISRvars.writeIdx > 0) || ((0 == SM.readIdx))) {       /* Equivalent to checking if write-index is NOT waiting at 0
                                                                  * for read-index to increment/rollover to 0,
                                                                  * i.e. main software thread has finished processing the buffer. */
        // Push new sample to the buffer, increment buf index
        sampBuf[ISRvars.writeIdx] = HAL_ADCGetConv();
        ISRvars.writeIdx++;
    }
#endif
}