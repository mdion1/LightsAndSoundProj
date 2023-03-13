#include "Sleep.h"
#include "SamplingParams.h"
#include "SignalSampling.h"
#include "LEDManager.h"
#include "../HAL/HAL_sleepTimer.h"
#include "../HAL/HAL_sleep.h"
#include "../HAL/HAL_GPIO.h"    //todo include ./ as h file include directory
#include "../HelperClasses/AmpScalingMath.h"
#define SIGNAL_STRENGTH_CUTOFF 0//1234 /*! \todo move this into SamplingParams.h */

/* Private variable declarations */
#define LOWSIG_THRESH_CNT_MAX 4

/* State machine */
static struct
{
    SleepTimerInt_t deepSleepDur;
    uint8_t t_prev;
    uint8_t lowSigCnt;
}SM;

/* Private function declarations */
static void initDeepSleep(void);
static void blockingSleep(SleepTimerInt_t sleepLevel);
static void onDeepSleepWake(void);

/* Public function definitions */
void Sleep_init()
{
    HAL_sleepTimerInit();
    
    // Start program as if MCU just woke up
    onDeepSleepWake();
}

void Sleep_tasks()
{
    uint8_t timebase = SigSamp_getTimebase();
    if (timebase - SM.t_prev < SLEEP_TASKS_UPDATE_INTERVAL) {
        return;
    }
    SM.t_prev = timebase;

    /* If signal strength is below threshold for too long, increment the deep sleep duration */
    int32_t SigStrSin, SigStrCos;
    uint8_t numCycles;
    SigSamp_getSigStr(&SigStrSin, &SigStrCos, &numCycles);
    uint8_t newBrightnessVal = AmpToBrightness(SigStrSin, SigStrCos, numCycles);
    if (newBrightnessVal < SIGNAL_STRENGTH_CUTOFF)
    {
        SM.lowSigCnt++;
        if (SM.lowSigCnt >= LOWSIG_THRESH_CNT_MAX)
        {
            initDeepSleep();
            onDeepSleepWake();
            
            // Reset lowSigCnt, Increment deep sleep duration
            SM.lowSigCnt = 0;
            if (SM.deepSleepDur < SLEEP_INT_MAX) {
                SM.deepSleepDur++;
            }
        }
    }
    /* If signal strength is above threshold, reset deep sleep duration and initiate sleep
     * with wake-on-ADC-conversion.
     */
    else
    {
        // Decrement low-signal count
        if (SM.lowSigCnt > 0) {
            SM.lowSigCnt--;
        }
        
        // Reset deep sleep duration
        SM.deepSleepDur = SLEEP_INT_MIN;
        
        /* ADC is already set to wake from sleep (enabled in SigSamp_start()), call SLEEP() */
        HAL_sleep();
    }
}


/* Private function definitions */
static void initDeepSleep(void)
{
    // Disable analog front end and PWM
    HAL_AmpStageEnable(false);
    LEDMgr_disable();
    
    /* Disable ADC + interrupt */
    SigSamp_stop();
    blockingSleep(SM.deepSleepDur);
}

static void onDeepSleepWake(void)
{
    // Turn on analog front end, wait for warmup (blocking wait)
    HAL_AmpStageEnable(true);
    blockingSleep(SLEEP_INT_AFESTAGE_POWERUP);

    // Enable sampling (sets ADC conversion as wake trigger)
    SigSamp_start();
    
    // Enable PWM, reset LEDMgr state machine
    LEDMgr_enable();
}

static void blockingSleep(SleepTimerInt_t sleepLevel)
{
    /* Set sleep duration, call sleep */
    HAL_SleepTimerEnable(true);
    HAL_sleepTimerSetInterval(sleepLevel);
    HAL_sleepTimerStart();
    HAL_sleep();
    
    /* On wake, disable interrupt, disable Timer 0*/
    HAL_SleepTimerEnable(false);
}