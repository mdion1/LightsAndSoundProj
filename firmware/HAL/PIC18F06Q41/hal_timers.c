#ifdef __PIC18F06Q41__
#include <xc.h>
#include "hal_timers.h"

/* With clock source = 31kHz LFINTOSC and 1:8192 divider, timer
 * tick interval is ~264ms. With a timer period of 2, an interrupt is generated
 * every ~1.06 seconds.
 */
#define TMR0_CLOCK_DIV_8192 0b1101
#define TMR0_CLOCK_DIV_4096 0b1100
#define TMR0_PERIOD 4

void TMR_configTMR0()
{
    // Set clock source, prescaler, and period
    T0CON1bits.CS = 0b100;  // LFINTOSC
    T0CON1bits.CKPS = TMR0_CLOCK_DIV_8192;   // 1:8192
    TMR0H = TMR0_PERIOD;
}

void TMR_EnTMR0() 
{
    PMD1 &= ~(0x01);     // Clear Peripheral Module Disable bit
    T0CON0bits.EN = 1;
}

void TMR_DisTMR0()
{
    T0CON0bits.EN = 0;
    PMD1 |= 1;     // Set Peripheral Module Disable bit
}

/* With clock source = 31.25kHz MFINTOSC and 1:8 divider, timer
 * tick interval is 256us. The 16-bit overflow period is 16.777 seconds.
 */
#define TMR1_CLOCK_DIV_8 3
#define TMR1_CLOCK_DIV_4096 0b1100

void TMR_configTMR1()
{
    TMR1CLKbits.CS = 5;                 // MFINTOSC (31kHz)
    T1CONbits.CKPS = TMR1_CLOCK_DIV_8;
    T1CONbits.RD16 = 1;
}

void TMR_EnTMR1() 
{
    PMD1 &= ~(1 << 1);     // Clear Peripheral Module Disable bit
    T1CONbits.ON = 1;
}

void TMR_DisTMR1()
{
    T1CONbits.ON = 0;
    PMD1 |= (1 << 1);     // Set Peripheral Module Disable bit
}

uint16_t TMR_getTMR1Count()
{
    /* Note: when RD16 bit is enabled, the 8 upper bits of the timer are buffered when the lower 8 bits are read. */
    uint8_t lower = TMR1L;
    uint8_t upper = TMR1H;
    return (upper << 8) | lower;
}


/* Timer2 */
void TMR_configTMR2(uint8_t prescaler, uint8_t postscaler, uint8_t period)
{
    T2CLKCONbits.CS = 3;            // Set HFINTOSC as clock source
    T2PR = period;
    T2CONbits.CKPS = prescaler;     // 3 bits; 1:2^n, where CKPS = n
    T2CONbits.OUTPS = postscaler;   // 4 bits; 1:n+1, where OUTPS = n
}

void TMR_EnTMR2() 
{
    PMD1 &= ~(1 << 2);  // Clear Peripheral Module Disable bit
    T2CONbits.ON = 1;
}

void TMR_DisTMR2()
{
    T2CONbits.ON = 0;
    PMD1 |= (1 << 2);   // Set Peripheral Module Disable bit
}

#endif