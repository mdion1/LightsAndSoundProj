from TransferFn import TransferFn
from HPF import HPF
from LPF import LPF
from singleBinDFT import singleBinDFT
from matplotlib import pyplot as plt
from typing import List
import math
import numpy as np

# SCRIPT INPUTS
TARGET_FREQ = 263
RELATIVE_FSAMP = 4
NUM_CYCLES_SAMPLED = 64

def main():
    global TARGET_FREQ
    global RELATIVE_FSAMP
    global NUM_CYCLES_SAMPLED

    # Build system from transfer function blocks
    signalChain: List["TransferFn"] = []

    # Optional: add on single-pole low-pass and high-pass filters
    #signalChain.append(LPF(LPF_CORNER_FREQ))
    #signalChain.append(HPF(HPF_CORNER_FREQ))

    # Add single-bin DFT
    signalChain.append(singleBinDFT(TARGET_FREQ, RELATIVE_FSAMP * TARGET_FREQ, NUM_CYCLES_SAMPLED))

    # create list of input frequencies to test
    CHROM_STEP = math.pow(2, 1/12)
    NUM_CHROM_STEPS = 1     # Number of chromatic steps in either direction
    SWEEP_RES = 160          # Number of points on the graph

    chromStepList = np.append(
        np.linspace(-NUM_CHROM_STEPS, 0, int(SWEEP_RES / 2)),
        np.linspace(0, NUM_CHROM_STEPS, int(SWEEP_RES / 2)) )
    freqList = np.power(CHROM_STEP, chromStepList) * TARGET_FREQ
    gain: List[float] = []

    # Apply each transfer function in the signal chain
    for f in freqList:
        x = 1
        for trnFn in signalChain:
            x *= trnFn.apply(f)
        gain.append(20 * math.log10(x))

    # set up plot
    fig, ax = plt.subplots()
    ax.plot(chromStepList, gain)

    # title and labels
    fig.suptitle('Filter transfer function', fontsize=12)
    ax.set_xlabel('Chromatic steps\nfrom center frequency', fontsize=10)
    ax.set_ylabel('Gain(dB)', fontsize='medium')
    plt.show(block=True)

if __name__ == '__main__':
   main()