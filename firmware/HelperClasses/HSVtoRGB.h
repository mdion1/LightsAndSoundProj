#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int R;
    int G;
    int B;
}RGB_t;

RGB_t HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val);