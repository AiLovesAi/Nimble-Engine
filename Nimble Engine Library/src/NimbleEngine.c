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

#if NIMBLE_OS == NIMBLE_WINDOWS
static LONG nEngineHandleException(EXCEPTION_POINTERS *exceptionInfo)
{
    const nTime_t errorTime = nTime();

    /** @todo Set info and crash; also use ExceptionRecord->ExceptionAddress and ExceptionInformation (with segv). */
    int error = NSUCCESS;
    char *infoStr = NULL;
    int infoLen;
    switch (exceptionInfo->ExceptionRecord->ExceptionCode)
    {
        /* Unique exceptions */
        case EXCEPTION_ACCESS_VIOLATION:
            error = NERROR_SIGSEGV;
#  define formatStr "Caught access violation exception at 0x%p. The thread tried to read from or "\
 "write to a virtual address for which it does not have the appropriate access.\n"
            /* Documentation states:
             * The first element of the array contains a read-write flag that indicates the type of operation
             * that caused the access violation.
             * If this value is 0, the thread attempted to read the inaccessible data.
             * If this value is 1, the thread attempted to write to an inaccessible address.
             * If this value is 8, the thread causes a user-mode data execution prevention (DEP) violation.
             * 
             * The second array element specifies the virtual address of the inaccessible data.
             */
            switch (exceptionInfo->ExceptionRecord->ExceptionInformation[0])
            {
                case 0:
#  define readStr "Tried to read from unaccessible address 0x%p."
                    infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0)
                     + NCONST_STR_FORMAT_LEN(readStr, 1, 0, 0, 0) + (2 * (sizeof(uintptr_t) * 2));
                    infoStr = nAlloc(infoLen + 1);
                    infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) +
                     NCONST_STR_FORMAT_LEN(readStr, 1, 0, 0, 0) + (2 * (sizeof(uintptr_t) * 2));
                    infoStr = nAlloc(infoLen + 1);
                    snprintf(
                     infoStr,
                     NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     formatStr,
                     exceptionInfo->ExceptionRecord->ExceptionAddress
                    );
                    snprintf(
                     infoStr + NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     NCONST_STR_FORMAT_LEN(readStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     readStr,
                     exceptionInfo->ExceptionRecord->ExceptionInformation[1]
                    );
                    infoStr[infoLen] = '\0';
#  undef readStr
                    break;
                case 1:
#  define writeStr "Tried to write to unaccessible address 0x%p."
                    infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0)
                     + NCONST_STR_FORMAT_LEN(writeStr, 1, 0, 0, 0) + (2 * (sizeof(uintptr_t) * 2));
                    infoStr = nAlloc(infoLen + 1);
                    infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) +
                     NCONST_STR_FORMAT_LEN(writeStr, 1, 0, 0, 0) + (2 * (sizeof(uintptr_t) * 2));
                    infoStr = nAlloc(infoLen + 1);
                    snprintf(
                     infoStr,
                     NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     formatStr,
                     exceptionInfo->ExceptionRecord->ExceptionAddress
                    );
                    snprintf(
                     infoStr + NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     NCONST_STR_FORMAT_LEN(writeStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     writeStr,
                     exceptionInfo->ExceptionRecord->ExceptionInformation[1]
                    );
                    infoStr[infoLen] = '\0';
#  undef writeStr
                    break;
                default:
#  define userModeStr "Thread caused a user-mode data executation prevention (DEP) violation to "\
 "address 0x%p."
                    infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) +
                     NCONST_STR_FORMAT_LEN(userModeStr, 1, 0, 0, 0) + (2 * (sizeof(uintptr_t) * 2));
                    infoStr = nAlloc(infoLen + 1);
                    snprintf(
                     infoStr,
                     NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     formatStr,
                     exceptionInfo->ExceptionRecord->ExceptionAddress
                    );
                    snprintf(
                     infoStr + NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     NCONST_STR_FORMAT_LEN(userModeStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2),
                     userModeStr,
                     exceptionInfo->ExceptionRecord->ExceptionInformation[1]
                    );
                    infoStr[infoLen] = '\0';
#  undef userModeStr
                    break;
            }
#  undef addressStr
#  undef formatStr
            break;

        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            error = NERROR_BOUNDS_OVERFLOW;
#  define formatStr "Caught access array out of bounds exception at 0x%p. The thread tried to access "\
 "an array element that is out of bounds and the underlying hardware supports bounds checking."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;

        case EXCEPTION_DATATYPE_MISALIGNMENT:
            error = NERROR_INV_TYPE_ALIGNMENT;
#  define formatStr "Caught datatype misalignment exception at 0x%p. The thread tried to read or write "\
 "data that is misaligned on hardware that does not provide alignment. For example, 16-bit "\
 "values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;

        case EXCEPTION_IN_PAGE_ERROR:
            error = NERROR_INV_PAGE;
