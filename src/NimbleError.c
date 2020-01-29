/*
 *  NimbleError.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/26/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include <string.h>

#include "NimbleError.h"
#include "NimbleMemory.h"

// Returns a string description of error.
char * nimbleErrorString(const uint32_t errorCode)
{
    char * output = NULL;
    
    switch (errorCode)
    {
        
        // GENERAL ERRORS
        case NIMBLE_ERROR_GENERAL_NULL:
        {
            char errorString[] = "Unexpected null pointer in function.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        // MATH ERRORS
        case NIMBLE_ERROR_MATH_OVERFLOW:
        {
            char errorString[] = "Math operation was too large and would overflow.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        case NIMBLE_ERROR_MATH_DIVIDE_BY_ZERO:
        {
            char errorString[] = "Math function divisor input was zero.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        // BIG NUMBER ERRORS
        case NIMBLE_ERROR_BIGNUM_OVERFLOW:
        {
            char errorString[] = "Big number function input was too large and would overflow memory.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        
        default:
        {
            char errorString[] = "Unknown error code.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
    }
    
    return output;
}


// NimbleError.c
