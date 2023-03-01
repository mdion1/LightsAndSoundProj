#ifdef __PIC18F06Q41__
#include "hal_interrupts.h"
#include <xc.h>

/* Private function declarations */
static void dummyCallback();        // dummy function for unused callback function pointers

/* Private variables */
static void (*ADC_interrupt_callback)(void) = &dummyCallback;
static void (*Timer0_interrupt_callback)(void) = &dummyCallback;

/* Public function definitions */

/* ADC interrupts */

void INT_registerADCISRCallback(void (*p_callback)(void)) {
    ADC_interrupt_callback = p_callback;
}

void INT_EnADCInt(bool b_en) {
    PIE1bits.ADIE = b_en;
}

void INT_clrADCIntFlag() {
    PIR1bits.ADIF = 0;
}

/* Timer0 interrupts */
void INT_resisterTMR0ISRCallback(void (*p_callback)(void)) {
    Timer0_interrupt_callback = p_callback;
}

void INT_EnTMR0Int(bool b_en) {
    PIE3bits.TMR0IE = b_en;
}

void INT_clrTMR0IntFlag()  {
    PIR3bits.TMR0IF = 0;
}

void INT_GlobalIntEn() {
    INTCON0bits.GIE = 1; //Global Interrupt Enable bit
}

void INT_GlobalIntDis() {
    INTCON0bits.GIE = 0; //Global Interrupt Enable bit
}

/* Private function definitions */
static void dummyCallback() {
    // do nothing
}

/* ISR's */
void __interrupt(irq(AD),high_priority) ADCInt(void)
{
    INT_clrADCIntFlag();
    (*ADC_interrupt_callback)();
}

void __interrupt(irq(TMR0),high_priority) TMR0Int(void)
{
    INT_clrTMR0IntFlag();
    (*Timer0_interrupt_callback)();
}

#endif