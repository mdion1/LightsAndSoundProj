#include "WindowAvg.h"

/* Private variable declarations */

/* Private function declarations */

/* Public function definitions */

void WndAvg_init(WndAvg_t* pObj, int16_t* buf, uint8_t len)
{
    pObj->buf = buf;
    pObj->len = (len > 0) ? len : 1;    //guard against len == 0
    WndAvg_clear(pObj);
}

void WndAvg_clear(WndAvg_t* pObj)
{
    pObj->sum = 0;
    pObj->idx = 0;
    for (uint8_t i = 0; i < pObj->len; i++) {
        pObj->buf[i] = 0;
    }
}

void WndAvg_pushVal(WndAvg_t* pObj, int16_t val)
{
    pObj->sum += val - pObj->buf[pObj->idx];    // Add new val, subtract old val
    pObj->buf[pObj->idx] = val;                 // Replace old val
    
    // Increment index
    pObj->idx++;
    if (pObj->idx == pObj->len) {
        pObj->idx = 0;
    }
}

int32_t WndAvg_getSum(WndAvg_t* pObj) {
    return pObj->sum;
}

/* Private function definitions */