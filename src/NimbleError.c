/*
 *  NimbleError.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/26/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
