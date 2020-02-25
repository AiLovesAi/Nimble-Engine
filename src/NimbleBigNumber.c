/*
 *  NimbleBigNumber.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NimbleBigNumber.h"
#include "NimbleError.h"
#include "NimbleMath.h"

// TODO Nullable types (*length can be null, BigInt_t * instead of BigInt_t)

#define BIG_INT_NULL(x) (!x.number || !x.size)
#define BIG_DEC_NULL(x) (!x.integer.number || !x.integer.size || !x.decimal.number || !x.decimal.size)

#define DIGITS_PER_BYTE 2.40823996531 // log2(256) / log2(10)

uint32_t uintStringToBinary(const char * string, const uint64_t digits, BigInt_t result, uint32_t * leadingZeros)
{
    char * convertedString = nimbleMemoryAllocate(digits);
    
    for (uint32_t i = 0; i < digits; i++)
    {
        convertedString[i] = string[i] - '0'; // Convert to base 10 digits
    }
    
    const char * buffer          = convertedString;
    uint8_t      remainingDigits = digits;
    uint8_t      remainder       = 0;
    uint8_t      nextRemainder   = 0;
    uint8_t      i               = 0;
    uint8_t      firstNonZero    = 0;
    uint32_t     byte            = result.size;
    for (uint64_t bit = 0; (remainingDigits || (*convertedString)); bit++) // While convertedString != "0"
    {
        
        if (!(*buffer))
        {
            // Skip leading zeros.
            
            while (!(*buffer) && (firstNonZero < digits))
            {
                firstNonZero++;
                buffer++;
            }
            
            remainingDigits = digits - firstNonZero;
        }
        
        if (leadingZeros && !(*leadingZeros))
        {
            *leadingZeros = firstNonZero;
        }
        
        for (i = firstNonZero; i < digits; i++)
        {
            nextRemainder = (convertedString[i] % 2) ? 5 : 0;
            convertedString[i] = nimbleMathFloorF((convertedString[i] / 2), NULL) + remainder;
            remainder = nextRemainder;
        }
        
        if (!(bit % 32))
        {
            byte--;
            result.number[byte] = 0;
        }
        
        result.number[byte] = remainder ? (result.number[byte] | (1 << (bit % 32))) : (result.number[byte] & ~(1 << (bit % 32))); // Set bit if remainder, clear bit otherwise.
        remainder = 0;
    }
    
    if (leadingZeros && *leadingZeros == firstNonZero)
    {
        *leadingZeros = 0;
    }
    
    nimbleMemoryFree(convertedString, digits);
    
    return byte;
}


// NOTE: Big integers have the same format as a signed integer in little endian, with the sign bit as the MSB.
// Returns a big integer defined as string.
BigInt_t nimbleBigIntFromString(const char * string, uint32_t * error)
{
    BigInt_t result = {};
    
    if (!string)
    {
        
        if (error)
        {
            *error = NIMBLE_ERROR_GENERAL_NULL;
        }
        
        return result;
    }
    
    const uint8_t sign = (string[0] == '-');
    const char * signlessString = string + sign;
    const uint64_t digits = strlen(signlessString);
    
    if (digits > UINT32_MAX)
    {
        *error = NIMBLE_ERROR_BIGNUM_OVERFLOW;
        return result;
    }
    
    if (!digits || (signlessString[0] == '0'))
    {
        result.size = 1;
        result.number = nimbleMemoryAllocate(sizeof(uint32_t));
        result.number[0] = 0;
        return result;
    }
    
    result.size = (uint32_t) nimbleMathCeilD(digits / DIGITS_PER_BYTE, NULL) + sign;
    result.number = nimbleMemoryAllocate((sizeof(uint32_t) * result.size));
    
    uint32_t byte = uintStringToBinary(signlessString, digits, result, NULL);
    
    if(byte)
    {
        result.number[byte - 1] = 0;
    }
    
    byte -= (result.number[byte] >> 31) & 1UL; // NOTE: Put sign bit in result[byte] if the MSB is set in result[byte], otherwise use result[byte - 1].
    result.number[byte] |= sign << 31;
    
    if (byte)
    {
        result.size -= byte;
        memcpy(result.number, result.number + byte, (sizeof(uint32_t) * result.size));
        result.number = nimbleMemoryReallocate(result.number, (sizeof(uint32_t) * (result.size + byte)), (sizeof(uint32_t) * result.size));
    }
    
    return result;
}

// Returns big integer x as a string.
char * nimbleBigIntToString(const BigInt_t x, uint64_t * length, uint32_t * error)
{
    
    if (BIG_INT_NULL(x) || !length)
    {
        
        if (error)
        {
            *error = NIMBLE_ERROR_GENERAL_NULL;
        }
        
        return NULL;
    }
    
    const uint8_t sign = (x.number[0] >> 31) & 1UL;
    *length = nimbleMathCeilD((x.size * sizeof(uint32_t)) * DIGITS_PER_BYTE, error) + sign;
    char *   currentPower           = nimbleMemoryAllocate(*length + 1);
    uint64_t currentPowerLength     = 1;
    uint8_t  currentPowerRemainder  = 0;
    uint8_t  nextPowerRemainder     = 0;
    uint64_t currentResultLength    = 1;
    uint8_t  currentResultRemainder = 0;
    uint8_t  nextResultRemainder    = 0;
    uint32_t byte                   = x.size;
    currentPower[*length] = '\0';
    currentPower[*length - 1] = 1;
    char * currentPowerBuffer = currentPower + (*length - 1);
    char * result = nimbleMemoryAllocateClear(*length + 1);
    result[*length] = '\0';
    char * resultBuffer = result + (*length - 1);
    // TODO Find MSB So as to not do more work on currentPower than needed.
    
    for (uint64_t bit = 0; bit < ((x.size * 32) - 1); bit++) // Subtract one to ignore the sign bit.
    {
        
        if (!(bit % 32))
        {
            byte--;
        }
        
        if ((x.number[byte] >> bit) & 1UL)
        {
            
            for (uint64_t digit = 0; digit < currentPowerLength; digit++)
            {
                nextResultRemainder = (*resultBuffer + *currentPowerBuffer) >= 10;
                *resultBuffer = ((*resultBuffer + *currentPowerBuffer) % 10) + currentResultRemainder;
                
                if (*resultBuffer == 10)
                {
                    nextResultRemainder = 1;
                    *resultBuffer = 0;
                }
                
                currentResultRemainder = nextResultRemainder;
                resultBuffer--;
                currentPowerBuffer--;
            }
            
            if (currentResultRemainder)
            {
                *resultBuffer = 1;
                currentResultRemainder = 0;
            }
            
            resultBuffer = result + (*length - 1);
            currentPowerBuffer = currentPower + (*length - 1);
            currentResultLength = currentPowerLength;
        }
        
        for (uint64_t digit = 0; digit < currentPowerLength; digit++)
        {
            nextPowerRemainder = (*currentPowerBuffer * 2) >= 10;
            *currentPowerBuffer = ((*currentPowerBuffer * 2) % 10) + currentPowerRemainder;
            currentPowerRemainder = nextPowerRemainder;
            currentPowerBuffer--;
        }
        
        if (currentPowerRemainder)
        {
            currentPowerLength++;
            *currentPowerBuffer = 1;
            currentPowerRemainder = 0;
        }
        
        currentPowerBuffer = currentPower + (*length - 1);
    }
    
    nimbleMemoryFree(currentPower, *length + 1);
    
    if (sign)
    {
        result[*length - currentResultLength - 1] = '-';
        currentResultLength--;
    }
    
    if (*length - currentResultLength)
    {
        memcpy(result, result + currentResultLength, *length - currentResultLength);
        result = nimbleMemoryReallocate(result, *length + 1, *length - currentResultLength + 1);
        *length -= currentResultLength;
    }
    
    // Translate from number to string
    for (uint64_t digit = sign; digit < *length; digit++)
    {
        result[digit] += '0';
    }
    
    return result;
}

// Returns x + y.
int32_t nimbleBigIntAdd(const BigInt_t x, const BigInt_t y, BigInt_t result)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
#   if 0
    // TODO Negative, use result
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    BigInt_t result = nimbleMemoryAllocate(sizeof(uint32_t) * (greatestSize + 1));
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
#   endif
    return 0;
}

// Returns x - y.
int32_t nimbleBigIntSub(const BigInt_t x, const BigInt_t y, BigInt_t result)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
#   if 0
    // TODO Negative
    const uint8_t greatestSize = (xSize > ySize) ? xSize : ySize;
    *resultSize = greatestSize;
    BigInt_t result = nimbleMemoryAllocate(sizeof(uint32_t) * (greatestSize + 1));
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
#   endif
    return 0;
}

// Returns x * y.
int32_t nimbleBigIntMul(const BigInt_t x, const BigInt_t y, BigInt_t result)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Returns x / y.
int32_t nimbleBigIntDiv(const BigInt_t x, const BigInt_t y, BigInt_t result)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    if ((y.size == 1) && !y.number[0])
    {
        return NIMBLE_ERROR_MATH_DIVIDE_BY_ZERO;
    }
    
    // TODO
    return 0;
}

// Returns x % y.
int32_t nimbleBigIntMod(const BigInt_t x, const BigInt_t y, BigInt_t result)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Returns x ^ y.
int32_t nimbleBigIntPow(const BigInt_t x, const BigInt_t y, BigInt_t result)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Returns x == y.
int32_t nimbleBigIntTET(const BigInt_t x, const BigInt_t y)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    if (x.size != y.size)
    {
        return 0;
    }
    
    for (uint8_t i = 0; i < x.size; i++)
    {
        
        if (x.number[i] != y.number[i])
        {
            return 0;
        }
        
    }
    
    return 1;
}

// Returns x > y.
int32_t nimbleBigIntTGT(const BigInt_t x, const BigInt_t y)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 0;
    }
    
    if (!xNeg && yNeg)
    {
        return 1;
    }
    
    if (x.size == y.size)
    {
        
        for (uint32_t i = 0; i < x.size; i++)
        {
            
            if (x.number[i] != y.number[i])
            {
                return (x.number[i] > y.number[i]) ^ xNeg;
            }
            
        }
        
        return 0; // Equal
    }
    
    return (x.size > y.size) ^ xNeg;
}

// Returns x < y.
int32_t nimbleBigIntTLT(const BigInt_t x, const BigInt_t y)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 1;
    }
    
    if (!xNeg && yNeg)
    {
        return 0;
    }
    
    if (x.size == y.size)
    {
        
        for (uint32_t i = 0; i < x.size; i++)
        {
            
            if (x.number[i] != y.number[i])
            {
                return (x.number[i] < y.number[i]) ^ xNeg;
            }
            
        }
        
        return 0; // Equal
    }
    
    return (x.size < y.size) ^ xNeg;
}

// Returns x >= y.
int32_t nimbleBigIntTGE(const BigInt_t x, const BigInt_t y)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 0;
    }
    
    if (!xNeg && yNeg)
    {
        return 1;
    }
    
    if (x.size == y.size)
    {
        
        for (uint32_t i = 0; i < x.size; i++)
        {
            
            if (x.number[i] != y.number[i])
            {
                return (x.number[i] > y.number[i]) ^ xNeg;
            }
            
        }
        
        return 1; // Equal
    }
    
    return (x.size > y.size) ^ xNeg;
}

// Returns x <= y.
int32_t nimbleBigIntTLE(const BigInt_t x, const BigInt_t y)
{
    
    if (BIG_INT_NULL(x) || BIG_INT_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 1;
    }
    
    if (!xNeg && yNeg)
    {
        return 0;
    }
    
    if (x.size == y.size)
    {
        
        for (uint32_t i = 0; i < x.size; i++)
        {
            
            if (x.number[i] != y.number[i])
            {
                return (x.number[i] < y.number[i]) ^ xNeg;
            }
            
        }
        
        return 1; // Equal
    }
    
    return (x.size < y.size) ^ xNeg;
}

// Returns x as a big decimal.
BigDec_t nimbleBigIntToBigDec(const BigInt_t x)
{
    BigDec_t result = {};
    result.integer.number = nimbleMemoryAllocate(x.size * sizeof(uint32_t));
    result.integer.size = x.size;
    memcpy(result.integer.number, x.number, x.size * sizeof(uint32_t));
    result.decimal.number = nimbleMemoryAllocate(sizeof(uint32_t));
    result.decimal.size = 1;
    result.leadingZeros = 0;
    result.decimal.number[0] = 0;
    return result;
}

/* BIG DECIMAL */

