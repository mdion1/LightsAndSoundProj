#ifdef __PIC18F06Q41__
#include "../HAL_sleepTimer.h"
#include <xc.h>

/* With clock source = 31kHz LFINTOSC and 1:8192 divider, timer
 * tick interval is ~264ms. With a timer period of 2, an interrupt is generated
 * every ~1.06 seconds.
 * 
 * With clock source = 31kHz LFINTOSC, 
 *      Clock divider       Tick interval
 *      4096                
 *      8192                264ms
 */
#define TMR0_CLOCK_DIV_8192 13
#define TMR0_CLOCK_DIV_4096 12
#define TMR0_CLOCK_DIV_512  9
#define TMR0_PERIOD 4

void HAL_sleepTimerInit(void)
{
    // Set clock source, prescaler, and period
    T0CON1bits.CS = 0b100;  // LFINTOSC
}

void HAL_sleepTimerSetInterval(SleepTimerInt_t interval)
{
    uint8_t period;
    uint8_t prescaler;
    switch (interval)
    {
        //...
    }
    TMR0H = period;
    T0CON1bits.CKPS = prescaler;
}

void HAL_SleepTimerEnable(bool en)
{
    /* Set/clear Timer0's peripheral module disable bit */
    if (en) {
        PMD1 &= ~(0x01);
    }
    else {
        PMD1 |= 1;
    }
    
    /* Clear Timer0's interrupt flag and set/clear enable bit */
    PIR3bits.TMR0IF = 0;
    PIE3bits.TMR0IE = en;

    /* Start (stop)  timer */
    T0CON0bits.EN = en;
}

/* ISR */
void __interrupt(irq(TMR0),high_priority) TMR0Int(void)
{
    /* Clear Timer0's interrupt flag */
    PIR3bits.TMR0IF = 0;
}

#endif