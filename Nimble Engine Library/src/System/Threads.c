#include "../../include/Nimble/NimbleLicense.h"
/*
 * Threads.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-11-03.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/Threads.h"

/**
 * @file Threads.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
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
#include <Windows.h>
#elif defined(NTHREAD_PTHREAD)
#include <pthread.h>
#else
#include <threads.h>
#endif

int nThreadCreate(nThread_t *thread, nThreadRoutine_t (*start)(void *),
 void *data)
{
    nThread_t thrd;
    int err;
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CreateThread() failed in nThreadCreate()."
    thrd = CreateThread(NULL, 0, start, data, 0, NULL);
    err = nErrorAssert(thrd != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_create() failed in nThreadCreate()."
    err = nErrorAssert(!pthread_create(thrd, NULL, start, data),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "thrd_create() failed in nThreadCreate()."
    err = nErrorAssert(thrd_create(thrd, start, data) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#undef einfoStr

#endif
    if (thread) *thread = thrd;
    return NSUCCESS;
}

int nThreadJoin(nThread_t thread, int *ret)
{
    int err;
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
    DWORD r = 0;
#  define einfoStr "WaitForSingleObject() failed in nThreadJoin()."
    err = nErrorAssert(WaitForSingleObject(thread, INFINITE) != WAIT_FAILED,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr
#  define einfoStr "GetExitCodeThread() failed in nThreadJoin()."
    err = nErrorAssert(GetExitCodeThread(thread, &r),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr
#  define einfoStr "CloseHandle() failed in nThreadJoin()."
    err = nErrorAssert(CloseHandle(thread),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
    int r;
    int *pr = &r;
#  define einfoStr "pthread_join() failed in nThreadJoin()."
    err = nErrorAssert(!pthread_join(thread, (void **) &pr),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
int r;
#  define einfoStr "thrd_join() failed in nThreadJoin()."
    err = nErrorAssert(thrd_join(thread, &r) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    if (err) return err;
#  undef einfoStr

#endif
    if (ret) *ret = (int) r;
    return NSUCCESS;
}

int nThreadDetach(nThread_t thread)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CloseHandle() failed in nThreadDetach()."
    return nErrorAssert(CloseHandle(thread),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_detach() failed in nThreadDetach()."
    return nErrorAssert(!pthread_detach(thread),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "thrd_detach() failed in nThreadDetach()."
    return nErrorAssert(thrd_detach(thread) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

int nThreadMutexCreate(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CreateMutex() failed in nThreadMutexCreate()."
    *mutex = CreateMutex(NULL, 0, NULL);
    return nErrorAssert(*mutex != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_init() failed in nThreadMutexCreate()."
    return nErrorAssert(!pthread_mutex_init(mutex, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_init() failed in nThreadMutexCreate()."
    return nErrorAssert(mtx_init(mutex, mtx_plain) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

int nThreadMutexLock(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "WaitForSingleObject() failed in nThreadJoin()."
    return nErrorAssert(WaitForSingleObject(*mutex, INFINITE) != WAIT_FAILED,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_lock() failed in nThreadMutexLock()."
    return nErrorAssert(!pthread_mutex_lock(mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_lock() failed in nThreadMutexLock()."
    return nErrorAssert(mtx_lock(mutex) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

int nThreadMutexUnlock(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "ReleaseMutex() failed in nThreadMutexUnlock()."
    return nErrorAssert(ReleaseMutex(*mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_unlock() failed in nThreadMutexUnlock()."
    return nErrorAssert(!pthread_mutex_unlock(mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_unlock() failed in nThreadMutexUnlock()."
    return nErrorAssert(mtx_unlock(mutex) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

int nThreadMutexDestroy(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CloseHandle() failed in nThreadMutexDestroy()."
    return nErrorAssert(CloseHandle(*mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    return NSUCCESS;
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_destroy() failed in nThreadMutexDestroy()."
    return nErrorAssert(!pthread_mutex_destroy(mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_destroy() failed in nThreadMutexDestroy()."
    return nErrorAssert(mtx_destroy(mutex) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

// Threads.c
