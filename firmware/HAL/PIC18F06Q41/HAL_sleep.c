#ifdef __PIC18F06Q41__
#include "HAL/HAL_sleep.h"
#include <xc.h>

void HAL_sleep()
{
    SLEEP();
    NOP();      // instruction following SLEEP must be NOP
}

#endif