import numpy as np
import math

# USER INPUTS
# DEFINE LOOKUP TABLE LENGTH AND RESOLUTION
LOG2_LUT_TABLE_LEN: int = 6
LOG2_LUT_TABLE_SCALING: int = 6



def main():

    LUT_TABLE_LEN: int = 2**LOG2_LUT_TABLE_LEN
    LUT_TABLE_SCALING: int = 2**LOG2_LUT_TABLE_SCALING

    # Log2 lookup table calculation
    lowerBits = np.linspace(LUT_TABLE_LEN, LUT_TABLE_LEN * 2, num=LUT_TABLE_LEN, endpoint=False)
    Log2Lookup = np.round(LUT_TABLE_SCALING * (np.log2(lowerBits) - math.log2(LUT_TABLE_LEN)))

    # Output array to console, 16 values per line
    VALUES_PER_LINE = 16
    cnt = 0
    outStr: str = ''
    outStr += f'#define LOG_TABLE_BITDEPTH {LOG2_LUT_TABLE_LEN}\n'
    outStr += f'#define LOG_TABLE_PRECISION {LOG2_LUT_TABLE_SCALING}\n\n'
    outStr += 'static const uint8_t NLog2Lookup[1 << LOG_TABLE_BITDEPTH] = {\n'
    for val in Log2Lookup:
        if 0 == cnt:
            outStr += '    '        # add tab to beginning of line
        outStr += f'{int(val)}'
        cnt += 1
        if cnt == VALUES_PER_LINE:
            cnt = 0
            outStr += ',\n'
        else:
            outStr += ', '
    outStr += '};\n\n'

    # Pow2 lookup table calculation
    pow2Idx = np.linspace(0, LUT_TABLE_LEN, num=LUT_TABLE_LEN, endpoint=False)
    pow2Lookup = np.round(np.power(2, pow2Idx / LUT_TABLE_LEN) * LUT_TABLE_SCALING)

    outStr += 'static const uint8_t NExp2Lookup[1 << LOG_TABLE_BITDEPTH] = {\n'
    
    cnt = 0
    for val in pow2Lookup:
        if 0 == cnt:
            outStr += '    '        # add tab to beginning of line
        outStr += f'{int(val)}'
        cnt += 1
        if cnt == VALUES_PER_LINE:
            cnt = 0
            outStr += ',\n'
        else:
            outStr += ', '
    outStr += '};\n\n'


    print(outStr)


if __name__ == '__main__':
   main()