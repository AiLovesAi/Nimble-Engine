/*
 *  NimbleSystemInfo.c
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

#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <sys/utsname.h>
#endif

#include "NimbleMemory.h"
#include "NimbleSystemInfo.h"

#ifndef FORMAT_LENGTH_2
#define FORMAT_LENGTH_2 2
#endif


// Returns the OS name.
char * nimbleSystemGetOSString(uint8_t * length)
{
    char * osString = NULL;
#   ifdef _WIN32
    OSVERSIONINFOEX versionInfo;
    ZeroMemory(&versionInfo, sizeof(OSVERSIONINFOEX));
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx(&versionInfo);
    
    switch (versionInfo.dwMajorVersion)
    {
            
        case 10:
        {
            
            if (versionInfo.wProductType == VER_NT_WORKSTATION)
            {
                const char windows10String[] = "Windows 10";
                *length = sizeof(windows10String) - 1;
                osString = nimbleMemoryAllocate(*length + 1);
                strcpy(osString, windows10String);
            } else
            {
                const char windowsServerTechnicalString[] = "Windows Server Technical Preview";
                *length = sizeof(windowsServerTechnicalString) - 1;
                osString = nimbleMemoryAllocate(*length + 1);
                strcpy(osString, windowsServerTechnicalString);
            }
            
        }
        break;
        
        case 6:
        {
            
            if (versionInfo.wProductType == VER_NT_WORKSTATION)
            {
                
                switch (versionInfo.dwMinorVersion)
                {
                        
                    case 3:
                    {
                        const char windows81String[] = "Windows 8.1";
                        *length = sizeof(windows81String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windows81String);
                    }
                    break;
                    
                    case 2:
                    {
                        const char windows8String[] = "Windows 8";
                        *length = sizeof(windows8String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windows8String);
                    }
                    break;
                    
                    case 1:
                    {
                        const char windows7String[] = "Windows 7";
                        *length = sizeof(windows7String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windows7String);
                    }
                    break;
                    
                    case 0:
                    {
                        const char windowsVistaString[] = "Windows Vista";
                        *length = sizeof(windowsVistaString) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windowsVistaString);
                    }
                    break;
                    
                }
                
            } else
            {
                
                switch (versionInfo.dwMinorVersion)
                {
                    case 3:
                    {
                        const char windowsServer2012R2String[] = "Windows Server 2012 R2";
                        *length = sizeof(windowsServer2012R2String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windowsServer2012R2String);
                    }
                    break;
                    
                    case 2:
                    {
                        const char windowsServer2012String[] = "Windows Server 2012";
                        *length = sizeof(windowsServer2012String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windowsServer2012String);
                    }
                    break;
                        
                    case 1:
                    {
                        const char windowsServer2008R2String[] = "Windows Server 2008 R2";
                        *length = sizeof(windowsServer2008R2String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windowsServer2008R2String);
                    }
                    break;
                    
                    case 0:
                    {
                        const char windowsServer2008String[] = "Windows Server 2008";
                        *length = sizeof(windowsServer2008String) - 1;
                        osString = nimbleMemoryAllocate(*length + 1);
                        strcpy(osString, windowsServer2008String);
                    }
                    break;
                    
                }
                
            }
            
        }
        break;
        
    }
    
#   elif defined(__APPLE__)
    char osBuffer[32];
    char osVersionBuffer[10];
    int mib[] = {CTL_KERN, KERN_OSTYPE};
    size_t osBufferLength = sizeof(osBuffer);
    size_t osVersionBufferLength = sizeof(osVersionBuffer);
    
    if (sysctl(mib, 2, osBuffer, &osBufferLength, NULL, 0))
    {
        return NULL;
    }
    
    *length = osBufferLength - 1;
    mib[1] = KERN_OSRELEASE;
    
    if (sysctl(mib, 2, osVersionBuffer, &osVersionBufferLength, NULL, 0))
    {
        return NULL;
    }
    
    *length += osVersionBufferLength - 1;
    
    osString = nimbleMemoryAllocate(*length + 1);
    strcpy(osString, osBuffer);
    osString[osBufferLength - 1] = ' ';
    strcpy(osString + osBufferLength, osVersionBuffer);
    
#   elif defined(__linux__)
    struct utsname
    {
        char sysname[];    // Operating system name (e.g., "Linux")
        char nodename[];   // Name within "some implementation-defined network"
        char release[];    // Operating system release (e.g., "2.6.28")
        char version[];    // Operating system version
        char machine[];    // Hardware identifier
#       if defined(_GNU_SOURCE)
        char domainname[]; // NIS or YP domain name
#       endif
    };
    
    uname(&utsname);
    const uint32_t sysnameLength = strlen(utsname.sysname);
    *length = (sysnameLength + strlen(utsname.release) + 1);
    osString = nimbleMemoryAllocate(*length + 1);
    strcpy(osString, utsname.sysname);
    osString[sysnameLength] = ' ';
    strcpy(osString + sysnameLength + 1, utsname.release);
#   endif
    
    return osString;
}

// Retruns the CPU name.
char * nimbleSystemGetCPUBrandString(uint8_t * length)
{
    uint32_t regs[4] = {};
    const uint32_t bufferSize = ((sizeof(uint32_t) * sizeof(regs)) * 4) + 1;
    char * cpuBrandString = nimbleMemoryAllocate(bufferSize);
    uint32_t * buffer = (uint32_t *) cpuBrandString;
    
    for (uint32_t i = 0x80000002; i <= 0x80000004; i++)
    {
        asm volatile("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
                 : "a" (i), "c" (0));
        *buffer = regs[0];
        buffer++;
        *buffer = regs[1];
        buffer++;
        *buffer = regs[2];
        buffer++;
        *buffer = regs[3];
        buffer++;
    }
    
    *length = strlen(cpuBrandString);
    cpuBrandString = nimbleMemoryReallocate(cpuBrandString, bufferSize, *length + 1);
    return cpuBrandString;
}


// NimbleSystemInfo.c
