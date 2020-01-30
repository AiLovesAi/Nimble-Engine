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
} BigInt_t;

typedef struct BigDec {
    BigInt_t integer;
    BigInt_t decimal;
    uint32_t leadingZeros;
} BigDec_t;

/* BIG INTEGER */

// NOTE: Big integers have the same format as a signed integer in little endian, with the sign bit as the MSB.
// Returns a big integer defined as string.
extern BigInt_t nimbleBigIntFromString(const char * string, uint32_t * error);

// Returns big integer x as a string.
extern char * nimbleBigIntToString(const BigInt_t x, uint64_t * length, uint32_t * error);

// Frees a big integer.
ALWAYS_INLINE void nimbleBigIntFree(BigInt_t x)
{
    nimbleMemoryFree(x.number, x.size * sizeof(uint32_t));
    x.size = 0;
}

// Returns x + y.
extern int32_t nimbleBigIntAdd(const BigInt_t x, const BigInt_t y, BigInt_t result);

// Returns x - y.
extern int32_t nimbleBigIntSub(const BigInt_t x, const BigInt_t y, BigInt_t result);

// Returns x * y.
extern int32_t nimbleBigIntMul(const BigInt_t x, const BigInt_t y, BigInt_t result);

// Returns x / y.
extern int32_t nimbleBigIntDiv(const BigInt_t x, const BigInt_t y, BigInt_t result);

// Returns x % y.
extern int32_t nimbleBigIntMod(const BigInt_t x, const BigInt_t y, BigInt_t result);

// Returns x ^ y.
extern int32_t nimbleBigIntPow(const BigInt_t x, const BigInt_t y, BigInt_t result);

// Returns x == y.
extern int32_t nimbleBigIntTET(const BigInt_t x, const BigInt_t y);

// Returns x > y.
extern int32_t nimbleBigIntTGT(const BigInt_t x, const BigInt_t y);

// Returns x < y.
extern int32_t nimbleBigIntTLT(const BigInt_t x, const BigInt_t y);

// Returns x >= y.
extern int32_t nimbleBigIntTGE(const BigInt_t x, const BigInt_t y);

// Returns x <= y.
extern int32_t nimbleBigIntTLE(const BigInt_t x, const BigInt_t y);

// Returns x as a BigDec.
extern BigDec_t nimbleBigIntToBigDec(const BigInt_t x);

/* BIG DECIMAL */

// NOTE: Big decimal consists of two big integers: one for the integer and one for the decimal. The decimal big integer does not have a signed bit.
// Returns a big decimal defined as string.
extern BigDec_t nimbleBigDecFromString(const char * string, uint32_t * error);

// Returns big decimal x as a string.
char * nimbleBigDecToString(const BigDec_t x, uint64_t * length, uint32_t * error);

// Frees a big decimal.
ALWAYS_INLINE void nimbleBigDecFree(BigDec_t x)
{
    nimbleMemoryFree(x.integer.number, x.integer.size * sizeof(uint32_t));
    x.integer.size = 0;
    nimbleMemoryFree(x.decimal.number, x.decimal.size * sizeof(uint32_t));
    x.decimal.size = 0;
}

// Returns x + y.
extern int32_t nimbleBigDecAdd(const BigDec_t x, const BigDec_t y, BigDec_t result);

// Returns x - y.
extern int32_t nimbleBigDecSub(const BigDec_t x, const BigDec_t y, BigDec_t result);

// Returns x * y.
extern int32_t nimbleBigDecMul(const BigDec_t x, const BigDec_t y, BigDec_t result);

// Returns x / y.
extern int32_t nimbleBigDecDiv(const BigDec_t x, const BigDec_t y, BigDec_t result);

// Returns x % y.
extern int32_t nimbleBigDecMod(const BigDec_t x, const BigDec_t y, BigDec_t result);

// Returns x ^ y.
extern int32_t nimbleBigDecPow(const BigDec_t x, const BigDec_t y, BigDec_t result);

// Rounds x down and stores it in result.
extern int32_t nimbleBigDecFloor(const BigDec_t x, BigDec_t result);

// Rounds x up and stores it in result.
extern int32_t nimbleBigDecCeil(const BigDec_t x, BigDec_t result);

// Rounds x down at digit "precision" and stores it in result.
extern int32_t nimbleBigDecFloorToPrecision(const BigDec_t x, const uint32_t precision, BigDec_t result);

// Rounds x up at digit "precision" and stores it in result.
extern int32_t nimbleBigDecCeilToPrecision(const BigDec_t x, const uint32_t precision, BigDec_t result);

// Rounds x down and stores it in result as a big integer.
extern int32_t nimbleBigDecFloorToBigInt(const BigDec_t x, BigInt_t result);

// Rounds x up and stores it in result as a big integer.
extern int32_t nimbleBigDecCeilToBigInt(const BigDec_t x, BigInt_t result);

// Returns x == y.
extern int32_t nimbleBigDecTET(const BigDec_t x, const BigDec_t y);

// Returns x > y.
extern int32_t nimbleBigDecTGT(const BigDec_t x, const BigDec_t y);

// Returns x < y.
extern int32_t nimbleBigDecTLT(const BigDec_t x, const BigDec_t y);

// Returns x >= y.
extern int32_t nimbleBigDecTGE(const BigDec_t x, const BigDec_t y);

// Returns x <= y.
extern int32_t nimbleBigDecTLE(const BigDec_t x, const BigDec_t y);

#endif /* BigNumber_h */

// NimbleBigNumber.h
