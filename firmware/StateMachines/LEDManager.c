#include "LEDManager.h"
#include "../HelperClasses/HSVtoRGB.h"
#include "../HelperClasses/LinearRamp.h"
#include "../HelperClasses/AmpScalingMath.h"
#include "SamplingParams.h"
#include "SignalSampling.h"
#include "SignalAnalysis.h"
#include "../HAL/HAL_PWM.h"

/* Private variable declarations */
#define N_STEPS_PER_RAMP 120   /*! With an LED update interval of ~(1 / 30) = 33ms, a ramp duration
                                *  of 4 seconds works out to 4s * 30Hz = 120 update intervals. */

//State machine
static struct
{
    int brightLvl;
    RGB_t led;
    LinRamp_t hueRamp;
    LinRamp_t satRamp;
    uint16_t tPrev;
    uint16_t LPFsum;
}SM;

/* Private function declarations */
static void onRampComplete(void);
static uint8_t LPF_pushVal(uint8_t val);

/* Public function definitions */
void LEDMgr_init()
{
    HAL_initPWM();

    //todo: init State machine
}
void LEDMgr_disable(void)
{
    HAL_PWMEnable(false);
}

void LEDMgr_enable(void)
{
    // Reset brightness level
    SM.brightLvl = 0;
    
    SM.LPFsum = 0;
    //...
    
    HAL_PWMEnable(true);
}

void LEDMgr_tasks(void)
{
    //todo: implement filtering/averaging for brightness
    //convert SigLvl to BrtLvl, average
    //check if BrtLvl and SigLvl are below threshold, turn off and raise "off" event
    //todo: need on/off state hysteresis variables/delays (OR put the delays in the Sleep module logic!)
    uint16_t timebase = SigSamp_getTimebase();

    if (timebase - SM.tPrev < LED_REFRESH_INTERVAL) {
        return;
    }

    SM.tPrev = timebase;

    /* Get signal strength, convert to brightness level, filter result */
    int32_t SigStrSin, SigStrCos;
    uint8_t numCycles;
    SigSamp_getSigStr(&SigStrSin, &SigStrCos, &numCycles);
    uint16_t newBrightnessVal = AmpToBrightness(SigStrSin, SigStrCos, numCycles);
    uint8_t valFiltered = LPF_pushVal(newBrightnessVal);

    /* Increment hue and saturation ramp */
    uint8_t hueNext = LinRamp_incr(&SM.hueRamp);
    uint8_t satNext = LinRamp_incr(&SM.satRamp);

    /* Combine updated hue/sat/val to calculate next RGB value */
    RGB_t RGBNext = HSVtoRGB(hueNext, satNext, valFiltered);
    HAL_setPWM(RGBNext.R, RGBNext.G, RGBNext.B);

    /* Check for completed color ramp */
    if (LinRamp_isDone(&SM.hueRamp)
        && LinRamp_isDone(&SM.satRamp)
    )
    {
        // initialize next ramp to random color
        onRampComplete();
    }
}

/* Private function definitions */
static void onRampComplete(void)
{
    //get random color, init ramp
    uint8_t hueRand;
    uint8_t satRand;    //get rand uint8
    
    /* Calculate step size */
    
    
    LinRamp_setup(&SM.hueRamp, hueRand, N_STEPS_PER_RAMP);
    LinRamp_setup(&SM.satRamp, satRand, N_STEPS_PER_RAMP);
}

static uint8_t LPF_pushVal(uint8_t x)
{
    /* Low-pass exponential filter:
     *      y_new = (1 - alpha) * y + alpha * x
     *            = (((1 / alpha) - 1) * y + x) * alpha
     * 
     * If we store the filter sum as y_new / alpha for better resolution:
     *      Y = y / alpha
     *      Y_new = Y - alpha * Y + x
     * 
     * For an LED refresh rate of ~30Hz, an alpha value of 1/8 works out to a
     * filter corner frequency of ~4Hz.
     */
    SM.LPFsum += x - (SM.LPFsum >> 3);
    
    return (SM.LPFsum + 4) >> 3;  // add 4 to round up
}