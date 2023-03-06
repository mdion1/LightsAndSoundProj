#include "LinearRamp.h"


#define N_STEPS_PER_RAMP 128   /*! With an LED update interval of ~(1 / 30) = 33ms, a ramp duration
                                *  of 4.27 seconds works out to 4.27s * 30Hz = 128 update intervals. */


/* Private function declarations */
static uint16_t min_u16(uint16_t a, uint16_t b);
static uint16_t max_u16(uint16_t a, uint16_t b);

/* Public function definitions */

void LinRamp_setup(LinRamp_t* pObj, uint8_t start, uint8_t end)
{
    pObj->b_done = false;
    pObj->start = pObj->now = ((uint16_t)start) << 8;
    pObj->end = ((uint16_t)end) << 8;
    pObj->step = (pObj->end - pObj->start) / N_STEPS_PER_RAMP;      // Divide by 128 should compile into >> 7
}

uint8_t LinRamp_incr(LinRamp_t* pObj)
{
    if (!pObj->b_done)
    {
        if (pObj->end > pObj->start) {
            pObj->now = min_u16(pObj->now + pObj->step, pObj->end);
        }
        else {

            pObj->now = (pObj->now < pObj->step) ? 0 : pObj->now - pObj->step;  // Check for underflow before subtracting
            pObj->now = max_u16(pObj->now , pObj->end);
        }
        pObj->b_done = pObj->now == pObj->end;
    }
    return pObj->end >> 8;
}

bool LinRamp_isDone(LinRamp_t* pObj)
{
    return pObj->b_done;
}

/* Private function definitions */
static uint16_t min_u16(uint16_t a, uint16_t b)
{
    return a < b ? a : b;
}

static uint16_t max_u16(uint16_t a, uint16_t b)
{
    return a > b ? a : b;
}