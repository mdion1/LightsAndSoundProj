#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int start;
    int end;
    int t_start;
    int step_dt;
    bool b_active;
    bool b_done;
}LinRamp_t;

void LinRamp_init(LinRamp_t* pObj);
void LinRamp_reset(LinRamp_t* pObj);
void LinRamp_setup(LinRamp_t* pObj, int end, int step_dt);
void LinRamp_start(LinRamp_t* pObj);
int LinRamp_getValNow(LinRamp_t* pObj);
bool LinRamp_isDone(LinRamp_t* pObj);