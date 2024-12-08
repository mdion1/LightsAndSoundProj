#include "HAL_Osctune.h"
#include <xc.h>

/* From the datasheet:
 * "The TUN bits default to a 6-bit, two’s compliment value of 0x00, which indicates that the oscillator is operating at the selected frequency. 
 * When a value between 0x01 and 0x1F is written to the TUN bits, the HFINTOSC frequency is increased.
 * When a value between 0x3F and 0x20 is written to the TUN bits, the HFINTOSC frequency is decreased."
 */

void OscTune_incrFreq(void) {
    OscTune_setTun(OscTune_getTun() + 1);
}

void OscTune_decrFreq(void) {
    OscTune_setTun(OscTune_getTun() - 1);
}

int8_t OscTune_getTun(void) {
    int8_t tune = OSCTUNEbits.TUN;

    // convert from signed 6-bit to signed 8-bit
    if (tune > 31) {
        tune = tune - 64;
    }
    return tune;
}

void OscTune_setTun(int8_t val) {
    if (val > 31) {
        val = 31;
    }
    if (val < -32) {
        val = -32;
    }
    OSCTUNEbits.TUN = (uint8_t)val; // truncates to 6 bits
}