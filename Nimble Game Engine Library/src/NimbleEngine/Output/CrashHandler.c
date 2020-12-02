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

#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../../../include/Nimble/NimbleEngine/Output/Errors.h"


static _Bool crashtest = 0;
nMutex_t crashMutex = NULL;

/**
 * @brief The default crash handler callback.
 * @param[in] error The error that caused the crash.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument. A length of
 * zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 * @param[in] stack The stack as a string.
 * @param[in] stackLen The length of the stack string.
 */
void nCrashHandlerDefault(const nint_t error,
                          const time_t errorTime,
                          char *errorDesc,
                          nint_t errorDescLen,
                          char *stack,
                          nint_t stackLen
                          );

void (*crashCallback) (const nint_t error, const time_t errorTime,
                        char *errorDesc, nint_t errorDescLen, char *stack,
                        nint_t stackLen) = nCrashHandlerDefault;


void nCrashHandlerDefault(const nint_t error, const time_t errorTime,
                          char *errorDesc, nint_t errorDescLen, char *stack,
                          nint_t stackLen)
{
    /** @todo Make default callback (threads, engine, logs, etc.). */
}

nint_t nCrashSetCallback(void (*callback)(const nint_t error,
        const time_t errorTime, char *errorDesc, nint_t errorDescLen,
        char *stack, nint_t stackLen))
{
    if (callback == NULL)
    {
        NCONST_STR einfoCallbackStr[] = "Callback parameter null in nCrashSetCallback().";
        nErrorThrow(NERROR_NULL, einfoCallbackStr, NCONST_STR_LEN(einfoCallbackStr));
        return NERROR;
    }
    
    crashCallback = callback;
    return NSUCCESS;
}

_Noreturn void nCrashSafe(const nint_t error, time_t errorTime,  const char *errorDesc,
                nint_t errorDescLen)
{
    nThreadMutexCreate(crashMutex);
    nThreadMutexLock(crashMutex);
    if (crashtest || (crashCallback == NULL))
    {
        nCrashAbort(error);
        /* NO RETURN */
    }
    
    crashtest = 1;
    
    
    if (errorTime == 0)
    {
        errorTime = time(NULL);
    }
    
    char *errorDescPtr;

    if ((errorDescLen <= 0) && (errorDesc != NULL))
    {
        errorDescLen = strlen(errorDesc);
    }

    if (errorDesc == NULL)
    {
        
        if (nErrorToStringLocal(errorDescPtr, &errorDescLen, error, NULL, 0) !=
            NSUCCESS)
        {
            NCONST_STR defaultErrorStr[] = "NERROR_ERROR_NOT_FOUND: An error "\
"passed to a function was not valid: nErrorToStringLocal() failed while "\
"crashing with nCrashSafe().";
            errorDescLen = NCONST_STR_LEN(defaultErrorStr);
            errorDescPtr = nRealloc(errorDescPtr, errorDescLen + 1);
            nStringCopy(errorDescPtr, defaultErrorStr, errorDescLen);
        }
        
    }
    else
    {
        errorDescPtr = nAlloc(errorDescLen);
        nStringCopy(errorDescPtr, errorDesc, errorDescLen);
    }
    
    char *stack;
    nint_t stackLen;
    nErrorGetStacktrace(stack, &stackLen, NULL);
    crashCallback(error, errorTime, errorDescPtr, errorDescLen, stack, stackLen);
    
    errorDescPtr = nFree(errorDescPtr);

    exit(error);
    /* NO RETURN */
}

_Noreturn void nCrashSignal(const int signum)
{
    const nint_t error = nErrorFromSignal(signum);
    const time_t errorTime = time(NULL);
    char *errorDesc;
    nint_t errorDescLen;
    
    signal(signum, SIG_DFL);
    nErrorToStringLocal(errorDesc, &errorDescLen, error, NULL, 0);
    nCrashSafe(error, errorTime, errorDesc, errorDescLen);
    /* NO RETURN */
}

_Noreturn void nCrashAbort(const nint_t error)
{
    fprintf(stderr, "The program failed to crash safely and is aborting. "\
     "Error: %s (%x/%d) - %s", nErrorStr(error), error, error,
     nErrorDesc(error));
    abort();
    /* NO RETURN */
}

// CrashHandler.c
