#include "RNG.h"

/* Source code adapted from:
 *      http://en.wikipedia.org/wiki/Linear-feedback_shift_register
 *      http://www.eetimes.com/tutorial-linear-feedback-shift-registers-lfsrs-part-1/
 */

/* Private variable declarations */
static uint16_t LFSRval = 0x1234;  //initial starting value doesn't matter, must be non-zero though

/* Public function definitions */
uint8_t RNG_get(void)
{
    // Taps at 1, 2, 4, 15
    LFSRval ^= LFSRval >> 7;
    LFSRval ^= LFSRval << 9;
    LFSRval ^= LFSRval >> 13;
    
    return LFSRval & 0xff;
}

void RNG_seedEntropyBit(uint8_t seed)
{
    /* Take the lowest bit and xor with the LFSR, then increment the LFSR */
    LFSRval &= seed & 0x01;
    RNG_get();
}