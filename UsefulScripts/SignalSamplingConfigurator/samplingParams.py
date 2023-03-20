import math
import numpy as np
from Note import Note
from globalConstants import *

class samplingParams:
    def __init__(self, note: Note):

        self.note = note
        self.FSampRel = RELATIVE_FSAMP
        self.NCyclesSampled = NUM_PERIODS_SUMMED

        '''
        Calculations for an 8-bit timer with a prescaler and postscaler
        Target sampling frequency = target detection frequency (desired note frequency) * relativeFSamp (number of samples in 2*pi radians)
        Target sampling period = 1 / (target sampling frequency)
        Actual sampling period = (Base timer frequency) / (timer prescaler) / (timer postscaler) / (timer period)
        First solve for the pre- and postscalers, and the timer period last. This will allow us to retain the maximum timer period possible,
        hence minimizing the difference between target and actual sampling period
              - set a pre-scaler of 1 and a timer period of MAX_PERIOD (hardware-dependent)
              - solve for the post-scaler:
                      timer postscaler = (Base timer frequency) / (timer prescaler = 1) / (target sampling freq) / (timer period = MAX_PERIOD)
              - if this postscaler value exceeds the maximum, increment the prescaler and try again
              - once the pre- and post-scaler values are set, solve for timer period:
                      timer period = (Base timer frequency) / (timer prescaler) / (target sampling freq) / (timer postscaler)
        '''

        # Prescaler, postscaler
        fSig = note.getFreq()
        TSig = 1.0 / fSig
        targetFSamp = self.FSampRel * fSig
        log2Prescale = 0
        postscale = 1
        while True:
            postscale = math.ceil(PIC18F_BASE_TIMER_FREQ / targetFSamp / PIC18F_TIMER_MAX_PERIOD / 2**log2Prescale)
            if postscale > PIC18F_TIMER_MAX_POSTSCALE:
                log2Prescale += 1
                if log2Prescale > PIC18F_TIMER_MAX_PRESCALE:
                    raise ValueError("Sampling interval is too slow for the HF clock, use another clock source!")
                    break
                continue
            else:
                break
            

        # Period
        period = round(PIC18F_BASE_TIMER_FREQ / targetFSamp / postscale / (2**log2Prescale))        # todo: this is outputting values > 255

        self.log2Prescale = log2Prescale
        self.postscale = postscale
        self.period = period

        # Calculate sample averaging and LED brightness update rates
        NCyclesPerRefresh = round(self.note.getFreq() / LED_REFRESH_RATE)
        self.FourierSumArrayLen = math.ceil(self.NCyclesSampled / NCyclesPerRefresh)
        self.NSamplesPerRefresh = min(NCyclesPerRefresh * 4, RELATIVE_FSAMP * NUM_PERIODS_SUMMED - 1)

        # Calculate wake test sampling interval
        wakeTestSampPeriod = min(WAKE_TEST_SAMPLING_PERIOD, self.NCyclesSampled * TSig)      # wakeTestSampPeriod should not exceed (Ncycles * signal period)
        NCyclesPerWakeSampPeriod = round(wakeTestSampPeriod / TSig)
        self.NSamplesPerWakeSampPeriod = min(NCyclesPerWakeSampPeriod * 4, RELATIVE_FSAMP * NUM_PERIODS_SUMMED - 1)

        return

    def getMacrosText(self) -> str:

        outStr = ''

        # Document the sampling timer calculations
        ifdefStr = '#if '
        noteAliasList = self.note.toFriendlyStrList()
        for idx, noteAlias in enumerate(noteAliasList):
            ifdefStr += 'defined __NOTE_{}__'.format(noteAlias)
            if idx < len(noteAliasList) - 1:   # not last item in list
                ifdefStr += ' || '

        outStr += ifdefStr  \
                + '\n\n'    \
                + '/* {} note frequency = {:.2f}Hz\n'.format(self.note.toStr(),                                             \
                                                             self.note.getFreq())                                           \
                + ' * Target sampling frequency: {} * {:.2f}Hz = {:.2f}Hz\n'.format(self.FSampRel,                          \
                                                                                    self.note.getFreq(),                    \
                                                                                    self.FSampRel * self.note.getFreq())    \
                + ' * With a sampling timer clock prescaler of 1:{}, postscaler of 1:{}, and period of {},\n'.format(2**(self.log2Prescale),     \
                                                                                                                        self.postscale, \
                                                                                                                        self.period)    \
                + ' * the actual sampling frequency is\n'       \
                 ' *      {:.2E}Hz / {} / {} / {} = {:.2f}Hz\n'.format(PIC18F_BASE_TIMER_FREQ,  \
                                                                        (2**self.log2Prescale), \
                                                                        self.postscale,         \
                                                                        self.period,            \
                                                                        PIC18F_BASE_TIMER_FREQ / (2**self.log2Prescale) / self.postscale / self.period)  \
                + ' */\n\n'

        # Add macros for timer configuration
        outStr += '#define TSAMP_PRESCALER {}       //prescaler 1:(2^(N-1))\n'.format(self.log2Prescale)          \
                    + '#define TSAMP_POSTSCALER {}      //postscaler 1:(N + 1)\n'.format(self.postscale)    \
                    + '#define TSAMP_PERIOD {}        //sampling period = N+1\n'.format(self.period)

        # Add macros for LED update rate
        outStr += '#define LED_REFRESH_INTERVAL {}  // Number of ADC samples per LED update calculation\n'.format(self.NSamplesPerRefresh)
        #            + '#define FOURIER_ACCUM_BUFLEN {}      //\n'.format(self.FourierSumArrayLen)    \

        # Add macros for sleep tasks update interval
        outStr += '#define SLEEP_TASKS_UPDATE_INTERVAL {}  // Number of ADC samples evaluated in sleep tasks calculation\n'.format(self.NSamplesPerWakeSampPeriod)

        outStr += '\n#endif // (#ifdef __NOTE_{}__)'.format(self.note.toStr())
        return outStr