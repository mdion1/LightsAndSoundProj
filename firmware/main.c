#include "StateMachines/SignalAnalysis.h"
#include "StateMachines/SignalSampling.h"
#include "StateMachines/Sleep.h"
#include "StateMachines/TaskManager.h"

void main(void)
{
    TaskMgr_init();
    int x = 0;
    for (int i = 0; i < 10; i++)
    {
        x++;
    }
    return;
}