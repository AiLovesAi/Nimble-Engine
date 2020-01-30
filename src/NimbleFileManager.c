/*
 *  NimbleFileManager.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

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

