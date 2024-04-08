/* 
 * CS:APP Data Lab 
 * 
 * Collin McDevitt cmcdev
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
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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



NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */


#endif
/* Copyright (C) 1991-2021 Free Software Foundation, Inc.
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

     
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */

int bitXor(int x, int y) {
   // xor is equivalent to ~x&y | x&~y the expresion bellow is equivalent to that by using De Morgan's laws 
   //because we can't use | 
  return ~(~(~x&y) & ~(x&~y));
}


//2
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
   //This works off the fact that in signed integer representation that 
   //All numbers to the left of some point in the digit will be the same. 
   //e.g. -10 = 1111 0110 as we can see there is 4 repeated 1's on the 'left' side
   // Similar for the case when it is positive we have 10= 0000 1010 this tells us that we only 
   //Need 5 digits to represent the number 4 for the right side and a single 1 or 0 to represent the repeated
   //digits i.e. the sign of the number. 

   //A high level overview of the function is that we check if all the digits past the n-th digit are the same 
   //I accomplish that by creating a mask that is left shifted by n-1 (the reason for n-1 instead of 1 is because the n'th bit denotes the sign ) 
   //Then there are two 'branches' that deal with weather the number is positive or negative 
   


   int negative_1= ~0;
   
   //The mask- due to what was said above we only need to examine weather all 
   //bits past n-1 are the same 
   int mask = negative_1<<(n+negative_1);

   

   //4 cases here either x is negative or positive
   //if it is positive and does not fit then (~x & mask) will be 1 note that this should always give 1 if x is positive 
   //and (x& mask) will overlap hence 1 as well 
   //The case for when x is negative is essentially the same 


   //Now if x is positive and fits we would have mask not overlap anywhere hence (x & mask )==0
   //Which after we take ! would be ! the other case where x is negative is again essentially the same due to the symmetry 
   return !(~x & mask) | !(x & mask);
}



//3
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x187654321
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */

int rotateRight(int x, int n) {
   //Works by storing the first n bits of x by shifting them over to the left 
   // Then shift over bits of x to the right and use the mask to ensure that the bits are filled in with 0 
   // Which  allows us to use or to place in the stored bits 


   //This is here because i need for the bit's that are filled in by the shift to be 0 
   int mask = (~0)^(1<<31);
   //This is getting the first n bits of x and putting them at the end and filling the rest with 0's
   int temp = x<<(32+ ~n+1);

   //the (x>>n) & mask>>(n+~0) is ensuring that the bits when right shifted are 0 and then
   //I can just use or and the temp will be placed there
return ((x>>n ) & (mask>>(n+~0)))| temp;
}

//4
/*
 * bitReverse - Reverse bits in a 32-bit word
 *   Examples: bitReverse(0x80000002) = 0x40000001
 *             bitReverse(0x89ABCDEF) = 0xF7D3D591
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int bitReverse(int x) {


      //I came up with another solution that used about 60 operators but it was harder to understand and if I am already over the limit 
      //I would rather have the solution be more readable.


      //This just grabs all the bits of the number stores them and swaps them in the return statement by controlling the shift
      int bit_0= x& 1;
      int bit_1= (x>>1) & 1;
      int bit_2= (x>>2) & 1;
      int bit_3= (x>>3) & 1;
      int bit_4= (x>>4) & 1;
      int bit_5= (x>>5) & 1;
      int bit_6= (x>>6) & 1;
      int bit_7= (x>>7) & 1;
      int bit_8= (x>>8) & 1;
      int bit_9= (x>>9) & 1;
      int bit_10= (x>>10) & 1;
      int bit_11= (x>>11) & 1;
      int bit_12= (x>>12) & 1;
      int bit_13= (x>>13) & 1;
      int bit_14= (x>>14) & 1;
      int bit_15= (x>>15) & 1;
      int bit_16= (x>>16) & 1;
      int bit_17= (x>>17) & 1;
      int bit_18= (x>>18) & 1;
      int bit_19= (x>>19) & 1;
      int bit_20= (x>>20) & 1;
      int bit_21= (x>>21) & 1;
      int bit_22= (x>>22) & 1;
      int bit_23= (x>>23) & 1;
      int bit_24= (x>>24) & 1;
      int bit_25= (x>>25) & 1;
      int bit_26= (x>>26) & 1;
      int bit_27= (x>>27) & 1;
      int bit_28= (x>>28) & 1;

      int bit_29= (x>>29) & 1;
      int bit_30= (x>>30) & 1;
      int bit_31= (x>>31) & 1;

      

      return (bit_0<<31) | (bit_1<<30) | (bit_2<<29) | (bit_3<<28) | (bit_4<<27) | (bit_5<<26) | (bit_6<<25) | (bit_7<<24) | (bit_8<<23) | (bit_9<<22) | (bit_10<<21) | (bit_11<<20) | (bit_12<<19) | (bit_13<<18) | (bit_14<<17) | (bit_15<<16) | (bit_16<<15) | (bit_17<<14) | (bit_18<<13) | (bit_19<<12) | (bit_20<<11) | (bit_21<<10) | (bit_22<<9) | (bit_23<<8) | (bit_24<<7) | (bit_25<<6) | (bit_26<<5) | (bit_27<<4) | (bit_28<<3) | (bit_29<<2) | (bit_30<<1) | (bit_31<<0);

}
