#pragma once
#include <stdint.h>
#include <stdbool.h>

#define SAMPLE_BUF_SIZE 64      // number of ADC samples per buffer, in which 1 buffer contains >= 2pi rad worth of samples at the target detection frequency
#define NUM_BUFS 8              // number of buffers used in the rolling average
#define SIG_STR_FLOOR 256

#ifdef __PIC18F67K40__

/*
 * Sampling limits:
 * 
 * For a relative sampling period of 4 (F_samp = 4 * F_sig), and an ADC resolution of 10 bits (unsigned):
 *      -Every 4 samples (2pi rad) can be summed and stored in two signed 10-bit numbers, one for sine, one for cosine
 *      -Every 32 periods (32 * 2pi rad) can be summed and stored in two signed 16-bit numbers
 *      -For summing a greater number of periods, either 32-bit ints are needed, or sample sums need to be right-shifted
 *          for a loss in resolution.
 */

/* C4 note frequency = 261.6Hz
 * Target sampling frequency: 4 * 261.6Hz = 1046.5Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of  319,
 * the actual sampling frequency is
 *      1.0e6Hz / 1 / 3 / 319 = 1044.9Hz
 */
#define RELATIVE_FSAMP 4
#define NUM_CYCLES_SAMPLED 32
#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 318        //sampling period = N+1



#define SIN_IDXMASK (RELATIVE_FSAMP - 1)

#define POST_FILT_SUM_LEN 8 // how many cycles need to be sampled, total? divide this by NUM_CYCLES_SAMPLED, result is POST_FILT_SUM_LEN
#define CYCLE_SUM_RIGHTSHIFT 16   //todo: figure out the appropriate scaling for averaging/summing of the 16-bit fourier terms. Use POST_FILT_SUM_LEN to calculate


#endif // #ifdef __PIC18F67K40__