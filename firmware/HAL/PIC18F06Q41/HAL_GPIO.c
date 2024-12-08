#ifdef __PIC18F06Q41__
#include "HAL/HAL_GPIO.h"
#include "HAL/HAL_PMD.h"
#include <xc.h>

/* Board */
void HAL_initPins(void) {
    /* Configure the internal oscillator. At startup, HFINTOSC is running at 4MHz with a
     * 4:1 divider. Change to 1MHz with a 1:1 divider. */
    OSCFRQ = 0; //1MHz
    OSCCON1bits.NDIV = 0; // 1:1 divider
    
    /* Set Peripheral Module Disable bit for all modules */
    HAL_PMD_disAll();
    
    /* Set all pins to digital outputs, set low. */
    LATA = 0;
    LATC = 0;
    ANSELA = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISC = 0;
}

void HAL_AmpStageEnable(bool en) {
    LATAbits.LATA2 = en;
}


#endif