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

volatile _Bool NIMBLE_INITIALIZED = 0;

void *nAlloc(const size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
    {
        /* Check if successfully allocated. */
        nCrashSafe(NERROR_NO_MEMORY, time(NULL), nErrorDesc(NERROR_NO_MEMORY), nErrorDescLen(NERROR_NO_MEMORY));
        /* NO RETURN */
    }

    return ptr;
}

void *nRealloc(void *ptr, const size_t size)
{
    ptr = realloc(ptr, size);

    /* Check if successfully allocated. */
    if (!ptr)
    {
        nCrashSafe(NERROR_NO_MEMORY, time(NULL), nErrorDesc(NERROR_NO_MEMORY),
         nErrorDescLen(NERROR_NO_MEMORY));
         /* NO RETURN */
    }

    return ptr;
}

size_t nStringCopy(char *const restrict dst, const char *const restrict src,
 const size_t len)
{
    if (!src)
    {
        const char einfoNullStr[] = "Source string NULL in nStringCopy().";
        nErrorThrow(NERROR_NULL, einfoNullStr, NCONST_STR_LEN(einfoNullStr));
        return 0;
    }

    char *d = dst;
    const char *s = src;
    size_t l = len;

    /* For each character that is not equal to the null terminator,
     * src char = dst char. */
    while (l-- && (*s != '\0'))
    {
        *d++ = *s++;
    }
    
    /* Ensure the string is null-terminated. */
    dst[len] = '\0';

    return len - l;
}


_Noreturn void nEngineExit(void)
{
    /** @todo Make safe exit function */
    exit(EXIT_SUCCESS);
}

static void nEngineExitSignal(int signum)
{
    nEngineExit();
}

nint_t nEngineInit(
 void (*errorCallback) (const nint_t error, const time_t errorTime,
 const char *errorDesc, const size_t errorDescLen, const char *stack,
 const size_t stackLen),

 void (*crashCallback)(const nint_t error, const time_t errorTime,
 const char *errorDesc, const size_t errorDescLen, const char *stack,
 const size_t stackLen)

 )
{
    nint_t err = 0;

    /* Add nEngineExit() to the exit() functions. */
    if (atexit(nEngineExit) != NSUCCESS)
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

    /* Set executable file name. */
    nFileGetExecutablePath();
    
    NIMBLE_INITIALIZED = 1;

    return NSUCCESS;
}

// NimbleEngine.c
