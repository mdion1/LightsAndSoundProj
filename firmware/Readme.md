# Firmware Overview

To allow flexibility in microcontroller selection, the firmware is divided into "business logic" and "HAL interface" sections. The HAL interface controls the sleep and sampling timers, the ADC, the low-power features, and the PWM module for driving the LED's. The "business logic" section has 3 main state machines running task loops:
- SignalSampling module
- LEDManager module
- Sleep module

## SignalSampling.c/.h

The timer-triggered ADC uses interrupts to move samples to a buffer. HAL_ADC.h is used to set up the ADC timing and interrupt-driven buffer transfers. The main while-loop calls SigSamp_tasks() to performs the single-bin DFT as samples fill up the buffer. The raw sample buffer holds 256 samples, enough for 64 full "cycles" of the target frequency. Once the buffer fills, samples are thrown away until the main software thread completely processes every sample in the buffer. There is no real-time processing requirement, as long as the amplitude can be calculated fast enough to keep up with the target "framerate" (LED update rate). For lower frequencies/slower sampling rates the software will keep up with sampling, and will sleep between samples and wake on the ADC interrupt.

The results of the DFT are smoothed using a windowed average (using the HelperClasses/WindowAvg.c/.h "class"): every 4-sample real/imaginary accumulation is pushed to a buffer, and a simple moving average FIR filter is used to evaluate the sums of the last 256 samples/64 cycles.

*Side note: The filter also tracks the number of valid samples, in order to accommodate the "empty" buffer state when the device wakes from sleep. That way the signal ampltiude can be determined without waiting for it to "roll up" to the full-scale value as the buffer fills. See the numCycles input argument to the function AmpToBrightness().*

The index of the latest sample processed acts as a "timestamp" for the Sleep and LEDManager modules to loosely enforce the timing of the LED refresh rate.

## LEDManager.c/.h
LEDMgr_tasks() updates the brightness and color at a targeted refresh rate of ~30Hz. The SignalSampleConfigurator script determines how many samples warrants an LED brightness/color refresh. The module grabs two random 8-bit integers (using a linear feedback shift register seeded with noise from the ADC, see HelperClasses/RNG.c/.h) to use for the color hue and saturation. A "ramp" is executed from the current color value to the target color value using the LinearRamp "class" (see HelperClases/LinearRamp.c/.h). The ramp duration is 128 refresh cycles (~4 seconds for a 30Hz update rate), after which a new random color is chosen.

The HSV color space "value" parameter (aka brightness) is scaled from the audio amplitude (calculated using the AmpToBrightness() in HelperClasses/AmpScalingMath.c/.h). There is an optional exponential filter used to smooth the latest brightness values (*see the static function LPF_pushVal()*). In conjunction with the current hue and saturation (from the LinearRamp state), the RGB values are calculated with the function HSVtoRGB(). These are fed directly to the HAL_PWM module.

*Side note: HSVtoRGB() is implemented using integer-only math, see the UsefulScripts/HSVtoRGBtest directory for a rough documentation/scratch work for the development of this function.*

## Sleep.c/.h
The Sleep module decides when to put the microcontroller to sleep, and for how long. During active signal sampling, every call to Sleep_tasks() will put the microcontroller to sleep, to be woken up by the ADC interrupt. Then at fixed intervals the module will evaluate if the audio amplitude is below a hard-coded threshold. If this the signal is below the threshold for long enough, the module will shut down the analog gain stage, the microphone, and all peripherals and enter a low-power sleep mode. Upon waking from this sleep using a peripheral timer trigger, the gain stage and mic are powered back on and the signal is sampled again.

The business logic of this sleep mode control is an ongoing piece of development. The current logic (which I am not satisfied with) starts with a low-power sleep intervals of 100ms, and then subsequently doubles it if subsequent polling does not detect audio amplitude above the threshold, to a maximum sleep interval of 6.4 seconds.

The repository also includes an MPLAB X project named "PIC18build.X." As of Mar 20 2023, I have not added project configurations for every note configuration.