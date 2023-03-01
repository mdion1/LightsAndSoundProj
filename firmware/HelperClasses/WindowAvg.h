#pragma once
#include <stdint.h>

typedef struct
{
    int32_t* buf;
    uint16_t idx;
    uint16_t len;
    int32_t sum;
}WndAvg_t;

//NOTE: These functions assum the WndAvg_t object has had its buffer initialized correctly!!

void WndAvg_init(WndAvg_t* pObj, int32_t* buf, uint16_t len);
void WndAvg_clear(WndAvg_t* pObj);
void WndAvg_pushVal(WndAvg_t* pObj, int32_t val);
int32_t WndAvg_getSum(WndAvg_t* pObj);