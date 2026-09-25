/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x) | (~y));  // 徳·摩根律
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~((~x) & (~y));  // 真值表
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (((!x) && y) ^ (x && !y)) {
        return 0;
    }
    if (((x >> 31) & 1) ^ ((y >> 31) & 1)) {
        return 0;
    }
    return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0;

    int a = (v >> 16) > 0;
    int b = a << 4;
    v = v >> b;
    result |= b;

    a = (v >> 8) > 0;
    b = a << 3;
    v = v >> b;
    result |= b;

    a = (v >> 4) > 0;
    b = a << 2;
    v = v >> b;
    result |= b;

    a = (v >> 2) > 0;
    b = a << 1;
    v = v >> b;
    result |= b;

    a = (v >> 1) > 0;
    result |= a;

    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int move1 = n << 3;
    int move2 = m << 3;
    int a = (x >> move1) & (0x000000FF);
    int b = (x >> move2) & (0x000000FF);
    x = x & (~(0x000000FF << move1)) & (~(0x000000FF << move2));
    x = x | (a << move2) | (b << move1);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v & 0x55555555) << 1) | ((v >> 1) & 0x55555555);
    v = ((v & 0x33333333) << 2) | ((v >> 2) & 0x33333333);
    v = ((v & 0x0F0F0F0F) << 4) | ((v >> 4) & 0x0F0F0F0F);
    v = ((v & 0x00FF00FF) << 8) | ((v >> 8) & 0x00FF00FF);
    v = ((v & 0x0000FFFF) << 16) | ((v >> 16) & 0x0000FFFF);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x = x >> n;
    x = x & ((1 << (31 + (~n + 1)) << 1) + (~1 + 1));
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int sign = x >> 31;
    x = (~x) & sign;
    int result = 0;

    int a = !!(x >> 16);
    int b = a << 4;
    x = x >> b;
    result += b;

    a = !!(x >> 8);
    b = a << 3;
    x = x >> b;
    result += b;

    a = !!(x >> 4);
    b = a << 2;
    x = x >> b;
    result += b;

    a = !!(x >> 2);
    b = a << 1;
    x = x >> b;
    result += b;

    a = !!(x >> 1);
    x = x >> a;
    result += a + x;

    result = (32 + (~result + 1)) & sign;
    return result;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (!x) {
        return 0;
    }
    unsigned ux = x;
    int s = ux & 0x80000000;
    if (s) {
        ux = -ux;
    }
    int e = 0;
    unsigned temp = ux;
    while (temp >> 1) {
        temp = temp >> 1;
        e = e + 1;
    }
    int E = e + 127;
    unsigned M = 0;
    if (e <= 23) {
        M = (ux & ((1 << e) - 1)) << (23 - e);
    } else {
        unsigned keep = (ux >> (e - 23)) & 0x7FFFFF;
        unsigned drop = ux & ((1 << (e - 23)) - 1);
        unsigned half = 1 << (e - 24);
        if ((drop + (keep & 1)) > half) {
            keep += 1;
        }
        M = keep;
    }
    unsigned result = s + (E << 23) + M;
    return result;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    if (((uf >> 23) & 0xFF) == 255) {
        return uf;
    }
    if (!((uf >> 23) & 0xFF)) {  // E=0
        if ((uf >> 22) & 1) {
            return (uf & 0x80000000) | (1 << 23) | ((uf & 0x003FFFFF) << 1);
        }
        return (uf & 0xFF800000) | ((uf & 0x003FFFFF) << 1);
    }
    if (((uf >> 23) & 0xFF) == 254) {
        return (uf & 0x80000000) | (0xFF << 23) | ((uf & 0x007FFFFF));
    }
    return uf + 0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int s = (uf2 >> 31) & 1;
    int E = (uf2 >> 20) & 0x7FF;
    int uf3 = uf2 & 0xFFFFF;
    int e = E - 1023;
    if (e < 0) {
        return 0;
    }
    if (e >= 31) {
        return 0x80000000;
    }
    int x;
    if (e <= 20) {
        x = (1 << e) | (uf3 >> (20 - e));
    } else {
        x = (1 << e) | (uf3 << (e - 20)) | (uf1 >> (52 - e));
    }
    if (s) {
        return -x;
    }

    return x;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }
    if (x > 127) {
        return 0x7F800000;
    }
    if (x < -126) {
        return (1 << (149 + x));
    }
    return ((x + 127) << 23);
}
