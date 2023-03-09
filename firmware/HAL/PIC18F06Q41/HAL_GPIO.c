#ifdef __PIC18F06Q41__
#include "../HAL_GPIO.h"
#include <xc.h>

/* Board */
void HAL_initPins(void)
{
    /* Set Peripheral Module Disable bit for all modules */
    PMD0 = 0xff;    // Disable FOSC, FVR, HLVD, CRC, SCAN, CLKR, IOC
    PMD1 = 0xff;    // Disable C1, ZCD, SMT1, Timers 0 - 4
    PMD2 = 0xff;    // Disable CCP1, CWG1, DSM1, NCO1, ACT, DAC1, ADC, C2
    PMD3 = 0xff;    // Disable UART1 and 2; SPI1 and 2; I2C1; PWM 1, 2, and 3
    PMD4 = 0xff;    // Disable DMA 1, 2, 3; CLC 1, 2, 3, 4; UART0
    PMD5 = 0xff;    // Disable OPA1, DAC2, DMA0;
    
    /* Set all pins to digital outputs, set low. */
    LATA = 0;
    LATC = 0;
    ANSELA = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISC = 0;
    
    /* Enable LFINTOSC */
    OSCENbits.LFOEN = 1;
}

void HAL_AmpStageEnable(bool en)
{
    if (en) {
        LATA = (1 << 2);        // pin high
    }
    else {
        LATA &= ~(1 << 2);      // pin low
    }
}


#endif