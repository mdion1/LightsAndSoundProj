#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint16_t start;
    uint16_t end;
    uint16_t now;
    uint16_t step;
    bool b_done;
}LinRamp_t;

void LinRamp_setup(LinRamp_t* pObj, uint8_t start, uint8_t end);
uint8_t LinRamp_incr(LinRamp_t* pObj);
bool LinRamp_isDone(LinRamp_t* pObj);