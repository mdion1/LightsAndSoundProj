#ifdef __PIC18F06Q41__
#include <xc.h>
#include "../HAL_ADC.h"

/* For positive channel selection register ADPCH */
#define ADCINPUTCHAN 0b101          // selects port/pin RA5
//#define TEMPINPUTCHAN 0b111100

/* For register auto conversion trigger source register ADACT */
#define SAMPTRIGSRC 0b100   //TMR2 postscaled
//#define TRIGDISABLE 0

/* Private function declarations */
static void dummyCallback(void) {}        // dummy function for unused callback function pointers

/* Private variables */
static void (*ADC_interrupt_callback)(void) = &dummyCallback;

/* Public function definitions */
void HAL_initADC(uint8_t prescaler, uint8_t postscaler, uint8_t period)
{
    PMD2 &= ~(1 << 1);      // Clear ADC peripheral module disable bit
    PMD1 &= ~(1 << 2);      // Clear TMR2 peripheral module disable bit
    
    /* Init ADC module */
    ADCON0bits.ON = 1;      // Enable module
    ADCON0bits.CS = 1;      // Clock source = ADCRC oscillator
    ADCON0bits.FM = 1;      // Conversion results are right-justified
    ADPCH = ADCINPUTCHAN;   // input channel
    ADACT = SAMPTRIGSRC;    // trigger source
    PIE1bits.ADIE = 1;      // enable interrupt

    /* Init Timer2 trigger source */
    T2CLKCONbits.CS = 3;            // Set HFINTOSC as clock source
    T2PR = period;
    T2CONbits.CKPS = prescaler;     // 3 bits; 1:2^n, where CKPS = n
    T2CONbits.OUTPS = postscaler;   // 4 bits; 1:n+1, where OUTPS = n
}

void HAL_registerADCisrCallback(void (*p_callback)(void))
{
    ADC_interrupt_callback = p_callback;
}

int16_t HAL_ADCGetConv(void)
{
    return (int16_t)ADRES;
}

void HAL_ADCEnable(void)
{
    PMD2 &= ~(1 << 1);     // Clear peripheral module disable bit
    
    // Configure input pin as an analog input
    TRISA |= (1 << 5);
    ANSELA |= (1 << 5);

    /* Enable Timer2 trigger source */
    PMD1 &= ~(1 << 2);  // Clear Peripheral Module Disable bit
    T2CONbits.ON = 1;
}

void HAL_ADCDisable(void)
{
    /* Disable Timer2 trigger source, set PMD bits */
    T2CONbits.ON = 0;
    PMD1 |= (1 << 2);   // Set Timer2 Peripheral Module Disable bit
    PMD2 |= (1 << 1);     // Set ADC Peripheral Module Disable bit
    
    // Set input pin to digital output, clamp to Vdd
    TRISA &= ~(1 << 5);
    ANSELA &= ~(1 << 5);
    TRISA |= (1 << 5);      // set pin high
}

/* ISR */
void __interrupt(irq(AD),high_priority) ADCInt(void)
{
    PIR1bits.ADIF = 0;
    (*ADC_interrupt_callback)();
}

#endif