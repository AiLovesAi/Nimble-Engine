/*
 *  NimbleMath.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#include "NimbleMath.h"


// Returns the number of digits in unsigned 64-bit integer x.
uint8_t nimbleMathDigits64u(const uint64_t x)
{
    return (x >= 10000000000000000000UL) ? 20 : (x >= 1000000000000000000UL) ? 19 :
    (x >= 100000000000000000UL) ? 18 : (x >= 10000000000000000UL) ? 17 :
    (x >= 1000000000000000UL) ? 16 : (x >= 1000000000000000UL) ? 15 :
    (x >= 10000000000000UL) ? 14 : (x >= 1000000000000UL) ? 13 :
    (x >= 100000000000UL) ? 12 : (x >= 10000000000UL) ? 11 :
    (x >= 1000000000UL) ? 10 : (x >= 100000000UL) ? 9 : (x >= 10000000UL) ? 8 :
    (x >= 1000000UL) ? 7 : (x >= 100000UL) ? 6 : (x >= 10000UL) ? 5 :
    (x >= 1000UL) ? 4 : (x >= 100UL) ? 3 : (x >= 10UL) ? 2 : 1;
}

// Returns the number of digits in 64-bit integer x.
uint8_t nimbleMathDigits64(const int64_t x)
{
    const int64_t absx = (((x >> 63) | 1) * x);
    return ((x == (-9223372036854775807L - 1L)) || (absx >= 1000000000000000000UL)) ? 19 : (absx >= 100000000000000000UL) ? 18 : // NOTE: The negative sign is ignored by the compiler when deciding how large 9,223,372,036,854,775,808 is, so subtract one from the highest positive value to keep it from complaining.
    (absx >= 10000000000000000UL) ? 17 : (absx >= 1000000000000000UL) ? 16 :
    (absx >= 1000000000000000UL) ? 15 : (absx >= 10000000000000UL) ? 14 :
    (absx >= 1000000000000UL) ? 13 : (absx >= 100000000000UL) ? 12 : (absx >= 10000000000UL) ? 11 :
    (absx >= 1000000000UL) ? 10 : (absx >= 100000000UL) ? 9 : (absx >= 10000000UL) ? 8 :
    (absx >= 1000000UL) ? 7 : (absx >= 100000UL) ? 6 : (absx >= 10000UL) ? 5 :
    (absx >= 1000UL) ? 4 : (absx >= 100UL) ? 3 : (absx >= 10UL) ? 2 : 1;
}

// Returns the number of digits in unsigned 32-bit integer x.
uint8_t nimbleMathDigits32u(const uint32_t x)
{
    return (x >= 1000000000UL) ? 10 : (x >= 100000000UL) ? 9 : (x >= 10000000UL) ? 8 :
    (x >= 1000000UL) ? 7 : (x >= 100000UL) ? 6 : (x >= 10000UL) ? 5 :
    (x >= 1000UL) ? 4 : (x >= 100UL) ? 3 : (x >= 10UL) ? 2 : 1;
}

// Returns the number of digits in 32-bit integer x.
uint8_t nimbleMathDigits32(const int32_t x)
{
    const int32_t absx = (((x >> 31) | 1) * x);
    return ((x == -2147483648L) || (absx >= 1000000000UL)) ? 10 : (absx >= 100000000UL) ? 9 : (absx >= 10000000UL) ? 8 :
    (absx >= 1000000UL) ? 7 : (absx >= 100000UL) ? 6 : (absx >= 10000UL) ? 5 :
    (absx >= 1000UL) ? 4 : (absx >= 100UL) ? 3 : (absx >= 10UL) ? 2 : 1;
}

// Returns the number of digits in unsigned 16-bit integer x.
uint8_t nimbleMathDigits16u(const uint16_t x)
{
    return (x >= 10000UL) ? 5 : (x >= 1000UL) ? 4 : (x >= 100UL) ? 3 : (x >= 10UL) ? 2 : 1;
}

// Returns the number of digits in 16-bit integer x.
uint8_t nimbleMathDigits16(const int16_t x)
{
    const int16_t absx = (((x >> 15) | 1) * x);
    return ((x == -32768L) || (absx >= 10000UL)) ? 5 : (absx >= 1000UL) ? 4 :
    (absx >= 100UL) ? 3 : (absx >= 10UL) ? 2 : 1;
}

// Returns the number of digits in float x.
uint8_t nimbleMathDigitsF(const float x, uint32_t * error)
{
    uint8_t count = nimbleMathDigits64(nimbleMathFloorF(x, error));
    float num = fabs(x);
    num -= nimbleMathFloorF(num, error);
    while (num >= 0.00000001f)
    {
        num *= 10;
        count++;
        num -= nimbleMathFloorF(num, error);
    }
    
    return count;
}

// Returns the number of digits in double x.
uint8_t nimbleMathDigitsD(const double x, uint32_t * error)
{
    uint8_t count = nimbleMathDigits64(nimbleMathFloorD(x, error));
    double num = fabs(x);
    num -= nimbleMathFloorD(num, error);
    while (num >= 0.0000000000000001)
    {
        num *= 10;
        count++;
        num -= nimbleMathFloorD(num, error);
    }
    
    return count;
}


// NimbleMath.c