// NOTE: Big decimal consists of two big integers: one for the integer and one for the decimal. The decimal big integer does not have a signed bit.
// Returns a big decimal defined as string.
BigDec_t nimbleBigDecFromString(const char * string, uint32_t * error)
{
    BigDec_t result = {};
    
    if (!string)
    {
        *error = NIMBLE_ERROR_GENERAL_NULL;
        return result;
    }
    
    const uint8_t sign = (string[0] == '-');
    const char * signlessString = string + sign;
    const uint64_t signlessStringLength = strlen(signlessString);
    
    int64_t decimalPosition = -1;
    uint32_t trailingZeros = 0;
    int64_t i = signlessStringLength;
    uint8_t numberFound = 0;
    
    // Find decimal and remove trailing zeros.
    do
    {
        i--;
        
        if (signlessString[i] == '.')
        {
            decimalPosition = i;
            break;
        } else if (!numberFound && (signlessString[i] == '0'))
        {
            trailingZeros++;
        } else
        {
            numberFound = 1;
        }
        
    } while (i > 0);
    
    // No decimal point; integer.
    if ((decimalPosition < 0) || (decimalPosition == signlessStringLength - 1))
    {
        char * noDecimalString = nimbleMemoryAllocate(signlessStringLength + sign + 1);
        strncpy(noDecimalString, string, signlessStringLength + 1);
        
        if (decimalPosition >= 0)
        {
            noDecimalString[decimalPosition] = '\0';
        }
        
        BigInt_t resultInteger = nimbleBigIntFromString(noDecimalString, error);
        result = nimbleBigIntToBigDec(resultInteger);
        nimbleBigIntFree(resultInteger);
        nimbleMemoryFree(noDecimalString, signlessStringLength + sign + 1);
        return result;
    }
    
    const uint64_t decimalLength = signlessStringLength - decimalPosition - trailingZeros - 1;
    
    if ((decimalPosition > UINT32_MAX) || (decimalLength > UINT32_MAX))
    {
        *error = NIMBLE_ERROR_BIGNUM_OVERFLOW;
        return result;
    }
    
    if (decimalPosition)
    {
        result.integer.size = (uint32_t) nimbleMathCeilD(decimalPosition / DIGITS_PER_BYTE, NULL) + sign;
        result.integer.number = nimbleMemoryAllocate((sizeof(uint32_t) * result.integer.size));
        uint32_t byte = uintStringToBinary(signlessString, decimalPosition, result.integer, NULL);
        
        if(byte)
        {
            result.integer.number[byte - 1] = 0;
        }
        
        byte -= (result.integer.number[byte] >> 31) & 1UL; // NOTE: Put sign bit in result[byte] if the MSB is set in result[byte], otherwise use result[byte - 1].
        result.integer.number[byte] |= sign << 31;
        
        if (byte)
        {
            result.integer.size -= byte;
            memcpy(result.integer.number, result.integer.number + byte, (sizeof(uint32_t) * result.integer.size));
            result.integer.number = nimbleMemoryReallocate(result.integer.number, (sizeof(uint32_t) * (result.integer.size + byte)), (sizeof(uint32_t) * result.integer.size));
        }
        
    } else
    {
        result.integer.number = nimbleMemoryAllocate(sizeof(uint32_t));
        result.integer.size = 1;
        result.integer.number[0] = 0;
    }
    
    result.decimal.size = (uint32_t) nimbleMathCeilD(decimalLength / DIGITS_PER_BYTE, NULL);
    result.decimal.number = nimbleMemoryAllocate((sizeof(uint32_t) * result.decimal.size));
    uint32_t byte = uintStringToBinary(signlessString + decimalPosition + 1, decimalLength, result.decimal, &result.leadingZeros);
    
    if (byte)
    {
        result.decimal.size -= byte;
        memcpy(result.decimal.number, result.decimal.number + byte, (sizeof(uint32_t) * result.decimal.size));
        result.decimal.number = nimbleMemoryReallocate(result.decimal.number, (sizeof(uint32_t) * (result.decimal.size + byte)), (sizeof(uint32_t) * result.decimal.size));
    }
    
    return result;
}

