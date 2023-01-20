#include "SignalAnalysis.h"
#include "SignalSampling.h"
#include "SamplingParams.h"
#include "HelperClasses/WindowAvg.h"

/* Private variable declarations */

// Raw buffers for averaging/summing
int16_t sinSumBuf[POST_FILT_SUM_LEN];
int16_t cosSumBuf[POST_FILT_SUM_LEN];

//State machine
static struct
{
    //partially-filled buffer
    int16_t sumSin;     //int16's can hold 32*(4 sample cycles * trig table coefficients) = 128 ADC samples
    int16_t sumCos;
    uint16_t sumCnt;
    
    // Averaging/summing
    WndAvg_t avgSin;
    WndAvg_t avgCos;

    //newest signal strength data
    uint16_t sigStrength;
}SM;

/* Private function declarations */
void resetSums();   // Reset index and sums
uint16_t fastSqrt(int32_t x);

/* Public function definitions */

void SigAnalysis_init()
{
    WndAvg_init(&SM.avgSin, sinSumBuf, POST_FILT_SUM_LEN);
    WndAvg_init(&SM.avgCos, cosSumBuf, POST_FILT_SUM_LEN);
    
    SigAnalysis_reset();
}

void SigAnalysis_reset()
{
    SM.sigStrength = 0;
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
    uint16_t newSmpGroups = (SigSamp_getNumSamples() - SM.sumCnt) / 4;
    for (uint16_t i = 0; i < newSmpGroups; i++)
    {
        const int16_t* buf = &SigSamp_getSampBuf()[SM.sumCnt];
        // 2-bit sine lookup table = {0, 1, 0, -1}
        // 2-bit cosine lookup table = {1, 0, -1, 0}
        SM.sumSin += buf[1] - buf[3];
        SM.sumCos += buf[0] - buf[2];
        SM.sumCnt += 4;
    }

    // Post-averaging and signal strength calculations
    if (SM.sumCnt >= SAMPLE_BUF_SIZE)
    {
        // Push sums into WindowAvg buffers
        //TODO: MAKE SURE THE SCALING IS CORRECT WITHOUT TRUNCATING BITS!!
        int16_t avgIm = WndAvg_pushVal(&SM.avgSin, SM.sumSin) >> CYCLE_SUM_RIGHTSHIFT;
        int16_t avgRe = WndAvg_pushVal(&SM.avgSin, SM.sumCos) >> CYCLE_SUM_RIGHTSHIFT;
        
        // todo: fast sqrt??
        SM.sigStrength = avgIm * avgIm + avgRe * avgRe;     // calculate abs(Re,Im)
        
        resetSums();
    }
}

/* Private function definitions */

void resetSums()
{
    // Reset index and sums
    SM.sumCnt = 0;
    SM.sumCos = 0;
    SM.sumSin = 0;
}

uint16_t fastSqrt(int32_t x)
{
    //todo
    return 0;
}