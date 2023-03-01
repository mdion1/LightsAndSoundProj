#pragma once
/*! \todo specify packed */
typedef union
{
    int8_t bytes[3];
    struct
    {
        int8_t upper8;
        int16_t lower16;
    };
}int24_t;

inline int8_t int16upper8(int16_t i16)
{
#ifdef BIGENDIAN
    return ((int8_t*)&i16)[0];
#elif defined LITTLENDIAN
    return ((int8_t*)&i16)[1];
#else
    return i16 >> 8;
#endif
}

inline int8_t sign(int16_t i16)
{
    return 0x80 & int16upper8(i16);
}

inline int24_t sum24x16(int24_t i24, int16_t i16)
{
    int16_t sum = i24.lower16 + i16;
    int8_t sumSign = sign(sum);
    bool ovf = (sumSign ^ int16upper8(i16)) & (sumSign ^ int16upper8(i24.lower16));
    if (ovf) {
        i24.upper8 += sumSign ? 1 : -1;
    }
    // if ovf is saved as 0 or 1, then this works too:
    //      i24.upper8 += (sumSign ? 1 : -1) * ovf;
    i24.lower16 = sum;
    
    return i24;
}