# Signal sampling configurator

I'm not awesome at Python, but hopefully this is easy enough to follow. In globalConstants.py set parameters particular to your microcontroller of choice: the sampling timer's base frequency and max prescaler/postscaler/period.

You can also change NUM_PERIODS_SUMMED to make the DFT filter more or less selective in what frequencies it filters out. Fewer periods summed means faster response times (more noticeable for lower frequencies), but a wider notch filter.

Running the script generates SamplingParams.h, which you can then copy into your firmware source files.

NOTE: the PIC18's prescaler/postscaler are arranged such that the prescaler is in powers of 2, while the postscaler is integers between 1 - 16. You'll have to change this arrangement somewhere around lines 32-43 of samplingParams.py.