# Microcontroller parameters
PIC18F_TIMER_MAX_POSTSCALE = 16
PIC18F_TIMER_MAX_PRESCALE = 3        # max prescaler is 2^3 = 8
PIC18F_TIMER_MAX_PERIOD = 256
PIC18F_BASE_TIMER_FREQ = 1e6
# Note: the PIC18 timer sources are:
#       HFINT = 1e6Hz
#       MFINT = 31.25kHz or 500kHz (HFINT divided by 2 or 32)
#       LFINT = 31kHz

# Sampling parameters
RELATIVE_FSAMP = 4      # this is critical for implementing a computationally simple single-bin DFT
NUM_PERIODS_SUMMED = 64     # number of periods (of the target frequency) evaluated in the DFT

# Task intervals
LED_REFRESH_RATE = 30  # in Hz
WAKE_TEST_SAMPLING_PERIOD = 0.1 # in seconds. Approximate period of time the signal is evaluated to see if the
                                # amplitude is above some minimum threshold, below which the controller
                                # enters deep sleep mode