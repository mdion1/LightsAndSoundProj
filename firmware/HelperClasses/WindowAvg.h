#pragma once
#include <stdint.h>

typedef struct
{
    int16_t* buf;
    uint8_t idx;
    uint8_t len;
    int32_t sum;
}WndAvg_t;

//NOTE: These functions assum the WndAvg_t object has had its buffer initialized correctly!!

void WndAvg_init(WndAvg_t* pObj, int16_t* buf, uint8_t len);
void WndAvg_clear(WndAvg_t* pObj);
void WndAvg_pushVal(WndAvg_t* pObj, int16_t val);
int32_t WndAvg_getSum(WndAvg_t* pObj);
uint8_t WndAvg_getCount(WndAvg_t* pObj);