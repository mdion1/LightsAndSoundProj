#include "HAL_tuningPins.h"
#include <xc.h>

// TODO list pinout in debug and release modes
void Pins_tearDownTuningMode(void) {
#ifndef NDEBUG
#else
    // Set up RA0 to output low
    LATAbits.LATA0 = 0;
    WPUAbits.WPUA0 = 0;
    TRISAbits.TRISA0 = 0;
#endif
}

bool Pins_getTriggerState(void) {
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


void Pins_setupTuningMode(void) {
#ifndef NDEBUG
    // No "Tuning mode" trigger pin available in debug mode
#else
    // Set up RA0 as an input with internal pullup
    TRISAbits.TRISA0 = 1;
    WPUAbits.WPUA0 = 1;
#endif
}