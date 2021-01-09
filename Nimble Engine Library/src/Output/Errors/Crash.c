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

#include "../../../include/Nimble/Output/Errors/Errors.h"


static volatile _Bool crashtest = 0;

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
static void nCrashCallbackDefault(const nErrorInfo_t errorInfo);

void (*volatile crashCallback)(const nErrorInfo_t errorInfo) = &nCrashCallbackDefault;


static void nCrashCallbackDefault(const nErrorInfo_t errorInfo)
{
    /** @todo Make default callback (threads, engine, logs, etc.). */
}

void nCrashSetCallback(void (*callback) (const nErrorInfo_t errorInfo))
{
    if (callback)
    {
        crashCallback = callback;
    }
    else
    {
        crashCallback = nCrashCallbackDefault;
    }
}

_Noreturn void nCrashSafe(const int error, nErrorInfo_t errorInfo)
{
    if (crashtest || !crashCallback)
    {
        nCrashAbort(error);
        /* NO RETURN */
    }
    crashtest = 1;

    if (!errorInfo.time.secs)
    {
        errorInfo.time = nTime();
    }

    errorInfo.error = error;

    if (!errorInfo.errorStr)
    {
        errorInfo.errorStr = nErrorStr(error);
        errorInfo.errorLen = nErrorStrLen(error);
    }
    else if (errorInfo.errorLen <= 0)
    {
        errorInfo.errorLen = nErrorStrLen(error);
    }

    if (!errorInfo.descStr)
    {
        errorInfo.descStr = nErrorDesc(error);
        errorInfo.descLen = nErrorDescLen(error);
    }
    else if (errorInfo.descLen <= 0)
    {
        errorInfo.descLen = nErrorDescLen(error);
    }
    
    if (!errorInfo.stackStr)
    {
        errorInfo.stackStr = nErrorStacktrace(&errorInfo.stackLen, &errorInfo.stackLevels);
    }
    else if (errorInfo.stackLen <= 0)
    {
        errorInfo.stackLen = strlen(errorInfo.stackStr);
    }

    /* Call the user-defined crash callback function. */
    crashCallback(errorInfo);
    
    nErrorInfoFree(&errorInfo);

    exit(error);
    /* NO RETURN */
}

_Noreturn void nCrashSignal(const int signum)
{
    const nTime_t errorTime = nTime();
    const int error = nErrorFromSignal(signum);
    
    signal(signum, SIG_DFL);

    nErrorInfo_t errorInfo;
#define einfoStr "Caught a signal using nCrashSignal()."
    nErrorInfoSet(&errorInfo, error, errorTime, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
    nCrashSafe(error, errorInfo);
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
