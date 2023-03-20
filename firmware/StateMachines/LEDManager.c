#include "LEDManager.h"
#include "HelperClasses/HSVtoRGB.h"
#include "HelperClasses/LinearRamp.h"
#include "HelperClasses/AmpScalingMath.h"
#include "HelperClasses/RNG.h"
#include "SamplingParams.h"
#include "SignalSampling.h"
#include "HAL/HAL_PWM.h"
#include "HAL/HAL_ADC.h"

/* Private variable declarations */

//State machine
static struct
{
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
    
    SM.hueRamp = LinRamp_getObj();
    SM.satRamp = LinRamp_getObj();
}
void LEDMgr_disable(void)
{
    HAL_PWMEnable(false);
}

void LEDMgr_enable(void)
{
    SM.LPFsum = 0;
    SM.tPrev = 0;   //reset local state machine's time count
    HAL_PWMEnable(true);
}

void LEDMgr_tasks(void)
{
    uint8_t timebase = SigSamp_getTimebase();

    if ((uint8_t)(timebase - SM.tPrev) < LED_REFRESH_INTERVAL) {
        return;
    }

    SM.tPrev = timebase;

    /* Get signal strength, convert to brightness level, filter result */
    int32_t SigStrSin, SigStrCos;
    uint8_t numCycles;
    SigSamp_getSigStr(&SigStrSin, &SigStrCos, &numCycles);
    uint8_t newBrightnessVal = AmpToBrightness(SigStrSin, SigStrCos, numCycles);
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
    ) {
        // initialize next ramp to random color
        onRampComplete();
    }
}

/* Private function definitions */
static void onRampComplete(void)
{
    /* Add entropy to the random number generator (LSB of most recent ADC conversion). */
    RNG_seedEntropyBit((uint8_t)HAL_ADCGetConv());
    
    /* Get random number for next hue and saturation values, setup ramp.
     * Next hue must between 25%-50% of the way around the color wheel from the previous
     * value (from 64 to 127).
     * Next saturation value must be between 50%-100% (from 128 to 255).
     */
    uint8_t hueNext = LinRamp_getCurrentVal(&SM.hueRamp);
    hueNext += 64 + (RNG_get() & 63);
    uint8_t satNext = RNG_get() | 0x80;   // random values of sat between 128 - 255
    
    LinRamp_setup(&SM.hueRamp, hueNext);
    LinRamp_setup(&SM.satRamp, satNext);
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
     * Filter corner frequency = -(Refresh rate)*ln(1-alpha)
     * For an LED refresh rate of ~30Hz:
     *      alpha   filter corner
     *              frequency (Hz)
     *      1/16        1.9
     *      1/8         4.0
     *      1/4         8.6
     *      1/2         20.8
     * 
     *  an alpha value of 1/8 works out to a
     * filter corner frequency of ~4Hz.
     */
//#define LOG2_ALPHA 2
#define LOG2_ALPHA 1
#define ROUNDUP_BIT 0// (1 << (LOG2_ALPHA - 1))
    SM.LPFsum += x - (SM.LPFsum >> LOG2_ALPHA);
    return (SM.LPFsum + ROUNDUP_BIT) >> LOG2_ALPHA;
}