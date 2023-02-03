from TransferFn import TransferFn
from HPF import HPF
from LPF import LPF
from digitalFourierFilt import digitalFourierFilt
from matplotlib import pyplot as plt
from typing import List
import math
import numpy as np


def main():

    # Build system from transfer function blocks
    TARGET_FREQ = 263
    RELATIVE_FSAMP = 4
    NUM_CYCLES_SAMPLED = 64
    LPF_CORNER_FREQ = 512   # in Hz
    HPF_CORNER_FREQ = 128   # in Hz
    signalChain: List["TransferFn"] = []

    #signalChain.append(LPF(LPF_CORNER_FREQ))
    #signalChain.append(HPF(HPF_CORNER_FREQ))
    signalChain.append(digitalFourierFilt(TARGET_FREQ, RELATIVE_FSAMP * TARGET_FREQ, NUM_CYCLES_SAMPLED))

    # create list of input frequencies to test
    CHROM_STEP = math.pow(2, 1/12)
    
    NUM_CHROM_STEPS = 1     #Number of chromatic steps in either direction
    SWEEP_RES = 80

    chromStepList = np.append(
        np.linspace(-NUM_CHROM_STEPS, 0, SWEEP_RES),
        np.linspace(0, NUM_CHROM_STEPS, SWEEP_RES) )
    freqList = np.power(CHROM_STEP, chromStepList) * TARGET_FREQ
    gain: List[float] = []
    for f in freqList:
        x = 1
        for trnFn in signalChain:
            x *= trnFn.apply(f)
        gain.append(20 * math.log10(x))

    plt.plot(chromStepList, gain)
    plt.show(block=True)


if __name__ == '__main__':
   main()