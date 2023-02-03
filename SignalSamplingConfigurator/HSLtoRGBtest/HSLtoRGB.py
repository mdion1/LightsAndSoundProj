from typing import Tuple

def getRGB_int(hue: int, sat: int, lightness: int) -> Tuple[int, int, int]:
    '''
    0 <= hue <= 255
    0 <= sat <= 255
    0 <= lightness <= 255
    '''

    return (0,0,0)#todo

def getRGB(hue: float, sat: float, lightness: float) -> Tuple[float, float, float]:
    '''
    0 <= hue < 360
    0 <= sat <= 1
    0 <= lightness <= 1
    '''

    C = (1 - abs(2 * lightness - 1)) * sat
    X = C * (1 - abs((hue / 60)%2 - 1))
    m = lightness - C / 2

    (R, B, G) = (0, 0, 0)
    if hue < 60:
        (R, B, G) = (C, X, 0)
    elif hue < 120:
        (R, B, G) = (X, C, 0)
    elif hue < 180:
        (R, B, G) = (0, C, X)
    elif hue < 240:
        (R, B, G) = (0, X, C)
    elif hue < 300:
        (R, B, G) = (X, 0, C)
    else:
        (R, B, G) = (C, 0, X)

    R = (R + m) * 255
    G = (G + m) * 255
    B = (B + m) * 255
    return (R, B, G)


   #    https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both

   #    https://www.had2know.org/technology/hsv-rgb-conversion-formula-calculator.html#:~:text=Converting%20HSV%20to%20RGB&text=For%20example%2C%20if%20H%20%3D%20135,you%20divide%20it%20by%202.&text=B%20%3D%20m.&text=B%20%3D%20m.,-If%20120%20%E2%89%A4

def HSVtoRGB(hue: float, sat: float, value: float) -> Tuple[float, float, float]:
    '''
    Hue: on a 360 degree color wheel, red is at 0 degrees, green is at 120 degrees, and blue is at 240 degrees
    Saturation: grayscale colors have a saturation of 0.0, and colors liek red, green and blue have a saturation of 1.0
    Value: the brightness of a color
    '''

    # Input guards: accept 0 - 255
    value = max(min(255, value), 0)         # 0 <= value <= 255
    sat = max(min(255, sat), 0)         # 0 <= value <= 255
    hue = max(min(255, hue), 0)         # 0 <= value <= 255

    # Scale the inputs
    value /= 255        # scale value from 0 to 1.0
    sat /= 255          # scale sat from 0 to 1.0
    hue *= 360 / 255    # scale hue from 0 to 360

    M = value * 255
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

class FixPt():
    def __init__(self, val:float = 0):
        self.int16Val = min(max(round(val), 0), 65535)
    
    def getInt8(self) -> int:
        return round(self.int16Val / 256)

    def getInt16(self) -> int:
        return self.int16Val

    def mult(a: "FixPt", b: "FixPt") -> "FixPt":
        x = a.getInt8() * b.getInt8()
        return FixPt(x)

    def add(a: "FixPt", b: "FixPt") -> "FixPt":
        # does NOT check for overflow!!!!
        x = a.getInt16() + b.getInt16()
        return FixPt(x)

    def subtract(a: "FixPt", b: "FixPt") -> "FixPt":
        # does NOT check for underflow!!!!
        x = a.getInt16() - b.getInt16()
        return FixPt(x)

class FixPt2():
    def __init__(self, val:float = 0):
        self.int16Val = min(max(round(val), 0), 65536)
    
    def getInt8(self) -> int:
        return round(self.int16Val / 256)

    def getInt16(self) -> int:
        return self.int16Val

    def mult(a: "FixPt2", b: "FixPt2") -> "FixPt2":
        x = a.getInt8() * b.getInt8()
        return FixPt2(x)

    def add(a: "FixPt2", b: "FixPt2") -> "FixPt2":
        # does NOT check for overflow!!!!
        x = a.getInt16() + b.getInt16()
        return FixPt2(x)

    def subtract(a: "FixPt2", b: "FixPt2") -> "FixPt2":
        # does NOT check for underflow!!!!
        x = a.getInt16() - b.getInt16()
        return FixPt2(x)

