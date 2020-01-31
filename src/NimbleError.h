/*
 *  NimbleError.h
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
 #include "NimbleLicense.c"

#ifndef NimbleError_h
#define NimbleError_h

#include <stdint.h>


// ERROR TYPES
#define NIMBLE_ERROR_GENERAL (0x00 << 24) | (1UL << 31)
#define NIMBLE_ERROR_MATH    (0x01 << 24) | (1UL << 31)
#define NIMBLE_ERROR_BIGNUM  (0x02 << 24) | (1UL << 31)

// GENERAL ERRORS
#define NIMBLE_ERROR_GENERAL_NULL NIMBLE_ERROR_GENERAL | 0x000001 // Unexpected null pointer in function.

// MATH ERRORS
#define NIMBLE_ERROR_MATH_OVERFLOW        NIMBLE_ERROR_MATH | 0x000001 // Math operation was too large and would overflow.
#define NIMBLE_ERROR_MATH_DIVIDE_BY_ZERO  NIMBLE_ERROR_MATH | 0x000002 // Math function divisor input was zero.

// BIG NUMBER ERRORS
#define NIMBLE_ERROR_BIGNUM_OVERFLOW NIMBLE_ERROR_BIGNUM | 0x000001 // Big number function input was too large and would overflow memory.


// Returns a string description of errorCode.
extern char * nimbleErrorString(const uint32_t errorCode);

#endif /* NimbleError_h */

// NimbleError.h
