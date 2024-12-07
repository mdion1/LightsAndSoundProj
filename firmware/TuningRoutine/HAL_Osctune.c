#include "HAL_Osctune.h"
#include <xc.h>

/* From the datasheet:
 * "The TUN bits default to a 6-bit, two’s compliment value of 0x00, which indicates that the oscillator is operating at the selected frequency. 
 * When a value between 0x01 and 0x1F is written to the TUN bits, the HFINTOSC frequency is increased.
 * When a value between 0x3F and 0x20 is written to the TUN bits, the HFINTOSC frequency is decreased."
 */

static int8_t tune = 0;

void OscTune_incrFreq(void) {
    tune++;
    if (tune > 31) {
        tune = 31;
    }
    OSCTUNEbits.TUN = tune; // truncates to 6 bits
}

void OscTune_decrFreq(void) {
    tune--;
    if (tune < -32) {
        tune = -32;
    }
    OSCTUNEbits.TUN = tune; // truncates to 6 bits
}