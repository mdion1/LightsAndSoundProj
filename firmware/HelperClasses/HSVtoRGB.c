#include "HSVtoRGB.h"

/**
 * The equation to convert Hue/Saturation/Value (HSV) to RGB is:
 *      0 <= hut < 360 degrees
 *      0 <= sat <= 1
 *      0 <= val <= 1
 * 
 *      M = val
 *      m = M * (1 - sat)
 *      z = (M - m) * (1 - abs((hue / 60) % 2 - 1))
 * 
 *  For 0 <= hue < 60:
 *      R = M
 *      G = z + m
 *      B = m
 *  For 60 <= hue < 120:
 *      R = z + m
 *      G = M
 *      B = m
 *  For 120 <= hue < 180:
 *      R = m
 *      G = M
 *      B = z + m
 *  For 180 <= hue < 240:
 *      R = m
 *      G = z + m
 *      B = M
 *  For 240 <= hue < 300:
 *      R = z + m
 *      G = m
 *      B = M
 *  For 300 <= hue < 360:
 *      R = M
 *      G = m
 *      B = z + m
 * 
 * ---> 0 <= R, G, B <= 1.0
 * 
 * In order to elliminate expensive floating point math for uint8/uint16 math, let
 * us first make the following assumptions and adjustments:
 *      - Hue, saturation, and value can be scaled from 0 - 256, representing them
 *        as unsigned 8-bit or 16-bit numbers, while acknowledging that saturation and
 *        values of 1.0 cannot be represented (256 and 65536 are out of bounds).
 *      - We recognize that certain mathematical operations are guaranteed by the design
 *        equations not to overflow:
 *          m = M * (1 - sat) ---> m will always be <= M
 *          z = (M - m) * X, where X = 1 - abs((hue / 60) % 2 - 1)
 *              ---> z <= M, and z + m will not overflow
 *      - We can represent fractional numbers with uint16_t's, with 0x0000 to 0xffff representing
 *          0 to 65535 / 65536. To multiply two fixed-point values, first we round/truncate the uint16_t's
 *          to uint8_t's, then multiply.
 *          To start:
 *              0 <= hue, sat, val < 256
 *              M = val << 8                    scale to fixed-point uint16_t
 *              m = M - M * (sat << 8)
 *      - We can eliminate the modulo operator by taking advantage of the if-else blocks that are already necessary.
 *          Let X = 1 - abs((hue / 60) % 2 - 1)
 *          For each block of 60 degrees, X is a linear function of hue
 *          First scale hue from 0 - 256 instead of 0 - 360
 *          if (hue < 43)               0 to 60 degrees
 *              X = 6 * hue
 *          else if (hue < 86)          60 to 120 degrees
 *              X = 512 - 6 * hue
 *          else if (hue < 128)         120 to 180 degrees
 *              X = 6 * hue - 512
 *          else if (128 == hue)        180 degrees
 *              X = 1       <--- this will be important later to catch a special case of overflow
 *          else if (hue < 171)         180 to 240 degrees
 *              X = 1024 - 6 * hue
 *          else if (hue < 214)         240 to 300 degrees
 *              X = 6 * hue - 1024
 *          else                        300 to 360 degrees
 *              X = 1536 - 6 * hue
 * 
 *          The result is an 8-bit value for X, which can then be scaled up to the 16-bit fixed-point
 *          fractional value (or not, the next operation is to truncate and multiply it anyway).
 *              z = (M - m) * X
 *          The only case where X would overflow is where hue = 128. In this special case, X represents 1.0,
 *          so we can just skip the multiply operation:
 *              z = M - m
 *          
 *          *(Note that these calculations for X involve 16-bit integers, but we can elimnate them by making
 *          the following simplifications:
 *              X = 512 - 6 * hue = 6*(85 - hue) + 2
 *              X = 6 * hue - 512 = 6*(hue - 86) + 4
 *              X = 1024 - 6 * hue = 6*(170 - hue) + 4
 *              X = 6 * hue - 1024 = 6*(hue - 171) + 2
 *              X = 1536 - 6 * hue = = 6*(256 - hue) = 0 - 6*hue
 *      - Once z, M, and m are calculated, they can be truncated/scaled down to 8-bits and assigned to R, G, and B
 */

/* Private function declarations */
/* "Fixed point" math functions */

