

//todo: implement with integer-only math
RGB_t HSLtoRGB(const HSL_t* pHSL)
{
    /* For hue, saturation, and lightness scaled to :
     *      0 <= hue < 360
     *      0 <= sat <= 1
     *      0 <= lightness <= 1
     * The calculations are as follows (from https://www.rapidtables.com/convert/color/hsl-to-rgb.html)
     *  
     *  C = (1 - abs(2 * lightness - 1)) * sat
     *  X = C * (1 - abs((hue / 60)%2 - 1))
     *  m = lightness - C / 2
     * 
     *  (R, B, G) = (0, 0, 0)
     *  if hue < 60:
     *      (R, B, G) = (C, X, 0)
     *  elif hue < 120:
     *      (R, B, G) = (X, C, 0)
     *  elif hue < 180:
     *      (R, B, G) = (0, C, X)
     *  elif hue < 240:
     *      (R, B, G) = (0, X, C)
     *  elif hue < 300:
     *      (R, B, G) = (X, 0, C)
     *  else:
     *      (R, B, G) = (C, 0, X)
     * 
     *  R = (R + m) * 255
     *  G = (G + m) * 255
     *  B = (B + m) * 255
    */


   
}
def getRGB(hue: float, sat: float, lightness: float) -> Tuple[float, float, float]:
    '''
    
    
    
    '''


    return (R, B, G)