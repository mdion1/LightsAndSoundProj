#pragma once
#include <stdint.h>

#define SAMPLE_BUF_SIZE 64      // number of ADC samples per buffer, in which 1 buffer contains >= 2pi rad worth of samples at the target detection frequency
#define NUM_BUFS 8              // number of buffers used in the rolling average
#define SIG_STR_FLOOR 256

//todo: figure out if these should be 8-, 16-, or 32-bit
extern const int16_t sinTable[SAMPLE_BUF_SIZE];
extern const int16_t cosTable[SAMPLE_BUF_SIZE];