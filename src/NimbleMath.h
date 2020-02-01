/*
 *  NimbleMath.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
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
#include "NimbleLicense.h"

#ifndef NimbleMath_h
#define NimbleMath_h

#include <stdint.h>
#include <math.h>

#include "NimbleError.h"

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute__((always_inline))
#endif

#define M_PI2 6.28318530717958647692528676655900576 // pi * 2
#define M_DEG_TO_RAD (M_PI / 180.0)
#define M_RAD_TO_DEG (180.0 / M_PI)

// Sets vec3 destination to values.
ALWAYS_INLINE void nimbleMathVec3Init(float * destination, const float val0, const float val1, const float val2, uint32_t * error)
{
    
    if (destination)
    {
        destination[0] = val0;
        destination[1] = val1;
        destination[2] = val2;
    } else if (error)
    {
        *error = NIMBLE_ERROR_GENERAL_NULL;
    }
    
}

// Sets vec3 destination to vec3 from.
ALWAYS_INLINE void nimbleMathVec3InitFrom(float * destination, const float * from, uint32_t * error)
{
    
    if (destination && from)
    {
        destination[0] = from[0];
        destination[1] = from[1];
        destination[2] = from[2];
    } else if (error)
    {
        *error = NIMBLE_ERROR_GENERAL_NULL;
    }
    
}

// Sets vec4 destination to values.
ALWAYS_INLINE void nimbleMathVec4Init(float * destination, const float val0, const float val1, const float val2, const float val3, uint32_t * error)
{
    
    if (destination)
    {
        destination[0] = val0;
        destination[1] = val1;
        destination[2] = val2;
        destination[3] = val3;
    } else if (error)
    {
        *error = NIMBLE_ERROR_GENERAL_NULL;
    }
    
}
#define nimbleMathQuatInit nimbleMathVec4Init

// Sets vec4 destination to vec4 from.
ALWAYS_INLINE void nimbleMathVec4InitFrom(float * destination, const float * from, uint32_t * error)
{
    
    if (destination && from)
    {
        destination[0] = from[0];
        destination[1] = from[2];
        destination[2] = from[2];
        destination[3] = from[3];
    } else if (error)
    {
        *error = NIMBLE_ERROR_GENERAL_NULL;
    }
    
}
#define nimbleMathQuatInitFrom nimbleMathVec4InitFrom

// Returns float x rounded down without checking extensively for overflow.
ALWAYS_INLINE int32_t nimbleMathFloorF(const float x, uint32_t * error)
{
    
    if ((x >= ((uint64_t) INT32_MAX + 1)) || (x < ((int64_t) INT32_MIN)))
    {
        
        if (error)
        {
            *error = NIMBLE_ERROR_MATH_OVERFLOW;
        }
        
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    int32_t i = (int32_t) x;
    return i - (i > x);
}

// Returns float x rounded up without checking for overflow.
ALWAYS_INLINE int32_t nimbleMathCeilF(const float x, uint32_t * error)
{
    
    if ((x > ((int64_t) INT32_MAX)) || (x <= ((int64_t) INT32_MIN - 1)))
    {
        
        if (error)
        {
            *error = NIMBLE_ERROR_MATH_OVERFLOW;
        }
        
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    int32_t i = (int32_t) x;
    return i + (x > i);
}

// Returns double x rounded down without checking for overflow.
ALWAYS_INLINE int64_t nimbleMathFloorD(const double x, uint32_t * error)
{
    
    if ((x >= ((uint64_t) INT64_MAX + 1)) || (x < INT64_MIN))
    {
        
        if (error)
        {
            *error = NIMBLE_ERROR_MATH_OVERFLOW;
        }
        
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    int64_t i = (int64_t) x;
    return i - (i > x);
}

// Returns double x rounded up without checking for overflow.
ALWAYS_INLINE int64_t nimbleMathCeilD(const double x, uint32_t * error)
{
    
    if ((x > INT64_MAX) || (x < (INT64_MIN)))
    {
        
        if (error)
        {
            *error = NIMBLE_ERROR_MATH_OVERFLOW;
        }
        
        return NIMBLE_ERROR_GENERAL_NULL;
    }
    
    int64_t i = (int64_t) x;
    return i + (x > i);
}

// Returns the number of digits in unsigned 64-bit integer x.
extern uint8_t nimbleMathDigits64u(const uint64_t x);

// Returns the number of digits in 64-bit integer x.
extern uint8_t nimbleMathDigits64(const int64_t x);

// Returns the number of digits in unsigned 32-bit integer x.
extern uint8_t nimbleMathDigits32u(const uint32_t x);

// Returns the number of digits in 32-bit integer x.
extern uint8_t nimbleMathDigits32(const int32_t x);

// Returns the number of digits in unsigned 16-bit integer x.
extern uint8_t nimbleMathDigits16u(const uint16_t x);

// Returns the number of digits in 16-bit integer x.
extern uint8_t nimbleMathDigits16(const int16_t x);

// Returns the number of digits in unsigned 8-bit integer x.
ALWAYS_INLINE uint8_t nimbleMathDigits8u(const uint8_t x)
{
    return (x >= 100UL) ? 3 : (x >= 10UL) ? 2 : 1;
}

// Returns the number of digits in 8-bit integer x.
ALWAYS_INLINE uint8_t nimbleMathDigits8(const int8_t x)
{
    const int16_t absx = (((x >> 15) | 1) * x);
    return ((x == -128L) || (absx >= 100UL)) ? 3 : (absx >= 10UL) ? 2 : 1;
}

// Returns the number of digits in float x.
extern uint8_t nimbleMathDigitsF(const float x, uint32_t * error);

// Returns the number of digits in double x.
extern uint8_t nimbleMathDigitsD(const double x, uint32_t * error);

#endif /* NimbleMath_h */

// NimbleMath.h