typedef uint16_t FixPt_t;
static inline FixPt_t mult8x8(uint8_t a, uint8_t b);
static inline FixPt_t Int8ToFixedPt(uint8_t x);
static inline uint8_t FixPtToInt8(FixPt_t x);
static inline FixPt_t mult16x8(FixPt_t a, uint8_t b);
static inline FixPt_t multFixPt(FixPt_t a, FixPt_t b);
static inline FixPt_t addFixPt(FixPt_t a, FixPt_t b);
static inline FixPt_t subtractFixPt(FixPt_t a, FixPt_t b);

/* Public function definitions */

RGB_t HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val)
{
    FixPt_t S = Int8ToFixedPt(sat);
    FixPt_t M = Int8ToFixedPt(val);
    FixPt_t m = subtractFixPt(M, multFixPt(M, S));

    static const uint8_t SLOPE = 6;
    if (hue < 43)     // 60 / 360 * 256 = 42.667
    {
        uint8_t X = 6 * hue;
        FixPt_t z = mult16x8(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(M),
            .G = FixPtToInt8(addFixPt(z, m)),       // z + m guaranteed not to overflow
            .B = FixPtToInt8(m)
        };
    }
    else if (hue < 86)      // 120 / 360 * 256 = 85.333
    {
        uint8_t X = 6 * (85 - hue) + 2;
        FixPt_t z = mult16x8(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(addFixPt(z, m)),
            .G = FixPtToInt8(M),
            .B = FixPtToInt8(m)
        };
    }
    else if (hue < 128)     // 180 / 360 * 256 = 128
    {
        uint8_t X = 6 * (hue - 86) + 4;
        FixPt_t z = mult16x8(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(m),
            .G = FixPtToInt8(M),
            .B = FixPtToInt8(addFixPt(z, m))
        };
    }
    else if (128 == hue)    // 180 / 360 * 256 = 128; special case where fixed point X would "overflow", representing "1.0"
    {
        FixPt_t z = subtractFixPt(M, m);
        return (RGB_t) {
            .R = FixPtToInt8(m),
            .G = FixPtToInt8(addFixPt(z, m)),
            .B = FixPtToInt8(M)
        };
    }
    else if (hue < 171)     // 240 / 360 * 256 = 171.667
    {
        uint8_t X = 6 * (170 - hue) + 4;
        FixPt_t z = mult16x8(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(m),
            .G = FixPtToInt8(addFixPt(z, m)),
            .B = FixPtToInt8(M),
        };
    }
    else if (hue < 214)     // 300 / 360 * 256 = 213.333
    {
        uint8_t X = 6 * (hue - 171) + 2;
        FixPt_t z = mult16x8(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(addFixPt(z, m)),
            .G = FixPtToInt8(m),
            .B = FixPtToInt8(M),
        };
    }
    else
    {
        uint8_t X = 0 - 6 * hue;
        FixPt_t z = mult16x8(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(M),
            .G = FixPtToInt8(m),
            .B = FixPtToInt8(addFixPt(z, m))
        };
    }
}

/* Private function definitions */

static inline uint16_t mult8x8(uint8_t a, uint8_t b) {
    return a * b;   /*! \todo Check if the compiler figured this out. */
}

static inline FixPt_t Int8ToFixedPt(uint8_t x)
{
    return (uint16_t)x << 8;       // promote to uint16_t
}

static inline uint8_t FixPtToInt8(FixPt_t x)
{
    return (x + 128) >> 8;      // adding 128 first has the effect of rounding up for lower byte values between 128 - 255
}

static inline FixPt_t mult16x8(FixPt_t a, uint8_t b)
{
    return mult8x8(FixPtToInt8(a), b);
}

static inline FixPt_t multFixPt(FixPt_t a, FixPt_t b)       // round down to 8 bits, then multiply to get back to 16
{
    return mult8x8(FixPtToInt8(a), FixPtToInt8(b));
}

static inline FixPt_t addFixPt(FixPt_t a, FixPt_t b)        // does NOT check for overflow, assumes a + b < 1
{
    return a + b;   //trivial
}

static inline FixPt_t subtractFixPt(FixPt_t a, FixPt_t b)    // does NOT check for overflow, assumes a > b
{
    return a - b;   //trivial
}