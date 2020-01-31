/*
 *  NimbleFileManager.c
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
 #include "NimbleLicense.c"

#include "NimbleFileManager.h"


// Sets buffer to the directory of the executable, and sets bufferSize to its length.
char * nimbleFileGetExecutableDirectory(size_t * length)
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


// NimbleFileManger.c

