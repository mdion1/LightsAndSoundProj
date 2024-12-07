/*


Timer1 has gated mode (also timer3)

GPOL + TxG bits
he gate source for Timer1 is selected using the GSS bits. 
he polarity selection for the gate source is controlled by
the GPOL bit.

Gate sources:
TxGATE = 0; --> Pin selected by T1GPPS register

Can use "gate toggle mode" to get a full period instead of just high or low pulse
GTM bit

interrupt: use TMRxGIF and TMRxGIE 
*/

#include "HAL_gatedTmr.h"
#include <xc.h>

/* Private variables */
static void dummyCallback(void) {}        // dummy function for unused callback function pointers
static void (*Timer1Gate_interrupt_callback)(void) = &dummyCallback;

/* Private function declarations */
void __interrupt(irq(TMR1G),high_priority) Timer1GateInt(void);

/* Public function definitions */

void GatedTmr_setPrescale(TimerPrescale_t prescale) {
    T1CONbits.CKPS = prescale;
}

void GatedTmr_setClkSrc(TimerClkSrc_t clkSrc) {
    T1CLKbits.CS = clkSrc;
}

void GatedTmr_setRd16(bool rd16) {
    T1CONbits.RD16 = rd16;
}

void GatedTmr_en(bool en) {
    T1CONbits.ON = en;
}

void GatedTmr_gateEn(bool en) {
    T1GCONbits.GE = en;
}

void GatedTmr_enGateToggle(bool en) {
    T1GCONbits.GTM = en;
}

void GatedTmr_enSinglePulseMode(bool en) {
    T1GCONbits.GSPM = en;
}

void GatedTmr_clrConfig(void) {
    T1CON = 0;
    T1GCON = 0;
}

void GatedTmr_setGateSrc(TimerGateSrc_t gateSrc, TimerGateInputPort_t gateInputPort, uint8_t gateInputPin) {
    T1GATEbits.GSS = gateSrc;
    T1GPPSbits.PORT = gateInputPort;
    T1GPPSbits.PIN = gateInputPin;
}

uint16_t GatedTmr_getTimer(void) {
    return TMR1;
}

void GatedTmr_clrTimerVal(void) {
    TMR1 = 0;
}

bool GatedTmr_isGateActive(void) {
    return T1GCONbits.GVAL;
}

bool GatedTmr_isSinglePulseDone(void) {
    return (T1GCONbits.GGO == 0);   // active low
}

void GatedTmr_clrSinglePulseDoneFlag(void) {
    T1GCONbits.GGO = 1; // armed
}

// Interrupts
void GatedTmr_enGateInt(bool en) {
    PIE3bits.TMR1GIE = en;
}

bool GatedTmr_isIntEnabled(void) {
    return PIE3bits.TMR1GIE;
}

void GatedTmr_clrIntFlag(void) {
    PIR3bits.TMR1GIF = 0;
}

void GatedTmr_registerIntCallback(void (*p_callback)(void)) {
    Timer1Gate_interrupt_callback = p_callback;
}

void __interrupt(irq(TMR1G),high_priority) Timer1GateInt(void) {
    GatedTmr_clrIntFlag();
    (*Timer1Gate_interrupt_callback)();
}