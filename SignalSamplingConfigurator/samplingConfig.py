from typing import Dict, List
import math
import numpy as np

# TODO: DOCUMENT ALL YOUR SAMPLING THEORY/ASSUMPTIONS/EQUATIONS !!!!

#set global parameters
RELATIVE_FSAMP = 4
NUM_PERIODS_SUMMED = 64     # number of periods (of the target frequency) evaluated in the fourier sum
PIC18F_BASE_TIMER_FREQ = 1e6
MAX_CYCLES_PER_16B_SUM = 32     # For unsigned 10-bit ADC conversions, with a 4-entry sin/cos lookup table,
                                # each cycle sums to +-1023 (10-bits + sign bit). 32 cycles sums to +-32736
                                # ( 15-bits + sign bit)
PIC18F_TIMER_MAX_POSTSCALE = 16
PIC18F_TIMER_MAX_PERIOD = 256

# Task intervals
LED_REFRESH_RATE = 30  # in Hz
WAKE_TEST_SAMPLING_PERIOD = 0.1 # in seconds. Approximate period of time the signal is evaluated to see if the
                                # amplitude is above some minimum threshold, below which the controller
                                # enters deep sleep mode


class Note:

    NoteList: Dict[int, str] = {
        0: "C",
        1: "C#/Db",
        2: "D",
        3: "D#/Eb",
        4: "E",
        5: "F",
        6: "F#/Gb",
        7: "G",
        8: "G#Ab",
        9: "A",
        10: "A#/Bb",
        11: "B",
    }
    FreqList: Dict[int, float] = {
        0: 261.6255653,
        1: 277.182631,
        2: 293.6647679,
        3: 311.1269837,
        4: 329.6275569,
        5: 349.2282314,
        6: 369.9944227,
        7: 391.995436,
        8: 415.3046976,
        9: 440,
        10: 466.1637615,
        11: 493.8833013,
    }

    def __init__(self, idx: int, octave: int):
        if idx not in Note.NoteList.keys():
            raise KeyError("Note index must be between 0-11!")
            return
        
        self._idx: int = idx
        self._octave = octave
        self._noteName: str = f'{Note.NoteList[idx]}{octave}'
        self._freq: float = Note.FreqList[idx] * (2**(octave - 4))       # FreqList is based on octave 4

    def toStr(self) -> str:
        return self._noteName

    def toFriendlyStrList(self) -> List[str]:       # if note name has an alias (e.g. C#/Db), this returns list (e.g. ['C#', 'Db'])
        alia = f'{Note.NoteList[self._idx]}'.split('/')
        for idx in range(0, len(alia)):
            alia[idx] = alia[idx].replace('#','sharp')
            alia[idx] += f'{self._octave}'
        return alia

    def getFreq(self) -> float:
        return self._freq

