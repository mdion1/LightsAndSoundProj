#ifdef __PIC18F67K40__
#include <xc.h>

/* Private function declarations */
static void dummyCallback();        // dummy function for unused callback function pointers

/* Private variables */
static void (*ADC_interrupt_callback)(void) = &dummyCallback;
static void (*Timer0_interrupt_callback)(void) = &dummyCallback;

/* Public function definitions */
void HAL_registerADCisr(void (*p_callback)(void))
{
    ADC_interrupt_callback = p_callback;
    
    PIR1bits.ADIF = 0;      //ADC Interrupt Flag bit (must be cleared by software)
    PIE1bits.ADIE = 1;      //ADC Interrupt Enable bit
}

void HAL_registerTimer0isr(void (*p_callback)(void))
{
    Timer0_interrupt_callback = p_callback;
}

void HAL_enableInt()
{
    INTCONbits.GIE = 1; //Global Interrupt Enable bit
}

void HAL_disableInt()
{
    INTCONbits.GIE = 0; //Global Interrupt Enable bit
}

/* Private function definitions */
static void dummyCallback() {
    // do nothing
}

void __interrupt() generalISR(void)
{
    if (PIR1bits.ADIF)
    {
        PIR1bits.ADIF = 0;
        (*ADC_interrupt_callback)();
    }

    if (PIR0bits.TMR0IF)
    {
        PIR0bits.TMR0IF = 0;
        (*Timer0_interrupt_callback)();
    }
}
#endif