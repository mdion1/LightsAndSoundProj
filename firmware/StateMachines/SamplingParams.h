#pragma once

#define __NOTE_C2__
//#define __NOTE_Csharp2__
//#define __NOTE_D2__
//#define __NOTE_Dsharp2__
//#define __NOTE_E2__
//#define __NOTE_F2__
//...

/*
 * Sampling limits:
 * 
 * For a relative sampling period of 4 (F_samp = 4 * F_sig), and an ADC resolution of 10 bits (unsigned):
 *      -Every 4 samples (2pi rad) can be summed and stored in two signed 10-bit numbers, one for sine, one for cosine
 *      -Every 32 periods (32 * 2pi rad) can be summed and stored in two signed 16-bit numbers
 *      -For summing a greater number of periods, either 32-bit ints are needed, or sample sums need to be right-shifted
 *          for a loss in resolution.
 */

#if defined __NOTE_C2__

/* C2 note frequency = 65.41Hz
 * Target sampling frequency: 4 * 65.41Hz = 261.63Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:14, and period of 273,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 14 / 273 = 261.64Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 14      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 273        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C2__)

#if defined __NOTE_Csharp2__ || defined __NOTE_Db2__

/* C#/Db2 note frequency = 69.30Hz
 * Target sampling frequency: 4 * 69.30Hz = 277.18Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:14, and period of 258,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 14 / 258 = 276.85Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 14      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 258        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C#/Db2__)

#if defined __NOTE_D2__

/* D2 note frequency = 73.42Hz
 * Target sampling frequency: 4 * 73.42Hz = 293.66Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:13, and period of 262,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 13 / 262 = 293.60Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 13      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 262        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D2__)

#if defined __NOTE_Dsharp2__ || defined __NOTE_Eb2__

/* D#/Eb2 note frequency = 77.78Hz
 * Target sampling frequency: 4 * 77.78Hz = 311.13Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:12, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 12 / 268 = 310.95Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 12      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D#/Eb2__)

#if defined __NOTE_E2__

/* E2 note frequency = 82.41Hz
 * Target sampling frequency: 4 * 82.41Hz = 329.63Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:11, and period of 276,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 11 / 276 = 329.38Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 11      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 276        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_E2__)

#if defined __NOTE_F2__

/* F2 note frequency = 87.31Hz
 * Target sampling frequency: 4 * 87.31Hz = 349.23Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:11, and period of 260,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 11 / 260 = 349.65Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 11      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 260        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F2__)

#if defined __NOTE_Fsharp2__ || defined __NOTE_Gb2__

/* F#/Gb2 note frequency = 92.50Hz
 * Target sampling frequency: 4 * 92.50Hz = 369.99Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:10, and period of 270,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 10 / 270 = 370.37Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 10      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 270        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F#/Gb2__)

#if defined __NOTE_G2__

/* G2 note frequency = 98.00Hz
 * Target sampling frequency: 4 * 98.00Hz = 392.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:9, and period of 283,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 9 / 283 = 392.62Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 9      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 283        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G2__)

#if defined __NOTE_GsharpAb2__

/* G#Ab2 note frequency = 103.83Hz
 * Target sampling frequency: 4 * 103.83Hz = 415.30Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:9, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 9 / 268 = 414.59Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 9      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G#Ab2__)

#if defined __NOTE_A2__

/* A2 note frequency = 110.00Hz
 * Target sampling frequency: 4 * 110.00Hz = 440.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:8, and period of 284,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 8 / 284 = 440.14Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 8      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 284        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A2__)

#if defined __NOTE_Asharp2__ || defined __NOTE_Bb2__

/* A#/Bb2 note frequency = 116.54Hz
 * Target sampling frequency: 4 * 116.54Hz = 466.16Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:8, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 8 / 268 = 466.42Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 8      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A#/Bb2__)

#if defined __NOTE_B2__

/* B2 note frequency = 123.47Hz
 * Target sampling frequency: 4 * 123.47Hz = 493.88Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:7, and period of 289,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 7 / 289 = 494.32Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 7      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 289        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_B2__)

#if defined __NOTE_C3__

/* C3 note frequency = 130.81Hz
 * Target sampling frequency: 4 * 130.81Hz = 523.25Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:7, and period of 273,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 7 / 273 = 523.29Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 7      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 273        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C3__)

#if defined __NOTE_Csharp3__ || defined __NOTE_Db3__

/* C#/Db3 note frequency = 138.59Hz
 * Target sampling frequency: 4 * 138.59Hz = 554.37Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:7, and period of 258,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 7 / 258 = 553.71Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 7      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 258        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C#/Db3__)

#if defined __NOTE_D3__

/* D3 note frequency = 146.83Hz
 * Target sampling frequency: 4 * 146.83Hz = 587.33Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:6, and period of 284,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 6 / 284 = 586.85Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 6      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 284        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D3__)

#if defined __NOTE_Dsharp3__ || defined __NOTE_Eb3__

/* D#/Eb3 note frequency = 155.56Hz
 * Target sampling frequency: 4 * 155.56Hz = 622.25Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:6, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 6 / 268 = 621.89Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 6      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D#/Eb3__)

#if defined __NOTE_E3__

/* E3 note frequency = 164.81Hz
 * Target sampling frequency: 4 * 164.81Hz = 659.26Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 303,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 303 = 660.07Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 303        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_E3__)

#if defined __NOTE_F3__

/* F3 note frequency = 174.61Hz
 * Target sampling frequency: 4 * 174.61Hz = 698.46Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 286,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 286 = 699.30Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 286        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F3__)

#if defined __NOTE_Fsharp3__ || defined __NOTE_Gb3__

/* F#/Gb3 note frequency = 185.00Hz
 * Target sampling frequency: 4 * 185.00Hz = 739.99Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 270,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 270 = 740.74Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 270        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F#/Gb3__)

#if defined __NOTE_G3__

/* G3 note frequency = 196.00Hz
 * Target sampling frequency: 4 * 196.00Hz = 783.99Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 319,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 319 = 783.70Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 319        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G3__)

#if defined __NOTE_GsharpAb3__

/* G#Ab3 note frequency = 207.65Hz
 * Target sampling frequency: 4 * 207.65Hz = 830.61Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 301,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 301 = 830.56Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 301        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G#Ab3__)

#if defined __NOTE_A3__

/* A3 note frequency = 220.00Hz
 * Target sampling frequency: 4 * 220.00Hz = 880.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 284,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 284 = 880.28Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 284        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A3__)

#if defined __NOTE_Asharp3__ || defined __NOTE_Bb3__

/* A#/Bb3 note frequency = 233.08Hz
 * Target sampling frequency: 4 * 233.08Hz = 932.33Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 268 = 932.84Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A#/Bb3__)

#if defined __NOTE_B3__

/* B3 note frequency = 246.94Hz
 * Target sampling frequency: 4 * 246.94Hz = 987.77Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 337,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 337 = 989.12Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 337        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_B3__)

#if defined __NOTE_C4__

/* C4 note frequency = 261.63Hz
 * Target sampling frequency: 4 * 261.63Hz = 1046.50Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 319,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 319 = 1044.93Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 319        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C4__)

#if defined __NOTE_Csharp4__ || defined __NOTE_Db4__

/* C#/Db4 note frequency = 277.18Hz
 * Target sampling frequency: 4 * 277.18Hz = 1108.73Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 301,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 301 = 1107.42Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 301        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C#/Db4__)

#if defined __NOTE_D4__

/* D4 note frequency = 293.66Hz
 * Target sampling frequency: 4 * 293.66Hz = 1174.66Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 284,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 284 = 1173.71Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 284        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D4__)

#if defined __NOTE_Dsharp4__ || defined __NOTE_Eb4__

/* D#/Eb4 note frequency = 311.13Hz
 * Target sampling frequency: 4 * 311.13Hz = 1244.51Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 268 = 1243.78Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D#/Eb4__)

#if defined __NOTE_E4__

/* E4 note frequency = 329.63Hz
 * Target sampling frequency: 4 * 329.63Hz = 1318.51Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 379,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 379 = 1319.26Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 379        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_E4__)

#if defined __NOTE_F4__

/* F4 note frequency = 349.23Hz
 * Target sampling frequency: 4 * 349.23Hz = 1396.91Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 358,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 358 = 1396.65Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 358        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F4__)

#if defined __NOTE_Fsharp4__ || defined __NOTE_Gb4__

/* F#/Gb4 note frequency = 369.99Hz
 * Target sampling frequency: 4 * 369.99Hz = 1479.98Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 338,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 338 = 1479.29Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 338        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F#/Gb4__)

#if defined __NOTE_G4__

/* G4 note frequency = 392.00Hz
 * Target sampling frequency: 4 * 392.00Hz = 1567.98Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 319,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 319 = 1567.40Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 319        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G4__)

#if defined __NOTE_GsharpAb4__

/* G#Ab4 note frequency = 415.30Hz
 * Target sampling frequency: 4 * 415.30Hz = 1661.22Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 301,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 301 = 1661.13Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 301        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G#Ab4__)

#if defined __NOTE_A4__

/* A4 note frequency = 440.00Hz
 * Target sampling frequency: 4 * 440.00Hz = 1760.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 284,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 284 = 1760.56Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 284        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A4__)

#if defined __NOTE_Asharp4__ || defined __NOTE_Bb4__

/* A#/Bb4 note frequency = 466.16Hz
 * Target sampling frequency: 4 * 466.16Hz = 1864.66Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 268 = 1865.67Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A#/Bb4__)

#if defined __NOTE_B4__

/* B4 note frequency = 493.88Hz
 * Target sampling frequency: 4 * 493.88Hz = 1975.53Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 506,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 506 = 1976.28Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 506        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_B4__)

#if defined __NOTE_C5__

/* C5 note frequency = 523.25Hz
 * Target sampling frequency: 4 * 523.25Hz = 2093.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 478,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 478 = 2092.05Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 478        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C5__)

#if defined __NOTE_Csharp5__ || defined __NOTE_Db5__

/* C#/Db5 note frequency = 554.37Hz
 * Target sampling frequency: 4 * 554.37Hz = 2217.46Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 451,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 451 = 2217.29Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 451        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_C#/Db5__)

#if defined __NOTE_D5__

/* D5 note frequency = 587.33Hz
 * Target sampling frequency: 4 * 587.33Hz = 2349.32Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 426,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 426 = 2347.42Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 426        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D5__)

#if defined __NOTE_Dsharp5__ || defined __NOTE_Eb5__

/* D#/Eb5 note frequency = 622.25Hz
 * Target sampling frequency: 4 * 622.25Hz = 2489.02Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 402,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 402 = 2487.56Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 402        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_D#/Eb5__)

#if defined __NOTE_E5__

/* E5 note frequency = 659.26Hz
 * Target sampling frequency: 4 * 659.26Hz = 2637.02Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 379,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 379 = 2638.52Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 379        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_E5__)

#if defined __NOTE_F5__

/* F5 note frequency = 698.46Hz
 * Target sampling frequency: 4 * 698.46Hz = 2793.83Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 358,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 358 = 2793.30Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 358        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F5__)

#if defined __NOTE_Fsharp5__ || defined __NOTE_Gb5__

/* F#/Gb5 note frequency = 739.99Hz
 * Target sampling frequency: 4 * 739.99Hz = 2959.96Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 338,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 338 = 2958.58Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 338        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_F#/Gb5__)

#if defined __NOTE_G5__

/* G5 note frequency = 783.99Hz
 * Target sampling frequency: 4 * 783.99Hz = 3135.96Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 319,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 319 = 3134.80Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 319        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G5__)

#if defined __NOTE_GsharpAb5__

/* G#Ab5 note frequency = 830.61Hz
 * Target sampling frequency: 4 * 830.61Hz = 3322.44Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 301,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 301 = 3322.26Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 301        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_G#Ab5__)

#if defined __NOTE_A5__

/* A5 note frequency = 880.00Hz
 * Target sampling frequency: 4 * 880.00Hz = 3520.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 284,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 284 = 3521.13Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 284        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A5__)

#if defined __NOTE_Asharp5__ || defined __NOTE_Bb5__

/* A#/Bb5 note frequency = 932.33Hz
 * Target sampling frequency: 4 * 932.33Hz = 3729.31Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 268,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 268 = 3731.34Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 268        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_A#/Bb5__)

#if defined __NOTE_B5__

/* B5 note frequency = 987.77Hz
 * Target sampling frequency: 4 * 987.77Hz = 3951.07Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 253 = 3952.57Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define N_CYCLES_SUMMED_16b 32
#define CYCLE_SUM_ARRAY_LEN 4
#define CYCLE_SUM_RIGHTSHIFT 8

#endif // (#ifdef __NOTE_B5__)

