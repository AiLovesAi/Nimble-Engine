#include "../../../include/Nimble/NimbleLicense.h"
/*
 * Crash.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-19.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../../include/Nimble/Output/Errors/Crash.h"

/**
 * @file Crash.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
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
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../../../include/Nimble/Output/Errors/Errors.h"


static _Bool crashtest = 0;
nMutex_t crashMutex = NULL;

/**
 * @brief The default crash callback.
 * @param[in] error The error that caused the crash.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument. A length of
 * zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 * @param[in] stack The stack as a string.
 * @param[in] stackLen The length of the stack string.
 */
static void nCrashCallbackDefault(const int error,
                                  const time_t errorTime,
                                  const char *restrict errorDesc,
                                  const size_t errorDescLen,
                                  const char *restrict stack,
                                  const size_t stackLen
                                  );

void (*volatile crashCallback) (const int error, const time_t errorTime,
 const char *restrict errorDesc, const size_t errorDescLen, 
 const char *restrict stack, const size_t stackLen) = &nCrashCallbackDefault;


static void nCrashCallbackDefault(const int error, const time_t errorTime,
 const char *restrict errorDesc, const size_t errorDescLen,
 const char *restrict stack, const size_t stackLen)
{
    /** @todo Make default callback (threads, engine, logs, etc.). */
}

void nAssert(const int check, const int error, const char *info,
 const size_t infoLen)
{
    if (!check)
    {
        int err = 0;
#if NIMBLE_OS == NIMBLE_WINDOWS
        nErrorLastWindows(err);
        if (err)
        {
            err = error;
            size_t errorDescLen;
            char *errorDescStr = nErrorToStringWindows(&errorDescLen, err,
             info, infoLen);
            nCrashSafe(err, time(NULL), errorDescStr, errorDescLen);
            /* NO RETURN */
        }
#endif
        if (errno)
        {
            nErrorLastErrno(err);
            err = nErrorFromErrno(err);
        }
        else
        {
            err = error;
        }

        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, err,
         info, infoLen);
        nCrashSafe(err, time(NULL), errorDescStr, errorDescLen);
        /* NO RETURN */
    }
}

int nCrashSetCallback(void (*callback)(const int error,
 const time_t errorTime, const char *restrict errorDesc, const size_t errorDescLen,
 const char *restrict stack, const size_t stackLen))
{
    if (callback)
    {
        crashCallback = callback;
    }
    else
    {
        crashCallback = nCrashCallbackDefault;
    }
    return NSUCCESS;
}

_Noreturn void nCrashSafe(const int error, time_t errorTime,
 const char *errorDesc, size_t errorDescLen)
{
    if (!crashMutex)
    {
        nThreadMutexCreate(&crashMutex);
    }

    if ((nThreadMutexLock(&crashMutex) != NSUCCESS) ||
     crashtest || (crashCallback == NULL))
    {
        nCrashAbort(error);
        /* NO RETURN */
    }
    crashtest = 1;
    
    if (!errorTime)
    {
        errorTime = time(NULL);
    }

    if ((errorDescLen <= 0) && errorDesc)
    {
        errorDescLen = strlen(errorDesc);
    }

    char *errorDescStr = NULL;

    if (errorDesc)
    {
        errorDescStr = nAlloc(errorDescLen);
        nStringCopy(errorDescStr, errorDesc, errorDescLen);
    }
    else
    {
        errorDescStr = nErrorToString(&errorDescLen, error, NULL, 0);
        if (!errorDescStr)
        {
            const char defaultErrorStr[] = "NERROR_ERROR_NOT_FOUND: An error "\
 "passed to a function was not valid: nErrorToString() failed while "\
 "crashing with nCrashSafe().";
            errorDescLen = NCONST_STR_LEN(defaultErrorStr);
            errorDescStr = nRealloc(errorDescStr, errorDescLen + 1);
            nStringCopy(errorDescStr, defaultErrorStr, errorDescLen);
        }
    }
    
    size_t stackLen = 0;
#if 0
    char *stackStr = nErrorGetStacktrace(&stackLen, NULL);
#endif
    /* Call the user-defined crash callback function. */
    crashCallback(error, errorTime, errorDescStr, errorDescLen, "stack",
     stackLen);
    
#if 0
    nFree(stackStr);
#endif
    nFree(errorDescStr);

    nThreadMutexDestroy(&crashMutex);
    exit(error);
    /* NO RETURN */
}

_Noreturn void nCrashSignal(const int signum)
{
    const int error = nErrorFromSignal(signum);
    const time_t errorTime = time(NULL);
    
    signal(signum, SIG_DFL);
    nCrashSafe(error, errorTime, NULL, 0);
    /* NO RETURN */
}

_Noreturn void nCrashAbort(const int error)
{
    fprintf(stderr, "The program failed to crash safely and is aborting. "\
     "Error: %s - %s", nErrorStr(error), nErrorDesc(error));
    signal(SIGABRT, SIG_DFL);
    abort();
    /* NO RETURN */
}

// Crash.c
