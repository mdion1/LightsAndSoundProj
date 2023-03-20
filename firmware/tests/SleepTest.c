#include "StateMachines/SignalSampling.h"
#include "StateMachines/Sleep.h"
#include "StateMachines/LEDManager.h"
#include "HAL/HAL_GPIO.h"

void main(void)
{
    /* Initialize all modules */
    HAL_initPins();
    SigSamp_init();
    LEDMgr_init();
    
    while (1)
    {
        SleepTest();
    }
}