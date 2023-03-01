#include "LEDManager.h"
#include "../HelperClasses/HSVtoRGB.h"
#include "../HelperClasses/LinearRamp.h"
#include "SamplingParams.h"

/* Private variable declarations */
#define RAMP_UPDATE_INT 1       // in milliseconds

//State machine
static struct
{
    int brightLvl;
    RGB_t led;
    LinRamp_t hueRamp;
    LinRamp_t satRamp;
}SM;

/* Private function declarations */
static void onRampComplete();
static int32_t gammaFunction(int32_t sumSin, int32_t sumCos);
static void LPF_pushVal(int32_t val);

/* Public function definitions */
void LEDMgr_init()
{
    LinRamp_init(&SM.hueRamp);
    LinRamp_init(&SM.satRamp);

    //todo: init State machine
}

void LEDMgr_tasks()
{
    //todo: implement filtering/averaging for brightness
    //convert SigLvl to BrtLvl, average
    //check if BrtLvl and SigLvl are below threshold, turn off and raise "off" event
    //todo: need on/off state hysteresis variables/delays (OR put the delays in the Sleep module logic!)
    uint16_t NTotalSamples = SigSamp_getNumSamples();

    if (NTotalSamples - SM.sampPrev < LED_TASK_INTERVAL) {
        return;
    }

    SM.sampPrev = NTotalSamples;        /*! \todo what about sample index reset/wraparound? Use a different SigSamp getter? */

    int32_t SigStrSin, SigStrCos;
    SigAnalysis_getSigStr(&SigStrSin, &SigStrCos);

    int32_t sigStrNorm = gammaFunction(SigStrSin, SigStrCos);
    uint8_t valFiltered = LPF_pushVal(sigStrNorm);

    // Increment hue and saturation ramp
    uint8_t hueNext = LinRamp_step(&SM.rampHue);
    uint8_t satNext = LinRamp_step(&SM.rampSat);

    // Combine updated hue/sat/val to calculate next RGB value
    RGB_t RGBNext = HSVtoRGB(hueNext, satNext, valFiltered);
    HAL_setPWM(RGBNext.R, RGBNext.G, RGBNext.B);

    // Check for completed color ramp
    if (LinRamp_isDone(&SM.rampHue)
        && LinRamp_isDone(&SM.rampSat)
    )
    {
        // initialize next ramp to random color
        onRampComplete();
    }

}

/* Private function definitions */
void onRampComplete()
{
    //get random color, init ramp
    uint8_t hueRand;
    uint8_t satRand;    //get rand uint8
    
    LinRamp_setup(&SM.hueRamp, hueRand, RAMP_UPDATE_INT);
    LinRamp_setup(&SM.satRamp, satRand, RAMP_UPDATE_INT);
}