/*
 *  NimbleMemory.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#ifndef NimbleMemory_h
#define NimbleMemory_h

#include <stdint.h>
#include <stdlib.h>

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute__((always_inline))
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

// Returns the allocated pointer and adds size to the total used memory.
ALWAYS_INLINE __attribute__((warn_unused_result)) void * nimbleMemoryAllocateClear(const size_t size)
{
    nimbleMemoryUsed += size;
    return calloc(sizeof(void *) + size, 1);
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
