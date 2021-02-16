#include "../../include/Nimble/NimbleLicense.h"
/*
 * Errors.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-17.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

#include "../../include/Nimble/Errors/Errors.h"

/**
 * @file Errors.c
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

#include <inttypes.h>

#if NIMBLE_OS == NIMBLE_WINDOWS
#include <dbghelp.h>
#include <imagehlp.h>
#include <windows.h>
#else
#include <execinfo.h>
#include <unistd.h>
#endif

#include "../../../include/Nimble/Errors/Crash.h"
#include "../../../include/Nimble/Output/Files.h"
#include "../../../include/Nimble/System/Memory.h"
#include "../../../include/Nimble/System/Time.h"
#include "../../../include/Nimble/System/Threads.h"

static __thread _Bool stacktraceAttempted = 0;
nMutex_t nStacktraceMutex = NULL;

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
    printf("%s: %s === %s === %s\n%s", errorInfo.errorStr, errorInfo.descStr, errorInfo.sysDescStr,
     errorInfo.infoStr, errorInfo.stackStr);
}

int nErrorThrow(const int error, const char *const info, size_t infoLen, const int setError)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "Callback argument NULL in nErrorThrow()."
    nAssert(
     errorCallback != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#  undef einfoStr
#endif

    const nTime_t errorTime = nTime();
    char *sysDescStr = NULL;
    size_t sysDescLen = 0;
    int err = error;
    if (setError || !error)
    {
        if (!(err = nErrorLast(&sysDescLen, &sysDescStr)))
        {
            err = error;
        }
    }
    
    nErrorInfo_t errorInfo;
    nErrorInfoSet(&errorInfo, err, errorTime, info, infoLen, sysDescStr, sysDescLen);
    
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
# define noDescStr "No system error description."
                *sysDescStr = nRealloc(*sysDescStr, NCONST_STR_LEN(noDescStr) + 1);
                nStringCopy(*sysDescStr, noDescStr, NCONST_STR_LEN(noDescStr));
#  undef noDescStr
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
 const nTime_t errorTime, const char *restrict info, size_t infoLen,
 const char *const sysDescStr, size_t sysDescLen)
{
#ifndef NIMBLE_NO_ARG_CHECK
    if (!errorInfo) return;
#endif
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
        if (infoLen <= 0)
        {
            infoLen = strlen(info);
        }
        errorInfo->infoStr = nStringDuplicate(info, infoLen);
        errorInfo->infoLen = infoLen;
    }
    else
    {
#define noInfoStr "No info."
        errorInfo->infoStr = nStringDuplicate(noInfoStr,
         NCONST_STR_LEN(noInfoStr));
        errorInfo->infoLen = NCONST_STR_LEN(noInfoStr);
#undef noInfoStr
    }

    if (sysDescStr)
    {
        if (sysDescLen <= 0)
        {
            sysDescLen = strlen(sysDescStr);
        }
        errorInfo->sysDescStr = nStringDuplicate(sysDescStr, sysDescLen);
        errorInfo->sysDescLen = sysDescLen;
    }
    else
    {
#define noSysDescStr "No system error description."
        errorInfo->infoStr = nStringDuplicate(noSysDescStr,
         NCONST_STR_LEN(noSysDescStr));
        errorInfo->sysDescLen = NCONST_STR_LEN(noSysDescStr);
#undef noSysDescStr
    }
    
    if (stacktraceAttempted)
    {
#define noStackStr "No stacktrace."
        errorInfo->stackStr = nStringDuplicate(noStackStr, NCONST_STR_LEN(noStackStr));
        errorInfo->stackLen = NCONST_STR_LEN(noStackStr);
#undef noStackStr
        errorInfo->stackLevels = 0;
    }
    else
    {
        errorInfo->stackStr = nErrorStacktrace(&errorInfo->stackLen,
         &errorInfo->stackLevels);
    }
}

void nErrorInfoFree(nErrorInfo_t *errorInfo)
{
#ifndef NIMBLE_NO_ARG_CHECK
    if (!errorInfo) return;
#endif
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

void nErrorSetCallback(void (*const callback) (const nErrorInfo_t errorInfo))
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

struct frameInfo {
    char *func;  /* Function name */
    int funcLen; /* Length of func */
    char *file;  /* File name */
    int fileLen; /* Length of file */

    int line;    /* Line number */
    int offset;  /* Offset from beginning of line */
};
struct frame {
    struct frame *bp; /* Stack pointer */
    void *ip; /* Function pointer */
};
NIMBLE_USE_RESULT
NIMBLE_INLINE
struct frameInfo *nErrorStackSymbols(int *levels, int maxLevels)
{
    if (nStacktraceMutex) nThreadMutexLock(&nStacktraceMutex);

