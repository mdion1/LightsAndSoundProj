#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
}RGB_t;

RGB_t HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val);