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

def main():
    print(getRGB(200,1,0.5))

if __name__ == '__main__':
   main()


   #    https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both

   #    https://www.had2know.org/technology/hsv-rgb-conversion-formula-calculator.html#:~:text=Converting%20HSV%20to%20RGB&text=For%20example%2C%20if%20H%20%3D%20135,you%20divide%20it%20by%202.&text=B%20%3D%20m.&text=B%20%3D%20m.,-If%20120%20%E2%89%A4


   '''
   M = 255V
m = M(1-S).
z = (M-m)[1 - |(H/60)mod_2 - 1|],

   When 0 ≤ H < 60,

R = M
G = z + m
B = m.

If 60 ≤ H < 120,

R = z + m
G = M
B = m.

If 120 ≤ H < 180,

R = m
G = M
B = z + m.

When 180 ≤ H < 240,

R = m
G = z + m
B = M.

When 240 ≤ H < 300,

R = z + m
G = m
B = M.

And if 300 ≤ H < 360,

R = M
G = m
B = z + m.
https://www.had2know.org/technology/hsv-rgb-conversion-formula-calculator.html
© 2010-2023 had2know.org
   
   '''