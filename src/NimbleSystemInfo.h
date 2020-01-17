/*
 *  NimbleSystemInfo.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleSystemInfo_h
#define NimbleSystemInfo_h

#include <stdint.h>
#include <GL/glew.h>

#if defined(__APPLE__) || defined(__linux__)
#include <sys/sysctl.h>
#endif

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute((always_inline))
#endif
#ifndef NULL
#define NULL (void *) 0
#endif


// Returns the OS name.
extern char * nimbleSystemGetOSString(uint8_t * length);

// Retruns the CPU name.
extern char * nimbleSystemGetCPUBrandString(uint8_t * length);

// Returns the logical processor count.
#ifdef _WIN32
ALWAYS_INLINE uint8_t nimbleSystemGetLogicalProcessorCount(void)
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwNumberOfProcessors;
}
#elif defined(__APPLE__) || defined(__linux__)
#define nimbleSystemGetLogicalProcessorCount() sysconf(_SC_NPROCESSORS_ONLN)
#endif

// Returns the graphics card name.
ALWAYS_INLINE char * nimbleSystemGetGraphicsCardBrandString(uint8_t * length)
{
    char * graphicsCardString = (char *) glGetString(GL_RENDERER);
    // TODO Remove "OpenGL Engine"
    *length = (uint8_t) strlen(graphicsCardString);
    return graphicsCardString;
}

#endif /* NimbleSystemInfo_h */

// NimbleSystemInfo.h
