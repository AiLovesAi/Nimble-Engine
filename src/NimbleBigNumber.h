/*
 *  BigNumber.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef BigNumber_h
#define BigNumber_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL (void *) 0
#endif
#ifndef ptrSize
#define ptrSize sizeof(NULL)
#endif

/* BIG INTEGER */

// NOTE: Big integers have the same format as a signed integer, with the sign bit as the MSB.
// Returns a big integer defined as string.
extern uint8_t * nimbleBigIntFromString(const char * string, uint8_t * resultSize);

// Returns big integer x as a string.
extern char * nimbleBigIntToString(const uint8_t * x, const uint8_t xSize);

// Returns x + y.
extern uint8_t * nimbleBigIntAdd(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x - y.
extern uint8_t * nimbleBigIntDub(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x * y.
extern uint8_t * nimbleBigIntMul(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x / y.
extern uint8_t * nimbleBigIntDiv(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x % y.
extern uint8_t * nimbleBigIntMod(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x == y.
extern uint8_t nimbleBigIntTET(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x > y.
extern uint8_t nimbleBigIntTGT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x < y.
extern uint8_t nimbleBigIntTLT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x >= y.
extern uint8_t nimbleBigIntTGE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x <= y.
extern uint8_t nimbleBigIntTLE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

/* BIG DECIMAL */

// NOTE: Big decimals have the same format as a signed double, with the sign bit as the MSB. // TODO Make sure this is true in code
// Returns a big decimal defined as string.
extern uint8_t * nimbleBigDecFromString(const char * string, uint8_t * resultSize);

// Returns big decimal x as a string.
extern char * nimbleBigDecToString(const uint8_t * x, const uint8_t xSize);

// Returns x + y.
extern uint8_t * nimbleBigDecAdd(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x - y.
extern uint8_t * nimbleBigDecDub(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x * y.
extern uint8_t * nimbleBigDecMul(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x / y.
extern uint8_t * nimbleBigDecDiv(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x % y.
extern uint8_t * nimbleBigDecMod(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize);

// Returns x == y.
extern uint8_t nimbleBigDecTET(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x > y.
extern uint8_t nimbleBigDecTGT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x < y.
extern uint8_t nimbleBigDecTLT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x >= y.
extern uint8_t nimbleBigDecTGE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

// Returns x <= y.
extern uint8_t nimbleBigDecTLE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize);

#endif /* BigNumber_h */

// BigNumber.h
