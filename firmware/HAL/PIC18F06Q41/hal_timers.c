#ifdef __PIC18F06Q41__
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "../HAL.h"

/* With clock source = 31kHz LFINTOSC and 1:8192 divider, timer
 * tick interval is ~264ms. With a timer period of 2, an interrupt is generated
 * every ~1.06 seconds.
 */
#define TMR0_CLOCK_DIV_8192 0b1101
#define TMR0_CLOCK_DIV_4096 0b1100
#define TMR0_PERIOD 4

void Timer0Configure()
{
    // Set clock source, prescaler, and period
    T0CON1bits.CS = 0b100;  // LFINTOSC
    T0CON1bits.CKPS = CLOCK_DIV_8192;   // 1:8192
    TMR0H = TMR0_PERIOD;
}

void Timer0Enable() 
{
    PMD1 &= ~(0x01);     // Clear Peripheral Module Disable bit
    T0CONbits.EN = 1;
}

void Timer0Disable()
{
    T0CONbits.EN = 0;
    PMD1 |= 1;     // Set Peripheral Module Disable bit
}

/* With clock source = 31.25kHz MFINTOSC and 1:8 divider, timer
 * tick interval is 256us. The 16-bit overflow period is 16.777 seconds.
 */
#define TMR1_CLOCK_DIV_8 3
#define TMR1_CLOCK_DIV_4096 0b1100

void Timer1Configure()
{
    TMR1CLKbits.CS = 5;                 // MFINTOSC (31kHz)
    T1CONbits.CKPS = TMR1_CLOCK_DIV_8;
    T1CONbits.RD16 = 1;
}

void Timer1Enable() 
{
    PMD1 &= ~(1 << 1);     // Clear Peripheral Module Disable bit
    T1CONbits.EN = 1;
}

void Timer1Disable()
{
    T1CONbits.EN = 0;
    PMD1 |= (1 << 1);     // Set Peripheral Module Disable bit
}

uint16_t Timer1Count()
{
    /* Note: when RD16 bit is enabled, the 8 upper bits of the timer are buffered when the lower
     * 8 bits are read. Double-check the compiled assembly to make sure TMRxL is read first, then TMRxH
     */
    return TMR1;
}


/* Timer2 */

void Timer2Configure(uint8_t period)
{
    T2CLKCONbits.CS = 3;   //HFINTOSC
    T2PR = period;
}

void Timer2Enable() 
{
    PMD1 &= ~(1 << 2);  // Clear Peripheral Module Disable bit
    T2CONbits.ON = 1;
}

void Timer2Disable()
{
    T2CONbits.ON = 0;
    PMD1 |= (1 << 2);   // Set Peripheral Module Disable bit
}

#endif