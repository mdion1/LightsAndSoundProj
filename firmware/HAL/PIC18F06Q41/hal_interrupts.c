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
}

void HAL_enableADCint(bool b_en)
{
    PIE1bits.ADIE = b_en;
}

void HAL_clearADCintFlag()
{
    PIR1bits.ADIF = 0;
}

void HAL_registerTimer0isr(void (*p_callback)(void))
{
    Timer0_interrupt_callback = p_callback;
}

void HAL_enableTMR0int(bool b_en)
{
    PIE3bits.TMR0IE = b_en;
}

void HAL_clearTMR0intFlag()
{
    PIR3bits.TMR0IF = 0;
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

void __interrupt(irq(AD),high_priority) ADCInt(void)
{
    HAL_clearADCintFlag();
    (*ADC_interrupt_callback)();
}

void __interrupt(irq(TMR0),high_priority) TMR0Int(void)
{
    HAL_clearTMR0intFlag();
    (*Timer0_interrupt_callback)();
}

#endif