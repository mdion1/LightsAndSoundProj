#include "StateMachines/SignalAnalysis.h"
#include "StateMachines/SignalSampling.h"
#include "StateMachines/Sleep.h"
#include "StateMachines/TaskManager.h"

void main(void)
{
    TaskMgr_init();
    TaskMgr_loopNoReturn();
}