def HSVtoRGB_INTMATH(hue: float, sat: float, value: float) -> Tuple[float, float, float]:
    '''
    Hue: on a 360 degree color wheel, red is at 0 degrees, green is at 120 degrees, and blue is at 240 degrees
    Saturation: grayscale colors have a saturation of 0.0, and colors liek red, green and blue have a saturation of 1.0
    Value: the brightness of a color
    '''

    # Input guards: accept 0 - 255
    value = max(min(255, value), 0)         # 0 <= value <= 255
    sat = max(min(255, sat), 0)         # 0 <= value <= 255
    hue = max(min(255, hue), 0)         # 0 <= value <= 255

    V = FixPt(value * 256)
    S = FixPt(sat * 256)
    H = FixPt(hue * 256)

    # Scale hue for readability
    hue *= 360 / 255    # scale hue from 0 to 360
    
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
        X = FixPt(256*(slope * H.getInt8() - 0))
        z = FixPt.mult(FixPt.subtract(M, m), X)     #error in m propagates here?
        R = M
        G = FixPt.add(z, m)
        B = m
    elif hue < 120:
        X = FixPt(256*(510 - slope * H.getInt8()))
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = FixPt.add(z, m)
        G = M
        B = m
    elif hue < 180:
        X = FixPt(256*(slope * H.getInt8() - 510))
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = m
        G = M
        B = FixPt.add(z, m)
    elif hue < 240:
        X = FixPt(256*(1020 - slope * H.getInt8()))
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = m
        G = FixPt.add(z, m)
        B = M
    elif hue < 300:
        X = FixPt(256*(slope * H.getInt8() - 1020))
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = FixPt.add(z, m)
        G = m
        B = M
    else:
        X = FixPt(256*(1530 - slope * H.getInt8()))
        z = FixPt.mult(FixPt.subtract(M, m), X)
        R = M
        G = m
        B = FixPt.add(z, m)

    return (R.getInt8(), G.getInt8(), B.getInt8())


def HSVtoRGB_INTMATH2(hue: float, sat: float, value: float) -> Tuple[float, float, float]:
    '''
    Hue: on a 360 degree color wheel, red is at 0 degrees, green is at 120 degrees, and blue is at 240 degrees
    Saturation: grayscale colors have a saturation of 0.0, and colors liek red, green and blue have a saturation of 1.0
    Value: the brightness of a color
    '''

    # Input guards: accept 0 - 255
    value = max(min(255, value), 0)         # 0 <= value <= 255
    sat = max(min(255, sat), 0)         # 0 <= value <= 255
    hue = max(min(255, hue), 0)         # 0 <= value <= 255

    V = FixPt2(value * 256 + 1)
    S = FixPt2(sat * 256 + 1)
    H = FixPt2(hue * 256 + 1)

    # Scale hue for readability
    hue *= 360 / 255    # scale hue from 0 to 360
    
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
    m = FixPt2.subtract(M, FixPt2.mult(M, S))     # <== here is where the rounding error comes in!

    R, G, B, X = (FixPt2(), FixPt2(), FixPt2(), FixPt2())
    slope = 6
    if hue < 60:
        X = FixPt2(256*(slope * H.getInt8() - 0))
        z = FixPt2.mult(FixPt2.subtract(M, m), X)     #error in m propagates here?
        R = M
        G = FixPt2.add(z, m)
        B = m
    elif hue < 120:
        X = FixPt2(256*(510 - slope * H.getInt8()))
        z = FixPt2.mult(FixPt2.subtract(M, m), X)
        R = FixPt2.add(z, m)
        G = M
        B = m
    elif hue < 180:
        X = FixPt2(256*(slope * H.getInt8() - 510))
        z = FixPt2.mult(FixPt2.subtract(M, m), X)
        R = m
        G = M
        B = FixPt2.add(z, m)
    elif hue < 240:
        X = FixPt2(256*(1020 - slope * H.getInt8()))
        z = FixPt2.mult(FixPt2.subtract(M, m), X)
        R = m
        G = FixPt2.add(z, m)
        B = M
    elif hue < 300:
        X = FixPt2(256*(slope * H.getInt8() - 1020))
        z = FixPt2.mult(FixPt2.subtract(M, m), X)
        R = FixPt2.add(z, m)
        G = m
        B = M
    else:
        X = FixPt2(256*(1530 - slope * H.getInt8()))
        z = FixPt2.mult(FixPt2.subtract(M, m), X)
        R = M
        G = m
        B = FixPt2.add(z, m)

    return (R.getInt8(), G.getInt8(), B.getInt8())



def main():
    
    for value in range(255, 0, -1):
        maxerr = 0
        for hue in range(0, 255):
            for sat in range(0, 255):
                r1, g1, b1 = HSVtoRGB(hue, sat, value)
                r2, g2, b2 = HSVtoRGB_INTMATH2(hue, sat, value)
                err = max([abs(r1 - r2), abs(g1 - g2), abs(b1 - b2)])

                if err > maxerr:
                    #print(err)
                    maxerr = err
        print(f'{value}, {maxerr}')

    #print(HSVtoRGB(hue=200, sat=1.0, value=0.5))

if __name__ == '__main__':
   main()