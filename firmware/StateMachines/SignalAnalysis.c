#include "SignalAnalysis.h"
#include "SignalSampling.h"
#include "SamplingParams.h"
#include "HelperClasses/WindowAvg.h"

#define N_SAMPLES_PER_REFRESH 8
#define N_CYCLES_PER_REFRESH 2
#define FOURIER_SUM_ARRAY_LEN 64
#define TRIG_LOOKUP_TABLE_LEN 4     // must equal 4

/* Private variable declarations */

// Raw buffers for averaging/summing
/*! \todo If math optimization is needed, int16 or int24 can be used instead of int32 */
int32_t FourierSumSin[FOURIER_SUM_ARRAY_LEN];
int32_t FourierSumCos[FOURIER_SUM_ARRAY_LEN];

//State machine
static struct
{
    uint16_t idxProcessed; /*! \todo can idxProcessed be a uint8_t? */
    
    // Averaging/summing
    WndAvg_t avgSin;
    WndAvg_t avgCos;

    //newest signal strength data
    uint16_t sigStrength;
}SM;

/* Private function declarations */
void resetSums();   // Reset index and sums

/* Public function definitions */

void SigAnalysis_init()
{
    WndAvg_init(&SM.avgSin, FourierSumSin, FOURIER_SUM_ARRAY_LEN);
    WndAvg_init(&SM.avgCos, FourierSumCos, FOURIER_SUM_ARRAY_LEN);
    
    SigAnalysis_reset();
}

void SigAnalysis_reset()
{
    resetSums();
    WndAvg_clear(&SM.avgSin);
    WndAvg_clear(&SM.avgCos);
}

void SigAnalysis_tasks()
{
    /*
     * Task loop description:
     * 
     * -New ADC samples are processed 4 samples at a time, since f_samp = 4 * (frequency of interest), and 4 samples = 2*pi radians
     * -Once the predetermined number of periods ("period" = 4 samples) are processed, the sine/cosine sums are saved in a buffer
     *      used for post-averaging/filtering.
     */
    
    /* Process new samples in groups of 4 */
    uint16_t NTotalSamples = SigSamp_getNumSamples();
    while (NTotalSamples - SM.idxProcessed >= 4)
    {
        const int16_t* buf = &SigSamp_getSampBuf()[SM.idxProcessed];
        /** 2-bit sine lookup table = {0, 1, 0, -1}
         *  2-bit cosine lookup table = {1, 0, -1, 0}
         */
        int16_t sumSin = buf[1] - buf[3];
        int16_t sumCos = buf[0] - buf[2];
        
        SM.idxProcessed += 4;
        WndAvg_pushVal(&SM.avgSin, sumSin);     /*! \todo: what are the minimum sizes for the WndAvg_pushVal() input arguments? */
        WndAvg_pushVal(&SM.avgCos, sumCos);
    }
}

void SigAnalysis_getSigStr(int32_t* pSinOut, int32_t* pCosOut)
{
    *pSinOut = WndAvg_getSum(&SM.avgSin);
    *pCosOut = WndAvg_getSum(&SM.avgCos);
}

/* Private function definitions */

void resetSums()
{
    // Reset index and sums
    SM.idxProcessed = 0;
}