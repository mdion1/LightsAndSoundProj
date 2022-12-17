#pragma once
#include <stdint.h>

typedef struct
{
    int* buf;
    int idx;
    int sum;
}WndAvg_t;

void WndAvg_init(WndAvg_t* pObj, int* buf);
void WndAvg_clear(WndAvg_t* pObj);
int WndAvg_pushVal(WndAvg_t* pObj, int val);