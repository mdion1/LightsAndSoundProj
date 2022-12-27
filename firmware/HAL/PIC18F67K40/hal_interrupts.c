
#ifdef __PIC18F67K50__
//#include <appropriate PIC h-file>

static void dummyCallback() {};
static void (*ADC_interrupt_callback)(void) = &dummyCallback;
static void (*Timer0_interrupt_callback)(void) = &dummyCallback;

void HAL_registerADCisr(void (*p_callback)(void))
{
    ADC_interrupt_callback = p_callback;
}

void HAL_registerTimer0isr(void (*p_callback)(void))
{
    Timer0_interrupt_callback = p_callback;
}

void __interrupt()
{
    PIR0bits.TMR0IF = 0;    //clear interrupt flag
    UART_BUF__reset_buf();
    T0CON0bits.T0EN = 0;        //stop timer



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