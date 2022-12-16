#include "TaskManager.h"
#include "LEDManager.h"
#include "Sleep.h"
#include "SignalSampling.h"
#include "SignalAnalysis.h"

void TaskMgr_init(void)
{
    return;
}

void TaskMgr_loopNoReturn(void)
{
    while(1) {
        SigSamp_tasks();
        SigAnalysis_tasks();
        LEDMgr_tasks();
        Sleep_tasks();
        continue;
    }
}