class textFmt:
    def __init__(self, note: Note):
        global PIC18F_TIMER_MAX_POSTSCALE
        global PIC18F_TIMER_MAX_PERIOD
        global PIC18F_BASE_TIMER_FREQ
        global MAX_CYCLES_PER_16B_SUM
        global LED_REFRESH_RATE
        global WAKE_TEST_SAMPLING_PERIOD
        global NUM_PERIODS_SUMMED

        self.note = note
        self.FSampRel = RELATIVE_FSAMP
        self.NCyclesSampled = NUM_PERIODS_SUMMED        #todo RENAME!
        self.NCyclesSummed16b = min(self.NCyclesSampled, MAX_CYCLES_PER_16B_SUM)
        self.CycleSumArrayLen = math.ceil(self.NCyclesSampled / self.NCyclesSummed16b)
        self.CycleSumRightShift = 8        #TODO calculate an appropriate number!!!

        # Calculations for an 8-bit timer with a prescaler and postscaler
        # Target sampling frequency = target detection frequency (desired note frequency) * relativeFSamp (number of samples in 2*pi radians)
        # Target sampling period = 1 / (target sampling frequency)
        # Actual sampling period = (Base timer frequency) / (timer prescaler) / (timer postscaler) / (timer period)
        # First solve for the pre- and postscalers, and the timer period last. This will allow us to retain the maximum timer period possible,
        # hence minimizing the difference between target and actual sampling period
        #       - set a pre-scaler of 1 and a timer period of MAX_PERIOD (hardware-dependent)
        #       - solve for the post-scaler:
        #               timer postscaler = (Base timer frequency) / (timer prescaler = 1) / (target sampling freq) / (timer period = MAX_PERIOD)
        #       - if this postscaler value exceeds the maximum, increment the prescaler and try again
        #       - once the pre- and post-scaler values are set, solve for timer period:
        #               timer period = (Base timer frequency) / (timer prescaler) / (target sampling freq) / (timer postscaler)

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
                if log2Prescale > 3:        # max prescaler is 2^3 = 8
                    raise ValueError("Sampling interval is too slow for the HF clock, use another clock source!")
                    # Note/todo: the PIC18 timer sources are:
                    #       HFINT = 1e6Hz
                    #       MFINT = 31.25kHz or 500kHz (HFINT divided by 2 or 32)
                    #       LFINT = 31kHz
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
        self.NCyclesPerRefresh = round(self.note.getFreq() / LED_REFRESH_RATE)
        self.FourierSumArrayLen = math.ceil(self.NCyclesSampled / self.NCyclesPerRefresh)

        # Calculate wake test sampling interval
        wakeTestSampPeriod = min(WAKE_TEST_SAMPLING_PERIOD, self.NCyclesSampled * TSig)      # wakeTestSampPeriod should not exceed (Ncycles * signal period)
        self.NCyclesPerWakeSampPeriod = round(wakeTestSampPeriod / TSig)
        

        return

    def toStr(self) -> str:

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

        # Add macros for sample summing/analysis
        # outStr += '#define N_CYCLES_SUMMED_16b {}\n'.format(self.NCyclesSummed16b)      \
        #             + '#define CYCLE_SUM_ARRAY_LEN {}\n'.format(self.CycleSumArrayLen)  \
        #             + '#define CYCLE_SUM_RIGHTSHIFT {}\n'.format(self.CycleSumRightShift)

        # Add macros for LED update rate
        outStr += '#define LED_REFRESH_INTERVAL {}  // Number of signal periods per LED update calculation\n'.format(self.NCyclesPerRefresh)
        #            + '#define FOURIER_ACCUM_BUFLEN {}      //\n'.format(self.FourierSumArrayLen)    \

        # Add macros for sleep tasks update interval
        outStr += '#define SLEEP_TASKS_UPDATE_INTERVAL {}  // Number of signal periods evaluated in sleep tasks calculation\n'.format(self.NCyclesPerWakeSampPeriod)

        outStr += '\n#endif // (#ifdef __NOTE_{}__)'.format(self.note.toStr())
        return outStr
    
    def gammaFn_toStr():
        LUT_BIT_DEPTH = 6
        LUT_LEN = 2**LUT_BIT_DEPTH

        idx = np.array(range(0, LUT_LEN))
        idx = idx + LUT_LEN
        gammaLUT = np.round((np.log2(idx) - math.log2(LUT_LEN)) * LUT_LEN)
        return gammaLUT



def main():
    global RELATIVE_FSAMP

    numOctaves = 4
    octaveStart = 2
    outStr = '#pragma once\n\n'

    # todo: includes, other comments at top

    textFmt(Note(0, 4))     #debugging with middle c
    textFmt.gammaFn_toStr()

    for octave in range(octaveStart, octaveStart + numOctaves):
        for idx in Note.NoteList.keys():
            outStr += textFmt(Note(idx, octave)).toStr() + '\n\n'

    #todo: add on C6
    outStr += textFmt(Note(0, 6)).toStr() + '\n\n'

    #print(outStr)

    with open("SamplingParams.h", "w") as text_file:
        text_file.write(outStr)




if __name__ == '__main__':
   main()