// Returns big decimal x as a string.
char * nimbleBigDecToString(const BigDec_t x, uint64_t * length, uint32_t * error)
{
    
    if (BIG_DEC_NULL(x))
    {
        *error = NIMBLE_ERROR_GENERAL_NULL;
        return NULL;
    }
    
    uint64_t integerLength = 0;
    uint64_t decimalLength = 0;
    char * result = nimbleBigIntToString(x.integer, &integerLength, error);
    
    if (*error)
    {
        return NULL;
    }
    
    const char * decimalString = nimbleBigIntToString(x.decimal, &decimalLength, error); // FIXME Use non-negative version
    
    if (*error)
    {
        return NULL;
    }
    
    *length = integerLength + decimalLength + x.leadingZeros + 1;
    result = nimbleMemoryReallocate(result, integerLength + 1, *length + 1);
    result[integerLength] = '.';
    
    for (uint64_t i = integerLength + 1; i < (integerLength + 1 + x.leadingZeros); i++)
    {
        result[i] = '0';
    }
    
    strncat(result, decimalString, decimalLength + 1);
    return result;
}

// Returns x + y.
int32_t nimbleBigDecAdd(const BigDec_t x, const BigDec_t y, BigDec_t result)
{
    // TODO
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    return 0;
}

// Returns x - y.
int32_t nimbleBigDecSub(const BigDec_t x, const BigDec_t y, BigDec_t result)
{
    // TODO
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    return 0;
}

