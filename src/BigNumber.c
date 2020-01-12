/*
 *  BigNumber.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include "BigNumber.h"


// NOTE: Big integers have the same format as a signed integer, with the sign bit as the MSB.
// Returns a big integer defined as string.
uint8_t * nimbleBigIntFromString(const char * string, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns big integer x as a string.
char * nimbleBigIntToString(const uint8_t * x, const uint8_t xSize)
{
    // TODO
    return NULL;
}

// Returns x + y.
uint8_t * nimbleBigIntrAdd(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint8_t * result = calloc(ptrSize + greatestSize + 1, 1);
    uint8_t carry = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint8_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint8_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
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
        result = realloc(result, ptrSize + greatestSize);
    }
    
    return result;
}

// Returns x - y.
uint8_t * nimbleBigIntSub(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint8_t * result = calloc(ptrSize + greatestSize + 1, 1);
    uint8_t borrow = 0;
    uint8_t mostSignificantByte = 0;
    uint8_t dataFound = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint8_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint8_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
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
        result = realloc(result, ptrSize + 1);
        return result;
    }
    
    if (mostSignificantByte)
    {
        *resultSize -= mostSignificantByte;
        *resultSize = *resultSize ? *resultSize : 1;
        memcpy(result, result + mostSignificantByte, *resultSize);
        result = realloc(result, ptrSize + *resultSize);
    }
    
    return result;
}

// Returns x * y.
uint8_t * nimbleBigIntMul(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x / y.
uint8_t * nimbleBigIntDiv(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x % y.
uint8_t * nimbleBigIntMod(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x == y.
uint8_t nimbleBigIntTET(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    
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

// Returns x > y.
uint8_t nimbleBigIntTGT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] > y[0];
    }
    
    return xSize > ySize;
}

// Returns x < y.
uint8_t nimbleBigIntTLT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] < y[0];
    }
    
    return xSize < ySize;
}

// Returns x >= y.
uint8_t nimbleBigIntTGE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] >= y[0];
    }
    
    return xSize >= ySize;
}

// Returns x <= y.
uint8_t nimbleBigIntTLE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] <= y[0];
    }
    
    return xSize <= ySize;
}

/* BIG DECIMAL */

// NOTE: Big decimal have the same format as a signed double, with the sign bit as the MSB.
// Returns a big decimal defined as string.
uint8_t * nimbleBigDecFromString(const char * string, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns big decimal x as a string.
char * nimbleBigDecToString(const uint8_t * x, const uint8_t xSize)
{
    // TODO
    return NULL;
}

// Returns x + y.
uint8_t * nimbleBigDecrAdd(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint8_t * result = calloc(ptrSize + greatestSize + 1, 1);
    uint8_t carry = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint8_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint8_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
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
        result = realloc(result, ptrSize + greatestSize);
    }
    
    return result;
}

// Returns x - y.
uint8_t * nimbleBigDecSub(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    uint8_t * result = calloc(ptrSize + greatestSize + 1, 1);
    uint8_t borrow = 0;
    uint8_t mostSignificantByte = 0;
    uint8_t dataFound = 0;
    
    for (uint8_t index = 0; index < greatestSize; index++)
    {
        
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            const uint8_t xBit = ((index < xSize) ? ((x[xSize - index - 1] >> bitIndex) & 1UL) : 0); // Get bit bitIndex from input at index.
            const uint8_t yBit = ((index < ySize) ? ((y[ySize - index - 1] >> bitIndex) & 1UL) : 0);
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
        result = realloc(result, ptrSize + 1);
        return result;
    }
    
    if (mostSignificantByte)
    {
        *resultSize -= mostSignificantByte;
        *resultSize = *resultSize ? *resultSize : 1;
        memcpy(result, result + mostSignificantByte, *resultSize);
        result = realloc(result, ptrSize + *resultSize);
    }
    
    return result;
}

// Returns x * y.
uint8_t * nimbleBigDecMul(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x / y.
uint8_t * nimbleBigDecDiv(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x % y.
uint8_t * nimbleBigDecMod(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize, uint8_t * resultSize)
{
    // TODO
    return NULL;
}

// Returns x == y.
uint8_t nimbleBigDecTET(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    
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

// Returns x > y.
uint8_t nimbleBigDecTGT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] > y[0];
    }
    
    return xSize > ySize;
}

// Returns x < y.
uint8_t nimbleBigDecTLT(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] < y[0];
    }
    
    return xSize < ySize;
}

// Returns x >= y.
uint8_t nimbleBigDecTGE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] >= y[0];
    }
    
    return xSize >= ySize;
}

// Returns x <= y.
uint8_t nimbleBigDecTLE(const uint8_t * x, const uint8_t xSize, const uint8_t * y, const uint8_t ySize)
{
    // TODO Negative
    if (xSize == ySize)
    {
        return x[0] <= y[0];
    }
    
    return xSize <= ySize;
}


// BigNumber.c
