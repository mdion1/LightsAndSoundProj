/* Private variable declarations */
static typedef enum {
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
    uint16_t sampPrev;
    int lowSigCnt;
}SM;

/* Private function declarations */


/* Public function definitions */
void Sleep_tasks()
{
    uint16_t NTotalSamples = SigSamp_getNumSamples();
        
    if (NTotalSamples - SM.sampPrev < SLEEP_TASK_INTERVAL) {
        return;
    }
        
    SM.sampPrev = NTotalSamples;        /*! \todo what about sample index reset/wraparound? Use a different SigSamp getter? */
        
        
        //////////////////// 
    /* If signal strength is below threshold for too long, increment the deep sleep duration */
    if (SigAnalysis_getSigStr() < SIG_STR_CUTOFF)
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
void initDeepSleep()
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

void initSleepWhileSampling()
{
    // set wake trigger

}

void onDeepSleepWake()
{
    // Turn on analog front end, wait for warmup (blocking wait)
    //...
}