#include "StateMachines/SignalAnalysis.h"
#include "StateMachines/SignalSampling.h"
#include "StateMachines/Sleep.h"
#include "StateMachines/LEDManager.h"

void main(void)
{
    /* Initialize all modules */
    SigSamp_init();
    SigAnalysis_init();
    LEDMgr_init();
    Sleep_init();
    
    while (1)
    {
        SigSamp_tasks();
        SigAnalysis_tasks();
        LEDMgr_tasks();
        Sleep_tasks();  // check threshold, # of samples/time below threshold, calculate sleep time/type, call SLEEP()
    }
}