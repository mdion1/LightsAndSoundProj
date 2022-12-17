#include "LEDManager.h"
#include "../HelperClasses/HSLtoRGB.h"
#include "../HelperClasses/LinearRamp.h"
#include "SamplingParams.h"

/* Private variable declarations */
#define RAMP_UPDATE_INT 1       // in milliseconds
static LinRamp_t ramp_R;
static LinRamp_t ramp_G;
static LinRamp_t ramp_B;

//List of state
typedef enum{
    OFF = 0,
    ON,
}LEDMgrState_t;

//State machine
static struct
{
    LEDMgrState_t state;
    int brightLvl;
    RGB_t led;
}SM;

/* Private function declarations */
static void onRampComplete();

/* Public function definitions */
void LEDMgr_init()
{
    LinRamp_init(&ramp_R);
    LinRamp_init(&ramp_G);
    LinRamp_init(&ramp_B);

    //todo: init State machine
}

void LEDMgr_tasks(int sigStr)
{
    switch (SM.state)
    {
    case OFF:
        //check sigStr, compare to threshold level
        if (sigStr >= SIG_STR_FLOOR)
        {
            SM.state = ON;

            LinRamp_reset(&ramp_R);
            LinRamp_reset(&ramp_G);
            LinRamp_reset(&ramp_B);
            onRampComplete();
        }
        break;

    case ON:
    {
        //todo: implement filtering/averaging for brightness
        //convert SigLvl to BrtLvl, average
        //check if BrtLvl and SigLvl are below threshold, turn off and raise "off" event
        //todo: need on/off state hysteresis variables/delays (OR put the delays in the Sleep module logic!)

        int R = LinRamp_getValNow(&ramp_R);
        R = normalizeBright(R);
        // set PWM for R
        //repeat for B, G
        //...


        if (LinRamp_isDone(&ramp_R)
            && LinRamp_isDone(&ramp_G)
            && LinRamp_isDone(&ramp_B)
        )
        {
            // initialize next ramp to random color
            onRampComplete();
        }
    }
    break;
    
    default:
        break;
    }
}

int LEDMgr_getBrightLvl()
{
    return SM.brightLvl;
}

/* Private function definitions */
void onRampComplete()
{
    //get random color, init ramp
    HSL_t randColor = (HSL_t) {
        .hue = 0,
        .sat = 0
    };
    RGB_t targetColor = HSLtoRGB(&randColor);
    
    LinRamp_setup(&ramp_R, targetColor.R, RAMP_UPDATE_INT);
    LinRamp_setup(&ramp_G, targetColor.G, RAMP_UPDATE_INT);
    LinRamp_setup(&ramp_B, targetColor.B, RAMP_UPDATE_INT);
    LinRamp_start(&ramp_R);
    LinRamp_start(&ramp_G);
    LinRamp_start(&ramp_B);
}