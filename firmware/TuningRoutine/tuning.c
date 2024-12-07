#include <stdint.h>
#include <stdbool.h>
#include "HAL_gatedTmr.h"
#include "HAL_Osctune.h"

// Private variable declarations

/* Period Averaging
 * For a timer frequency of 1MHz and a 100Hz reference signal, the expected gated timer capture value is 10^4.
 * This will give us an error resolution of 0.01%.
 * If the actual captured value is less than expected, the oscillator is running too slow and the tuning value should be increased.
 * Conversely, captured values greater expected indicate the oscillator is running too fast.
 * A 100 Hz refenr
 */
#define TMR_EXPECTED 10000

// Private function declarations
static void setup(void);
static void tearDown(void);
static void tuningRoutine(void);

// Public function definitions

void tune(void) {
    setup();

    while (checkTuningMode()) {
        tuningRoutine();
    }

    tearDown();
}

// Private function definitions

static bool checkTuningMode(void) {
#ifndef NDEBUG
    /* For debug mode, GPIO's RA0 and RA1 are used as ICSP_DAT and ICSP_CLK pins and are unavailable.
     * Return a constant value based on debugging needs.
     */
    return true;
    // return false;
#else

    // Return state of RA0 pin. Low = active.
    return (PORTAbits.RA0 == 0);
#endif
}

static void setup(void) {
    // Set up "Tuning mode" trigger pin with internal pullup
#ifndef NDEBUG
    // No "Tuning mode" trigger pin available in debug mode

    // Set up RA5 as the timer gate input
    GatedTmr_setGateSrc(TIMER_GATE_SRC_GPIO, TIMER_GATE_PPS_PORTA, 5);
#else
    // Set up RA0 as an input with internal pullup
    TRISAbits.TRISA0 = 1;
    WPUAbits.WPUA0 = 1;

    // Set up RA1 as the timer gate input
    GatedTmr_setGateSrc(TIMER_GATE_SRC_GPIO, TIMER_GATE_PPS_PORTA, 1);

#endif

    // Set up gated timer + interrupt
    GatedTmr_clrConfig();
    GatedTmr_setClkSrc(TIMER_CLK_HFINTOSC);
    GatedTmr_setPrescale(TIMER_PRESCALE_1);
    GatedTmr_setRd16(true);
    GatedTmr_enGateToggle(true);
    GatedTmr_enSinglePulseMode(true);
    GatedTmr_clrTimerVal();
    GatedTmr_gateEn(true);
}

static void tearDown(void) {
    GatedTmr_clrConfig();

    // TODO reset pin configuration

    // Set up RA0 to output low     TODO put in hal pins file
    LATAbits.LATA0 = 0;
    WPUAbits.WPUA0 = 0;
    TRISAbits.TRISA0 = 0;
}

static void tuningRoutine(void) {
    // Wait for gate to go inactive before starting the timer and arming the single pulse trigger
    while(GatedTmr_isGateActive()) {}
    GatedTmr_clrSinglePulseDoneFlag();
    GatedTmr_clrTimerVal();
    GatedTmr_en(true);

    // Wait for the single pulse to complete
    while (!GatedTmr_isSinglePulseDone()) {}
    
    // Disable the timer, read the captured value
    GatedTmr_en(false);
    uint16_t tmrCapture = GatedTmr_getTimer();

    // Compare expected and actual captured timer values
    if (tmrCapture < TMR_EXPECTED) {
        // Oscillator is running too slow
        OscTune_incrFreq();
        // Set LED to red
    } else if (tmrCapture > TMR_EXPECTED) {
        // Oscillator is running too fast
        OscTune_decrFreq();
        // Set LED to red
    } else {
        // Oscillator is running at the correct frequency
        // Set LED to green
    }
}