#pragma once
#include <stdint.h>
#include <stdbool.h>

void RNG_seedEntropyBit(uint8_t seed);
uint8_t RNG_get(void);