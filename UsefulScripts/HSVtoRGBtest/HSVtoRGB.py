from typing import Tuple
from FixedPtMath import FixPt

def HSVtoRGB(hue: float, sat: float, value: float) -> Tuple[float, float, float]:
    '''
    Hue: on a 360 degree color wheel, red is at 0 degrees, green is at 120 degrees, and blue is at 240 degrees
    Saturation: grayscale colors have a saturation of 0.0, and colors liek red, green and blue have a saturation of 1.0
    Value: the brightness of a color
    '''

    # Input guards: accept 0 - 256
    value = max(min(256, value), 0)         # 0 <= value <= 256
    sat = max(min(256, sat), 0)         # 0 <= value <= 256
    hue = max(min(256, hue), 0)         # 0 <= value <= 256

    # Scale the inputs
    value /= 256        # scale value from 0 to 1.0
    sat /= 256          # scale sat from 0 to 1.0
    hue *= 360 / 256    # scale hue from 0 to 360

    M = value * 256
    m = M * (1 - sat)
    # z = (M - m) * (1 - abs((hue / 60) % 2 - 1))

    # eliminating the modulo operator,
    # z = (M - m) * X, where
    # X = 1 - abs((hue / 60) % 2 - 1)
    #   = 0.016666667 * hue         for 0 <= hue < 60
    #     -0.016666667 * hue + 2    for 60 <= hue < 120
    #     0.016666667 * hue - 2     for 120 <= hue < 180
    #     -0.016666667 * hue + 4    for 180 <= hue < 240
    #     0.016666667 * hue - 4     for 240 <= hue < 300
    #     -0.016666667 * hue + 6    for 300 <= hue < 360


    R, G, B = (0, 0, 0)
    X = 0

    if hue < 60:
        X = 0.016666667 * hue
        z = (M - m) * X
        R = M
        G = z + m
        B = m
    elif hue < 120:
        X = -0.016666667 * hue + 2
        z = (M - m) * X
        R = z + m
        G = M
        B = m
    elif hue < 180:
        X = 0.016666667 * hue - 2
        z = (M - m) * X
        R = m
        G = M
        B = z + m
    elif hue < 240:
        X = -0.016666667 * hue + 4
        z = (M - m) * X
        R = m
        G = z + m
        B = M
    elif hue < 300:
        X = 0.016666667 * hue - 4
        z = (M - m) * X
        R = z + m
        G = m
        B = M
    else:
        X = -0.016666667 * hue + 6
        z = (M - m) * X
        R = M
        G = m
        B = z + m

    return (round(R), round(G), round(B))


def HSVtoRGB_INTMATH(hue: float, sat: float, value: float) -> Tuple[float, float, float]:
    '''
    Hue: on a 360 degree color wheel, red is at 0 degrees, green is at 120 degrees, and blue is at 240 degrees
    Saturation: grayscale colors have a saturation of 0.0, and colors liek red, green and blue have a saturation of 1.0
    Value: the brightness of a color
    '''

    # Input guards: accept 0 - 256
    value = max(min(256, value), 0)         # 0 <= value <= 256
    sat = max(min(256, sat), 0)         # 0 <= value <= 256
    hue = max(min(256, hue), 0)         # 0 <= value <= 256

    V = FixPt(value / 256)
    S = FixPt(sat / 256)
    H = FixPt(hue / 256)

    # Scale hue for readability
    hue *= 360 / 256    # scale hue from 0 to 360
    
    # eliminating the modulo operator,
    # z = (M - m) * (1 - abs((hue / 60) % 2 - 1))
    #   = (M - m) * X, where
    # X = 1 - abs((hue / 60) % 2 - 1)
    #   = 6 * hue           for 0 <= hue < 60
    #     510 - 6 * hue     for 60 <= hue < 120
    #     6 * hue - 510     for 120 <= hue < 180
    #     1020 - 6 * hue    for 180 <= hue < 240
    #     6 * hue - 1020    for 240 <= hue < 300
    #     1530 - 6 * hue    for 300 <= hue < 360

    M = V
    m = FixPt.subtract(M, FixPt.mult(M, S))     # <== here is where the rounding error comes in!

    R, G, B, X = (FixPt(), FixPt(), FixPt(), FixPt())
    slope = 6
    if hue < 60:
        X = FixPt((slope * H.getInt8() - 0) / 256)
        z = FixPt.mult(FixPt.subtract(M, m), X)     #error in m propagates here?
        R = M
        G = FixPt.add(z, m)
        B = m
    elif hue < 120:
        X = FixPt((512 - slope * H.getInt8()) / 256)
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = FixPt.add(z, m)
        G = M
        B = m
    elif hue < 180:
        X = FixPt((slope * H.getInt8() - 512) / 256)
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = m
        G = M
        B = FixPt.add(z, m)
    elif H.getInt8() == 128:    # (1024 - slope * H.getInt8()) / 256 == 1.0
        z = FixPt.subtract(M, m)
        R = m
        G = FixPt.add(z, m)
        B = M
    elif hue < 240:
        X = FixPt((1024 - slope * H.getInt8()) / 256)
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = m
        G = FixPt.add(z, m)
        B = M
    elif hue < 300:
        X = FixPt((slope * H.getInt8() - 1024) / 256)
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = FixPt.add(z, m)
        G = m
        B = M
    else:
        X = FixPt((1536 - slope * H.getInt8()) / 256)
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = M
        G = m
        B = FixPt.add(z, m)

    return (R.getInt8(), G.getInt8(), B.getInt8())

def mainOnce():
    
    value = 255
    hue = 170
    sat = 232
    r1, g1, b1 = HSVtoRGB(hue, sat, value)
    r2, g2, b2 = HSVtoRGB_INTMATH(hue, sat, value)
    err = max([abs(r1 - r2), abs(g1 - g2), abs(b1 - b2)])

    print(f'{value}, {err}')

    #print(HSVtoRGB(hue=200, sat=1.0, value=0.5))

def mainLoop():
    for value in range(128, 0, -1):
        maxerr = 0
        for hue in range(0, 255):
            for sat in range(128, 255):
                r1, g1, b1 = HSVtoRGB(hue, sat, value)
                r2, g2, b2 = HSVtoRGB_INTMATH(hue, sat, value)
                err = max([abs(r1 - r2), abs(g1 - g2), abs(b1 - b2)])

                if err > maxerr:
                    #print(err)
                    maxerr = err
        print(f'{value}, {maxerr}')

    #print(HSVtoRGB(hue=200, sat=1.0, value=0.5))

if __name__ == '__main__':
   mainLoop()
   #mainOnce()