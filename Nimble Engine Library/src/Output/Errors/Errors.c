#include "../../include/Nimble/NimbleLicense.h"
/*
 * Errors.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-17.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../../include/Nimble/Output/Errors/Errors.h"

/**
 * @file Errors.c
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
#include <time.h>

#include "../../../include/Nimble/Output/Errors/Crash.h"


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
static void nErrorHandlerDefault(const nint_t error,
                                 const time_t errorTime,
                                 const char * errorDesc,
                                 const size_t errorDescLen,
                                 const char * stack,
                                 const size_t stackLen
                                 );

/**
 * @brief The error callback function that gets defined by nErrorSetCallback().
 */
void (*volatile errorCallback) (const nint_t error, const time_t errorTime,
 const char * errorDesc, const size_t errorDescLen, const char * stack,
 const size_t stackLen) = &nErrorHandlerDefault;

static void nErrorHandlerDefault(const nint_t error, const time_t errorTime,
 const char * errorDesc, const size_t errorDescLen, const char * stack,
 const size_t stackLen)
{
    /** @todo Make default callback. */
}

nint_t nErrorAssert(const nint_t check, const nint_t error, const char *info,
 const size_t infoLen)
{
    if (!check)
    {
        nint_t err = 0;
#if NIMBLE_OS == NIMBLE_WINDOWS
        nErrorLastWindows(err);
        if (err)
        {
            err = error;
            if (info)
            {
                size_t errorDescLen;
                char *errorDescStr = nErrorToStringWindows(&errorDescLen, err,
                info, infoLen);
                nErrorThrow(err, errorDescStr, errorDescLen);
                nFree(errorDescStr);
            }
            return err;
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

        if (info)
        {
            size_t errorDescLen;
            char *errorDescStr = nErrorToString(&errorDescLen, err,
            info, infoLen);
            nErrorThrow(err, errorDescStr, errorDescLen);
            nFree(errorDescStr);
        }
        return err;
    }
    return NSUCCESS;
}

void nErrorThrow(const nint_t error, char *errorDescStr, size_t errorDescLen)
{
    const time_t errorTime = time(NULL);
    
#define einfoStr "Callback argument NULL in nErrorThrow()."
    nAssert(errorCallback != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
    
    _Bool funcAllocates = 0;
    if (!errorDescStr)
    {
        funcAllocates = 1;
        errorDescStr = nErrorToString(&errorDescLen, error, NULL, 0);
    }
    
    size_t stackLen = 0;
#if 0
    char *stackStr = nErrorGetStacktrace(&stackLen, NULL);
#endif
    
    /* Call the user-defined error callback function. */
    errorCallback(error, errorTime, errorDescStr, errorDescLen, "stack", stackLen);

#if 0
    nFree(stackStr);
#endif
    if (funcAllocates)
    {
        nFree(errorDescStr);
    }
}

char *nErrorToString(size_t *errorLen, const nint_t error, const char *info,
 size_t infoLen)
{
    if (info && (infoLen <= 0))
    {
        infoLen = strlen(info);
    }
    
    /* Get error information. */
    const char *errorStr = nErrorStr(error);
    const size_t errorStrLen = nErrorStrLen(error);
    const char *errorDescStr = nErrorDesc(error);
    const size_t errorDescStrLen = nErrorDescLen(error);

    const char formatStr[] = "\nInfo: %s\nError: %s: %s\n";
    const size_t formatStrLen = NCONST_STR_FORMAT_LEN(formatStr, 3, 0, 0, 0);
    size_t errLen;
    char *dst;
    
    if (!info)
    {
        errLen = formatStrLen + errorStrLen + errorDescStrLen +
         NCONST_STR_LEN(noInfoStr);
        dst = nAlloc(errLen + 1);
        snprintf(dst, errLen + 1, formatStr, noInfoStr, errorStr, errorDescStr);
    }
    else
    {
        errLen = formatStrLen + errorStrLen + errorDescStrLen + infoLen;
        dst = nAlloc(errLen + 1);
        snprintf(dst, errLen + 1, formatStr, info, errorStr, errorDescStr);
    }
    
    if (errorLen)
    {
        *errorLen = errLen;
    }
    
    return dst;
}

#if NIMBLE_OS == NIMBLE_WINDOWS
char *nErrorToStringWindows(size_t *errorLen, const nint_t error,
 const char *info, size_t infoLen)
{
    if (info && (infoLen <= 0))
    {
        infoLen = strlen(info);
    }

    /* Get error information. */
    char *buffer, *dst;
    const size_t len = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
     FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
     NULL,
     error,
     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
     (LPTSTR) &buffer,
     0,
     NULL);

    if (!len)
    {
        dst = nErrorToString(errorLen, NERROR_UNKNOWN, info, infoLen);
        goto retLbl;
    }

    /* Copy error to heap. */
    dst = nAlloc(len + 1);
    nStringCopy(dst, buffer, len);
    if (errorLen)
    {
        *errorLen = len;
    }

retLbl:;
    if (buffer)
    {
        LocalFree(buffer);
    }
    return dst;
}
#endif

nint_t nErrorSetCallback(void (*callback)(const nint_t error,
 const time_t errorTime, const char *errorDesc, const size_t errorDescLen,
 const char *stack, const size_t stackLen))
{
    if (callback)
    {
        errorCallback = callback;
    }
    else
    {
        errorCallback = nErrorHandlerDefault;
    }

    return NSUCCESS;
}

char *nErrorGetStacktrace(size_t *stackLen, size_t *stackLevels)
{
    /* Set max levels */
    size_t maxLevels = 128;
    if (stackLevels && (*stackLevels > 0) && (*stackLevels <= 1024))
    {
        maxLevels = *stackLevels;
    }

#ifdef NIMBLE_32BIT
    struct frame {
        struct frame *bp;
        uint32_t ip;
    };
    struct frame *stack = {0};
#else
    struct frame {
        struct frame *bp;
        uint64_t ip;
    };
    struct frame *stack = {0};
#endif

    /* Get stack frame pointer. */
#if (NIMBLE_ARCH == NIMBLE_INTEL) | (NIMBLE_ARCH == NIMBLE_AMD)
#  ifdef NIMBLE_32BIT
    asm("movl %%ebp, %0\n" : "=r" (stack) ::);
#  else
    asm("movq %%rbp, %0\n" : "=r" (stack) ::);
#  endif
#elif NIMBLE_ARCH == NIMBLE_ARM
#  ifdef __thumb__
    asm("mov %%r7, %0\n" : "=r" (stack) ::);
#  else
    asm("mov %%r11, %0\n" : "=r" (stack) ::);
#  endif
#endif

    /* Prepare stackStr with buffer. */
#ifdef NIMBLE_32BIT
    const char formatStr[] = "<%08x> %s\n";
#else
    const char formatStr[] = "<%016I64x> %s\n";
#endif
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
