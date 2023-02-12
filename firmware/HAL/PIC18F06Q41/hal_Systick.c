#ifdef __PIC18F67K40__
#include <xc.h>
#include "hal_Systick.h"

/* Private variable declarations */

/* Private function declarations */

/* Public function definitions */

void hal_SystickInit() {
    Timer1Configure();
}

void hal_SystickDelay(uint16_t delay)
{
    uint16_t begin = hal_Systick16();
    while (hal_Systick16() - begin <= delay);
}

uint16_t hal_Systick()
{
    return Timer1Count();
}

/* Private function definitions */

#endif //#ifdef __PIC18F67K40__