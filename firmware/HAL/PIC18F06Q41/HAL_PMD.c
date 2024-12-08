#include "HAL/HAL_PMD.h"
#include <xc.h>

void HAL_PMD_disAll(void) {
    PMD0 = 0xff;    // Disable FOSC, FVR, HLVD, CRC, SCAN, CLKR, IOC
    PMD1 = 0xff;    // Disable C1, ZCD, SMT1, Timers 0 - 4
    PMD2 = 0xff;    // Disable CCP1, CWG1, DSM1, NCO1, ACT, DAC1, ADC, C2
    PMD3 = 0xff;    // Disable UART1 and 2; SPI1 and 2; I2C1; PWM 1, 2, and 3
    PMD4 = 0xff;    // Disable DMA 1, 2, 3; CLC 1, 2, 3, 4; UART0
    PMD5 = 0xff;    // Disable OPA1, DAC2, DMA0;
}

void HAL_PMD_enADC(bool en) {
    PMD2bits.ADCMD = !en;
}

void HAL_PMD_enPWM(bool en) {
    PMD3bits.PWM1MD = !en;
    PMD3bits.PWM2MD = !en;
    PMD3bits.PWM3MD = !en;
}

void HAL_PMD_enTMR(bool en, uint8_t timer) {
    switch (timer) {
        case 0:
            PMD1bits.TMR0MD = !en;
            break;
        case 1:
            PMD1bits.TMR1MD = !en;
            break;
        case 2:
            PMD1bits.TMR2MD = !en;
            break;
        default:
            break;
    }
}

