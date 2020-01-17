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

#ifndef NULL
#define NULL (void *) 0
#endif

/* BIG INTEGER */

// NOTE: Big integers have the same format as a signed integer in little endian, with the sign bit as the MSB.
// Returns a big integer defined as string or null if an error occurs.
extern uint32_t * nimbleBigIntFromString(const char * string, uint32_t * resultSize);

// Returns big integer x as a string or null if an error occurs.
extern char * nimbleBigIntToString(const uint32_t * x, const uint32_t xSize);

// Returns x + y or null if an error occurs.
extern uint32_t * nimbleBigIntAdd(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x - y or null if an error occurs.
extern uint32_t * nimbleBigIntDub(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x * y or null if an error occurs.
extern uint32_t * nimbleBigIntMul(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x / y or null if an error occurs.
extern uint32_t * nimbleBigIntDiv(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x % y or null if an error occurs.
extern uint32_t * nimbleBigIntMod(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x == y or -1 if an error occurs.
extern int8_t nimbleBigIntTET(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x > y or -1 if an error occurs.
extern int8_t nimbleBigIntTGT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x < y or -1 if an error occurs.
extern int8_t nimbleBigIntTLT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x >= y or -1 if an error occurs.
extern int8_t nimbleBigIntTGE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x <= y or -1 if an error occurs.
extern int8_t nimbleBigIntTLE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

/* BIG DECIMAL */

// NOTE: Big decimals have the same format as a signed double, with the sign bit as the MSB. // TODO Make sure this is true in code
// Returns a big decimal defined as string or null if an error occurs.
extern uint32_t * nimbleBigDecFromString(const char * string, uint32_t * resultSize);

// Returns big decimal x as a string or null if an error occurs.
extern char * nimbleBigDecToString(const uint32_t * x, const uint32_t xSize);

// Returns x + y or null if an error occurs.
extern uint32_t * nimbleBigDecAdd(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x - y or null if an error occurs.
extern uint32_t * nimbleBigDecDub(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x * y or null if an error occurs.
extern uint32_t * nimbleBigDecMul(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x / y or null if an error occurs.
extern uint32_t * nimbleBigDecDiv(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x % y or null if an error occurs.
extern uint32_t * nimbleBigDecMod(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize);

// Returns x == y or -1 if an error occurs.
extern int8_t nimbleBigDecTET(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x > y or -1 if an error occurs.
extern int8_t nimbleBigDecTGT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x < y or -1 if an error occurs.
extern int8_t nimbleBigDecTLT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x >= y or -1 if an error occurs.
extern int8_t nimbleBigDecTGE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

// Returns x <= y or -1 if an error occurs.
extern int8_t nimbleBigDecTLE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize);

#endif /* BigNumber_h */

// NimbleBigNumber.h
