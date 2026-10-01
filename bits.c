/* 
 * CS:APP Data Lab 
 * 
 * 黄宇浩yuhaoh666<Please put your name and userid here>
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int a = ~(~x & y);
  int b = ~(x & ~y);
  return ~(a & b);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int m = src << 3;
  int n = dst << 3;
  int a = (((0xff << m) & x) >> m) & 0xff;
  int b = ~(0xff << n) & x;
  return a << n | b;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int a = ((1 << 31) >> n) << 1;
  int b = x >> n;
  return ~a & b;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int s = 0x0f;
  int m = (s << 24) | (s << 16) | (s << 8) | s;
  int n = ~m;
  int low = (x & m) << 4;
  int high = (x & n) >> 4;
  int a = (1 << 31) >> 3;
  return low | (~a & high);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int s = x | (x + 1);
  int a = (s + 1) & ~s;
  return a;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  // 把所有位异或在一起，奇数个1会得到1，偶数个1会得到0
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int s = 1 << 31 >> 31 << n;
  int a = ~s & x;
  int t = ((1 << 31) >> n) << 1;
  int b = x >> n;
  int m = ~t & b;
  int c = a << (32 + ~n + 1);
  return m | c;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int half = 1 << (n + ~0);        // half = 2^(n-1)
  int mask_r = (1 << n) + ~0;      // mask_r = 2^n -1，取余数
  int r = x & mask_r;              // r = x mod 2^n
  int k = x >> n;                  // k = floor(x / 2^n)
  int low_r = half + ~0;           // low_r = half - 1

  int t1 = r & half;
  int b1 = !(!t1);                 // 是否置位half位
  int t2 = r & low_r;
  int b2 = !(!t2);                 // 低位是否存在1
  int cond1 = b1 & b2;             // cond1: r > half

  int t3 = r ^ half;
  int b3 = !t3;                    // r == half ?
  int t4 = k & 1;                  // k是否奇数
  int cond2 = b3 & t4;             // cond2:中点且k奇数

  int carry = cond1 | cond2;
  return (k + carry) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
    int avg = (x & y) + ((x ^ y) >> 1);
    int signX = x >> 31; // 取符号位
    int signY = y >> 31;
    // 无溢出判断 x>y
    int sameSign = !(signX ^ signY);
    int x_greater = (sameSign & ((x + ~y) >> 31 ^ 1)) | (signY & !signX);
    int oddSum = (x ^ y) & 1;
    int add = x_greater & oddSum;
    return avg + add;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    int sx = x >> 31; // 取符号位，有高位溢出风险影响结果时通常要先取符号位
    int sa = a >> 31;
    int sb = b >> 31;

    // 计算 ltxa = (x < a) ? 1 : 0
    int diffXA = sx ^ sa;
    // 异号时：如果x是负数，a是正数，则x < a成立（sx为全1，结果为-1）
    int case1XA = diffXA & sx; 
    // 同号时：x - a 不会溢出，直接看差值的符号位（同号相减必然不溢出，允许使用+和~）
    int case2XA = (!diffXA) & ((x + ~a + 1) >> 31); 
    int ltxa = (case1XA | case2XA) & 1;

    // 计算 ltxb = (x < b) ? 1 : 0
    int diffXB = sx ^ sb;
    int case1XB = diffXB & sx;
    int case2XB = (!diffXB) & ((x + ~b + 1) >> 31);
    int ltxb = (case1XB | case2XB) & 1;

    int cross = ltxa ^ ltxb; // 判断是否处于两者之间
    int equal = !(x ^ a) | !(x ^ b); // 判断是否在端点
    
    return cross | equal;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int signX = x >> 31; // 取符号位
  int signX2 = (x << 1) >> 31; // x*2的符号位
  int signX4 = (x << 2) >> 31; // x*4的符号位
  int signX5 = ((x << 2) + x) >> 31; // x*5的符号位
  int isOverflow = (signX ^ signX2) | (signX ^ signX4) | (signX ^ signX5); // 判断是否溢出
  return (isOverflow & (~signX + (1 << 31))) | (~isOverflow & (x + (x << 2)));
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    // 1. 获取三个数的符号位
    int signX = x >> 31;
    int signY = y >> 31;
    int signZ = z >> 31;
    int signS1 = (x + y) >> 31;
    int signS2 = (x + y + z) >> 31;

    // 计算 o1 (x+y 的溢出状态)
    int same_sign_xy = ~(signX ^ signY);      // x和y同号时为全1 (-1)
    int diff_sign_xy_s1 = signX ^ signS1;     // 结果符号与加数不同时为全1 (-1)
    int overflow1 = same_sign_xy & diff_sign_xy_s1; // 发生溢出时为全1
    int o1 = overflow1 & (1 | signX);         // 正溢出为1，负溢出为-1

    // 计算 o2 (s1+z 的溢出状态)
    int same_sign_s1z = ~(signS1 ^ signZ);
    int diff_sign_s1z_s2 = signS1 ^ signS2;
    int overflow2 = same_sign_s1z & diff_sign_s1z_s2;
    int o2 = overflow2 & (1 | signS1);        // 正溢出为1，负溢出为-1

    int total_ov = o1 + o2;
    return (total_ov >> 31) | (!!total_ov);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFFU;
    unsigned frac = uf & 0x7FFFFFU;

    // NaN / Inf
    if (exp == 0xFFU) return uf;

    // 非规格化 / ±0
    if (exp == 0U) {
        if (frac == 0U) return uf;          // 保留 ±0
        unsigned product = frac * 3U;
        unsigned q = product >> 1;
        unsigned r = product & 1U;
        if (r && (q & 1U)) q++;             // round to nearest even
        return (sign << 31) | q;            // 可能直接变成规格化数
    }

    // 规格化数
    unsigned val = (1U << 23) | frac;
    unsigned product = val * 3U;
    int exp_inc = 0;
    unsigned new_val;

    if (product < (1U << 25)) {             // 结果 < 2
        unsigned q = product >> 1;
        unsigned r = product & 1U;
        if (r && (q & 1U)) q++;
        new_val = q;
    } else {                                // 结果 >= 2
        unsigned q = product >> 2;
        unsigned r = product & 3U;
        if (r > 2U || (r == 2U && (q & 1U))) q++;
        new_val = q;
        exp_inc = 1;
    }

    // 处理舍入导致的进位到 2^24
    if (new_val >= (1U << 24)) {
        new_val >>= 1;
        exp_inc++;
    }

    unsigned new_exp = exp + exp_inc;
    if (new_exp >= 0xFFU) {
        return (sign << 31) | (0xFFU << 23); // 溢出为无穷大
    }
    unsigned frac_out = new_val & 0x7FFFFFU;
    return (sign << 31) | (new_exp << 23) | frac_out;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFFU;
    unsigned frac = uf & 0x7FFFFFU;

    if (exp == 0xFFU) return uf;            // NaN / Inf

    int e = (int)exp - 127;

    if (e < 0) {
        if (e == -1) {                      // 值在 [0.5, 1)
            if (frac > 0) {
                return (sign << 31) | (127U << 23); // 舍入到 1.0
            } else {
                return (sign << 31);        // 正好 0.5 -> 0，保留符号
            }
        } else {
            return (sign << 31);            // < 0.5 -> 0，保留符号
        }
    }

    if (e >= 23) return uf;                 // 已经是整数

    // 0 <= e < 23，有小数部分
    unsigned shift = 23 - e;
    unsigned mask = (1U << shift) - 1U;
    unsigned frac_frac = frac & mask;       // 小数部分
    unsigned frac_int = frac & (~mask);     // 整数部分在 frac 中的高位
    unsigned half = 1U << (shift - 1U);

    if (frac_frac > half) {
        frac_int += (1U << shift);
    } else if (frac_frac == half) {
        // tie to even：完整整数部分的最低位
        unsigned int_lsb = ((1U << e) | (frac_int >> shift)) & 1U;
        if (int_lsb) {
            frac_int += (1U << shift);
        }
    }

    if (frac_int == (1U << 23)) {
        frac_int = 0U;
        exp += 1U;
    }

    return (sign << 31) | (exp << 23) | frac_int;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    if (x == 0) return 0U;

    unsigned sign = 0U;
    unsigned abs_x = x;
    if (x < 0) {
        sign = 1U;
        abs_x = -x;                         // 对 INT_MIN 也能得到 0x80000000
    }

    // 找最高位位置 n
    unsigned tmp = abs_x;
    int n = 0;
    while (tmp >>= 1U) n++;

    unsigned exp = n + 127U;
    unsigned frac;
    int shift = 23 - n;

    if (shift >= 0) {
        frac = abs_x << shift;
        frac &= 0x7FFFFFU;
    } else {
        shift = -shift;
        unsigned mask = (1U << shift) - 1U;
        unsigned lost_bits = abs_x & mask;
        frac = (abs_x >> shift) & 0x7FFFFFU; // 立即屏蔽隐含 1
        unsigned guard = lost_bits >> (shift - 1U);
        if (guard) {
            if (lost_bits > (1U << (shift - 1U))) {
                frac += 1U;
            } else {
                if (frac & 1U) frac += 1U;   // tie to even
            }
        }
        if (frac == (1U << 23)) {            // 尾数溢出，指数加 1
            frac = 0U;
            exp += 1U;
        }
    }

    return (sign << 31) | (exp << 23) | frac;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55;
  m1 = m1 | (m1 << 8);
  m1 = m1 | (m1 << 16);

  int m2 = 0x33;
  m2 = m2 | (m2 << 8);
  m2 = m2 | (m2 << 16);

  int m4 = 0x0F;
  m4 = m4 | (m4 << 8);
  m4 = m4 | (m4 << 16);

  x = x + ~((x >> 1) & m1) + 1;
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
  int m16 = 0xFF | (0xFF << 8);
  int m8 = m16 ^ (m16 << 8);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);

  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);

  return ((x >> 16) & m16) | (x << 16);

}
