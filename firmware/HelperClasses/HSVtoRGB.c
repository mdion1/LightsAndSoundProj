#include "HSVtoRGB.h"

#define NO_OVERFLOW_CHECK

/** "Fixed point" math section */

static inline uint16_t mult8x8(uint8_t a, uint8_t b) {
    return a * b;   /*! \todo Check if the compiler figured this out. */
}

#ifndef NO_OVERFLOW_CHECK
typedef struct
{
    bool b_isOne;
    uint16_t val;
}FixPt_t;

static inline FixPt_t Int8ToFixedPt(uint8_t x)
{
    return (FixPt_t) {
        .b_isOne = false,
        .val = x << 8       // promote to uint16_t
    };
}

static inline FixPt_t roundTo8bits(FixPt_t x)
{
    // check for overflow
    if (x.val >= 0xff80 || x.b_isOne) {
        return (FixPt_t) { .b_isOne = true, .val = 0 };
    }
    x.val = (x.val + 128) & 0xff00;
    return x;
}

static inline uint8_t FixPtToInt8(FixPt_t x)
{
    x = roundTo8bits(x);
    if (x.b_isOne) {
        return 255;
    }
    return x.val >> 8;
}

static inline FixPt_t multFixPt(FixPt_t a, FixPt_t b)
{
    if (a.b_isOne) {
        return b;
    }
    else if (b.b_isOne) {
        return a;
    }
    else {
        a = roundTo8bits(a);
        b = roundTo8bits(b);
        return (FixPt_t) {
            .b_isOne = false,
            .val = (a.val >> 8) * (b.val >> 8)
        };
    }
}

static inline FixPt_t addFixPt(FixPt_t a, FixPt_t b)    // does NOT check for overflow, assumes a + b < 1
{
    return (FixPt_t) {
        .b_isOne = false,
        .val = a.val + b.val
    };
}

static inline FixPt_t subtractFixPt(FixPt_t a, FixPt_t b)    // does NOT check for overflow, assumes a > b
{
    return (FixPt_t) {
        .b_isOne = false,
        .val = a.val - b.val
    };
}

#else
typedef uint16_t FixPt_t;

static inline FixPt_t Int8ToFixedPt(uint8_t x)
{
    return (uint16_t)x << 8;       // promote to uint16_t
}

static inline FixPt_t roundTo8bits(FixPt_t x)
{
    return (x + 128) & 0xff00;
}

static inline uint8_t FixPtToInt8(FixPt_t x)
{
    return (x + 128) >> 8;
}

static inline FixPt_t multFixPt(FixPt_t a, FixPt_t b)
{
    return mult8x8(FixPtToInt8(a), FixPtToInt8(b));       // round down to 8 bits, then multiply to get back to 16
}

static inline FixPt_t addFixPt(FixPt_t a, FixPt_t b)    // does NOT check for overflow, assumes a + b < 1
{
    return a + b;   //trivial
}

static inline FixPt_t subtractFixPt(FixPt_t a, FixPt_t b)    // does NOT check for overflow, assumes a > b
{
    return a - b;   //trivial
}

#endif  //#ifndef NO_OVERFLOW_CHECK

RGB_t HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val)
{
    FixPt_t S = Int8ToFixedPt(sat);
    FixPt_t M = Int8ToFixedPt(val);
    FixPt_t m = subtractFixPt(M, multFixPt(M, S));

    static const uint8_t SLOPE = 6;
    if (hue < 43)     // 60 * 360 / 256 = 42.667
    {
        const uint16_t INTERCEPT = 0;
        FixPt_t X = Int8ToFixedPt((uint8_t)(mult8x8(SLOPE, hue) - INTERCEPT));        // (slope * hue) +- INTERCEPT guaranteed to be < 256, but intermediates are not 
        FixPt_t z = multFixPt(subtractFixPt(M, m), X);     // M guaranteed to be > m
        
        return (RGB_t) {
            .R = FixPtToInt8(M),
            .G = FixPtToInt8(addFixPt(z, m)),       // z + m guaranteed not to overflow
            .B = FixPtToInt8(m)
        };
    }
    else if (hue < 86)      // 120 * 360 / 256 = 85.333
    {
        const uint16_t INTERCEPT = 512;
        FixPt_t X = Int8ToFixedPt((uint8_t)(INTERCEPT - mult8x8(SLOPE, hue)));
        FixPt_t z = multFixPt(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(addFixPt(z, m)),
            .G = FixPtToInt8(M),
            .B = FixPtToInt8(m)
        };
    }
    else if (hue < 128)     // 180 * 360 / 256 = 128
    {
        const uint16_t INTERCEPT = 512;
        FixPt_t X = Int8ToFixedPt((uint8_t)(mult8x8(SLOPE, hue) - INTERCEPT));
        FixPt_t z = multFixPt(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(m),
            .G = FixPtToInt8(M),
            .B = FixPtToInt8(addFixPt(z, m))
        };
    }
    else if (128 == hue)    // 180 * 360 / 256 = 128; special case where fixed point X would "overflow", representing "1.0"
    {
        FixPt_t z = subtractFixPt(M, m);     // M guaranteed to be > m; no need to multiply by X = 1.0 (fixed point representation)
        return (RGB_t) {
            .R = FixPtToInt8(m),
            .G = FixPtToInt8(addFixPt(z, m)),
            .B = FixPtToInt8(M)
        };
    }
    else if (hue < 171)     // 240 * 360 / 256 = 171.667
    {
        const uint16_t INTERCEPT = 1024;
        FixPt_t X = Int8ToFixedPt((uint8_t)(INTERCEPT - mult8x8(SLOPE, hue)));
        FixPt_t z = multFixPt(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(m),
            .G = FixPtToInt8(addFixPt(z, m)),
            .B = FixPtToInt8(M),
        };
    }
    else if (hue < 214)     // 300 * 360 / 256 = 213.333
    {
        const uint16_t INTERCEPT = 1024;
        FixPt_t X = Int8ToFixedPt((uint8_t)(mult8x8(SLOPE, hue) - INTERCEPT));
        FixPt_t z = multFixPt(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(addFixPt(z, m)),
            .G = FixPtToInt8(m),
            .B = FixPtToInt8(M),
        };
    }
    else
    {
        const uint16_t INTERCEPT = 1536;
        FixPt_t X = Int8ToFixedPt((uint8_t)(INTERCEPT - mult8x8(SLOPE, hue)));
        FixPt_t z = multFixPt(subtractFixPt(M, m), X);
        
        return (RGB_t) {
            .R = FixPtToInt8(M),
            .G = FixPtToInt8(m),
            .B = FixPtToInt8(addFixPt(z, m))
        };
    }
}