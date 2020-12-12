#include "../include/Nimble/NimbleLicense.h"
/*
 * NimbleEngine.c
 * Nimble Game Engine
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
        NIMBLE_ARGS_LOCAL[i] = nFree(NIMBLE_ARGS_LOCAL[i]);
    }
    NIMBLE_ARGS_LOCAL = nFree(NIMBLE_ARGS_LOCAL);

    for (int i = 0; i < NIMBLE_ARGC; i++)
    {
        NIMBLE_ARGS[i] = nFree(NIMBLE_ARGS[i]);
    }
    NIMBLE_ARGS = nFree(NIMBLE_ARGS);
}

static void nEngineExitSignal(int signum)
{
    exit(signum);
}

nint_t nEngineInit(const char **args, const nint_t argc,
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
        nErrorThrow(NERROR_WARN, einfoAlreadyInitializedStr,
         NCONST_STR_LEN(einfoAlreadyInitializedStr));
        return NERROR;
    }

    nint_t err = 0;

    /* Add nEngineExit() to the exit() functions. */
    if (atexit(nEngineCleanup) != NSUCCESS)
    {
        err = nErrorFromErrno(errno);
        errno = 0;
        const time_t errorTime = time(NULL);
        char einfoAtExitStr[] = "atexit() failed in nEngineInit(), and the "\
 "exit functions could not be set.";
        nint_t errorDescLen;
        
        char *errorDescStr = nErrorToString(&errorDescLen, err, einfoAtExitStr,
         NCONST_STR_LEN(einfoAtExitStr));
        nCrashSafe(err, errorTime, errorDescStr, errorDescLen);
        /* NO RETURN */
    }

    /* Set signal callbacks. */
    signal(SIGTERM, nEngineExitSignal);
    signal(SIGABRT, nCrashSignal);
    signal(SIGFPE, nCrashSignal);
    signal(SIGILL, nCrashSignal);
    signal(SIGINT, nCrashSignal);
    signal(SIGSEGV, nCrashSignal);

    /* Set Nimble callbacks. */
    if (errorCallback)
    {
        nErrorSetCallback(errorCallback);
    }
    if (crashCallback)
    {
        nCrashSetCallback(crashCallback);
    }

    /* Copy args to NIMBLE_ARGS */
    if (!args || !argc)
    {
        goto noArgsLbl;
    }

    NIMBLE_ARGS_LOCAL = nAlloc(sizeof(char *) * argc);
    NIMBLE_ARGS = nAlloc(sizeof(char *) * argc);

    nint_t count = 0;
    for (size_t len = 0; args[count] && count < argc; count++)
    {
        len = strlen(args[count]);
        NIMBLE_ARGS_LOCAL[count] = nAlloc(len + 1);
        nStringCopy(NIMBLE_ARGS_LOCAL[count], args[count], len);
        NIMBLE_ARGS[count] = nAlloc(len + 1);
        nStringCopy(NIMBLE_ARGS[count], args[count], len);
    }

    if (!count)
    {
noArgsLbl:;
        const char einfoNoArgsStr[] = "No arguments passed to nEngineInit(). "\
 "This is necessary even if no arguments are sent, as the first argument is "\
 "always the executable file, which is needed for stacktraces.";
        nCrashSafe(NERROR_NULL, time(NULL), einfoNoArgsStr,
         NCONST_STR_LEN(einfoNoArgsStr));
        /* NO RETURN */
    }

    NIMBLE_ARGC = count;


    /* Set executable file name. */
    nFileSetExecutablePath();
    
    NIMBLE_INITIALIZED = 1;

    return NSUCCESS;
}

// NimbleEngine.c
