#include "../../include/Nimble/NimbleLicense.h"
/*
 * Crash.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-19.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

#include "../../include/Nimble/Errors/Crash.h"

/**
 * @file Crash.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if NIMBLE_OS == NIMBLE_WINDOWS
#include <windows.h>
#else
#include <signal.h>
#endif

#include "../../../include/Nimble/System/Memory.h"
#include "../../../include/Nimble/Errors/Errors.h"
#include "../../../include/Nimble/Output/Files.h"


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
    perror(errorInfo.infoStr);
}

void nCrashSetCallback(void (*const callback) (const nErrorInfo_t errorInfo))
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

void nAssert(const int check, const int error, const char *const info,
 const size_t infoLen)
{
    if (!check)
    {
        const nTime_t errorTime = nTime();
        char *sysDescStr;
        size_t sysDescLen;
        int err = nErrorLast(&sysDescLen, &sysDescStr);
        if (!err) err = error;

        nErrorInfo_t errorInfo;
        nErrorInfoSet(&errorInfo, err, errorTime, info, infoLen, sysDescStr,
         sysDescLen);
        nCrashSafe(err, errorInfo);
    }
}

_Noreturn void nCrashAbort(const int error)
{
    /* Print error using async-signal-safe functions */
#define einfoStr "The program failed to crash safely and is aborting. "\
 "Error: "
#define spaceStr " - "
    char *abortStr = malloc(NCONST_STR_LEN(einfoStr) +
                            nErrorStrLen(error) +
                            NCONST_STR_LEN(spaceStr) +
                            nErrorDescLen(error) +
                            1);
    if (abortStr)
    {
        nStringCopy(abortStr, einfoStr, NCONST_STR_LEN(einfoStr));
        int len = NCONST_STR_LEN(einfoStr);
#undef einfoStr
        nStringCopy(abortStr + len, nErrorStr(error), nErrorStrLen(error));
        len += nErrorStrLen(error);
        nStringCopy(abortStr + len, spaceStr, NCONST_STR_LEN(spaceStr));
        len += NCONST_STR_LEN(spaceStr);
#undef spaceStr
        nStringCopy(abortStr + len, nErrorDesc(error), nErrorDescLen(error));
        len += nErrorDescLen(error);

        write(STDERR_FILENO, abortStr, len);
    }

    /* Reset to default abort signal handler */
#ifdef NIMBLE_STD_POSIX
    struct sigaction sa = {};
    sa.sa_handler = SIG_DFL;
    if (!sigemptyset(&sa.sa_mask))
    {
#  if NIMBLE_OS == NIMBLE_MACOS
        sa.sa_flags = SA_SIGINFO;
#  else
        sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
#  endif

        sigaction(SIGABRT, &sa, NULL);
    }
#elif NIMBLE_OS == NIMBLE_WINDOWS
    SetUnhandledExceptionFilter(NULL);
#else
    signal(SIGABRT, SIG_DFL);
#endif

    /* ABORT! */
    abort();
    /* NO RETURN */
}

// Crash.c