    /* Get stack */
    struct frame *framePtr;
#if NIMBLE_INST == NIMBLE_INST_x86
    asm("movq %%rbp, %0\n" : "=r" (framePtr) ::);
#elif NIMBLE_INST == NIMBLE_INST_ARM
#  ifdef __thumb__
    asm("mov %%r7, %0\n" : "=r" (framePtr) ::);
#  else
    asm("mov %%r11, %0\n" : "=r" (framePtr) ::);
#  endif
#endif
    void *stack[NERRORS_STACK_MAX + 1];
    //for (*levels = 0; (framePtr && framePtr->ip) && (*levels < maxLevels); (*levels)++)
    for (*levels = 0; framePtr->ip && (*levels < maxLevels); (*levels)++)
    {
        stack[*levels] = framePtr->ip;
        framePtr = framePtr->bp;
    }
    stack[*levels] = NULL;

    struct frameInfo *frames = nAlloc(sizeof(struct frameInfo) * (*levels));
    memset(frames, 0, sizeof(struct frameInfo) * (*levels));

#if NIMBLE_OS == NIMBLE_WINDOWS
    /* Prepare Sym functions. */
    HANDLE process = GetCurrentProcess();
#  define einfoStr "GetCurrentProcess() failed in nErrorStacktrace()."
    nAssert(
     process != NULL,
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#  undef einfoStr
#  define einfoStr "SymInitialize() failed in nErrorStacktrace()."
    nAssert(
     SymInitialize(process, NULL, TRUE),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#  undef einfoStr

    SYMBOL_INFO *symbol = nAlloc(sizeof(SYMBOL_INFO) + NFUNCTION_NAME_MAX + 1);
    memset(symbol, 0, sizeof(SYMBOL_INFO) + NFUNCTION_NAME_MAX + 1);
    symbol->MaxNameLen = NFUNCTION_NAME_MAX;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    IMAGEHLP_LINE image;
    memset(&image, 0, sizeof(IMAGEHLP_LINE));
    image.SizeOfStruct = sizeof(IMAGEHLP_LINE);
    
    DWORD offset = 0;
    for (int i = 0; i < *levels; i++)
    {
        printf("%d\n", i);
#  define einfoStr "SymFromAddr() failed in nErrorStacktrace()."
        nAssert(
         SymFromAddr(
            process,
            (DWORD64) stack[i],
            NULL,
            symbol
         ),
         NERROR_INTERNAL_FAILURE,
         einfoStr,
         NCONST_STR_LEN(einfoStr)
        );
#  undef einfoStr
        frames[i].funcLen = symbol->NameLen;
        frames[i].func = nStringDuplicate(symbol->Name, symbol->NameLen);
        if (SymGetLineFromAddr64(
         process,
         (DWORD64) stack[i],
         &offset,
         &image
        ))
        {
            frames[i].line = image.LineNumber;
            frames[i].offset = (int) offset;
        }
        else
        {
            nErrorClear();
            HMODULE module = NULL;

            if (
             GetModuleHandleEx(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                (char *) stack[i],
                &module
             ) && module)
            {
                frames[i].file = nAlloc(NFUNCTION_NAME_MAX + 1);
                frames[i].fileLen = GetModuleFileNameA(module, frames[i].file, NFUNCTION_NAME_MAX);
                frames[i].file = nRealloc(frames[i].file, frames[i].fileLen);
                printf("%s\n", frames[i].file);
            }
            else nErrorClear();
        }
    }
    nFree((void **) &symbol);
    SymCleanup(process);

#else
    char **symbols = backtrace_symbols(stack, *levels);
    size_t bufferLen = 0;
    for (int i = 0; i < *levels; i++)
    {
        frames[i].func = symbols[i];
        frames[i].funcLen = strlen(symbols[i]);
        /// @todo File & line number.
    }
    nFree((void **) &symbols);

#endif

    if (nStacktraceMutex) nThreadMutexUnlock(&nStacktraceMutex);
    return frames;
}

char *nErrorStacktrace(size_t *restrict stackLen, int *restrict stackLevels)
{
    if (stacktraceAttempted) nCrashAbort(NERROR_LOOP);
    stacktraceAttempted = 1;

    /* Set max levels */
    size_t maxLevels = NERRORS_STACK_DEFAULT;
    if (stackLevels && (*stackLevels > 0) && (*stackLevels <= NERRORS_STACK_MAX))
    {
        maxLevels = *stackLevels;
    }

    size_t len = 0;
    int levels = 0;
    char *stackStr = NULL;

    struct frameInfo *frames = nErrorStackSymbols(&levels, maxLevels);
    for (int i = 0; i < levels; i++)
    {
        /// @todo Set string
        if (frames[i].file) nFree((void **) &frames[i].file);
        if (frames[i].func) nFree((void **) &frames[i].func);
    }
    nFree((void **) &frames);

    /* Cleanup */
    if (stackLevels) *stackLevels = levels;
    if (stackLen) *stackLen = len;

    stacktraceAttempted = 0;
    return stackStr;
}

// Errors.c
