/*
 *  NimbleBigNumber.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleBigNumber_h
#define NimbleBigNumber_h

#include <stdint.h>

#include "NimbleMemory.h"

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute((always_inline))
#endif
#ifndef NULL
#define NULL (void *) 0
#endif

typedef struct BigInt {
    uint32_t * number;
    uint32_t size;
} BigInt;

typedef struct BigDec {
    BigInt integer;
    BigInt decimal;
    uint32_t leadingZeros;
} BigDec;

/* BIG INTEGER */

// NOTE: Big integers have the same format as a signed integer in little endian, with the sign bit as the MSB.
// Returns a big integer defined as string.
extern BigInt nimbleBigIntFromString(const char * string, uint32_t * error);

// Returns big integer x as a string.
extern char * nimbleBigIntToString(const BigInt x, uint32_t * error);

// Frees a big integer.
ALWAYS_INLINE void nimbleBigIntFree(BigInt x)
{
    nimbleMemoryFree(x.number, x.size * sizeof(uint32_t));
    x.size = 0;
}

// Returns x + y.
extern int32_t nimbleBigIntAdd(const BigInt x, const BigInt y, BigInt result);

// Returns x - y.
extern int32_t nimbleBigIntSub(const BigInt x, const BigInt y, BigInt result);

// Returns x * y.
extern int32_t nimbleBigIntMul(const BigInt x, const BigInt y, BigInt result);

// Returns x / y.
extern int32_t nimbleBigIntDiv(const BigInt x, const BigInt y, BigInt result);

// Returns x % y.
extern int32_t nimbleBigIntMod(const BigInt x, const BigInt y, BigInt result);

// Returns x ^ y.
extern int32_t nimbleBigIntPow(const BigInt x, const BigInt y, BigInt result);

// Returns x == y.
extern int32_t nimbleBigIntTET(const BigInt x, const BigInt y);

// Returns x > y.
extern int32_t nimbleBigIntTGT(const BigInt x, const BigInt y);

// Returns x < y.
extern int32_t nimbleBigIntTLT(const BigInt x, const BigInt y);

// Returns x >= y.
extern int32_t nimbleBigIntTGE(const BigInt x, const BigInt y);

// Returns x <= y.
extern int32_t nimbleBigIntTLE(const BigInt x, const BigInt y);

// Returns x as a BigDec.
extern BigDec nimbleBigIntToBigDec(const BigInt x);

/* BIG DECIMAL */

// NOTE: Big decimal consists of two big integers: one for the integer and one for the decimal. The decimal big integer does not have a signed bit.
// Returns a big decimal defined as string.
extern BigDec nimbleBigDecFromString(const char * string, uint32_t * error);

// Returns big decimal x as a string.
extern char * nimbleBigDecToString(const BigDec x, uint32_t * error);

// Frees a big decimal.
ALWAYS_INLINE void nimbleBigDecFree(BigDec x)
{
    nimbleMemoryFree(x.integer.number, x.integer.size * sizeof(uint32_t));
    x.integer.size = 0;
    nimbleMemoryFree(x.decimal.number, x.decimal.size * sizeof(uint32_t));
    x.decimal.size = 0;
}

// Returns x + y.
extern int32_t nimbleBigDecAdd(const BigDec x, const BigDec y, BigDec result);

// Returns x - y.
extern int32_t nimbleBigDecSub(const BigDec x, const BigDec y, BigDec result);

// Returns x * y.
extern int32_t nimbleBigDecMul(const BigDec x, const BigDec y, BigDec result);

// Returns x / y.
extern int32_t nimbleBigDecDiv(const BigDec x, const BigDec y, BigDec result);

// Returns x % y.
extern int32_t nimbleBigDecMod(const BigDec x, const BigDec y, BigDec result);

// Returns x ^ y.
extern int32_t nimbleBigDecPow(const BigDec x, const BigDec y, BigDec result);

// Returns x rounded up.
extern int32_t nimbleBigDecCeil(const BigDec x, BigDec result);

// Returns x rounded down.
extern int32_t nimbleBigDecFloor(const BigDec x, BigDec result);

// Returns x == y.
extern int32_t nimbleBigDecTET(const BigDec x, const BigDec y);

// Returns x > y.
extern int32_t nimbleBigDecTGT(const BigDec x, const BigDec y);

// Returns x < y.
extern int32_t nimbleBigDecTLT(const BigDec x, const BigDec y);

// Returns x >= y.
extern int32_t nimbleBigDecTGE(const BigDec x, const BigDec y);

// Returns x <= y.
extern int32_t nimbleBigDecTLE(const BigDec x, const BigDec y);

#endif /* BigNumber_h */

// NimbleBigNumber.h