#  define formatStr "Caught page error exception. The thread tried to access a page that was "\
 "not present, and the system was unable to load the page. For example, this exception might "\
 "occur if a network connection is lost while running a program over the network."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;

        case EXCEPTION_INT_OVERFLOW:
            error = NERROR_OVERFLOW;
#  define formatStr "Caught integer overflow exception. The result of an integer operation "\
 "caused a carry out of the most significant bit of the result."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;

        case EXCEPTION_NONCONTINUABLE_EXCEPTION:
            error = NERROR_NONCONTINUABLE;
#  define formatStr "Caught \"noncontinuable exception\" exception. The thread tried to "\
 "continue execution after a noncontinuable exception occurred."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;

        /* Illegal instruction exceptions */
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            error = NERROR_SIGILL;
#  define formatStr "Caught illegal instruction exception. The thread tried to execute an "\
 "invalid instruction."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_PRIV_INSTRUCTION:
            error = NERROR_SIGILL;
#  define formatStr "Caught priv instruction exception. The thread tried to execute an "\
 "instruction whose operation is not allowed in the current machine mode."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
            
        /* Floating point exceptions */
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            error = NERROR_SIGFPE;
#  define formatStr "Caught integer divide by zero exception. The thread tried to divide an "\
 "integer value by an integer divisor of zero."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_DENORMAL_OPERAND:
            error = NERROR_SIGFPE;
#  define formatStr "Caught float denormal operand exception. One of the operands in a "\
 "floating-point operation is denormal. A denormal value is one that is too small to "\
 "represent as a standard floating-point value."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            error = NERROR_SIGFPE;
#  define formatStr "Caught float divide by zero exception. The thread tried to divide a "\
 "floating-point value by a floating-point divisor of zero."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_INEXACT_RESULT:
            error = NERROR_SIGFPE;
#  define formatStr "Caught float inexact result exception. The result of a floating-point "\
 "operation cannot be represented exactly as a decimal fraction."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_INVALID_OPERATION:
            error = NERROR_SIGFPE;
#  define formatStr "Caught float invalid operation exception. This exception represents "\
 "any floating-point exception not included in this list."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_OVERFLOW:
            error = NERROR_SIGFPE;
#  define formatStr "Caught float overflow exception. The exponent of a floating-point "\
 "operation is greater than the magnitude allowed by the corresponding type."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_UNDERFLOW:
#  define formatStr "Caught float underflow exception. The exponent of a floating-point "\
 "operation is less than the magnitude allowed by the corresponding type."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            error = NERROR_SIGFPE;
            break;

        /* Stack overflow exceptions */
        case EXCEPTION_STACK_OVERFLOW:
            error = NERROR_STACK_OVERFLOW;
#  define formatStr "Caught stack overflow exception. The thread used up its stack."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;
        case EXCEPTION_FLT_STACK_CHECK:
            error = NERROR_STACK_OVERFLOW;
#  define formatStr "Caught float stack check exception. The stack overflowed or "\
 "underflowed as the result of a floating-point operation."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(
             infoStr,
             infoLen,
             formatStr,
             exceptionInfo->ExceptionRecord->ExceptionAddress
            );
            infoStr[infoLen] = '\0';
#  undef formatStr
            break;

        /* Non-erroneous exceptions */
        case EXCEPTION_BREAKPOINT:
        case EXCEPTION_SINGLE_STEP:
        case EXCEPTION_INVALID_DISPOSITION: /* Documentation states: "Programmers using a high-level language such as C should never encounter this exception." */
        default:
            return EXCEPTION_EXECUTE_HANDLER;
    }

    nErrorInfo_t errorInfo;
    nErrorInfoSet(&errorInfo, error, errorTime, infoStr, infoLen, NULL, 0, exceptionInfo->ContextRecord);
    errorInfo.stackStr = nErrorStacktrace(&errorInfo.stackLen, &errorInfo.stackLevels, exceptionInfo->ContextRecord);
    nCrashSafe(error, errorInfo);
}
#else
_Noreturn static void nEngineHandleException(const int signum, siginfo_t *info, void *context)
{
    char *infoStr = NULL;
    size_t infoLen;
    switch (signum)
    {
        case SIGTERM:
            exit(SIGTERM);
            /* NO RETURN */
        case SIGSEGV:
#  define formatStr "Caught a segmentation fault signal at address 0x%p."
            infoLen = NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 0, 0) + (sizeof(uintptr_t) * 2);
            infoStr = nAlloc(infoLen + 1);
            snprintf(infoStr, infoLen, formatStr, info->si_addr);
            infoStr[infoLen] = '\0';
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
#if NIMBLE_OS == NIMBLE_WINDOWS
    SetUnhandledExceptionFilter(nEngineHandleException);
#else
    struct sigaction sa = {};
    sa.sa_handler = nEngineHandleException;
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
