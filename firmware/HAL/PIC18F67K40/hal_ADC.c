
#ifdef __PIC18F67K40__
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "../HAL.h"

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
    static bool once = true;
    if (once)
    {
        once = false;
        ADCON0bits.ADON = 1;        //enable ADC
        ADCON0bits.ADFM = 1;        //output format right-justified

        ADCLK = clkPrescaler;    //set ADC clock frequency. clock freq = F_osc / (2*(n+1))
    }
}

void HAL_ADCInit_single()
{

}

void HAL_ADCInit_onInterval(uint8_t clkPrescaler, uint8_t channelSel)
{
    

    

    ADPCH = channelSel;


    /******/
    //setup interrupt sampling
    ADACT = 2;    //Timer2 postscaled

    // timer setup
    T2CLKCONbits.CS = 2;   //F_osc     // 1 = F_osc / 4, 3 = HFINTOSC, 4 = LFINTOSC, 5 = MFINTOSC (31kHz)
    T2PR = clockPeriod;
    
    T2CONbits.CKPS = 7; // 1:2^n, where CKPS = n
    T2CONbits.OUTPS = 0; // 1:n+1, where OUTPS = n
    T2CONbits.ON = 1;
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