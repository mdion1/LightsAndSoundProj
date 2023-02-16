#include "LinearRamp.h"

/*typedef struct
{
    int start;
    int end;
    int t_start;
    int step_dt;
    bool b_active;
    bool b_done;
}LinRamp_t;*/

/* Private variable declarations */


/* Private function declarations */


/* Public function definitions */

void LinRamp_init(LinRamp_t* pObj)
{
    
}

void LinRamp_reset(LinRamp_t* pObj);
void LinRamp_setup(LinRamp_t* pObj, uint16_t start, uint16_t end, uint16_t step)
{
    pObj->b_done = false;
    pObj->start = start;
    pObj->now = now;
    pObj->end = end;
    pObj->step = step;
}

void LinRamp_start(LinRamp_t* pObj);
int LinRamp_getValNow(LinRamp_t* pObj);
bool LinRamp_isDone(LinRamp_t* pObj);

void LinRamp_incr(:inRamp_t* pObj)
{
    
    pObj->now += pObj->step;
    
    if (pObj->now < pObj// check overflow
    if (pObj->end - pObj->step)
}

/* Private function definitions */