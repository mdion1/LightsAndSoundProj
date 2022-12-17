#include "TaskManager.h"
#include "LEDManager.h"
#include "Sleep.h"
#include "SignalSampling.h"
#include "SignalAnalysis.h"



/* Private variable declarations */


/* Private function declarations */


/* Public function definitions */

void TaskMgr_init(void)
{
    return;
}

void TaskMgr_loopNoReturn(void)
{
    while(1) {
        SigSampEvents_t sigSamp_evt = SigSamp_tasks();
        SigAnl_t sigAnl_evt = SigAnalysis_tasks(sigSamp_evt.newSamples, sigSamp_evt.buf);       // is there even a need for a "newData" flag?
        LEDMgr_tasks(SigAnl_getSigStr());     //todo: SigAnl_getSigStr() should return a bool if it's a new value??? Or else the module's state machine doesn't need the b_isValid flag...
        Sleep_tasks();
        continue;
    }
}

/* Private function definitions */