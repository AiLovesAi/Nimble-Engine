#include "../../include/Nimble/NimbleLicense.h"
/*
 * Threads.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-11-03.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/Threads.h"

/**
 * @file Threads.c
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
 * @date 2020-11-03
 *
 * @brief This class defines thread functions.
 */

#include <stdlib.h>

#ifdef NTHREAD_WINAPI
#include <windows.h>
#elif defined(NTHREAD_PTHREAD)
#include <pthread.h>
#else
#include <threads.h>
#endif

nint_t nThreadCreate(nThread_t *thread, nint_t attributes,
 void *(*start)(void *), void *data)
{
    /// @todo Attributes, pointer conversion for some arguments
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
    *thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) start, data, 0,
     NULL);
    if (!(*thread))
    {
        const char einfoThreadStr[] = "CreateThread() failed in "\
 "nThreadCreate().";
        nint_t err;
        nErrorLastWindows(err);
        size_t errorDescLen;
        char *errorDescStr = nErrorToStringWindows(&errorDescLen,
         err, einfoThreadStr,
         NCONST_STR_LEN(einfoThreadStr));
        nErrorThrow(NERROR_INTERNAL_FAILURE, errorDescStr, errorDescLen);
        nFree(errorDescStr);
        return NERROR;
    }
#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
    nint_t err = pthread_create(*thread, NULL, start, data);
    if (err)
    {
        const char einfoThreadStr[] = "pthread_create() failed in "\
 "nThreadCreate().";
        nErrorFromErrno(err);
        size_t errorDescLen;
        char *errorDescStr = nErrorToStringWindows(&errorDescLen,
         nErrorFromErrno(err), einfoThreadStr,
         NCONST_STR_LEN(einfoThreadStr));
        nErrorThrow(nErrorFromErrno(err), errorDescStr, errorDescLen);
        nFree(errorDescStr);
        return NERROR;
    }
#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
    nint_t err = thrd_create(thread, start, data);
    if (err)
    {
        const char einfoThreadStr[] = "thrd_create() failed in "\
 "nThreadCreate().";
        size_t errorDescLen;
        char *errorDescStr = nErrorToStringWindows(&errorDescLen,
         nErrorFromErrno(err), einfoThreadStr,
         NCONST_STR_LEN(einfoThreadStr));
        nErrorThrow(NERROR_INTERNAL_FAILURE, errorDescStr, errorDescLen);
        nFree(errorDescStr);
        return NERROR;
    }
#endif
}

nThread_t nThreadSelf(void)
{
    /// @todo
    return NSUCCESS;
}

nint_t nThreadJoin(nThread_t thread, void *ret)
{
    /// @todo
    return NSUCCESS;
}

nint_t nThreadMutexCreate(nMutex_t mutex)
{
    /// @todo
    return NSUCCESS;
}

nint_t nThreadMutexLock(nMutex_t mutex)
{
    /// @todo
    return NSUCCESS;
}

nint_t nThreadMutexUnlock(nMutex_t mutex)
{
    /// @todo
    return NSUCCESS;
}

nint_t nThreadMutexDestroy(nMutex_t mutex)
{
    /// @todo
    return NSUCCESS;
}

// Threads.c
