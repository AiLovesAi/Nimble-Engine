#include "../../../include/Nimble/NimbleLicense.h"
/*
 * Errors.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-17.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../../include/Nimble/Output/Errors/Errors.h"

/**
 * @file Errors.c
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
 * SOFTWARE.t
 * @endparblock
 * @date 2020-08-17
 *
 * @brief This class defines error handling functions.
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "../../../include/Nimble/Output/Errors/Crash.h"
#include "../../../include/Nimble/Output/Files.h"
#include "../../../include/Nimble/System/Library.h"
#include "../../../include/Nimble/System/Time.h"


const char noInfoStr[] = "No info.";

/**
 * @brief The default error handler callback.
 * @param[in] error The error number.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument. A length of
 * zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 * @param[in] stack The stacktrace of the thread that caused the crash.
 * @param[in] stackLen The length of the @p stack argument. A length of zero (0)
 * uses strlen() to determine length.
 */
static void nErrorHandlerDefault(const nErrorInfo_t errorInfo);

/**
 * @brief The error callback function that gets defined by nErrorSetCallback().
 */
void (*volatile errorCallback)(const nErrorInfo_t errorInfo) = &nErrorHandlerDefault;

static void nErrorHandlerDefault(const nErrorInfo_t errorInfo)
{
    /** @todo Make default callback. */
}

int nErrorThrow(const int error, const char *info, size_t infoLen, const int setError)
{
#define einfoStr "Callback argument NULL in nErrorThrow()."
    nAssert(errorCallback != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    char *sysDescStr;
    size_t sysDescLen;
    int err = error;
    if (setError || !error)
    {
        if (!(err = nErrorLast(&sysDescLen, &sysDescStr)))
        {
            err = error;
        }
    }
    
    const nTime_t errorTime = nTime();
    
    nErrorInfo_t errorInfo;
    nErrorInfoSet(&errorInfo, err, errorTime, info, infoLen);
    
    /* Call the user-defined error callback function. */
    errorCallback(errorInfo);
    nErrorInfoFree(&errorInfo);
    return err;
}

int nErrorLast(size_t *sysDescLen, char **sysDescStr)
{
    int error = NSUCCESS;
    size_t len = 0;
    if (sysDescStr)
    {
        nFree((void **) sysDescStr);

        if ((error = nErrorLastErrno()))
        {
            char *errorDescStr = strerror(error);
            error = nErrorFromErrno(error);
            
            len = strlen(errorDescStr);
            *sysDescStr = nStringDuplicate(errorDescStr, len);
        }
        
#if NIMBLE_OS == NIMBLE_WINDOWS
        else if ((error = nErrorLastWindows()))
        {
            len = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) sysDescStr,
            0,
            NULL);
            error = NERROR_INTERNAL_FAILURE;

            if (len <= 0)
            {
                len = 0;
                nFree((void **) sysDescStr);
            }
        }
#endif
    }
    else
    {
        if ((error = nErrorLastErrno()))
        {
            error = nErrorFromErrno(error);
        }
#if NIMBLE_OS == NIMBLE_WINDOWS
        else if ((error = nErrorLastWindows()))
        {
            error = NERROR_INTERNAL_FAILURE;
        }
#endif
    }

    /* Copy error to heap. */
    if (sysDescLen)
    {
        *sysDescLen = len;
    }
    return error;
}

void nErrorInfoSet(nErrorInfo_t *restrict errorInfo, const int error,
 const nTime_t errorTime, const char *restrict info, size_t infoLen)
{
    if (!errorInfo) return;
    errorInfo->time = errorTime.secs ? errorTime : nTime();
    errorInfo->error = error;

    const size_t errorLen = nErrorStrLen(error);
    errorInfo->errorStr = nErrorStr(error);
    errorInfo->errorLen = errorLen;

    const size_t descLen = nErrorDescLen(error);
    errorInfo->descStr = nErrorDesc(error);
    errorInfo->descLen = descLen;

    if (info)
    {
        if (!infoLen)
        {
            infoLen = strlen(info);
        }
        errorInfo->infoStr = nStringDuplicate(info, infoLen + 1);
    }
    else
    {
        errorInfo->infoStr = nStringDuplicate(noInfoStr,
         NCONST_STR_LEN(noInfoStr));
    }
    
    size_t stackLen;
    int stackLevels = 0;
    errorInfo->stackStr = nErrorStacktrace(&stackLen, &stackLevels);
    errorInfo->stackLen = stackLen;
    errorInfo->stackLevels = stackLevels;
}

void nErrorInfoFree(nErrorInfo_t *errorInfo)
{
    errorInfo->error = 0;

    errorInfo->errorStr = NULL;
    errorInfo->errorLen = 0;

    errorInfo->descStr = NULL;
    errorInfo->descLen = 0;

    nFree((void **) &errorInfo->sysDescStr);
    errorInfo->sysDescLen = 0;

    nFree((void **) &errorInfo->infoStr);
    errorInfo->infoLen = 0;
    
    nFree((void **) &errorInfo->stackStr);
    errorInfo->stackLen = 0;
    errorInfo->stackLevels = 0;
}

void nErrorSetCallback(void (*callback) (const nErrorInfo_t errorInfo))
{
    if (callback)
    {
        errorCallback = callback;
    }
    else
    {
        errorCallback = nErrorHandlerDefault;
    }
}

char *nErrorStacktrace(size_t *restrict stackLen, int *restrict stackLevels)
{
    /* Set max levels */
    size_t maxLevels = 128;
    if (stackLevels && (*stackLevels > 0) && (*stackLevels <= NERRORS_MAX_STACK))
    {
        maxLevels = *stackLevels;
    }

    struct frame {
        struct frame *bp;
        uint64_t ip;
    };
    struct frame *stack = {0};

    /* Get stack frame pointer. */
#if NIMBLE_INST == NIMBLE_INST_x86
    asm("movq %%rbp, %0\n" : "=r" (stack) ::);
#elif NIMBLE_INST == NIMBLE_INST_ARM
#  ifdef __thumb__
    asm("mov %%r7, %0\n" : "=r" (stack) ::);
#  else
    asm("mov %%r11, %0\n" : "=r" (stack) ::);
#  endif
#endif

    /* Prepare stackStr with buffer. */
    const char formatStr[] = "<%016I64x> %s\n";
    const size_t maxLineLen = (NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 1, 0)
     + NFUNCTION_NAME_MAX + 8);
    const size_t bufferSize = (maxLevels * maxLineLen) + 1;
    char *stackStr = nAlloc(bufferSize);

    /* Ensure executable variable is set. */
    if (!NEXEC_LEN)
    {
       nFileSetExecutablePath();
    }

    /* Trace stack. */
    size_t level, len = 0;
    for (level = 0; stack && (level < maxLevels); level++)
    {
        len += snprintf(stackStr + len, maxLineLen, formatStr, stack->ip,
         (char *) &stack->ip); /** @todo Find function name from eip function poiter */
        stack = stack->bp;
    }

    /* Reallocate stackStr to its correct length. */
    stackStr = nRealloc(stackStr, len + 1);
    if (stackLen)
    {
        *stackLen = len;
    }
    if (stackLevels)
    {
        *stackLevels = level;
    }
    return stackStr;
}

// Errors.c
