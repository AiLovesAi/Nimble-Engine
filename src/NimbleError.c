/*
 *  NimbleError.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/26/20.
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

#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "NimbleError.h"
#include "NimbleMath.h"
#include "NimbleMemory.h"
#include "NimbleThread.h"
#include "NimbleTime.h"
#include "NimbleWindow.h"

#ifndef FORMAT_LENGTH_2
#define FORMAT_LENGTH_2 2
#endif
#ifndef FORMAT_LENGTH_4
#define FORMAT_LENGTH_4 4
#endif


volatile uint8_t alreadyCrashed = 0;

// Returns a string description of error.
char * nimbleErrorString(const uint32_t errorCode)
{
    char * output = NULL;
    
    switch (errorCode)
    {
        
        // GENERAL ERRORS
        case NIMBLE_ERROR_GENERAL_NULL:
        {
            char errorString[] = "Unexpected null pointer in function.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        // MATH ERRORS
        case NIMBLE_ERROR_MATH_OVERFLOW:
        {
            char errorString[] = "Math operation was too large and would overflow.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        case NIMBLE_ERROR_MATH_DIVIDE_BY_ZERO:
        {
            char errorString[] = "Math function divisor input was zero.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        // BIG NUMBER ERRORS
        case NIMBLE_ERROR_BIGNUM_OVERFLOW:
        {
            char errorString[] = "Big number function input was too large and would overflow memory.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
        
        default:
        {
            char errorString[] = "Unknown error code.";
            output = nimbleMemoryAllocate(sizeof(errorString));
            strcpy(output, errorString);
        }
        break;
        
    }
    
    return output;
}

// Crashes the game with crashMessage and errorCOde, and generates a crash log.
void nimbleErrorCrash(const char * crashMessage, const uint64_t crashMessageLength, const char * crashLogFilePath, const char * logFilePath, const int32_t errorCode, const uint8_t errorType)
{
    
    if (alreadyCrashed)
    {
        raise(SIGTERM);
    }
    
    alreadyCrashed = 1;
    nimbleGameRunning = 0;
    
    const struct timeval threadCloseWaitTime = nimbleTimeSetTimerMillis(3 * MILLIS_PER_SEC);
    
    while (!nimbleTimeHasPast(threadCloseWaitTime) && nimbleThreadCount)
    {
        nimbleTimeSleepMillis(100); // Wait 3 seconds or until threads are closed.
    }
    
    char *         output              = NULL;
    char *         errorMessage        = NULL;
    uint64_t       errorMessageLength  = 0;
    const char     crashFormatString[] = "\n\n[%02d-%02d-%04d %02d:%02d:%02d +%06d] %s\nError code: %d (%s)"; // TODO Time
    struct timeval tv                  = {};
    FILE *         crashLogFile        = NULL;
    FILE *         logFile             = NULL;
    
    if (crashLogFilePath)
    {
        crashLogFile = fopen(crashLogFilePath, "wb");
    }
    
    if (logFilePath)
    {
        logFile = fopen(logFilePath, "ab");
    }
    
    if (gettimeofday(&tv, NULL))
    {
        const struct tm * gmNow = gmtime(&tv.tv_sec);
        
        if (!gmNow)
        {
            
            if (errorCode)
            {
                
                switch (errorType) {
                    
                    case NIMBLE_ERROR_TYPE_ERRNO:
                    {
                        errorMessage = strerror(errorCode);
                        errorMessageLength = strlen(errorMessage);
                    }
                    break;
                    
                    case NIMBLE_ERROR_TYPE_NIMBLE:
                    {
                        errorMessage = nimbleErrorString((uint32_t) errorCode);
                        errorMessageLength = strlen(errorMessage);
                    }
                    break;
                    
                    default:
                    {
                        const char noErrorMessageString[] = "No error message.";
                        errorMessageLength = sizeof(noErrorMessageString) - 1;
                        errorMessage = malloc(sizeof(char *) + errorMessageLength + 1);
                        strcpy(errorMessage, noErrorMessageString);
                    }
                    break;
                    
                }
                
            }
            
            if (crashMessage && crashMessageLength)
            {
                const uint64_t outputLength = (sizeof(crashFormatString) - (FORMAT_LENGTH_2 * 3) - (FORMAT_LENGTH_4 * 7) - 1) + crashMessageLength + nimbleMathDigits64(errorCode) + errorMessageLength + 1;
                output = malloc(sizeof(char *) + outputLength);
                snprintf(output, outputLength, crashFormatString, (gmNow->tm_mon + TM_DIF_MONTH),gmNow->tm_mday, (gmNow->tm_year + TM_DIF_EPOCH), gmNow->tm_hour, gmNow->tm_min, gmNow->tm_sec, tv.tv_usec, crashMessage, errorCode, errorMessage);
            } else
            {
                const char crashMessageDefault[] = "Game crashed with no crash message.";
                const uint64_t outputLength = (sizeof(crashFormatString) - (FORMAT_LENGTH_2 * 3) - 1) + (sizeof(crashMessageDefault) - 1) + nimbleMathDigits64(errorCode) + errorMessageLength + 1;
                output = malloc(sizeof(char *) + outputLength);
                strcpy(output, crashMessageDefault);
                snprintf(output, outputLength, crashFormatString, (gmNow->tm_mon + TM_DIF_MONTH),gmNow->tm_mday, (gmNow->tm_year + TM_DIF_EPOCH), gmNow->tm_hour, gmNow->tm_min, gmNow->tm_sec, tv.tv_usec, crashMessageDefault, errorCode, errorMessage);
            }
            
            if (crashLogFile)
            {
                fputs(output, crashLogFile);
                fclose(crashLogFile);
            }
            
            if (logFile)
            {
                fputs(output, logFile);
                fclose(logFile);
            }
            
            fputs(output, stderr);
        }
        
    }
    
    exit(EXIT_FAILURE);
}


// NimbleError.c
