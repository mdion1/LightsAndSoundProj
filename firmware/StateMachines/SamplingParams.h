#pragma once

#if defined __NOTE_C2__

/* C2 note frequency = 65.41Hz
 * Target sampling frequency: 4 * 65.41Hz = 261.63Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:15, and period of 255,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 15 / 255 = 261.44Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 15      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 255        //sampling period = N+1
#define LED_REFRESH_INTERVAL 8  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 28  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C2__)

#if defined __NOTE_Csharp2__ || defined __NOTE_Db2__

/* C#/Db2 note frequency = 69.30Hz
 * Target sampling frequency: 4 * 69.30Hz = 277.18Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:15, and period of 241,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 15 / 241 = 276.63Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 15      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 241        //sampling period = N+1
#define LED_REFRESH_INTERVAL 8  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 28  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C#/Db2__)

#if defined __NOTE_D2__

/* D2 note frequency = 73.42Hz
 * Target sampling frequency: 4 * 73.42Hz = 293.66Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:14, and period of 243,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 14 / 243 = 293.94Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 14      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 243        //sampling period = N+1
#define LED_REFRESH_INTERVAL 8  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 28  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D2__)

#if defined __NOTE_Dsharp2__ || defined __NOTE_Eb2__

/* D#/Eb2 note frequency = 77.78Hz
 * Target sampling frequency: 4 * 77.78Hz = 311.13Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:13, and period of 247,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 13 / 247 = 311.43Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 13      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 247        //sampling period = N+1
#define LED_REFRESH_INTERVAL 12  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 32  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D#/Eb2__)

#if defined __NOTE_E2__

/* E2 note frequency = 82.41Hz
 * Target sampling frequency: 4 * 82.41Hz = 329.63Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:12, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 12 / 253 = 329.38Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 12      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 12  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 32  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_E2__)

#if defined __NOTE_F2__

/* F2 note frequency = 87.31Hz
 * Target sampling frequency: 4 * 87.31Hz = 349.23Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:12, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 12 / 239 = 348.68Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 12      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 12  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 36  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F2__)

#if defined __NOTE_Fsharp2__ || defined __NOTE_Gb2__

/* F#/Gb2 note frequency = 92.50Hz
 * Target sampling frequency: 4 * 92.50Hz = 369.99Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:11, and period of 246,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 11 / 246 = 369.55Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 11      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 246        //sampling period = N+1
#define LED_REFRESH_INTERVAL 12  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 36  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F#/Gb2__)

#if defined __NOTE_G2__

/* G2 note frequency = 98.00Hz
 * Target sampling frequency: 4 * 98.00Hz = 392.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:10, and period of 255,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 10 / 255 = 392.16Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 10      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 255        //sampling period = N+1
#define LED_REFRESH_INTERVAL 12  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 40  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G2__)

#if defined __NOTE_GsharpAb2__

/* G#Ab2 note frequency = 103.83Hz
 * Target sampling frequency: 4 * 103.83Hz = 415.30Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:10, and period of 241,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 10 / 241 = 414.94Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 10      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 241        //sampling period = N+1
#define LED_REFRESH_INTERVAL 12  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 40  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G#Ab2__)

#if defined __NOTE_A2__

/* A2 note frequency = 110.00Hz
 * Target sampling frequency: 4 * 110.00Hz = 440.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:9, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 9 / 253 = 439.17Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 9      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 16  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 44  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A2__)

#if defined __NOTE_Asharp2__ || defined __NOTE_Bb2__

/* A#/Bb2 note frequency = 116.54Hz
 * Target sampling frequency: 4 * 116.54Hz = 466.16Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:9, and period of 238,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 9 / 238 = 466.85Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 9      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 238        //sampling period = N+1
#define LED_REFRESH_INTERVAL 16  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 48  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A#/Bb2__)

#if defined __NOTE_B2__

/* B2 note frequency = 123.47Hz
 * Target sampling frequency: 4 * 123.47Hz = 493.88Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:8, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 8 / 253 = 494.07Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 8      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 16  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 48  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_B2__)

#if defined __NOTE_C3__

/* C3 note frequency = 130.81Hz
 * Target sampling frequency: 4 * 130.81Hz = 523.25Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:8, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 8 / 239 = 523.01Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 8      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 16  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 52  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C3__)

#if defined __NOTE_Csharp3__ || defined __NOTE_Db3__

/* C#/Db3 note frequency = 138.59Hz
 * Target sampling frequency: 4 * 138.59Hz = 554.37Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:8, and period of 225,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 8 / 225 = 555.56Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 8      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 225        //sampling period = N+1
#define LED_REFRESH_INTERVAL 20  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 56  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C#/Db3__)

#if defined __NOTE_D3__

/* D3 note frequency = 146.83Hz
 * Target sampling frequency: 4 * 146.83Hz = 587.33Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:7, and period of 243,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 7 / 243 = 587.89Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 7      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 243        //sampling period = N+1
#define LED_REFRESH_INTERVAL 20  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 60  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D3__)

#if defined __NOTE_Dsharp3__ || defined __NOTE_Eb3__

/* D#/Eb3 note frequency = 155.56Hz
 * Target sampling frequency: 4 * 155.56Hz = 622.25Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:7, and period of 230,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 7 / 230 = 621.12Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 7      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 230        //sampling period = N+1
#define LED_REFRESH_INTERVAL 20  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 64  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D#/Eb3__)

#if defined __NOTE_E3__

/* E3 note frequency = 164.81Hz
 * Target sampling frequency: 4 * 164.81Hz = 659.26Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:6, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 6 / 253 = 658.76Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 6      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 20  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 64  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_E3__)

#if defined __NOTE_F3__

/* F3 note frequency = 174.61Hz
 * Target sampling frequency: 4 * 174.61Hz = 698.46Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:6, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 6 / 239 = 697.35Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 6      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 24  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 68  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F3__)

#if defined __NOTE_Fsharp3__ || defined __NOTE_Gb3__

/* F#/Gb3 note frequency = 185.00Hz
 * Target sampling frequency: 4 * 185.00Hz = 739.99Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:6, and period of 225,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 6 / 225 = 740.74Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 6      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 225        //sampling period = N+1
#define LED_REFRESH_INTERVAL 24  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 72  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F#/Gb3__)

#if defined __NOTE_G3__

/* G3 note frequency = 196.00Hz
 * Target sampling frequency: 4 * 196.00Hz = 783.99Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 255,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 255 = 784.31Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 255        //sampling period = N+1
#define LED_REFRESH_INTERVAL 28  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 80  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G3__)

#if defined __NOTE_GsharpAb3__

/* G#Ab3 note frequency = 207.65Hz
 * Target sampling frequency: 4 * 207.65Hz = 830.61Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 241,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 241 = 829.88Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 241        //sampling period = N+1
#define LED_REFRESH_INTERVAL 28  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 84  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G#Ab3__)

#if defined __NOTE_A3__

/* A3 note frequency = 220.00Hz
 * Target sampling frequency: 4 * 220.00Hz = 880.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 227,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 227 = 881.06Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 227        //sampling period = N+1
#define LED_REFRESH_INTERVAL 28  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 88  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A3__)

#if defined __NOTE_Asharp3__ || defined __NOTE_Bb3__

/* A#/Bb3 note frequency = 233.08Hz
 * Target sampling frequency: 4 * 233.08Hz = 932.33Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:5, and period of 215,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 5 / 215 = 930.23Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 5      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 215        //sampling period = N+1
#define LED_REFRESH_INTERVAL 32  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 92  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A#/Bb3__)

#if defined __NOTE_B3__

/* B3 note frequency = 246.94Hz
 * Target sampling frequency: 4 * 246.94Hz = 987.77Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 253 = 988.14Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 32  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 100  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_B3__)

#if defined __NOTE_C4__

/* C4 note frequency = 261.63Hz
 * Target sampling frequency: 4 * 261.63Hz = 1046.50Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 239 = 1046.03Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 36  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 104  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C4__)

#if defined __NOTE_Csharp4__ || defined __NOTE_Db4__

/* C#/Db4 note frequency = 277.18Hz
 * Target sampling frequency: 4 * 277.18Hz = 1108.73Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 225,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 225 = 1111.11Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 225        //sampling period = N+1
#define LED_REFRESH_INTERVAL 36  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 112  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C#/Db4__)

#if defined __NOTE_D4__

/* D4 note frequency = 293.66Hz
 * Target sampling frequency: 4 * 293.66Hz = 1174.66Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 213,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 213 = 1173.71Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 213        //sampling period = N+1
#define LED_REFRESH_INTERVAL 40  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 116  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D4__)

#if defined __NOTE_Dsharp4__ || defined __NOTE_Eb4__

/* D#/Eb4 note frequency = 311.13Hz
 * Target sampling frequency: 4 * 311.13Hz = 1244.51Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:4, and period of 201,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 4 / 201 = 1243.78Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 4      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 201        //sampling period = N+1
#define LED_REFRESH_INTERVAL 40  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 124  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D#/Eb4__)

#if defined __NOTE_E4__

/* E4 note frequency = 329.63Hz
 * Target sampling frequency: 4 * 329.63Hz = 1318.51Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 253 = 1317.52Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 44  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 132  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_E4__)

#if defined __NOTE_F4__

/* F4 note frequency = 349.23Hz
 * Target sampling frequency: 4 * 349.23Hz = 1396.91Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 239 = 1394.70Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 48  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 140  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F4__)

#if defined __NOTE_Fsharp4__ || defined __NOTE_Gb4__

/* F#/Gb4 note frequency = 369.99Hz
 * Target sampling frequency: 4 * 369.99Hz = 1479.98Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 225,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 225 = 1481.48Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 225        //sampling period = N+1
#define LED_REFRESH_INTERVAL 48  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 148  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F#/Gb4__)

#if defined __NOTE_G4__

/* G4 note frequency = 392.00Hz
 * Target sampling frequency: 4 * 392.00Hz = 1567.98Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 213,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 213 = 1564.95Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 213        //sampling period = N+1
#define LED_REFRESH_INTERVAL 52  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 156  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G4__)

#if defined __NOTE_GsharpAb4__

/* G#Ab4 note frequency = 415.30Hz
 * Target sampling frequency: 4 * 415.30Hz = 1661.22Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 201,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 201 = 1658.37Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 201        //sampling period = N+1
#define LED_REFRESH_INTERVAL 56  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 168  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G#Ab4__)

#if defined __NOTE_A4__

/* A4 note frequency = 440.00Hz
 * Target sampling frequency: 4 * 440.00Hz = 1760.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 189,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 189 = 1763.67Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 189        //sampling period = N+1
#define LED_REFRESH_INTERVAL 60  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 176  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A4__)

#if defined __NOTE_Asharp4__ || defined __NOTE_Bb4__

/* A#/Bb4 note frequency = 466.16Hz
 * Target sampling frequency: 4 * 466.16Hz = 1864.66Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:3, and period of 179,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 3 / 179 = 1862.20Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 3      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 179        //sampling period = N+1
#define LED_REFRESH_INTERVAL 64  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 188  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A#/Bb4__)

#if defined __NOTE_B4__

/* B4 note frequency = 493.88Hz
 * Target sampling frequency: 4 * 493.88Hz = 1975.53Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 253,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 253 = 1976.28Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 253        //sampling period = N+1
#define LED_REFRESH_INTERVAL 64  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 196  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_B4__)

#if defined __NOTE_C5__

/* C5 note frequency = 523.25Hz
 * Target sampling frequency: 4 * 523.25Hz = 2093.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 239 = 2092.05Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 68  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 208  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C5__)

#if defined __NOTE_Csharp5__ || defined __NOTE_Db5__

/* C#/Db5 note frequency = 554.37Hz
 * Target sampling frequency: 4 * 554.37Hz = 2217.46Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 225,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 225 = 2222.22Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 225        //sampling period = N+1
#define LED_REFRESH_INTERVAL 72  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 220  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C#/Db5__)

#if defined __NOTE_D5__

/* D5 note frequency = 587.33Hz
 * Target sampling frequency: 4 * 587.33Hz = 2349.32Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 213,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 213 = 2347.42Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 213        //sampling period = N+1
#define LED_REFRESH_INTERVAL 80  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 236  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D5__)

#if defined __NOTE_Dsharp5__ || defined __NOTE_Eb5__

/* D#/Eb5 note frequency = 622.25Hz
 * Target sampling frequency: 4 * 622.25Hz = 2489.02Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 201,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 201 = 2487.56Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 201        //sampling period = N+1
#define LED_REFRESH_INTERVAL 84  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 248  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_D#/Eb5__)

#if defined __NOTE_E5__

/* E5 note frequency = 659.26Hz
 * Target sampling frequency: 4 * 659.26Hz = 2637.02Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 190,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 190 = 2631.58Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 190        //sampling period = N+1
#define LED_REFRESH_INTERVAL 88  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_E5__)

#if defined __NOTE_F5__

/* F5 note frequency = 698.46Hz
 * Target sampling frequency: 4 * 698.46Hz = 2793.83Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 179,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 179 = 2793.30Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 179        //sampling period = N+1
#define LED_REFRESH_INTERVAL 92  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F5__)

#if defined __NOTE_Fsharp5__ || defined __NOTE_Gb5__

/* F#/Gb5 note frequency = 739.99Hz
 * Target sampling frequency: 4 * 739.99Hz = 2959.96Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 169,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 169 = 2958.58Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 169        //sampling period = N+1
#define LED_REFRESH_INTERVAL 100  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_F#/Gb5__)

#if defined __NOTE_G5__

/* G5 note frequency = 783.99Hz
 * Target sampling frequency: 4 * 783.99Hz = 3135.96Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 159,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 159 = 3144.65Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 159        //sampling period = N+1
#define LED_REFRESH_INTERVAL 104  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G5__)

#if defined __NOTE_GsharpAb5__

/* G#Ab5 note frequency = 830.61Hz
 * Target sampling frequency: 4 * 830.61Hz = 3322.44Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 150,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 150 = 3333.33Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 150        //sampling period = N+1
#define LED_REFRESH_INTERVAL 112  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_G#Ab5__)

#if defined __NOTE_A5__

/* A5 note frequency = 880.00Hz
 * Target sampling frequency: 4 * 880.00Hz = 3520.00Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 142,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 142 = 3521.13Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 142        //sampling period = N+1
#define LED_REFRESH_INTERVAL 116  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_A5__)

#if defined __NOTE_Asharp5__ || defined __NOTE_Bb5__

/* A#/Bb5 note frequency = 932.33Hz
 * Target sampling frequency: 4 * 932.33Hz = 3729.31Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:2, and period of 134,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 2 / 134 = 3731.34Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 2      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 134        //sampling period = N+1
#define LED_REFRESH_INTERVAL 124  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

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
#define LED_REFRESH_INTERVAL 132  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_B5__)

#if defined __NOTE_C6__

/* C6 note frequency = 1046.50Hz
 * Target sampling frequency: 4 * 1046.50Hz = 4186.01Hz
 * With a sampling timer clock prescaler of 1:1, postscaler of 1:1, and period of 239,
 * the actual sampling frequency is
 *      1.00E+06Hz / 1 / 1 / 239 = 4184.10Hz
 */

#define TSAMP_PRESCALER 0       //prescaler 1:(2^(N-1))
#define TSAMP_POSTSCALER 1      //postscaler 1:(N + 1)
#define TSAMP_PERIOD 239        //sampling period = N+1
#define LED_REFRESH_INTERVAL 140  // Number of ADC samples per LED update calculation
#define SLEEP_TASKS_UPDATE_INTERVAL 255  // Number of ADC samples evaluated in sleep tasks calculation

#endif // (#ifdef __NOTE_C6__)
