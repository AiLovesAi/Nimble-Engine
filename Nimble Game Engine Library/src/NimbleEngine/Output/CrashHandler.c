#include "../../../include/Nimble/NimbleLicense.h"
/*
 * CrashHandler.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-19.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../../include/Nimble/NimbleEngine/Output/CrashHandler.h"

/**
 * @file CrashHandler.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * @endparblock
 * @date 2020-08-19
 *
 * @brief This class defines crash handling functions.
 */

#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../../../include/Nimble/NimbleEngine/Output/Errors.h"


volatile uint8_t crashtest = 0;

/**
 * @brief The default crash handler callback.
 * @param[in] error The error that caused the crash.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument, including the
 * null character. A length of zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 */
void nCrashHandlerDefault(const int32_t error,
                          char * errorDesc,
                          int32_t errorDescLen,
                          char * stack,
                          int32_t stackLen,
                          time_t errorTime
                          );

void (* crashCallback) (const int32_t error, char * errorDesc, 
         int32_t errorDescLen, char * stack, int32_t stackLen,
         time_t errorTime) = nCrashHandlerDefault;


void nCrashHandlerDefault(const int32_t error, char * errorDesc,
      int32_t errorDescLen, char * stack, int32_t stackLen,
      time_t errorTime)
{
    /** @todo Make default callback (threads, engine, logs, etc.). */
}

int32_t nCrashSetCallback(void (* callback)(const int32_t error,
         const time_t errorTime, char * errorDesc, int32_t errorDescLen,
         char * stack, int32_t stackLen))
{
    if (callback == NULL)
    {
        char callbackErrStr[] = "Callback parameter null in nCrashSetCallback().";
        nErrorThrow(NERROR_NULL, callbackErrStr, sizeof(callbackErrStr));
        return NERROR;
    }
    
    crashCallback = callback;
    return NSUCCESS;
}

void nCrashSafe(const int32_t error, char * errorDesc, int32_t errorDescLen,
      time_t errorTime)
{
    if (crashtest || (crashCallback == NULL))
    {
        nCrashAbort(error);
        /* NO RETURN */
    }
    
    crashtest++;
    
    
    if (errorTime == 0)
    {
        errorTime = time(NULL);
    }
    
    if (errorDesc == NULL)
    {
        
        if (nErrorToStringLocal(errorDesc, &errorDescLen, error, NULL, 0) !=
            NSUCCESS)
        {
            const char defaultErrorStr[] = "NERROR_ERROR_NOT_FOUND: An error "\
"passed to a function was not valid: nErrorToStringLocal() failed while "\
"crashing with nCrashSafe().";
            errorDescLen = sizeof(defaultErrorStr);
            errorDesc = malloc(sizeof(void *) + errorDescLen);
            strncpy(errorDesc, defaultErrorStr, errorDescLen);
        }
        
    }
    
    if ((errorDescLen <= 0) && (errorDesc != NULL))
    {
        errorDescLen = strlen(errorDesc) + 1;
    }
    
    
    crashCallback(error, errorDesc, errorDescLen, errorTime);
    exit(error);
    /* NO RETURN */
}

void nCrashSignal(const int signum)
{
    const time_t errorTime = time(NULL);
    char * errorDesc;
    int32_t errorDescLen;
    
    signal(signum, SIG_DFL);
    
    switch(signum)
    {
        case SIGABRT:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_SIGABRT, NULL,
             0);
            nCrashSafe(NERROR_SIGABRT, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        case SIGFPE:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_SIGFPE, NULL,
             0);
            nCrashSafe(NERROR_SIGFPE, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        case SIGILL:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_SIGILL, NULL,
             0);
            nCrashSafe(NERROR_SIGILL, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        case SIGINT:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_SIGINT, NULL,
             0);
            nCrashSafe(NERROR_SIGINT, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        case SIGSEGV:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_SIGSEGV, NULL,
             0);
            nCrashSafe(NERROR_SIGSEGV, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        case SIGTERM:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_SIGTERM, NULL,
             0);
            nCrashSafe(NERROR_SIGTERM, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        default:
        {
            nErrorToStringLocal(errorDesc, &errorDescLen, NERROR_ERROR_NOT_FOUND,
            NULL, 0);
            nCrashSafe(NERROR_ERROR_NOT_FOUND, errorDesc, errorDescLen, errorTime);
            /* NO RETURN */
        }
        break;
        /* NO RETURN */
    }
    /* NO RETURN */
}

void nCrashAbort(const int32_t error)
{
    fprintf(stderr, "Aborting program with error code: %s (%d)",
     NERROR_STRING(error), error);
    abort();
    /* NO RETURN */
}

// CrashHandler.c
