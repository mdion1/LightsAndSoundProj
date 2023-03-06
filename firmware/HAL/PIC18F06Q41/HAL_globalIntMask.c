#ifdef __PIC18F06Q41__
#include "../HAL_globalIntMask.h"
#include <xc.h>

/* Public function definitions */
void HAL_globalIntEn(void) {
    INTCON0bits.GIE = 1; //Global Interrupt Enable bit
}

void HAL_globalIntDis(void) {
    INTCON0bits.GIE = 0; //Global Interrupt Enable bit
}

#endif