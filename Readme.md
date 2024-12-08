Check out the prototype demos at https://imgur.com/gallery/lpTmvMc

# Project Summary
This project outlines the hardware and embedded software design of a coin-cell powered circuit that samples ambient sound and lights up a tricolor LED when a specific musical note is detected. The LED color randomly changes over time, and the brightness of the LED is proportional to volume detected at the specified note frequency.

# Project Inspiration
At a local art convention I met someone selling outdoor lamps consisting of used bottles with LED string lights powered off of small solar cells. The solar-powered string lights were purchased in bulk from an online seller, allowing this artist to focus on her project's aesthetics without having to worry about circuitry.

I wanted to design a kit in the same spirit: something low-cost, low-power, ordered in bulk, "just works" out of the box, that an artist can use without any technical knowledge. I also wanted to make something responsive to the environment: in this case, ambient sound.

I imagine a scenario in which of dozens of these devices are decorated, housed, or otherwise embedded into some workpiece, lighting up in synchrony with songs or speech.

My goal is to sell batches of these devices online at cost (maybe grouped by musical octaves), once I get the unit price down a little bit more.

# Hardware Overview
The 2-layer circular PCB has a 25mm diameter. One side holds the (electret condenser) microphone and the RGB LED. The other side holds the analog filter/gain stage, microcontroller, and the coin cell holder, which covers most of the other components. Low-cost, electret condenser mics consume current in the ~100's of uA, so the entire analog front end is powered down during sleep mode and periodically turned on to sample for the target frequency.

I chose an electret condenser mic because they were slightly cheaper than MEMS microphones. However, they can be interchanged, and if I find a similarly-priced MEMS with lower power consumption, I will probably do so. For MEMS microphones with pulse-density modulation output, some extra filtering will be needed on the front end of the analog gain stage.

I've designed a batch programming board with alignment pins and pogo pins for flashing the embedded code to each board. I intend to make a small enclosure/jig for this board to streamline the process. This board serves only as a break-out board for the programming header.

# Firmware Overview
For more detailed notes on the firmware, see firmware/Readme.md.

The firmware implements an ADC sampling scheme that allows for simple single-bin DFT processing. By sampling at 4 times the frequency of interest, you can calculate a DFT with simple addition and subtraction, no trig functions or floating point math needed. Once the real/imaginary terms are accumulated from the raw sample values, I use pow() and log() implemented with integer math and lookup tables to bypass having to use sqrt() or any floating point multiplication/division.

The calculated signal amplitude is used to determine the PWM values driving the LED's. The color is picked with a random number generator using a hue/saturation/value color scheme, and the RGB values are calculated with an HSV-to-RBG module that uses only 8- and 16-bit integer math. The color is slowly "ramped" to another randomly chosen hue/saturation, while value (brightness) is locked to the sound amplitude.

If the sound amplitude is below a certain threshold for too long, the device enters sleep mode. It periodically wakes up to sample audio. One of my work-in-progress tasks is determining appropriate threshold levels (which will vary across target audio frequencies) and appropriate timing to wake the device to poll ambient sound. The challenge is finding the right balances between power consumption, device responsiveness, and volume sensitivity.

# Design Files Overview 
This Github repository contains the following:
- The sub-repository named "NoteDector_PCBA" (at https://github.com/mdion1/NoteDector_PCBA) holds the KiCAD design files for the schematics and board layout. This includes both the main board and the batch programming breakout board.
- The folder titled "Simulations" holds an LTSpice model for the analog front end.
	- The gain stage consists of a high-pass filter input into an opamp stage that uses a "Tee configuration," which you can read about in this application note from Texas Instruments: https://www.ti.com/lit/an/sboa284/sboa284.pdf
	- The opamp circuit has a nominal DC gain of 63dB, but filtering components and opamp gain-bandwidth limits the actual gain depending on the input frequency. There are two versions of the BOM, one with passive filter components best for notes below middle C (65 - 262Hz), and one for notes above middle C (262 - 1047Hz).
- "UsefulScripts" directory: I've included Python scripts that helped me design my firmware, both to show my work as well as to aid anyone who needs to tweak design parameters. Each script has its own Readme that you can refer to for more details.
	- "SignalSamplingConfigurator": Since each device is hard-coded to a separate audio frequency, I wrote a script to automatically generate the sampling parameters (timer intervals) needed for each chromatic tone in a 4-octave span. Running the script will output the file SamplingParams.h, which holds a series of #define's for each note. All you have to do to select a particular musical note is to define a macro with the note name during firmware compilation.
	- "FastLogLookupTableGenerator": This shows how I generated the lookup tables for my integer-math log2/power2 functions.
	- "DFTFilterDesign": This plots the filter transfer function given the DFT design parameters as inputs.
	- "HSVtoRGBtest": The messiest script in the directory, mainly there just to show my process in designing 8- and 16-bit integer-only math for converting from Hue/Saturation/Value color format to RGB.
- The "Firmware" directory holds the embedded source code as well as an MPLAB X project, since the current board revision uses a PIC18 (8-bit) microcontroller. To allow flexibility in microcontroller selection, the firmware is divided into "business logic" and "HAL interface" sections. All you have to do to use a different microcontroller is to implement the low-level functions defined in the HAL interface.

# Power Consumption
Battery life is heavily dependent on how often the device is in sleep mode, which depends on how low the audio threshold is configured in the firmware. In standby mode, current consumption is 16uA. According to the microcontroller datasheet, I should be able to operate in a lower-power sleep mode with a current draw of 1.5uA. An ongoing development task is to find the discrepancy between my theoretical and actual sleep power consumption.

At 16uA standby current, it would take 1.4 years to consume a CR2032 cell's 200mAh capacity. With 1.5uA standby current, it would take over 15 years.

During active audio sampling, the PIC18 (operating at a clock frequency of 1MHz) consumes ~700uA. The electret condenser microphone has a quiescent current draw of ~200uA. Each of the three LED's can consume up to 3mA. According to simulations and the opamp datasheet, the analog stage consumes about 60uA.

So with the LED's consuming 1.5mA of their 3mA capacity, the total current consumption is roughly 2.5mA, which would consume a CR2032 cell's 200mAh capacity in 80 hours. As a result, battery lifespan will be highly situationally-dependent: 80 "useful" working hours, with potentially years of standby life.

# Future Development/State of the Project
Current project state = jenky, but works. I have tested using a prototype board (see the videos posted on Imgur!), but have not gotten to see a full array of these in action. My remaining tasks:

- Tweak the hard-coded sensitivity level for each of the audio frequencies
- Use the watchdog timer during sleep mode instead of the peripheral timer, in order to reduce standby power to 1.5uA.
- Order, assemble, and test the next board revision based on changes I've hacked onto the prototype
- Order, assemble, the batch programming PCB, and design an enclosure/jig to go with it.
- Source a cheaper microcontroller, now that I know how much RAM and flash I need.
- Source a cheaper microphone, possibly a MEM's with lower quiescent power consumption. For this I will probably have to go outside of Digikey and Mouser, as the availability of low cost microphones is limited.
- Source an LED diffuser. The light is a harsh point source, and I may want to offer diffusers built into the design.