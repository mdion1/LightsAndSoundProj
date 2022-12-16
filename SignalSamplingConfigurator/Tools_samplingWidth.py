import numpy as np
import math
from matplotlib import pyplot as plt
from typing import List

def getAmp(t: np.array, y: np.array, relFreq: float) -> float:
    im = y * np.sin(t * 2* math.pi * relFreq)
    re = y * np.cos(t * 2* math.pi * relFreq)
    return 2 * math.sqrt(np.sum(im)**2 + np.sum(re)**2) / len(t)

def main(
        RELATIVE_PERIOD: float = 8,         #number of samples per period
        NUM_CYCLES_SAMPLED: float = 128
        ):

    RELATIVE_FREQ = 1.0 / RELATIVE_PERIOD
    
    NUM_SAMPLES = NUM_CYCLES_SAMPLED * RELATIVE_PERIOD

    # other constants
    CHROM_STEP = math.pow(2, 1/12)

    #raw samples
    t = np.linspace(0, NUM_SAMPLES - 1, NUM_SAMPLES)
    

    #LUT's
    sinTable = np.sin(t * 2* math.pi * RELATIVE_FREQ)
    cosTable = np.cos(t * 2* math.pi * RELATIVE_FREQ)

    #nearby frequencies
    NUM_CHROM_STEPS = 2     #Number of chromatic steps in either direction
    SWEEP_RES = 40

    chromStepList = np.append(
        np.linspace(-NUM_CHROM_STEPS, 0, SWEEP_RES),
        np.linspace(0, NUM_CHROM_STEPS, SWEEP_RES) )
    freqList = np.power(CHROM_STEP, chromStepList) * RELATIVE_FREQ
    y: List[np.array] = []
    for f in freqList:
        y.append(np.sin(t * 2* math.pi * f))

    fourier_y = np.zeros(len(y))
    for idx, sig in enumerate(y):
        fourier_y[idx] = getAmp(t, sig, RELATIVE_FREQ)
    
    plt.plot(chromStepList, fourier_y)
    plt.show(block=True)


if __name__ == '__main__':
    rel_period = 128
    for i in range(1, 8):
        print(i)
        main(rel_period, i)