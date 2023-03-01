#ifdef __PIC18F06Q41__
#include "hal_PWM.h"
#include <xc.h>

/* With clock source = 1MHz HFINTOSC and period of 256, PWM frequency = 3.91kHz
 */
#define PWM_PERIOD 256

/* PWM1 output P1 = Red channel
 * PWM1 output P2 = Green channel
 * PWM2 output P1 = Blue channel
 */
#define PWM1S1P1_OUT 0x0a   // Peripheral pin select output register values
#define PWM1S1P2_OUT 0x0b
#define PWM1S2P1_OUT 0x0c

void PWM_config()
{
    /* Set clock source and period */
    PWM1CLK = 3; //HFINTOSC
    PWM2CLK = 3;
    PWM1PR = PWM_PERIOD;
    PWM2PR = PWM_PERIOD;
}

void PWM_en()
{
    PWMEN = 0b011;          // Enable PWM1 and PWM2
    PMD3 &= 0b11111000;     // Clear Peripheral Module Disable bits
    
    // Assign GPIO's using the Peripheral Pin Select registers
    RC0PPS = PWM1S1P1_OUT;  // Red channel
    RC1PPS = PWM1S1P2_OUT;  // Green channel
    RC2PPS = PWM1S2P1_OUT;  // Blue channel
}

void PWM_dis()
{
    PWMEN = 0;              // Disable PWM1 and PWM2
    PMD3 |= 0b00000111;     // Set Peripheral Module Disable bits
    
    // Set GPIO's back to digital outputs set to 0
    RC0PPS = 0;     // Red channel
    RC1PPS = 0;     // Green channel
    RC2PPS = 0;     // Blue channel
}

void PWM_setVals(uint8_t Rval, uint8_t Gval, uint8_t Bval)
{
    PWM1S1P1 = Rval;
    PWM1S1P2 = Gval;
    PWM1S1P1 = Bval;
    PWMLOAD = 0b11; // set "load" bit for PWM1 and PWM2
}

#endif