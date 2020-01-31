/*
 *  NimbleMemory.h
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

#ifndef NimbleMemory_h
#define NimbleMemory_h

#include <stdint.h>
#include <stdlib.h>

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute((always_inline))
#endif
#ifndef NULL
#define NULL (void *) 0
#endif


extern uint64_t nimbleMemoryUsed;

// Returns the allocated pointer and adds size to the total used memory.
ALWAYS_INLINE __attribute__((warn_unused_result)) void * nimbleMemoryAllocate(const size_t size)
{
    nimbleMemoryUsed += size;
    return malloc(sizeof(void *) + size);
}

// Returns the reallocated pointer and adds (newSize - oldSize) to the total used memory.
ALWAYS_INLINE __attribute__((warn_unused_result)) void * nimbleMemoryReallocate(void * pointer, const size_t oldSize, const size_t newSize)
{
    nimbleMemoryUsed += (newSize - oldSize);
    
    if (!pointer)
    {
        pointer = malloc(sizeof(void *) + newSize);
    } else
    {
        pointer = realloc(pointer, sizeof(void *) + newSize);
    }
    
    return pointer;
}

// Frees the allocated pointer, sets it to NULL, and subtracts size from the total used memory.
ALWAYS_INLINE void nimbleMemoryFree(void * pointer, const size_t size)
{
    nimbleMemoryUsed -= size;
    free(pointer);
}

#endif /* NimbleMemory_h */

// NimbleMemory.h
