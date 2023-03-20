# Single-bin DFT Design Script

This is a simple script for plotting the approximate selectivity of the DFT filter. To run the script, set the appropriate factors in under "SCRIPT INPUTS" (I'm not awesome at Python). TARGET_FREQUENCY is not important unless you're appending the optional single-pole low-pass and high-pass filters onto the transfer function. RELATIVE_FSAMP should be left at 4 unless you're planning on implementing trig/float math into your DFT implementation.

The important parameter is NUM_CYCLES_SAMPLED, which will make your filter narrower or wider. Too high, and your filter will respond more slowly (more noticeable at low frequencies). It's also important to note that if your microcontroller's oscillator is only accurate to 1-2%, it will be off by an eight-tone anyway...

The script outputs a matplotlib figure. The y-axis is in decibels, normalized to the filter center frequency. The x-axis is in chromatic half-steps (musical tones spaced by a factor of 2^(1/12) = 1.059).