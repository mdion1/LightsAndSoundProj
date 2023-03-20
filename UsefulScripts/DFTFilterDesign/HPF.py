from TransferFn import TransferFn
from math import sqrt

class HPF(TransferFn):
    def __init__(self, cornerFreq: float):
        self.fc: float = cornerFreq

    def apply(self, frequency: float) -> float:
        # v_in / v_out = gain or attenuation = 1 / sqrt(1 + (f_corner/f)^2)
        return 1 / sqrt(1 + (self.fc / frequency)**2)