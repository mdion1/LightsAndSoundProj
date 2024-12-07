#include "StateMachines/SignalSampling.h"
#include "StateMachines/Sleep.h"
#include "StateMachines/LEDManager.h"
#include "HAL/HAL_GPIO.h"

void main(void)
{
    tune();
    
    /* Initialize all modules */
    HAL_initPins();
    SigSamp_init();
    LEDMgr_init();
    Sleep_init();
    
    while (1)
    {
        SigSamp_tasks();
        LEDMgr_tasks();
        Sleep_tasks();  // check threshold, # of samples/time below threshold, calculate sleep time/type, call SLEEP()
    }
}