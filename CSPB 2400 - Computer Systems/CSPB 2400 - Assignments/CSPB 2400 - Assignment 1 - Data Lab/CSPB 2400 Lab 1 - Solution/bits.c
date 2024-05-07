/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically and a negative shift value results in zero.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES, FOLLOW THE DIRECTIONS in README.md
 */


#endif
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
/* bitAnd - Performs the bitwise 'and' operation of two integer values using only the 'negation' and 'or' bitwise operators
  Input:
    x - Integer value, to be used in the expression x & y
    y - Integer value, to be used in the expression x & y
  Algorithm:
    * De Morgan's Law states that the conjunction of two hypotheses is equivalent to the negation of the disjunction of negations
    of the hypotheses
    * In bitwise operation terms, this is x & y = ~(~x | ~y)
  Output:
    This function will return the De Morgan's Law equivalent of x & y (~(~x | ~y))
*/
int bitAnd(int x, int y) {
  return ~(~x | ~y); // De Morgan's Law equivalent of x & y
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
/* fitsShort - Determines if a 32 bit signed integer is able to be represented as a 16 bit signed integer
  Input:
    x - 32 bit integer that is being examined if it can be represented as a 16 bit integer
  Algorithm:
    * First, left shift the input parameter to place the LSBs into the MSBs (Fills first 16 with zeros)
    * Second, right shift the previously calculated integer so that the MSBs are placed into the LSBs (Fills last 16 with sign of x)
    * Return the logical NOT of x XOR y
      * 0 - Is returned if when x ^ y is calculated, at least one bit position is off (one is 1, other is 0), due to nature of logical NOT
      * 1 - Is returned if when x ^ y is calculated, no values are different (both bits in all positions are the same), due to nature of logical NOT
  Output:
    Returns the logical NOT of the XOR of x and y (aiming to observer if bits are different in shifted and original value)
*/
int fitsShort(int x) {
  int y = x << 16; // Shift LSBs to MSBs
  y = y >> 16; // Fill MSBs with sign of y
  return !(x ^ y); // Examine if any bits in all 32 positions are different
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
/* thirdBits - Creates a bit mask where every third bit is a 1 starting from LSB
  Input:
    void - This function does not have any input parameters
  Algorithm:
    * Start with 32 bit binary number pattern 0b00...001001001 (every thrid bit is a one)
    * Update this value by:
      * Left shifting 6 positions
      * Using OR with previous and left shifted values
        * Will update 'ret''s bits if previous bits are off parity (one is 1, other is 0)
    * Perform the previous process four times to cover all additional 24 bits
  Output:
    This function returns an integer value that in binary looks like:
      0b01001001001001001001001001001001001001001001
*/
int thirdBits(void) {
  int ret = 0x49; // Create initial mask
  ret = ret | (ret << 6); // Shift and compare to previous value
  ret = ret | (ret << 6); // Shift and compare to previous value
  ret = ret | (ret << 6); // Shift and compare to previous value
  ret = ret | (ret << 6); // Shift and compare to previous value
  return ret;
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
/* anyEvenBit - Checks if any even numbered bit in word is a 1
  Input:
    x - Integer value that is to be checked if it has any even bit set to 1
  Algorithm:
    * Create a bit mask that has the binary pattern of 0b00...01010101
    * Copy this pattern to the next 8 MSBs by:
      * Left shifting the previous value 8 positions
      * Performing an OR operation with the previous and shifted values
    * Copy the pattern to the next 16 MSBs by:
      * Left shifting the previous value 16 positions
      * Performing an OR operation with the previous and shifted values
    * AND this mask, with the original value, and perform a double Logical NOT on the AND to return the truth value
      * First NOT evaluates to 1 if all 0s (no even bits set to 1), 0 if there is atleast one 1 (one even bit is set to one)
      * Second NOT evalues to 1 if previous is 0 (even bits exist), 1 if previous is 1 (no even bits exist)
  Output:
    This function returns an integer value, 0 for false and 1 for true, for if a numbers binary representation has at least one
    even numbered bit that is a 1
*/
int anyEvenBit(int x) {
  int y = 0x55; // Create initial mask
  y = y | (y << 8); // Copy mask to next 8 MSBs
  y = y | (y << 16); // Copy mask to next 16 MSBs
  return !(!(x & y));
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
/* copyLSB - Copies the least significant bit to all bits in the word
  Input:
    x - Integer that is to have its LSB copied to all bits
  Algorithm:
    * Push the LSB to MSB by left shifting 31 times
    * Copy the sign bit (previously the LSB) to all other 31 bits
  Output:
    This function returns an integer where every bit is the LSB of the input parameter
*/
int copyLSB(int x) {
  int y = x << 31; // Push LSB to MSB
  y = y >> 31; // Propogate sign bit to all bits
  return y;
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
/* implication - Returns the truth value of x -> y using only bitwise operations
  Input:
    x - Integer value that represents x in x -> y
    y - Integer value that represents y in x -> y
  Algorithm:
    * In propositional logic, the equivalent of x -> y is !x | y
    * Return the aforementioned expression for the truth value desired in this problem
  Output:
    This function returns an integer value where 1 is true and 0 is false
*/
int implication(int x, int y) {
  return (!x | y);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
/* bitCount - Counts the number of 1's in a word
  Input:
    x - Integer value whos 1's are to be counted
  Algorithm:
    * First, define masks that will be used to count the ones in the word
    * Mask1: 0b01010101010101010000000000000000
      * Start by creating a 16 bit mask, by first ORing the 8 bit mask pattern with 
        a 16 bit mask pattern where the MSBs consist of the pattern
      * Shift LSBs to MSBs with a 16 bit shift
    * Mask2: 0b00110011001100110011001100110011
      * Start by creating a 16 bit mask, by first ORing the 8 bit mask pattern with
        a 16 bit mask pattern where the MSBs consist of the pattern
      * Shift LSBs to MSBs with a 16 bit shift
    * Mask3: 0b00001111000011110000111100001111
      * Start by creating a 16 bit mask, by first ORing the 8 bit mask pattern with
        a 16 bit mask pattern where the MSBs consist of the pattern
      * Shift LSBs to MSBs with a 16 bit shift
    * Mask4: 0b00000000111111110000000011111111
      * Take the 8 bit pattern: 0b11111111 and OR it with the 24 bit pattern
        0b000000001111111100000000
      * The resulting OR will produce the full pattern
    * Mask5: 0b00000000000000001111111111111111
      * Take the 8 bit pattern: 0b11111111 and OR it with the 16 bit pattern
        0b1111111100000000
      * The resulting OR will produce the full pattern
    * First, count the number of bits in pairs, ANDing and shifting the pairs in the input parameter
    * Next, count the number of bits in blocks, ANDing and shifting the pairs in the input parameter
    * Next, count the number of bits in bytes, ANDing and shifting the pairs in the input parameter
    * Next, count the number of bits in halves, ANDing and shifting the pairs in the input parameter
    * Finally, count the number of bits in the entire word, ANDing and shifting the pairs in the input parameter
  Output:
    x - Integer value that represents the number of set bits in an integer
*/
int bitCount(int x) {
  int mask1, mask2, mask3, mask4, mask5; // Define variables
  mask1 = 0x55 | (0x55 << 8); // Alternating 01 pattern in first 16 bits
  mask1 |= (mask1 << 16); // Alternating 01 32 bit pattern in first 16 MSBs
  mask2 = 0x33 | (0x33 << 8); // Alternating 0011 pattern in first 16 bits
  mask2 |= (mask2 << 16); // Alternating 0011 32 pattern
  mask3 = 0x0F | (0x0F << 8); // Alternating 00001111 pattern in first 16 bit
  mask3 |= (mask3 << 16); // Alternating 00001111 32 bit pattern
  mask4 = 0xFF | (0xFF << 16); // Centered 11111111 pattern in 24 bits
  mask5 = 0xFF | (0xFF << 8); // Alternating 11111111 even byte 32 bit pattern
  x = (x & mask1) + ((x >> 1) & mask1); // Count bits in pairs
  x = (x & mask2) + ((x >> 2) & mask2); // Count bits in blocks
  x = (x & mask3) + ((x >> 4) & mask3); // Count bits in bytes
  x = (x & mask4) + ((x >> 8) & mask4); // Count bits in halves
  x = (x & mask5) + ((x >> 16) & mask5); // Count bits in 32 bit word
  return x;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
/* ezThreeFourths - Calculates 3/4 of an integer value and rounds
  Input:
    x - Integer value that is to be multplied by 3/4
  Algorithm:
    * Multiply the original number by 3 and store it in a variable
    * Calculate the bias for positive and negative numbers
    * Divide the multiplication plus the bias by 4
  Output:
    ret - Returned integer value for x * 3/4
*/
int ezThreeFourths(int x) {
  int multX, bias, ret; // Define variables
  multX = x + x + x; // Multiply by 3
  bias = (multX >> 31) & 3; // Calculate bias, 0 for positive, 3 for negative
  ret = (multX + bias) >> 2; // Divide by 4
  return ret;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
/* satMul3 - Multiplies a number by three and saturates the value if needed
  Input:
    x - Integer value that is to be multiplied by 3
  Algorithm:
    * Calculate the minimum value by right shifting by 31
    * Calculate the maximum value by taking the negation of the minimum value
    * Multiply by 2
    * Get the sign of multiplication by 2
    * Multiply by 3
    * Get the sign of multiplication by 3
    * XOR the signs of the operations:
      * Original x sign and mult by 2 sign
      * Mult2 sign and mult 3 sign
    * Take the OR of the previous XORs to determine if overflow has occurred
    * Check for saturation with the sign of x and the minimum value
    * Check for saturation with the negation of the sign of x and the maximum value and OR it with the previous result
    * Determine with value to return with ANDs and an OR of the overflow variable, saturation, and mult3
  Output:
    ret - Value to be returned for the multiplcation by 3
*/
int satMul3(int x) {
  int mult2, mult3, xSign, mult2Sign, mult3Sign, overflow, tMin, tMax, sat, ret; // Define variables
  tMin = 1 << 31; // Smallest possible value
  tMax = ~tMin; // Largest possible value
  xSign = x >> 31; // Get sign of x
  mult2 = x + x; // Multiply by 2
  mult2Sign = mult2 >> 31; // Get sign of multiplication by 2
  mult3 = mult2 + x; // Multiply by 3
  mult3Sign = mult3 >> 31; // Get sign of multiplication by 3
  overflow = (xSign ^ mult2Sign) | (mult2Sign ^ mult3Sign); // Determine if overflow has occurred
  sat = xSign & tMin; // Saturation with x sign and tMin
  sat |= (~xSign) & tMax; // Saturation with negation of x sign and tMax
  ret = (overflow & sat) | (~overflow & mult3); // Determine which value to return
  return ret;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
/* bitParity - Determines the parity of the bits in an integer
  Input:
    x - Integer value whos parity is to be determined
  Algorithm:
    * Calculate the parity of each chunk of the number
    * AND the final half with one to determine the parity
  Output:
    This function returns the bit parity of an integer
*/
int bitParity(int x) {
  x ^= x >> 16; // Fold in half
  x ^= x >> 8; // Again
  x ^= x >> 4; // And again
  x ^= x >> 2; // Guess what? Again
  x ^= x >> 1; // One last time
  return x & 1;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
/* ilog2 - Calculates the integer logarithm base 2 of a given integer
  Input:
    x - Integer whose logarithm base 2 is to be calculated
  Algorithm:
    * Initialize MSB (Most Significant Bit) position as 0
    * Perform a series of bitwise shifts to determine the position of the MSB
    * In each step:
      * Use bitwise shift (>>) to check a specific range of bits in 'x'
      * The '!!' operator converts the result to 1 if any bit in the range is set, and 0 otherwise
      * Multiply this result (0 or 1) by the number of bits in the range being checked, using a left shift (<<)
      * This determines the value to add to MSB and how much to shift 'x' for the next step
    * The steps are:
      * Check upper 16 bits
      * Check next 8 bits
      * Check next 4 bits
      * Check next 2 bits
      * Check the last bit
    * Sum the shifts to find the position of the MSB
  Output:
    MSB - The position of the most significant bit in the binary representation of 'x'
*/
int ilog2(int x) {
  int MSB, shift; // Define variables
  MSB = 0; // Set MSB to zero
  shift = !(!(x >> 16)) << 4; // Upper 16
  MSB += shift; // Add MSB to shift value
  x = x >> shift; // Shift x
  shift = !(!(x >> 8)) << 3; // Next 8
  MSB += shift; // Add MSB to shift value
  x = x >> shift; // Shift x
  shift = !(!(x >> 4)) << 2; // Next 4
  MSB += shift; // Add MSB to shift value
  x = x >> shift; // Shift x
  shift = !(!(x >> 2)) << 1; // Next 2
  MSB += shift; // Add MSB to shift value
  x = x >> shift; // Shift x
  shift = !(!(x >> 1)); // Last bit
  MSB += shift; // Add MSB to shift value
  return MSB;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
/* trueThreeFourths - Multiplies an integer by 3/4 and rounds towards zero
  Input:
    x - Integer to be multiplied by 3/4
  Algorithm:
    * Calculate three-fourths of x by summing half and a quarter of x:
    * Calculate bias for rounding towards zero:
      * Extract the sign of x using right shift and AND (x >> 31) & 3
      * Isolate the lowest two bits of x using AND x & 3
      * Set the second lowest bit of x to 1 if the lowest bit is set
      * Calculate the total bias for rounding, which depends on the extracted sign and the lowest two bits
    * Add the total bias to the multiplication result
      * This step ensures proper rounding towards zero
    * The sum of the multiplication by 3/4 and the total bias forms the final result
  Output:
    ret - The result of multiplying x by 3/4, rounded towards zero
*/
int trueThreeFourths(int x)
{
  int mult34, regBias, lowest2, set2ndLowest, totalBias, ret; // Define variables
  mult34 = (x >> 1) + (x >> 2); // Multiply by three fourths
  regBias = (x >> 31) & 3; // Get bias
  lowest2 = x & 3; // Grab lowest two bits
  set2ndLowest = (x & 1) << 1; // Sets the second lowest bit to 1
  totalBias = (lowest2 + (set2ndLowest + regBias)) >> 2; // Calculate total bias
  ret = mult34 + totalBias; // Round to zero
  return ret;
}
/*
 * Extra credit
 */
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
/* float_neg - Returns the bit-level equivalent of negating a floating-point number
  Input:
    uf - An unsigned float
  Algorithm:
    * Create a mask for the sign bit (0x80000000) and a mask for NaN representation (~signMask)
    * Check if uf is a NaN:
      * Compare (uf & NaN) with the NaN check mask (0x7F800000)
      * If the value is greater, indicating it's NaN, return uf as is
    * Negate the sign of uf:
      * XOR uf with the sign mask to flip the sign bit, negating the floating-point number
      * This operation changes the sign while leaving other bits (exponent and fraction) unchanged
  Output:
    The bit-level representation of -uf if uf is not NaN, or uf itself if it is NaN
*/
unsigned float_neg(unsigned uf) {
  unsigned signMask = 0x80000000; // Mask for sign bit
  unsigned NaN = ~signMask; // Mask for NaN representation
  unsigned NaNCheck = 0x7F800000; // Mask to check for NaN
  // Check for if value is greater than NaN check
  if ((uf & NaN) > NaNCheck) {
    return uf;
  }
  // Compare original number with sign mask
  return uf ^ signMask;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/* float_i2f - Converts an integer to IEEE 754 single-precision floating point
  Input:
    x - An integer to be converted
  Algorithm:
    * Initial Check for Zero:
      * If x is 0, return 0
    * Sign Extraction:
      * Use a mask (0x80000000) to extract the sign bit from x
      * Store the sign bit in the 'sign' variable for later use in the final floating point number
    * Absolute Value Conversion:
      * If x is negative, convert it to its absolute value for further processing
    * Finding the Most Significant Bit (MSB):
      * Copy x to a temporary variable 'copy'
      * Use a while loop to right-shift 'copy' until it becomes zero
      * Increment MSB on each shift. The final value of MSB is the position of the highest set bit in x
    * Exponent Calculation:
      * Calculate the exponent for the floating point representation by adding 127 (the bias for single-precision floats) to MSB
      * This exponent is stored in the 'exponent' variable
    * Normalization and Mantissa Extraction:
      * Normalize x by left-shifting it such that its MSB is at the position of the implied bit
      * Right-shift the normalized x by 8 positions and mask the result with 0x007FFFFF to extract the 23-bit mantissa
    * Rounding:
      * Calculate the rounding decision based on the bits that are shifted out during the mantissa extraction
      * Use a combination of conditions to decide if rounding up is necessary
      * This involves checking if the most significant bit of the bits being shifted out is set and handling the round-to-nearest-even case
    * Final floating point Number Assembly:
      * Assemble the final floating point value by combining the sign bit, the exponent shifted into position, and the mantissa
      * If rounding is necessary, increment the assembled floating point number to round up
  Output:
    The bit-level representation of the IEEE 754 single-precision floating point equivalent of the input integer x
*/
unsigned float_i2f(int x) {
  unsigned int copy, exponent, mantissa, mantissaMask, MSB, ret, round, sign, signMask; // Define variables
  // Return 0 if x is 0
  if (x == 0) {
    return 0;
  }
    signMask = 0x80000000; // Mask for sign
    mantissaMask = 0x007FFFFF; // Mask for mantissa
    MSB = 0; // MSB counter
    sign = (x & signMask); // Extracting the sign bit
    // Convert to absolute value if needed
    if (x < 0) {
      x = -x;
    }
    copy = x;
    // Find the position of the MSB
    while (copy >>= 1 != 0) {
      MSB++;
    }
    exponent = MSB + 127; // Calculate the exponent
    x = x << (31 - MSB); // Normalize x
    mantissa = (x >> 8) & mantissaMask; // Extract the mantissa
    round = (x & 0xFF) > 0x80 || ((x & 0x180) == 0x180); // Handle rounding if needed
    ret = (sign | (exponent << 23) | mantissa) + round; // Final value
    return ret;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/* float_twice - Returns the bit-level equivalent of expression 2*f for a floating-point argument
  Input:
    uf - An unsigned integer representing the bit-level encoding of a single-precision floating-point value
  Algorithm:
    * Initial Check for Zero or Special Cases (NaN/Infinity):
      * If uf is 0 or if the exponent is 0xFF (indicating NaN or infinity), return uf as is
    * Masks Definition:
      * Define masks for the sign (0x80000000), exponent (0x7F800000), and mantissa (0x007FFFFF)
    * Sign Extraction:
      * Extract the sign bit from uf using the sign mask
    * Exponent and Mantissa Extraction:
      * Extract the exponent and mantissa from uf using their respective masks
    * Handling Denormalized Numbers:
      * If the exponent is 0 (denormalized number), double the mantissa
      * Check for overflow in the mantissa:
        * If overflow occurs, adjust the exponent to 1 and mask out the overflowed bit in mantissa
    * Handling Normalized Numbers:
      * If the number is normalized (exponent is not 0), increment the exponent by 1 to double the floating-point value
    * Final Floating-Point Number Assembly:
      * Reassemble the floating-point number by combining the sign, the modified exponent (shifted into position), and the mantissa
  Output:
    The bit-level representation of the IEEE 754 single-precision floating-point value equivalent to 2 times the input value uf
*/
unsigned float_twice(unsigned uf) {
  unsigned int exponent, exponentMask, mantissa, mantissaMask, ret, sign, signMask; // Define variables
  exponentMask = 0x7F800000; // Mask for exponents
  mantissaMask = 0x007FFFFF; // Mask for mantissa
  signMask = 0x80000000; // Mask for sign
  sign = (uf & signMask); // Extracting the sign bit
  exponent = (uf & exponentMask) >> 23; // Calculate exponent
  mantissa = (uf & mantissaMask); // Calculate mantissa
  // Check for overflow - return uf if true
  if (uf == 0 || exponent == 0xFF) {
    return uf;
  }
  // Check for denormalized value
  if (exponent == 0) {
    mantissa <<= 1; // Double by left shifting
    // Check for overflow of mantissa
    if (mantissa & 0x00800000) {
      exponent = 1; // Reset the exponent
      mantissa &= mantissaMask; // Mask out overflow
    }
  }
  // Handle normalized case
  else {
    exponent++; // Increment exponent (Add 1 to exp in IEEE)
  }
  ret = (sign | (exponent << 23) | mantissa); // Combine all values
  return ret;
}