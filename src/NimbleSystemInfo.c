/*
 *  SystemInfo.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include "SystemInfo.h"


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
                osString = malloc(ptrSize + *length + 1);
                strcpy(osString, windows10String);
            } else
            {
                const char windowsServerTechnicalString[] = "Windows Server Technical Preview";
                *length = sizeof(windowsServerTechnicalString) - 1;
                osString = malloc(ptrSize + *length + 1);
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
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windows81String);
                    }
                    break;
                    
                    case 2:
                    {
                        const char windows8String[] = "Windows 8";
                        *length = sizeof(windows8String) - 1;
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windows8String);
                    }
                    break;
                    
                    case 1:
                    {
                        const char windows7String[] = "Windows 7";
                        *length = sizeof(windows7String) - 1;
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windows7String);
                    }
                    break;
                    
                    case 0:
                    {
                        const char windowsVistaString[] = "Windows Vista";
                        *length = sizeof(windowsVistaString) - 1;
                        osString = malloc(ptrSize + *length + 1);
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
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windowsServer2012R2String);
                    }
                    break;
                    
                    case 2:
                    {
                        const char windowsServer2012String[] = "Windows Server 2012";
                        *length = sizeof(windowsServer2012String) - 1;
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windowsServer2012String);
                    }
                    break;
                        
                    case 1:
                    {
                        const char windowsServer2008R2String[] = "Windows Server 2008 R2";
                        *length = sizeof(windowsServer2008R2String) - 1;
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windowsServer2008R2String);
                    }
                    break;
                    
                    case 0:
                    {
                        const char windowsServer2008String[] = "Windows Server 2008";
                        *length = sizeof(windowsServer2008String) - 1;
                        osString = malloc(ptrSize + *length + 1);
                        strcpy(osString, windowsServer2008String);
                    }
                    break;
                    
                }
                
            }
            
        }
        break;
        
    }
#   elif defined(__APPLE__)
    // TODO
#   elif defined(__linux__)
    // TODO
#   endif
    return osString;
}

// Retruns the CPU name.
char * nimbleSystemGetCPUBrandString(uint8_t * length)
{
    uint32_t regs[4] = {};
    char * cpuBrandString = malloc(ptrSize + ((sizeof(uint32_t) * sizeof(regs)) * 4) + 1);
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
    cpuBrandString = realloc(cpuBrandString, ptrSize + *length + 1);
    return cpuBrandString;
}


// SystemInfo.c