// Returns x * y.
int32_t nimbleBigDecMul(const BigDec_t x, const BigDec_t y, BigDec_t result)
{
    // TODO
    return 0;
}

// Returns x / y.
int32_t nimbleBigDecDiv(const BigDec_t x, const BigDec_t y, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Returns x % y.
int32_t nimbleBigDecMod(const BigDec_t x, const BigDec_t y, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Returns x ^ y.
int32_t nimbleBigDecPow(const BigDec_t x, const BigDec_t y, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Rounds x down and stores it in result.
int32_t nimbleBigDecFloor(const BigDec_t x, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Rounds x up and stores it in result.
int32_t nimbleBigDecCeil(const BigDec_t x, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Rounds x down at digit "precision" and stores it in result.
int32_t nimbleBigDecFloorToPrecision(const BigDec_t x, const uint32_t precision, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Rounds x up at digit "precision" and stores it in result.
int32_t nimbleBigDecCeilToPrecision(const BigDec_t x, const uint32_t precision, BigDec_t result)
{
    
    if (BIG_DEC_NULL(x))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Rounds x down and stores it in result as a big integer.
int32_t nimbleBigDecFloorToBigInt(const BigDec_t x, BigInt_t result)
{
    
    if (BIG_DEC_NULL(x))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Rounds x up and stores it in result as a big integer.
int32_t nimbleBigDecCeilToBigInt(const BigDec_t x, BigInt_t result)
{
    
    if (BIG_DEC_NULL(x))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    // TODO
    return 0;
}

// Returns x == y.
int32_t nimbleBigDecTET(const BigDec_t x, const BigDec_t y)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    if ((x.integer.size != y.integer.size) || (x.decimal.size != y.decimal.size) || (x.leadingZeros != y.leadingZeros))
    {
        return 0;
    }
    
    for (uint8_t i = 0; i < x.integer.size; i++)
    {
        
        if (x.integer.number[i] != y.integer.number[i])
        {
            return 0;
        }
        
    }
    
    for (uint8_t i = 0; i < x.decimal.size; i++)
    {
        
        if (x.decimal.number[i] != y.decimal.number[i])
        {
            return 0;
        }
        
    }
    
    return 1;
}

// Returns x > y.
int32_t nimbleBigDecTGT(const BigDec_t x, const BigDec_t y)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.integer.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.integer.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 0;
    }
    
    if (!xNeg && yNeg)
    {
        return 1;
    }
    
    if (x.integer.size == y.integer.size)
    {
        
        for (uint32_t i = 0; i < x.integer.size; i++)
        {
            
            if (x.integer.number[i] != y.integer.number[i])
            {
                return (x.integer.number[i] > y.integer.number[i]) ^ xNeg;
            }
            
        }
        
        if (x.decimal.size == y.decimal.size)
        {
            
            for (uint32_t i = 0; i < x.decimal.size; i++)
            {
                
                if (x.decimal.number[i] != y.decimal.number[i])
                {
                    return (x.decimal.number[i] > y.decimal.number[i]) ^ xNeg;
                }
                
            }
            
            return 0; // Equal
        }
        
        return (x.decimal.size > y.decimal.size) ^ xNeg;
    }
    
    return (x.integer.size > y.integer.size) ^ xNeg;
}

// Returns x < y.
int32_t nimbleBigDecTLT(const BigDec_t x, const BigDec_t y)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.integer.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.integer.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 1;
    }
    
    if (!xNeg && yNeg)
    {
        return 0;
    }
    
    if (x.integer.size == y.integer.size)
    {
        
        for (uint32_t i = 0; i < x.integer.size; i++)
        {
            
            if (x.integer.number[i] != y.integer.number[i])
            {
                return (x.integer.number[i] < y.integer.number[i]) ^ xNeg;
            }
            
        }
        
        if (x.decimal.size == y.decimal.size)
        {
            
            for (uint32_t i = 0; i < x.decimal.size; i++)
            {
                
                if (x.decimal.number[i] != y.decimal.number[i])
                {
                    return (x.decimal.number[i] < y.decimal.number[i]) ^ xNeg;
                }
                
            }
            
            return 0; // Equal
        }
        
        return (x.decimal.size < y.decimal.size) ^ xNeg;
    }
    
    return (x.integer.size < y.integer.size) ^ xNeg;
}

// Returns x >= y.
int32_t nimbleBigDecTGE(const BigDec_t x, const BigDec_t y)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.integer.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.integer.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 0;
    }
    
    if (!xNeg && yNeg)
    {
        return 1;
    }
    
    if (x.integer.size == y.integer.size)
    {
        
        for (uint32_t i = 0; i < x.integer.size; i++)
        {
            
            if (x.integer.number[i] != y.integer.number[i])
            {
                return (x.integer.number[i] > y.integer.number[i]) ^ xNeg;
            }
            
        }
        
        if (x.decimal.size == y.decimal.size)
        {
            
            for (uint32_t i = 0; i < x.decimal.size; i++)
            {
                
                if (x.decimal.number[i] != y.decimal.number[i])
                {
                    return (x.decimal.number[i] > y.decimal.number[i]) ^ xNeg;
                }
                
            }
            
            return 1; // Equal
        }
        
        return (x.decimal.size > y.decimal.size) ^ xNeg;
    }
    
    return (x.integer.size > y.integer.size) ^ xNeg;
}

// Returns x <= y.
int32_t nimbleBigDecTLE(const BigDec_t x, const BigDec_t y)
{
    
    if (BIG_DEC_NULL(x) || BIG_DEC_NULL(y))
    {
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    const uint8_t xNeg = (x.integer.number[0] >> 31) & 1UL;
    const uint8_t yNeg = (y.integer.number[0] >> 31) & 1UL;
    
    if (xNeg && !yNeg)
    {
        return 1;
    }
    
    if (!xNeg && yNeg)
    {
        return 0;
    }
    
    if (x.integer.size == y.integer.size)
    {
        
        for (uint32_t i = 0; i < x.integer.size; i++)
        {
            
            if (x.integer.number[i] != y.integer.number[i])
            {
                return (x.integer.number[i] < y.integer.number[i]) ^ xNeg;
            }
            
        }
        
        if (x.decimal.size == y.decimal.size)
        {
            
            for (uint32_t i = 0; i < x.decimal.size; i++)
            {
                
                if (x.decimal.number[i] != y.decimal.number[i])
                {
                    return (x.decimal.number[i] < y.decimal.number[i]) ^ xNeg;
                }
                
            }
            
            return 1; // Equal
        }
        
        return (x.decimal.size < y.decimal.size) ^ xNeg;
    }
    
    return (x.integer.size < y.integer.size) ^ xNeg;
}


// NimbleBigNumber.c
