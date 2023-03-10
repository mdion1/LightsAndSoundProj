#include "AmpScalingMath.h"

/* Private function declarations */
static uint32_t abs32(int32_t x);
static uint16_t square8(uint8_t a);
static uint16_t mult8x8(uint8_t a, uint8_t b);

#ifndef OPTIMIZE_LATER_NOT_NOW
#include <math.h>

uint8_t AmpToBrightness(int32_t sin, int32_t cos, uint8_t numCycles)
{
#define MAX_VAL 90000
#define SCALAR 0.002
    sin = (sin < 0) ? -sin : sin;
    cos = (cos < 0) ? -cos : cos;
    float sin_f = (sin < MAX_VAL) ? sin : MAX_VAL;
    float cos_f = (cos < MAX_VAL) ? cos : MAX_VAL;    
    sin_f = sin_f*sin_f;
    cos_f = cos_f*cos_f;
    float hypot = sqrtf(sin_f + cos_f);
    
    const float scalar = SCALAR;
    return roundf(scalar * hypot);
    //const float scalar = 0.704;
    //return roundf(scalar * hypot / numCycles);
}

#else

#define GAMMALOOKUP_LEN 64
#define MASK_LSB_START 0x7fff
#define GAMMA_LEFTSHIFT 5

#define LOG_TABLE_LEN 64
#define LOG2_SCALING 

static const uint8_t NLog2Lookup;




uint8_t AmpToBrightness(int32_t sin, int32_t cos, uint8_t numCycles)
{
    // assumes inputs of 18bits + sign bit
    // right-shift 18 bits down to 8 bits, do an 8x8 multiply
    uint16_t sin2 = square8(abs32(sin) >> 10);
    uint16_t cos2 = square8(abs32(cos) >> 10);
    
    // divide by two to prevent overflow, then add. Result is 16 bits max.
    uint16_t mag2 = (sin2 >> 1) + (cos2 >> 1);
    
    uint16_t NLogMag = Nlog2(mag2);
    
    // todo: now scale log(amp) based on the number of cycles used from the filter/buffer (so there doesn't need to be amplitude rollup @ startup)
    // for example, subtract a number proportional to the number of samples in the buffer, so that for a low number of cycles log(N) doesn't decrease much
    // (essentially what we're doing is:
    //          log(Amp *64 / NumCycles) = log(amp) + const - log(numCycles)
    //                                   = log(amp) + const - log(numCycles*scalar) + log(scalar)   (where scalar is added to reduce rounding error)
    
    uint16_t LogNumCycles = Nlog2(numCycles << SCALAR_FOR_ROUNDING) - SCALAR_FOR_ROUNDING*N; //todo: do I need to bitshift this some amount
    
    
    // now calculate scalarB * 2 ^ (N log2(Amp))
    uint8_t newLEDval = NPow2(NLogMag - LogNumCycles + NUM_CYCLES_OFFSET);
    
    
}


/* returns base2 logarithm multiplied by N (where N is defined in some macro???) */
uint16_t Nlog2(uint16_t val)
{
    uint16_t maskMSB = 0x8000;
    uint16_t maskLSB = MASK_LSB_START;
    
    uint16_t msb = 15;
    uint16_t lsb = 0;

    /*! \todo look for "count trailing zeroes" and "count leading zeroes" assembly instruction! */
    while (msb)
    {
        if(val & maskMSB) {
            lsb = NLog2Lookup[val & maskLSB];
            break;
        }
        msb--;
        maskMSB >>= 1;
        maskLSB >>= 1;
    }
    return (msb << GAMMA_LEFTSHIFT) + lsb;      // todo GAMMA_LEFTSHIFT is related to the "N" here
}

uint16_t NPow2(uint16_t val)
{

    uint16_t maskMSB = (0x0f << GAMMA_LEFTSHIFT);
    uint16_t maskLSB = 0x00f0;      //this is just a placeholder
    
    return (1 << (val & maskMSB)) + NPow2Lookup[val & maskLSB];
}

static const uint16_t NLog2Lookup[GAMMALOOKUP_LEN] = {
    //...
};

static const uint16_t NPow2Lookup[GAMMALOOKUP_LEN] = {
//...
};

#endif

/* Private function definitions */
static uint32_t abs32(int32_t x)
{
    // does NOT check for an input value of 0x80000000
    return (x < 0) ? -x : x;
}

static uint16_t square8(uint8_t a) {
    return a * a;
}

static uint16_t mult8x8(uint8_t a, uint8_t b) {
    return a * b;
}