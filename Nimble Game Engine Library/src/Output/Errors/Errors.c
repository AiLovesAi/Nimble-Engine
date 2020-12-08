#include "../../include/Nimble/NimbleLicense.h"
/*
 * Errors.c
 * Nimble Game Engine
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
void nErrorHandlerDefault(const nint_t error,
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

void nErrorHandlerDefault(const nint_t error, const time_t errorTime,
 const char * errorDesc, const size_t errorDescLen, const char * stack,
 const size_t stackLen)
{
    /** @todo Make default callback. */
}

void nErrorThrow(const nint_t error, const char *info, size_t infoLen)
{
    const time_t errorTime = time(NULL);
    
    if (errorCallback == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        const char einfoCallbackStr[] = "Callback argument NULL in "\
         "nErrorThrow().";
        size_t crashErrorDescLen;
        
        char *crashErrorDesc = nErrorToString(&crashErrorDescLen, NERROR_NULL,
         einfoCallbackStr, NCONST_STR_LEN(einfoCallbackStr));
        nCrashSafe(NERROR_NULL, crashErrorTime, crashErrorDesc,
         crashErrorDescLen);
        /* NO RETURN */
    }
    
    size_t errorDescLen;
    char *errorDescStr = nErrorToString(&errorDescLen, error, info, infoLen);
    if (!errorDescStr)
    {
        const time_t crashErrorTime = time(NULL);
        const char einfoParseStr[] = "Error not found in nErrorThrow().";
        size_t crashErrorDescLen;
        
        char *crashErrorDesc = nErrorToString(&crashErrorDescLen,
         NERROR_INV_ERROR, einfoParseStr, NCONST_STR_LEN(einfoParseStr));
        nCrashSafe(NERROR_INV_ERROR, crashErrorTime, crashErrorDesc,
         crashErrorDescLen);
        /* NO RETURN */
    }
    
    size_t stackLen, stackLevels;
    char *stackStr = nErrorGetStacktrace(&stackLen, &stackLevels);
    
    /* Call the user-defined error callback function. */
    errorCallback(error, errorTime, errorDescStr, errorDescLen, stackStr, stackLen);

    stackStr = nFree(stackStr);
    errorDescStr = nFree(errorDescStr);
}

char *nErrorToString(size_t *errorLen, const nint_t error,
 const char *info, size_t infoLen)
{
    if (info && (infoLen == 0))
    {
        infoLen = strlen(info);
    }
    
    /* Get error information. */
    const char *errorStr = nErrorStr(error);
    const size_t errorStrLen = nErrorStrLen(error);
    const char *errorDescStr = nErrorDesc(error);
    const size_t errorDescStrLen = nErrorDescLen(error);

    const char formatStr[] = "Info: %s\nError: %s: %s\n";
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

nint_t nErrorSetCallback(void (*callback)(const nint_t error,
 const time_t errorTime, const char *errorDesc, const size_t errorDescLen,
 const char *stack, const size_t stackLen))
{
    if (!callback)
    {
        const char einfoCallbackStr[] = "Callback argument NULL in "\
         "nErrorSetCallback().";
        nErrorThrow(NERROR_NULL, einfoCallbackStr, 
         NCONST_STR_LEN(einfoCallbackStr));
        return NERROR_NULL;
    }
    
    errorCallback = callback;
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

    struct frame {
        struct frame *ebp;
        uint32_t eip;
    };
    struct frame *stack = {0};

    /* Get stack frame pointer. */
#if (NIMBLE_ARCH == NIMBLE_INTEL) | (NIMBLE_ARCH == NIMBLE_AMD)
    asm("movl %%ebp, %0\n" : "=r" (stack) ::);
#elif NIMBLE_ARCH == NIMBLE_ARM
#  ifdef __thumb__
    asm("movl %%r7, %0\n" : "=r" (stack) ::);
#  else
    asm("movl %%r11, %0\n" : "=r" (stack) ::);
#  endif
#endif

    /* Prepare stackStr with buffer. */
    const char formatStr[] = "<%08x> %s\n";
    const size_t maxLineLen = (NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 1, 0) + NFUNCTION_NAME_MAX + 8);
    const size_t bufferSize = (maxLevels * maxLineLen) + 1;
    char *stackStr = nAlloc(bufferSize);

    /* Ensure executable variable is set. */
    if (!NEXECUTABLE[0])
    {
        /** @todo Get executable. */
    }

    /* Trace stack. */
    size_t level, len = 0;
    for (level = 0; stack && (level < maxLevels); level++)
    {
        len += snprintf(stackStr + len, maxLineLen, formatStr, stack->eip, (char *) &stack->eip); /** @todo Find function name from eip function poiter */
        stack = stack->ebp;
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
