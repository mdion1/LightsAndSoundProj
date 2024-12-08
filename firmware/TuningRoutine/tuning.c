#include <stdint.h>
#include <stdbool.h>
#include "HAL_gatedTmr.h"
#include "HAL_Osctune.h"
#include "HAL_EEPROM.h"
#include "HAL_tuningPins.h"

// Private variable declarations

/* Period Averaging
 * For a timer frequency of 1MHz and a 100Hz reference signal, the expected gated timer capture value is 10^4.
 * This will give us an error resolution of 0.01%.
 * If the actual captured value is less than expected, the oscillator is running too slow and the tuning value should be increased.
 * Conversely, captured values greater expected indicate the oscillator is running too fast.
 * A 100 Hz refenr
 */
#define TMR_EXPECTED 10000
#define TUN_VAL_LOC 0   // EEPROM offset address for tuning value

// Private function declarations
static void setup(void);
static void tearDown(void);
static void tuningRoutine(void);

// Public function definitions

void tune(void) {
    // Load tuning value from NVM
    OscTune_setTun((int8_t)EEPROM_read(TUN_VAL_LOC));

    setup();

    while (Pins_getTriggerState()) {
        tuningRoutine();
    }

    tearDown();

    // Write tuning value to NVM
    if ((int8_t)EEPROM_read(TUN_VAL_LOC) != OscTune_getTun()) {
        EEPROM_write(TUN_VAL_LOC, (uint8_t)OscTune_getTun());
    }
}

// Private function definitions

static void setup(void) {
    Pins_setupTuningMode();

#ifndef NDEBUG
    // Set up RA5 as the timer gate input
    GatedTmr_setGateSrc(TIMER_GATE_SRC_GPIO, TIMER_GATE_PPS_PORTA, 5);
#else
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
    Pins_tearDownTuningMode();
}

static void tuningRoutine(void) {
    /* Make sure we're not right near the end of a pulse by waiting for the gate to go inactive,
     * then active, then inactive again. Then start the timer and arm the single pulse trigger.
     */
    while(!GatedTmr_isGateActive());
    while(GatedTmr_isGateActive());
    GatedTmr_clrSinglePulseDoneFlag();
    GatedTmr_clrTimerVal();
    GatedTmr_en(true);
    
    // Wait for the single pulse to complete
    while (!GatedTmr_isSinglePulseDone());
    
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