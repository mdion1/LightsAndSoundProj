# Fast integer-only Log2/Pow2 estimates

This script is included more for the sake of showing work than for future development. Taking the base-2 log of an integer can be as simple as checking the position of the most-significant 1 (or integer width - countLeadingZeroes(num)). You can add precision onto this by looking at the next N signficant digits after the MSBit, and using this number as an index for a lookup table. By scaling the original rough estimate by N and adding the lookup table value to the original MSBit position, you can implement a function that return N*log2() with precision equal to the length of the lookup table.

Similarly, you can implement a simple power(2,x) function by bitshifting 1 by x places. But you can achieve better precision by scaling the input value by factor N, then finding the appropriate lookup value and bitshifting by x/N places.

Running this script will print the lookup tables to the console. The functions that use these tables can be found in AmpScalingMath.c.