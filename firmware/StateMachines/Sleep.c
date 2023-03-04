#include "Sleep.h"
#include "SamplingParams.h"
#include "SignalSampling.h"
#include "SignalAnalysis.h"
#include "../HelperClasses/AmpScalingMath.h"
#define SIGNAL_STRENGTH_CUTOFF 1234 /*! \todo move this into SamplingParams.h */

/* Private variable declarations */
typedef enum {
    DEEPSLEEP_MIN = 0,
    DEEPSLEEP_100ms,
    DEEPSLEEP_200ms,
    DEEPSLEEP_400ms,
    DEEPSLEEP_800ms,
    DEEPSLEEP_1600ms,
    DEEPSLEEP_3200ms,
    DEEPSLEEP_6400ms,
    DEEPSLEEP_MAX
}deepSleepDur_t;

#define LOWSIG_THRESH_CNT_MAX 4

/* State machine */
static struct
{
    deepSleepDur_t deepSleepDur;
    uint16_t t_prev;
    int lowSigCnt;
}SM;

/* Private function declarations */
static void initDeepSleep();
static void initSleepWhileSampling();
static void onDeepSleepWake();

/* Public function definitions */
void Sleep_tasks()
{
    uint16_t timebase = SigSamp_getTimebase();
    if (timebase - SM.t_prev < SLEEP_TASKS_UPDATE_INTERVAL) {
        return;
    }
    SM.t_prev = timebase;
        
        
        //////////////////// 
    /* If signal strength is below threshold for too long, increment the deep sleep duration */
    int32_t SigStrSin, SigStrCos;
    uint8_t numCycles;
    SigAnalysis_getSigStr(&SigStrSin, &SigStrCos, &numCycles);
    uint16_t newBrightnessVal = AmpToBrightness(SigStrSin, SigStrCos, numCycles);
    if (newBrightnessVal < SIGNAL_STRENGTH_CUTOFF)
    {
        SM.lowSigCnt++;
        if (SM.lowSigCnt >= LOWSIG_THRESH_CNT_MAX)
        {
            SM.lowSigCnt = 0;
            
            // Increment deep sleep duration
            if (SM.deepSleepDur < DEEPSLEEP_MAX) {
                SM.deepSleepDur++;
            }
            
            initDeepSleep();
            onDeepSleepWake();
        }
    }
    /* If signal strength is above threshold, reset deep sleep duration and initiate sleep
     * with wake-on-ADC-conversion.
     */
    else
    {
        // Decrement low-signal count
        if (SM.lowSigCnt >= 0) {
            SM.lowSigCnt--;
        }
        
        // Reset deep sleep duration
        SM.deepSleepDur = DEEPSLEEP_MIN;
        
        initSleepWhileSampling();
    }
}


/* Private function definitions */
static void initDeepSleep()
{
    switch (SM.deepSleepDur)
    {
        default:
            // do nothing
            break;

        case DEEPSLEEP_100ms:
        case DEEPSLEEP_200ms:
        case DEEPSLEEP_400ms:
        case DEEPSLEEP_800ms:
        case DEEPSLEEP_1600ms:
        case DEEPSLEEP_3200ms:
        case DEEPSLEEP_6400ms:
            //todo
            break;
    }
    // set wake trigger
    // set timer duration
}

static void initSleepWhileSampling()
{
    // set wake trigger

}

static void onDeepSleepWake()
{
    // Turn on analog front end, wait for warmup (blocking wait)
    //...
}