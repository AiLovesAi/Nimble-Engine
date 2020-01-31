/*
 *  NimbleSystemInfo.h
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
    *length = (uint8_t) strlen(graphicsCardString);
    return graphicsCardString;
}

#endif /* NimbleSystemInfo_h */

// NimbleSystemInfo.h
