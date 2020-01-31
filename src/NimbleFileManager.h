/*
 *  NimbleFileManager.h
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
