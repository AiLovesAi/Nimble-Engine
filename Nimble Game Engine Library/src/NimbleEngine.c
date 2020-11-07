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

#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>

#include "../include/Nimble/NimbleEngine/Output/CrashHandler.h"

void * nAlloc(const size_t size)
{
    void* ptr = malloc(size);

    if (!ptr)
    {
        nCrashSafe(NERROR_NO_MEMORY, time(NULL), nErrorDesc(NERROR_NO_MEMORY), nErrorDescLen(NERROR_NO_MEMORY);
    }

    return ptr;
}

void nEngineExit(void)
{
    /** @todo Make safe exit function */
    exit(EXIT_SUCCESS);
}

void nEngineExitSignal(int signum)
{
    nEngineExit();
}

nint_t nEngineInit(void (* errorCallback)(const nint_t error,
         const time_t errorTime, char * errorDesc, nint_t errorDescLen,
         char * stack, nint_t stackLen),
         void (* crashCallback)(const nint_t error, const time_t errorTime,
         char * errorDesc, nint_t errorDescLen, char * stack,
         nint_t stackLen))
{
    /** @todo Make init function */
    if (atexit(nEngineExit) != NSUCCESS)
    {
        const time_t errorTime = time(NULL);
        char * errorDesc;
        nint_t errorDescLen;
        char * info;
        nint_t infoLen;
        
        nErrorToString(errorDesc, &errorDescLen, NERROR_INTERNAL_FAILURE,
         info, infoLen);
        nCrashSafe(NERROR_INTERNAL_FAILURE, errorTime, errorDesc,
         errorDescLen);
    }
    #ifdef SIGTERM
    signal(SIGTERM, nEngineExitSignal);
    #endif
    
    #ifdef SIGABRT
    signal(SIGABRT, nCrashSignal);
    #endif
    #ifdef SIGFPE
    signal(SIGFPE, nCrashSignal);
    #endif
    #ifdef SIGILL
    signal(SIGILL, nCrashSignal);
    #endif
    #ifdef SIGINT
    signal(SIGINT, nCrashSignal);
    #endif
    #ifdef SIGSEGV
    signal(SIGSEGV, nCrashSignal);
    #endif
    
    return NSUCCESS;
}

// NimbleEngine.c
