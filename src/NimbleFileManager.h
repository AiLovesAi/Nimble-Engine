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

#ifndef NULL
#define NULL (void *) 0
#endif


// Sets buffer to the directory of the executable, and sets bufferSize to its length.
extern char * nimbleFileGetExecutableDirectory(size_t * length);

#endif /* NimbleFileManager_h */

// NimbleFileManager.h
