#ifdef __PIC18F67K40__
#include <xc.h>
#include "hal_Systick.h"

/* Private variable declarations */

/* Private function declarations */

/* Public function definitions */

void hal_SystickInit() {
    
    TMR1CLKbits.CS = 1; // 1 = F_osc / 4, 2 = F_osc, 3 = HFINTOSC, 4 = LFINTOSC, 5 = MFINTOSC (31kHz)
    T1CONbits.CKPS = 3; // 0 = 1:1, 1 = 1:2, 2 = 1:4, 3 = 1:8
    T1CONbits.RD16 = 1;
    
    T1CONbits.RD16 = 1;
        
    T1CONbits.ON = 1;   // timer on
    
    //...
    //todo
    
    // use MFINTOSC clock at 31.25kHz, 1:8 prescaler, 256us per tick, and 16.777 seconds/16b overflow
}

void hal_SystickDelay(uint16_t delay)
{
    uint16_t begin = hal_Systick16();
    while (hal_Systick16() - begin <= delay);
}

uint16_t hal_Systick()
{
    /* Note: when RD16 bit is enabled, the 8 upper bits of the timer are buffered when the lower
     * 8 bits are read. Double-check the compiled assembly to make sure TMRxL is read first, then TMRxH
     */
    return TMR1;
}

/* Private function definitions */

#endif //#ifdef __PIC18F67K40__