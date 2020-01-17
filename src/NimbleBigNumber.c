/*
 *  NimbleBigNumber.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NimbleBigNumber.h"
#include "NimbleEndianness.h"
#include "NimbleMath.h"
#include "NimbleMemory.h"

#define DIGITS_PER_BYTE 2.40823996531 // ceil(log2(4294967296) / log2(10))

typedef enum {
   REMAINDER = 1,           // There is a non-zero remainder
   ZERO = 2,                // The quotient is zero or null
   NULL_DECIMAL = 4,        // The dividend is null or empty
   NON_DECIMALS = 8,        // Division was terminated on non-decimal characters
   LEADING_ZERO_COUNT = 16, // Count of leading zeroes in the quotient
   LEADING_ZERO_COUNT_MASK = ~(LEADING_ZERO_COUNT - 1),
   CLR_CARRY_MASK = ~REMAINDER,
   CLR_ZERO_MASK = ~ZERO,
} DivFlags;


// NOTE: Big integers have the same format as a signed integer in little endian, with the sign bit as the MSB.
// Returns a big integer defined as string or null if an error occurs.
uint32_t * nimbleBigIntFromString(const char * string, uint32_t * resultSize)
{
    
    if (!string)
    {
        return NULL;
    }
    
    const uint8_t sign = (string[0] == '-') ? -1 : 0;
    const char * signlessString = string + sign;
    const uint32_t digits = ((uint32_t) strlen(signlessString));
    
    if (!digits)
    {
        *resultSize = sizeof(uint32_t);
        uint32_t * result = nimbleMemoryAllocate(sizeof(uint32_t));
        result[0] = sign << 31UL;
        return result;
    }
    
    *resultSize = nimbleMathCeilF(digits / DIGITS_PER_BYTE) + sign;
    uint32_t * result = nimbleMemoryAllocate((sizeof(uint32_t) * (*resultSize)));
    
    for (uint64_t i = *resultSize, j = digits + sign; i >= 0; i--, j--)
    {
        //
    }
    
    result[0] = 0;
    nimbleForceLittleEndian(result, *resultSize);
    
    if (sign)
    {
        result[(result[1] >> 31) & 1UL] |= 1UL << 31;
    }
    
    if (!result[0])
    {
        (*resultSize)--;
        memcpy(result, result + 1, (sizeof(uint32_t) * (*resultSize)));
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * (*resultSize + 1)), (sizeof(uint32_t) * (*resultSize)));
    }
    
    return result;
}

// Returns big integer x as a string or null if an error occurs.
char * nimbleBigIntToString(const uint32_t * x, const uint32_t xSize)
{
    
    if (!x)
    {
        return NULL;
    }
    
    // TODO
    
    return NULL;
}

// Returns x + y or null if an error occurs.
uint32_t * nimbleBigIntrAdd(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint32_t * result = nimbleMemoryAllocate(sizeof(uint32_t) * (greatestSize + 1));
    uint8_t carry = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint32_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint32_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
            result[greatestSize - index] ^= ((-(carry ^ (xBit ^ yBit)) ^ result[greatestSize - index]) & (1UL << bitIndex)); // Set result bit at bitIndex to xBit ^ yBit ^ carry
            carry = carry ? (xBit | yBit) : (xBit & yBit); // If already carrying, continue if either bit is 1; otherwise carry if both bits are 1.
        }
        
    }
    
    if (carry)
    {
        result[0] = 1;
        *resultSize += 1; // NOTE: Cannot use ++ as this will increment the pointer rather than the value.
    } else
    {
        memcpy(result, result + 1, *resultSize);
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * greatestSize + 1), (sizeof(uint32_t) * greatestSize));
    }
    
    return result;
}

// Returns x - y or null if an error occurs.
uint32_t * nimbleBigIntSub(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint32_t * result = nimbleMemoryAllocate(sizeof(uint32_t) * (greatestSize + 1));
    uint8_t borrow = 0;
    uint8_t mostSignificantByte = 0;
    uint8_t dataFound = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint32_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint32_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
            result[greatestSize - index - 1] ^= ((-(borrow ^ (xBit ^ yBit)) ^ result[greatestSize - index - 1]) & (1UL << bitIndex)); // Set result bit at bitIndex to xBit ^ yBit ^ borrow.
            borrow = borrow ? (!(xBit ^ yBit)) | yBit : ((!xBit) & yBit); // If already borrowing, continue if yBit is 1 or both are 0; otherwise borrow if yBit > xBit.
        }
        
        dataFound = dataFound ? 1 : (result[index] ? 0 : 1);
        mostSignificantByte = dataFound ? mostSignificantByte : index + 1; // If all bits are 0, make this the most significant used byte. If it is not, make sure to remove it in case a full byte was used.
    }
    
    if (borrow) // NOTE: Negative result, error.
    {
        result[0] = 0;
        *resultSize = 1;
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * (greatestSize + 1)), (sizeof(uint32_t)));
        return result;
    }
    
    if (mostSignificantByte)
    {
        *resultSize -= mostSignificantByte;
        *resultSize = *resultSize ? *resultSize : 1;
        memcpy(result, result + mostSignificantByte, *resultSize);
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * (greatestSize + 1)), (sizeof(uint32_t) * (*resultSize)));
    }
    
    return result;
}

// Returns x * y or null if an error occurs.
uint32_t * nimbleBigIntMul(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO
    return NULL;
}

// Returns x / y or null if an error occurs.
uint32_t * nimbleBigIntDiv(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO
    return NULL;
}

// Returns x % y or null if an error occurs.
uint32_t * nimbleBigIntMod(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO
    return NULL;
}

// Returns x == y or -1 if an error occurs.
int8_t nimbleBigIntTET(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    for (uint8_t i = 0; i < xSize; i++)
    {
        
        if (x[i] != y[i])
        {
            return 0;
        }
        
    }
    
    return 1;
}

// Returns x > y or -1 if an error occurs.
int8_t nimbleBigIntTGT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] > y[0];
    }
    
    return xSize > ySize;
}

// Returns x < y or -1 if an error occurs.
int8_t nimbleBigIntTLT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] < y[0];
    }
    
    return xSize < ySize;
}

// Returns x >= y or -1 if an error occurs.
int8_t nimbleBigIntTGE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] >= y[0];
    }
    
    return xSize >= ySize;
}

// Returns x <= y or -1 if an error occurs.
int8_t nimbleBigIntTLE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] <= y[0];
    }
    
    return xSize <= ySize;
}

/* BIG DECIMAL */

