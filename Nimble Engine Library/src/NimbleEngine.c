#include "../include/Nimble/NimbleLicense.h"
/*
 * NimbleEngine.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-10.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

#include "../include/Nimble/NimbleEngine.h"

/**
 * @file NimbleEngine.c
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
 * @date 2020-08-10
 *
 * @brief This class includes all the necessary game engine header files.
 *
 * This class includes all the necessary game engine header files that are
 * used in game development, and defines the functions used in initialization.
 */

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if NIMBLE_OS == NIMBLE_WINDOWS
#include <windows.h>
#else
#include <signal.h>
#endif

#include "../include/Nimble/System/Memory.h"
#include "../include/Nimble/Errors/Errors.h"
#include "../include/Nimble/Errors/Crash.h"
#include "../include/Nimble/Output/Files.h"
#include "../include/Nimble/System/Threads.h"

volatile _Bool NIMBLE_INITIALIZED = 0;

char **NIMBLE_ARGS = NULL;
int NIMBLE_ARGC = 0;


static void nEngineCleanup(void)
{
    /* Free NIMBLE_ARGS */
    for (int i = 0; i < NIMBLE_ARGC; i++)
    {
        nFree((void **) &NIMBLE_ARGS[i]);
    }
    nFree((void **) &NIMBLE_ARGS);

    /* Destroy mutexes */
    nThreadMutexDestroy(&nStacktraceMutex);
}

#ifdef NIMBLE_STD_POSIX
_Noreturn static void nEngineHandleSignal(const int signum, siginfo_t *info, void *context)
{
    char *infoStr = NULL;
    size_t infoLen = 0;
    switch (signum)
    {
        case SIGTERM:
            exit(SIGTERM);
            /* NO RETURN */
        case SIGSEGV:
#  define formatStr "Caught a segmentation fault signal at address %p."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(infoStr, infoLen, formatStr, info->si_addr);
#  undef formatStr
        default:
            const nTime_t errorTime = nTime();
            const int error = nErrorFromSignal(signum);

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

            nErrorInfo_t errorInfo;
            if (!infoStr)
            {
#  define einfoStr "Caught a signal."
                infoLen = NCONST_STR_LEN(einfoStr);
                infoStr = nAlloc(infoLen + 1);
#  undef einfoStr
            }
            nErrorInfoSet(&errorInfo, error, errorTime, infoStr, infoLen),
             NULL, 0);
            nCrashSafe(error, errorInfo);
            /* NO RETURN */
    }
}
#elif NIMBLE_OS == NIMBLE_WINDOWS
static LONG nEngineHandleSignal(EXCEPTION_POINTERS *exceptionInfo)
{
    switch (exceptionInfo->ExceptionRecord->ExceptionCode)
    {
        case EXCEPTION_ACCESS_VIOLATION:
            /** @todo */
            break;
        default:
            break;
    }

    return EXCEPTION_EXECUTE_HANDLER;
}
#else
_Noreturn static void nEngineHandleSignal(int signum)
{
    switch (signum)
    {
        case SIGTERM:
            exit(SIGTERM);
            /* NO RETURN */
        default:
            const nTime_t errorTime = nTime();
            const int error = nErrorFromSignal(signum);

            signal(signum, SIG_DFL);

            nErrorInfo_t errorInfo;
#  define einfoStr "Caught a signal using nCrashSignal()."
            nErrorInfoSet(&errorInfo, error, errorTime, einfoStr, NCONST_STR_LEN(einfoStr),
            NULL, 0);
#  undef einfoStr
            nCrashSafe(error, errorInfo);
            /* NO RETURN */
    }
}
#endif

NIMBLE_INLINE
void nEngineCopyArgs(char **args, const int argc)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "No arguments passed to nEngineInit(). This is necessary "\
 "even if no arguments are sent, as the first argument is always the "\
 "executable file, which is needed for stacktraces."
    nAssert(
     args && argc,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#endif

    NIMBLE_ARGS = nAlloc(sizeof(char *) * argc);
    int count = 0;
    for (size_t len = 0; args[count] && count < argc; count++)
    {
        len = strlen(args[count]);
        NIMBLE_ARGS[count] = nStringDuplicate(args[count], len);
    }

#ifndef NIMBLE_NO_ARG_CHECK
    nAssert(
     count,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#  undef einfoStr
#endif
    NIMBLE_ARGC = count;
}

NIMBLE_INLINE
void nEngineSetSignalHandler(void)
{
#ifdef NIMBLE_STD_POSIX
    struct sigaction sa = {};
    sa.sa_handler = nEngineHandleSignal;
#  define einfoStr "sigemptyset() failed in nEngineInit(), and the signal "\
 "handlers could not be set."
    nAssert(
     !sigemptyset(&sa.sa_mask),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    ); 
#  undef einfoStr
#  if NIMBLE_OS == NIMBLE_MACOS
    sa.sa_flags = SA_SIGINFO;
#  else
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;

    /* Create new stack for signal handler. */
    stack_t ss;
    ss.ss_sp = nAlloc(SIGSTKSZ);
    ss.ss_size = SIGSTKSZ;
    ss_flags = 0;
#    define einfoStr "sigaltstack() failed in nEngineInit(), and the signal "\
 "handlers could not be set."
    nAssert(
     !sigaltstack(&ss, NULL),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#    undef einfoStr
#  endif

#  define einfoStr "sigaction() failed in nEngineInit(), and the signal "\
"handlers could not be set."
    nAssert(!sigaction(SIGTERM, &sa, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(!sigaction(SIGABRT, &sa, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(!sigaction(SIGFPE, &sa, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(!sigaction(SIGILL, &sa, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(!sigaction(SIGINT, &sa, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(!sigaction(SIGSEGV, &sa, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#elif NIMBLE_OS == NIMBLE_WINDOWS
    SetUnhandledExceptionFilter(nEngineHandleSignal);
#else
#  define einfoStr "signal() failed in nEngineInit(), and the signal handlers "\
 "could not be set."
    nAssert(signal(SIGTERM, nEngineHandleSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGABRT, nEngineHandleSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGFPE, nEngineHandleSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGILL, nEngineHandleSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGINT, nEngineHandleSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGSEGV, nEngineHandleSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr
#endif
}

int nEngineInit(char **args, const int argc,
 void (*const errorCallback) (const nErrorInfo_t errorInfo),
 void (*const crashCallback) (const nErrorInfo_t errorInfo))
{
#define einfoStr "nEngineInit() was called, but Nimble is already initialized."
    if (nErrorAssert(
     !NIMBLE_INITIALIZED,
     NERROR_WARN,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_WARN;
#undef einfoStr

    /* Add nEngineCleanup() to the exit functions. */
#define einfoStr "atexit() failed in nEngineInit(), and the exit functions "\
 "could not be set."
    nAssert(
     !atexit(&nEngineCleanup),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr

    /* Set signal callbacks. */
    nEngineSetSignalHandler();

    /* Set Nimble callbacks. */
    nErrorSetCallback(errorCallback);
    nCrashSetCallback(crashCallback);

    /* Copy args to NIMBLE_ARGS */
    nEngineCopyArgs(args, argc);

    /* Set executable file name. */
    nFileSetExecutablePath();

    // Setup mutexes
#define einfoStr "Could not create mutex with nThreadMutexCreate() "\
 "in nEngineInit()"
    nAssert(
     !nThreadMutexCreate(&nStacktraceMutex),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr
    
    NIMBLE_INITIALIZED = 1;

    return NSUCCESS;
}

// NimbleEngine.c
