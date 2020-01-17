/*
 *  NimbleFileManager.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleFileManager_h
#define NimbleFileManager_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#define PATH_MAX MAX_PATH
#elif defined(__APPLE__)
#include <limits.h>
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <limits.h>
#endif

#include "NimbleMemory.h"

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute((always_inline))
#endif
#ifndef NULL
#define NULL (void *) 0
#endif


// Sets buffer to the directory of the executable, and sets bufferSize to its length.
ALWAYS_INLINE char * nimbleFileGetExecutableDirectory(size_t * length)
{
    char * buffer = nimbleMemoryAllocate(PATH_MAX + 1);
#   ifdef _WIN32
    GetModuleFileName(NULL, buffer, PATH_MAX);
#   elif defined(__APPLE__)
    uint32_t bufferSize = PATH_MAX;
    _NSGetExecutablePath(buffer, &bufferSize);
#   elif defined(__linux__)
    readlink("/proc/self/exe", buffer, PATH_MAX);
#   endif
    
    if (!buffer)
    {
        return NULL;
    }
    
    char * temp = strrchr(buffer, '/');
    const uint16_t index = temp - buffer;
    buffer[index + 1] = '\0';
    *length = strlen(buffer);
    buffer = nimbleMemoryReallocate(buffer, PATH_MAX + 1, *length + 1);
    return buffer;
}

#endif /* NimbleFileManager_h */

// NimbleFileManager.h
