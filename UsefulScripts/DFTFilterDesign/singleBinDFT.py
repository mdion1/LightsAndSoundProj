import numpy as np
import math
from matplotlib import pyplot as plt
from typing import List
from TransferFn import TransferFn
import cmath

class singleBinDFT(TransferFn):
    def __init__(self, centerFreq: float, samplingFreq: float, NCyclesSampled: int):
        self.fCenter = centerFreq
        self.fSamp = samplingFreq
        self.NCyclesSampled = NCyclesSampled

        self.relativeFreq = self.fCenter / self.fSamp
        NSamples = int(self.NCyclesSampled / self.relativeFreq)
        self.timeData = np.linspace(0, NSamples - 1, NSamples)
        # self.sinTable = np.sin(self.timeData * 2* math.pi * self.relativeFreq)
        # self.cosTable = np.cos(self.timeData * 2* math.pi * self.relativeFreq)
        return

    def getAmp(t: np.array, y: np.array, relFreq: float) -> complex:
        im = y * np.sin(t * 2* math.pi * relFreq)
        re = y * np.cos(t * 2* math.pi * relFreq)
        return complex(np.sum(re), np.sum(im)) * 2.0 / len(t)

    def getModulus(t: np.array, y: np.array, relFreq: float) -> float:
        return abs(singleBinDFT.getAmp(t, y, relFreq))
    
    def getPhase(t: np.array, y: np.array, relFreq: float) -> float: # in radians
        return cmath.phase(singleBinDFT.getAmp(t, y, relFreq))

    def apply(self, frequency: float) -> float:
        y: np.array = np.sin(self.timeData * 2* math.pi * frequency / self.fSamp)
        return singleBinDFT.getModulus(self.timeData, y, self.relativeFreq)