// NOTE: Big decimal have the same format as a signed double, with the sign bit as the MSB.
// Returns a big decimal defined as string or null if an error occurs.
uint32_t * nimbleBigDecFromString(const char * string, uint32_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns big decimal x as a string or null if an error occurs.
char * nimbleBigDecToString(const uint32_t * x, const uint32_t xSize)
{
    // TODO
    return NULL;
}

// Returns x + y or null if an error occurs.
uint32_t * nimbleBigDecAdd(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    // TODO
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint32_t * result = nimbleMemoryAllocate(sizeof(uint32_t) * (greatestSize + 1));
    uint8_t carry = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint32_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint32_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
            result[greatestSize - index] ^= ((-(carry ^ (xBit ^ yBit)) ^ result[greatestSize - index]) & (1UL << bitIndex)); // Set result bit at bitIndex to xBit ^ yBit ^ carry
            carry = carry ? (xBit | yBit) : (xBit & yBit); // If already carrying, continue if either bit is 1; otherwise carry if both bits are 1.
        }
        
    }
    
    if (carry)
    {
        result[0] = 1;
        *resultSize += 1; // NOTE: Cannot use ++ as this will increment the pointer rather than the value.
    } else
    {
        memcpy(result, result + 1, *resultSize);
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * greatestSize + 1), (sizeof(uint32_t) * greatestSize));
    }
    
    return result;
}

// Returns x - y or null if an error occurs.
uint32_t * nimbleBigDecSub(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    // TODO
    if (!x || !y)
    {
        return NULL;
    }
    
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint32_t * result = nimbleMemoryAllocate(sizeof(uint32_t) * (greatestSize + 1));
    uint8_t borrow = 0;
    uint8_t mostSignificantByte = 0;
    uint8_t dataFound = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint32_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint32_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
            result[greatestSize - index - 1] ^= ((-(borrow ^ (xBit ^ yBit)) ^ result[greatestSize - index - 1]) & (1UL << bitIndex)); // Set result bit at bitIndex to xBit ^ yBit ^ borrow.
            borrow = borrow ? (!(xBit ^ yBit)) | yBit : ((!xBit) & yBit); // If already borrowing, continue if yBit is 1 or both are 0; otherwise borrow if yBit > xBit.
        }
        
        dataFound = dataFound ? 1 : (result[index] ? 0 : 1);
        mostSignificantByte = dataFound ? mostSignificantByte : index + 1; // If all bits are 0, make this the most significant used byte. If it is not, make sure to remove it in case a full byte was used.
    }
    
    if (borrow) // NOTE: Negative result, error.
    {
        result[0] = 0;
        *resultSize = 1;
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * (greatestSize + 1)), (sizeof(uint32_t)));
        return result;
    }
    
    if (mostSignificantByte)
    {
        *resultSize -= mostSignificantByte;
        *resultSize = *resultSize ? *resultSize : 1;
        memcpy(result, result + mostSignificantByte, *resultSize);
        result = nimbleMemoryReallocate(result, (sizeof(uint32_t) * (greatestSize + 1)), (sizeof(uint32_t) * (*resultSize)));
    }
    
    return result;
}

// Returns x * y or null if an error occurs.
uint32_t * nimbleBigDecMul(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x / y or null if an error occurs.
uint32_t * nimbleBigDecDiv(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x % y or null if an error occurs.
uint32_t * nimbleBigDecMod(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize, uint32_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x == y or -1 if an error occurs.
int8_t nimbleBigDecTET(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    if (xSize != ySize)
    {
        return 0;
    }
    
    for (uint8_t i = 0; i < xSize; i++)
    {
        
        if (x[i] != y[i])
        {
            return 0;
        }
        
    }
    
    return 1;
}

// Returns x > y or -1 if an error occurs.
int8_t nimbleBigDecTGT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO
    if (xSize == ySize)
    {
        return x[0] > y[0];
    }
    
    return xSize > ySize;
}

// Returns x < y or -1 if an error occurs.
int8_t nimbleBigDecTLT(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO
    if (xSize == ySize)
    {
        return x[0] < y[0];
    }
    
    return xSize < ySize;
}

// Returns x >= y or -1 if an error occurs.
int8_t nimbleBigDecTGE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO
    if (xSize == ySize)
    {
        return x[0] >= y[0];
    }
    
    return xSize >= ySize;
}

// Returns x <= y or -1 if an error occurs.
int8_t nimbleBigDecTLE(const uint32_t * x, const uint32_t xSize, const uint32_t * y, const uint32_t ySize)
{
    
    if (!x || !y)
    {
        return -1;
    }
    
    // TODO
    if (xSize == ySize)
    {
        return x[0] <= y[0];
    }
    
    return xSize <= ySize;
}


// NimbleBigNumber.c
