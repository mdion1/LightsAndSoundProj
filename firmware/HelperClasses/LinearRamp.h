#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint16_t start;
    uint16_t end;
    uint16_t step;
    uint16_t now;
//    int t_start;
//    int step_dt;
//    bool b_active;
    bool b_done;
}LinRamp_t;

void LinRamp_init(LinRamp_t* pObj);
void LinRamp_reset(LinRamp_t* pObj);
void LinRamp_setup(LinRamp_t* pObj, uint16_t start, uint16_t end, uint16_t step);
void LinRamp_start(LinRamp_t* pObj);
int LinRamp_getValNow(LinRamp_t* pObj);
bool LinRamp_isDone(LinRamp_t* pObj);

void LinRamp_incr();