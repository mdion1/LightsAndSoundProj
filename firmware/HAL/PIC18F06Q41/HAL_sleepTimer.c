#ifdef __PIC18F06Q41__
#include "HAL/HAL_sleepTimer.h"
#include <xc.h>

#define TMR0_CLOCK_DIV_1024 10
#define TMR0_CLOCK_DIV_512  9
#define TMR0_CLOCK_DIV_256  8
#define TMR0_CLOCK_DIV_128  7
#define TMR0_CLOCK_DIV_64   6

void HAL_sleepTimerInit(void){} // do nothing

void HAL_sleepTimerSetInterval(SleepTimerInt_t interval)
{
    uint8_t period = 255;
    uint8_t prescaler = TMR0_CLOCK_DIV_64;
    switch (interval)
    {
        default:
            // Invalid value, return
            return;
        case SLEEP_INT_AFESTAGE_POWERUP:
            period = 72;     // 151ms
            break;
        case SLEEP_INT_1:
            period = 47;    // 99.1ms
            break;
        case SLEEP_INT_2:
            period = 96;    // 200ms
            break;
        case SLEEP_INT_3:
            period = 193;   // 400ms
            break;
        case SLEEP_INT_4:
            period = 193;   // 800ms
            prescaler = TMR0_CLOCK_DIV_128;
            break;
        case SLEEP_INT_5:
            period = 193;   // 1.60s
            prescaler = TMR0_CLOCK_DIV_256;
            break;
        case SLEEP_INT_6:
            period = 193;   // 3.20s
            prescaler = TMR0_CLOCK_DIV_512;
            break;
        case SLEEP_INT_7:
            period = 193;   // 6.40s
            prescaler = TMR0_CLOCK_DIV_1024;
            break;
    }
    
    TMR0H = period;
    T0CON1bits.CKPS = prescaler;
}

void HAL_sleepTimerStart(void)
{
    TMR0L = 0;          // Reset count
    T0CON0bits.EN = 1;  // Start timer
}
void HAL_SleepTimerEnable(bool en)
{
    /* Set/clear Timer0's peripheral module disable bit */
    if (en) {
        PMD1 &= ~(0x01);
        T0CON1bits.CS = 0b100;  // Clock source = 31kHz LFINTOSC
        T0CON1bits.ASYNC = 1;   // Enable asynchronous mode, so timer can operate during sleep
    }
    else {
        T0CON0bits.EN = 0;  // Stop timer
        PMD1 |= 1;
    }
    
    /* Clear Timer0's interrupt flag and set/clear enable bit */
    PIR3bits.TMR0IF = 0;
    PIE3bits.TMR0IE = en;
}

/* ISR */
void __interrupt(irq(TMR0),high_priority) TMR0Int(void)
{
    /* Clear Timer0's interrupt flag */
    PIR3bits.TMR0IF = 0;
}

#endif