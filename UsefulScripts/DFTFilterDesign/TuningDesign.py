from singleBinDFT import singleBinDFT
from matplotlib import pyplot as plt
from typing import List
import math
import numpy as np
import cmath

def main():
    phaseOffset = []
    errList = np.linspace(0.99, 1.01, 20)
    for err in errList:
        phaseOffset.append(getPhaseOffset(err, NSampSize=16, NSampGap=0))

    # set up plot
    fig, ax = plt.subplots()
    ax.plot(errList, phaseOffset)

    # title and labels
    fig.suptitle('Filter transfer function', fontsize=12)
    ax.set_xlabel('Frequency relative err', fontsize=10)
    ax.set_ylabel('Phase shift (degrees)', fontsize='medium')
    plt.show(block=True)

'''
The amplitude detection with single-bin-fourier math expects a sampling rate exactly 4x frequency of interest.
This function looks at what happens to the phase if the signal is slightly off of the frequency of interest.
If you take the sample buffer and divide it into two parts, you should see the signal phase shift from the front samples
To the back samples. An input of err = 1.0 should give a phase shift of exactly zero.
'''
def getPhaseOffset(err: float = 1.0, NSampSize = 32, NSampGap = 0) -> float: # in degrees
    # The signal phase will be calculated for the first "NSampSize" samples, followed by a gap of "NSampGap", then
    # the last "NSampSize" samples.
    NSamples = NSampSize * 2 + NSampGap
    IDEAL_REL_FREQ = 0.25
    t = np.linspace(0, NSamples - 1, NSamples)
    y = np.sin(t * 2* math.pi * err * IDEAL_REL_FREQ)
    frontHalf = singleBinDFT.getPhase(t[:NSampSize], y[:NSampSize], IDEAL_REL_FREQ) * 180 / cmath.pi
    backHalf = singleBinDFT.getPhase(t[NSampSize + NSampGap:], y[NSampSize + NSampGap:], IDEAL_REL_FREQ) * 180 / cmath.pi
    return backHalf - frontHalf


if __name__ == '__main__':
   main()