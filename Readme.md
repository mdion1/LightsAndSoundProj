# Low Power, Low Cost, Sound-Responsive Lighting!

## Introduction

The purpose of this project was to create low-cost devices for art or music installations. Each individual device can be "tuned" (hard-coded) to any musical note between C2 (65.4Hz) and C6 (1046.5Hz), and when it detects that note via its onboard microphone, it exits sleep mode and lights up a tricolor LED. The brightness of the LED is proportional to the sound amplituded of the musical note. The color drifts slowly between randomized points on the color wheel.

Each device runs off of a CR2032 coin cell. The PCB is a 1-inch diameter circle. Current medium-quantity unit costs are ~$3.25 for the PCB, components, and assembly, not including the coin cell.

By programming several of these devices to different musical notes, you can make a lightup array that responds to music!

## Hardware Overview

The repository named "NoteDector_PCBA" holds the KiCAD design files for the schematics and board layout. The analog front-end consists of an electret condenser mic and a filter/gain stage. Low-cost, surface-mount electret condensers consume current in the ~100's of uA, so the entire analog front end can be powered down during sleep mode and periodically turned on to sample for the target frequency.

The folder titled "Simulations" holds an LTSpice model for the analog front end. I designed the circuit for a gain of 60dB, but right now I am only getting ~40dB... There are two versions of the BOM, one with passive filter components best for notes below middle C (65 - 262Hz), and one for notes above middle C (262 - 1047Hz).

An 8-bit PIC18 (running at 1MHz when not in sleep mode) samples the analog signal from the amplifier and performs a single-bin DFT to detect the sound amplitude of the desired note. It then applies the appropriate PWM pulses to the tricolor RGB LED according to the desired color and brightness. This calculation includes an HSV-to-RGB conversion designed for 8-bit integer math.

## Signal Sampling Configurator Script

The folder titled "SignalSamplingConfigurator" holds a python script for generating the sampling parameters (timer intervals) needed for each chromatic tone in the 4-octave scales covered. Running the script will output the file SamplingParams.h, which holds a series of #ifdef's for each note.

## Firmware Overview

To allow flexibility in microcontroller selection, the firmware is divided into "business logic" and "HAL interface" sections. The "business logic" section has 3 main state machines running task loops:
- SignalSampling module
- LEDManager module
- Sleep module

The timer-triggered ADC uses interrupts to move samples to a buffer. SigSamp_tasks() performs the single-bin DFT. LEDMgr_tasks() updates the brightness and color at a refresh rate of ~30Hz. Sleep_tasks() puts the microcontroller to sleep during sampling when no sampling processing is occuring. If the signal amplitude is below the hard-coded threshold for a specified amount of time, the microphone and gain stage are shut down, and the microcontroller sleeps. It periodically wakes and enables the mic/amp to check sound levels. The sleep interval gradually increases from ~10ms to ~6seconds if the note amplitude remains below the threshold.

The HAL interface controls the sleep and sampling timers, the ADC, the low-power features, and the PWM module for driving the LED's.

The repository also includes an MPLAB X project named "PIC18build.X."