#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    TIMER_PRESCALE_1 = 0,
    TIMER_PRESCALE_2 = 1,
    TIMER_PRESCALE_4 = 2,
    TIMER_PRESCALE_8 = 3,
} TimerPrescale_t;

typedef enum {
    TIMER_CLK_FOSC_DIV4 = 1,
    TIMER_CLK_FOSC = 2,
    TIMER_CLK_HFINTOSC = 3,
    TIMER_CLK_LFINTOSC = 4,
    TIMER_CLK_MFINTOSC_500k = 5,
    TIMER_CLK_MFINTOSC_32k = 6,
    // other options not listed
} TimerClkSrc_t;

typedef enum {
    TIMER_GATE_SRC_GPIO = 0,
    // other options not listed
} TimerGateSrc_t;

typedef enum {
    TIMER_GATE_PPS_PORTA = 0,
    TIMER_GATE_PPS_PORTB = 1,
    TIMER_GATE_PPS_PORTC = 2,
} TimerGateInputPort_t;

void GatedTmr_setPrescale(TimerPrescale_t prescale);
void GatedTmr_setClkSrc(TimerClkSrc_t clkSrc);
void GatedTmr_setRd16(bool rd16);
void GatedTmr_en(bool en);
void GatedTmr_gateEn(bool en);
void GatedTmr_enGateToggle(bool en);
void GatedTmr_enSinglePulseMode(bool en);
void GatedTmr_clrConfig(void);
void GatedTmr_setGateSrc(TimerGateSrc_t gateSrc, TimerGateInputPort_t gateInputPort, uint8_t gateInputPin);
uint16_t GatedTmr_getTimer(void);
void GatedTmr_clrTimerVal(void);
bool GatedTmr_isGateActive(void);

bool GatedTmr_isSinglePulseDone(void);  // TODO better name?
void GatedTmr_clrSinglePulseDoneFlag(void);

// Interrupts
void GatedTmr_enGateInt(bool en);
bool GatedTmr_isIntEnabled(void);
void GatedTmr_clrIntFlag(void);
void GatedTmr_registerIntCallback(void (*p_callback)(void));