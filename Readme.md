# Project Inspiration
At a local art convention I met someone selling outdoor lamps consisting of used bottles with LED string lights powered off of small solar cells. The solar-powered string lights were purchased in bulk from an online seller, allowing this artist to focus on her project's aesthetics without having to worry about circuitry.

I wanted to make a kit with the same design spirit: something low-cost, low-power, that could be ordered in bulk, that just worked out of the box, that an artist could play with as they wished. I wanted to make something responsive to the environment: in this case, ambient sound. I'm imagining arrays of these small PCB's, decorated, housed, or otherwise embedded into some workpiece, lighting up in synchrony with songs or speech.

My goal is to sell batches (maybe in "octaves") of these devices online at cost, once I get the unit cost down a little bit more.

# Hardware Overview
The PCB is a 2-layer circle with a 25mm diameter. One side holds the (electret condenser) microphone and the RGB LED. The other side holds the analog filter/gain stage, microcontroller, and the coin cell holder, which covers most of the other components. Low-cost, electret condenser mics consume current in the ~100's of uA, so the entire analog front end can be powered down during sleep mode and periodically turned on to sample for the target frequency.

I chose an electret condenser mic because they were slightly cheaper than MEMs microphones. However, they can be interchanged, and if I find a similarly-priced MEMs with lower power consumption, I will probably do so. For MEMs microphones with pulse-density modulation, some extra filtering might be needed on the front end of the analog gain stage.

I've designed a batch programming board with alignment pins and pogo pins for flashing the embedded code to each board. I intend to make a small enclosure/jig for this board to make the process smoother. This board serves only as a break-out board for an ICSP header.

# Firmware Overview
For more detailed notes on the firmware, see firmware/Readme.md.

The firmware implements an ADC sampling scheme that allows for simple single-bin DFT processing. By sampling at 4 times the frequency of interest, you can calculate a DFT with simple addition and subtraction, no any trig functions or float math needed. Once the real/imaginary terms are accumulated from the raw sample values, I pow() and log() implemented with integer math and lookup tables to bypass having to use sqrt() or any floating point multiplication/division.

The calculated signal amplitude is used to determine the PWM values driving the LED's. The color is picked with a random number generator using a hue/saturation/value color scheme, and the RBG values are calculated with an HSV-to-RBG module that uses only 8- and 16-bit integer math. At periodic intervals, the color is "ramped" to another randomly chosen hue/saturation, while value (brightness) is locked to the sound amplitude.

If the sound amplitude is below a certain threshold for too long, the device enters sleep mode. It periodically wakes up to sample audio. One of my work-in-progress tasks is determining appropriate threshold levels (which will vary across target audio frequencies) and appropriate timing to wake the device to poll ambient sound. The challenge is finding the right balances between power consumption and device responsiveness, and volume sensitivity.

# Design Files Overview 
This Github repository contains the following:
- The sub-repository named "NoteDector_PCBA" (at https://github.com/mdion1/NoteDector_PCBA) holds the KiCAD design files for the schematics and board layout. This includes both the main board and the batch programming breakout board.
- The folder titled "Simulations" holds an LTSpice model for the analog front end.
- The gain stage consists of a high-pass filter input into an opamp stage that uses a "Tee configuration," which you can read about in this application note from Texas Instruments: https://www.ti.com/lit/an/sboa284/sboa284.pdf
- The opamp gain circuit has a nominal DC gain of 63dB, but filtering components and opamp gain-bandwidth limits the actual gain depending on the input frequency. There are two versions of the BOM, one with passive filter components best for notes below middle C (65 - 262Hz), and one for notes above middle C (262 - 1047Hz).
- "UsefulScripts" directory: I've included Python scripts that helped me design my firmware, both to show my work as well as to aid anyone who needs to tweak design parameters. Each script has its own Readme that you can refer to for more details.
	- "SignalSamplingConfigurator": Since each device is hard-coded to a separate audio frequency, I wrote a script to automatically generate the sampling parameters (timer intervals) needed for each chromatic tone in a 4-octave span. Running the script will output the file SamplingParams.h, which holds a series of #define's for each note. All you have to do to select a particular musical note is to define the note name when compiling the firmware.
	- "FastLogLookupTableGenerator": This shows how I generated the lookup tables for my integer-math log2/power2 functions
	- "DFTFilterDesign": plots the filter transfer function given DFT design parameters.
	- "HSVtoRGBtest": the messiest script in the directory, mainly there just to show my process in designing 8- and 16-bit integer-only functions for converting from Hue/Saturation/Value color format to RGB.
- The "Firmware" directory holds the source code as well as an MPLAB X project, since the current board revision uses a PIC18 (8-bit) microcontroller. To allow flexibility in microcontroller selection, the firmware is divided into "business logic" and "HAL interface" sections. All you have to do to use a different microcontroller is to implement the low-level functions defined in the HAL interface.

# Power Consumption
Battery life is heavily dependent on how often the device is in sleep mode, which depends on how low the audio threshold is configured in the firmware. In standby mode, current consumption is 16uA. According to the microcontroller datasheet, I should be able to operate in a lower-power sleep mode with a current draw of 1.5uA if I use the Watchdog Timer instead of the peripheral timer I'm using now. At 16uA standby current, it would take 1.4 years to consume a CR2032 cell's 200mAh capacity. With 1.5uA standby current, it would take over 15 years.

During active audio sampling, the PIC18 consumes ~700uA. The electret condenser microphone has a quiescent current draw of ~200uA. Each of the three LED's can consume up to 3mA. According to simulations and the opamp datasheet, the analog stage consumes somewhere in between 20-40uA.

So with the LED's consuming 1.5mA of their 3mA capacity, the total current consumption is roughly 2.5mA, which would consume a CR2032 cell's 200mAh capacity in 80 hours.

# Future Development/State of the Project
Current project state = jenky, but works. I have tested using a prototype board, but have not gotten to see a full array of these in action. My remaining tasks:
- Tweak the hard-coded sensitivity level for each of the audio frequencies
- Use the watchdog timer during sleep mode instead of the peripheral timer, in order to reduce standby power to 1.5uA.
- Order, assemble, and test the next board revision based on changes I've hacked onto the prototype
- Order, assembly, the batch programming PCB, and design an enclosure/jig to go with it.
- Source a cheaper microcontroller, now that I know how much RAM and flash I need.
- Source a cheaper microphone, possibly a MEM's with lower quiescent power consumption. For this I will probably have to go outside of Digikey and Mouser, as the availability of low cost microphones is limited.
- Source an LED diffuser. The light is a harsh point source, and I may want to offer diffusers built into the design.