
#ifdef __PIC18F06Q41__
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "../HAL.h"

/* For positive channel selection register ADPCH */
#define ADCINPUTCHAN 0b101          // selects port/pin RA5
#define TEMPINPUTCHAN 0b111100

/* For register auto conversion trigger source register ADACT */
#define SAMPTRIGSRC 0b100   //TMR2 postscaled
#define TRIGDISABLE 0

// Notes:
/*
 * From the manual, Section 33.2: ADC Operation
 * To enable the ADC module, the ADON must be set to '1'.
 * Set the TRIS and ANSEL bits.
 * ADPCH sets positive ADC input
 * ADPREF and ADNREF set + and - reference inputs
 * ADCS = conversion clock source bit
 * ADCLK set clock div
 * 
 * Interrupt flags: ADIF bit in PIR1 reg, ADIE bit in PIE1 reg
 * 
 * ADFM bit = left or right justified result (10-bits in ADRESH and ADRESL).
 * ADFM = 1 ==> right-justified
 * 
 * 
 * ADPREVH/ADPREVL holds previous conversion
 * 
 * ADACC (ADACCH + ADACCL) can be used to accumulate results
 * 
 * 
 * ADC can operate during sleep if clock source = FRC oscillator, interrupt will wake it up, otherwise ADC module will turn off after conversion
 * 
 * 
 * ADACT register sets trigger source, such as a timer overflow or CCPxOUT

*/

//todo: put defines for MCU and ADC clock speeds in an .h file somewhere

static void initADCmodule()
{
    ADCON0bits.ON = 1;      // Enable module
    ADCON0bits.CS = 1;      // Clock source = ADCRC oscillator
    ADCON0bits.FM = 1;      // Conversion results are right-justified
    
    ADPCH = ADCINPUTCHAN;   // input channel
    ADACT = SAMPTRIGSRC;    // trigger source
}

void HAL_ADCInit_single()
{
    ADCON0bits.GO = 1;      // Initiate single conversion
}

void HAL_ADCInit_onInterval(uint8_t clkPrescaler, uint8_t channelSel)
{
    

    


    /******/
//    //setup interrupt sampling
    PIR1bits.ADIF = 0;  //clear interrupt flag
    PIE1bits.ADIE = 1;
    
    
}

void HAL_initSampTmr(uin8t_t prescaler, uint8_t postscaler, uint8_t period)
{
    T2PR = period;
    T2CONbits.CKPS = prescaler; // 3 bits; 1:2^n, where CKPS = n
    T2CONbits.OUTPS = postscaler; // 4 bits; 1:n+1, where OUTPS = n
}

bool ADCbusy()
{
    return ADCON0bits.ADGO;
}

int16_t getADCresult()
{
    return ADRES;
}

#endif