#include "AmpScalingMath.h"

/* Private variable declarations */

#define SCALAR_FOR_ROUNDING 0
#define NUM_CYCLES_OFFSET 0

#define LOG_TABLE_BITDEPTH 6
#define LOG_TABLE_PRECISION 6
#define LOG_TABLE_LEN ((uint8_t)(1 << LOG_TABLE_BITDEPTH))
#define TABLE_IDX_MASK ((uint8_t)((1 << LOG_TABLE_BITDEPTH) - 1))

static const uint8_t NLog2Lookup[1 << LOG_TABLE_BITDEPTH] = {
    0, 1, 3, 4, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18, 19,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34, 35, 35, 36,
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 47, 48, 49, 50, 51,
    52, 52, 53, 54, 55, 56, 56, 57, 58, 59, 60, 60, 61, 62, 63, 63
};

static const uint8_t NExp2Lookup[1 << LOG_TABLE_BITDEPTH] = {
    64, 65, 65, 66, 67, 68, 68, 69, 70, 71, 71, 72, 73, 74, 74, 75,
    76, 77, 78, 79, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    91, 91, 92, 93, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
    108, 109, 110, 111, 112, 114, 115, 116, 117, 119, 120, 121, 123, 124, 125, 127
};

static const uint16_t NLog2SampCntLookup[1 << LOG_TABLE_BITDEPTH] = {
    384, 320, 283, 256, 235, 219, 204, 192, 181, 171, 163, 155, 147, 140, 134, 128,
    122, 117, 112, 107, 103, 99, 94, 91, 87, 83, 80, 76, 73, 70, 67, 64,
    61, 58, 56, 53, 51, 48, 46, 43, 41, 39, 37, 35, 33, 30, 29, 27,
    25, 23, 21, 19, 17, 16, 14, 12, 11, 9, 8, 6, 4, 3, 1, 0
};

/* Private function declarations */

static uint16_t NLog2(uint16_t val);
static uint8_t NPow2(uint16_t val);
static uint8_t countLeadingZeroesInt8(uint8_t x);
static uint8_t countLeadingZeroesInt16(uint16_t x);
static uint32_t abs32(int32_t x);
static uint16_t square8(uint8_t a);
static uint16_t mult8x8(uint8_t a, uint8_t b);

/* Public function definitions */

uint8_t AmpToBrightness(int32_t sin, int32_t cos, uint8_t numCycles)
{
    if ((numCycles == 0) || (numCycles > LOG_TABLE_LEN)) {
        return 0;
    }

    /** Assumes inputs of 18bits + sign bit.
     *      -Take absolute value to get rid of sign bit.
     *      -Right-shift 18 bits down to 8 bits, do an 8x8 multiply
     *      -Right-shift 1 to prevent overflow.
     *      -Take fastLog:
     *          x = 64*log2(hypotenuse squared)
     *      - divide by 2 to take square root
     *          x / 2 = 64*log2(hypotenuse)
     *      -
     */
    uint16_t sin2 = square8(abs32(sin) >> 10);
    uint16_t cos2 = square8(abs32(cos) >> 10);
    
    // divide by two to prevent overflow, then add. Result is 16 bits max.
    uint16_t hypot2 = (sin2 >> 1) + (cos2 >> 1);
    uint16_t NLogHypot = NLog2(hypot2);
    if (NLogHypot == 0) {
        return 0;
    }
    NLogHypot = (NLogHypot + (1 << LOG_TABLE_BITDEPTH)) / 2;       //add (1<<LOG_TABLE_BITDEPTH) to counteract previous divide-by-two, since 64
    // todo: now scale log(amp) based on the number of cycles used from the filter/buffer (so there doesn't need to be amplitude rollup @ startup)
    // for example, subtract a number proportional to the number of samples in the buffer, so that for a low number of cycles log(N) doesn't decrease much
    // (essentially what we're doing is:
    //          log(Amp *64 / NumCycles) = log(amp) + const - log(numCycles)
    //                                   = log(amp) + const - log(numCycles*scalar) + log(scalar)   (where scalar is added to reduce rounding error)
    //uint16_t LogNumCycles = NLog2(numCycles << SCALAR_FOR_ROUNDING) - SCALAR_FOR_ROUNDING*N; //todo: do I need to bitshift this some amount
    
    NLogHypot += NLog2SampCntLookup[numCycles - 1];       // index bounds have already been checked
    if (NLogHypot <= 32) //the 32 corresponds to 64*log2(sqrt(2)), since if sin = cos = max input value, amp = sqrt(sin^2 + cos^2) = sqrt(2) * max value
    {
        return 0;
    }
    NLogHypot -= 32;
    
    return NPow2(NLogHypot);
}

/* Private function definitions */

/* returns base2 logarithm multiplied by N (where N is defined in some macro???) */
static uint16_t NLog2(uint16_t val)
{
    int16_t MSBit = 15 - countLeadingZeroesInt16(val);

    if (MSBit < 0) {
        return 0;
    }
    
    uint8_t LSBits = 0;
    val &= ~(1 << MSBit);   // mask off upper bit
    if (MSBit >= LOG_TABLE_BITDEPTH) {
        LSBits = val >> (MSBit - LOG_TABLE_BITDEPTH);
    }
    else {
        LSBits = val << (LOG_TABLE_BITDEPTH - MSBit);    // can't bitshift by a negative number of bits
    }
    LSBits &= TABLE_IDX_MASK;

    return ((uint16_t)MSBit << LOG_TABLE_PRECISION) + NLog2Lookup[LSBits];
}

static uint8_t NPow2(uint16_t val)
{
    // assumes value between 0 - 1024 (10-bit number)
    // comes from log table lookup:
    //      log2(uint16) < 16
    //      64 * log2(uint16) = (4-bit number) << (6-bit-depth table len) = 10 bit number
    
    /* Cap max value */
    if (val > 1023) {
        val = 1023;
    }

    uint8_t bitshift = val >> (LOG_TABLE_BITDEPTH);
    uint8_t LSBits = TABLE_IDX_MASK & val;
    if (bitshift >= LOG_TABLE_PRECISION) {
        return ((uint16_t)NExp2Lookup[LSBits]) << (bitshift - LOG_TABLE_PRECISION);
    }
    else {
        return ((uint16_t)NExp2Lookup[LSBits]) >> (LOG_TABLE_PRECISION - bitshift);
    }
}

static uint8_t countLeadingZeroesInt16(uint16_t x)
{
    uint8_t leadingZeroes = countLeadingZeroesInt8(x >> 8); //check MSByte
    if (leadingZeroes < 8)
    {
        return leadingZeroes;
    }
    return countLeadingZeroesInt8((uint8_t)x) + 8;
}

static uint8_t countLeadingZeroesInt8(uint8_t x)
{
    uint8_t pos = 8;
    uint8_t mask = 0x80;
    while(pos) {
        if (x & mask) {
            break;
        }
        pos--;
        mask >>= 1;
    }
    return 8 - pos;
}

static uint32_t abs32(int32_t x)
{
    // does NOT check for an input value of 0x80000000
    return (uint32_t)(
            (x < 0) ? -x : x
        );
}

static uint16_t square8(uint8_t a) {
    return a * a;
}

static uint16_t mult8x8(uint8_t a, uint8_t b) {
    return a * b;
}