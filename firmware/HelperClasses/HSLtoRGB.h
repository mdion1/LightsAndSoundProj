#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int hue;
    int sat;
}HSL_t;

typedef struct
{
    int R;
    int G;
    int B;
}RGB_t;

RGB_t HSLtoRGB(const HSL_t* pHSL);
