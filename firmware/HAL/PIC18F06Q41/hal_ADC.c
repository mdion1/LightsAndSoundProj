
#ifdef __PIC18F06Q41__
#include <xc.h>
#include "hal_ADC.h"

/* For positive channel selection register ADPCH */
#define ADCINPUTCHAN 0b101          // selects port/pin RA5
#define TEMPINPUTCHAN 0b111100

/* For register auto conversion trigger source register ADACT */
#define SAMPTRIGSRC 0b100   //TMR2 postscaled
#define TRIGDISABLE 0

void ADC_init()
{
    ADCON0bits.ON = 1;      // Enable module
    ADCON0bits.CS = 1;      // Clock source = ADCRC oscillator
    ADCON0bits.FM = 1;      // Conversion results are right-justified
    
    ADPCH = ADCINPUTCHAN;   // input channel
    ADACT = SAMPTRIGSRC;    // trigger source
}

void ADC_En() {
    PDM2 &= 0b11111101;     // Clear peripheral module disable bit
    
    // Configure input pin as an analog input
    TRISA |= (1 << 5);
    ANSELA |= (1 << 5);
}

void ADC_Dis() {
    PMD2 |= 0b00000010;     // Set peripheral module disable bit
    
    // Set input pin to digital output, clamp to Vdd
    TRISA &= ~(1 << 5);
    ANSELA &= ~(1 << 5);
    TRISA |= (1 << 5);      // set pin high
}

//void HAL_ADCInit_single()
//{
//    ADCON0bits.GO = 1;      // Initiate single conversion
//}

bool ADC_isBusy() {
    return ADCON0bits.ADGO;
}

int16_t ADC_getConv() {
    return ADRES;
}

#endif