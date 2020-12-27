#include "../include/Nimble/NimbleLicense.h"
/*
 * NimbleEngine.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-10.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../include/Nimble/NimbleEngine.h"

/**
 * @file NimbleEngine.c
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
 * @date 2020-08-10
 *
 * @brief This class includes all the necessary game engine header files.
 *
 * This class includes all the necessary game engine header files that are
 * used in game development, and defines the functions used in initialization.
 */

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

volatile _Bool NIMBLE_INITIALIZED = 0;

static char **NIMBLE_ARGS_LOCAL = NULL;
static nint_t NIMBLE_ARGC_LOCAL = 0;
char **NIMBLE_ARGS = NULL;
nint_t NIMBLE_ARGC = 0;


static void nEngineCleanup(void)
{
    /* Free NIMBLE_ARGS */
    for (int i = 0; i < NIMBLE_ARGC_LOCAL; i++)
    {
        nFree(NIMBLE_ARGS_LOCAL[i]);
    }
    nFree(NIMBLE_ARGS_LOCAL);

    for (int i = 0; i < NIMBLE_ARGC; i++)
    {
        nFree(NIMBLE_ARGS[i]);
    }
    nFree(NIMBLE_ARGS);
}

static void nEngineExitSignal(int signum)
{
    exit(signum);
}

nint_t nEngineInit(char **args, const nint_t argc,
 void (*errorCallback) (const nint_t error, const time_t errorTime,
 const char *errorDesc, const size_t errorDescLen, const char *stack,
 const size_t stackLen),

 void (*crashCallback)(const nint_t error, const time_t errorTime,
 const char *errorDesc, const size_t errorDescLen, const char *stack,
 const size_t stackLen)

 )
{
    if (NIMBLE_INITIALIZED)
    {
        const char einfoAlreadyInitializedStr[] = "nEngineInit() was called, "\
 "but Nimble is already initialized.";
        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, NERROR_WARN,
         einfoAlreadyInitializedStr,
         NCONST_STR_LEN(einfoAlreadyInitializedStr));
        nErrorThrow(NERROR_WARN, errorDescStr, errorDescLen);
        nFree(errorDescStr);
        return NERROR;
    }

    /* Add nEngineCleanup() to the exit functions. */
#define einfoStr "atexit() failed in nEngineInit(), and the exit functions "\
 "could not be set."
    nAssert(!atexit(&nEngineCleanup),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    /* Set signal callbacks. */
#define einfoStr "signal() failed in nEngineInit(), and the signal handlers "\
 "could not be set."
    nAssert(signal(SIGTERM, nEngineExitSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGABRT, nCrashSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGFPE, nCrashSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGILL, nCrashSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGINT, nCrashSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(signal(SIGSEGV, nCrashSignal) != SIG_ERR,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    /* Set Nimble callbacks. */
    nErrorSetCallback(errorCallback);
    nCrashSetCallback(crashCallback);

#define einfoStr "No arguments passed to nEngineInit(). This is necessary "\
 "even if no arguments are sent, as the first argument is always the "\
 "executable file, which is needed for stacktraces."
    /* Copy args to NIMBLE_ARGS */
    nAssert(args && argc , NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));

    NIMBLE_ARGS_LOCAL = nRealloc(NIMBLE_ARGS_LOCAL, sizeof(char *) * argc);
    NIMBLE_ARGS = nRealloc(NIMBLE_ARGS, sizeof(char *) * argc);
    nint_t count = 0;
    for (size_t len = 0; args[count] && count < argc; count++)
    {
        len = strlen(args[count]);
        NIMBLE_ARGS_LOCAL[count] = nRealloc(NIMBLE_ARGS_LOCAL[count], len + 1);
        nStringCopy(NIMBLE_ARGS_LOCAL[count], args[count], len);
        NIMBLE_ARGS[count] = nRealloc(NIMBLE_ARGS[count], len + 1);
        nStringCopy(NIMBLE_ARGS[count], args[count], len);
    }

    nAssert(count, NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    NIMBLE_ARGC_LOCAL = count;
    NIMBLE_ARGC = count;


    /* Set executable file name. */
    nFileSetExecutablePath();
    
    NIMBLE_INITIALIZED = 1;

    return NSUCCESS;
}

// NimbleEngine.c
