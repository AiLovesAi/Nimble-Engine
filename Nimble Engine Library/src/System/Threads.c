#include "../../include/Nimble/NimbleLicense.h"
/*
 * Threads.c
 * Nimble Engine
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

nint_t nThreadCreate(nThread_t *thread, nThreadRoutine_t (*start)(void *),
 void *data)
{
    nThread_t thrd;
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CreateThread() failed in nThreadCreate()."
    thrd = CreateThread(NULL, 0, start, data, 0, NULL);
    nErrorAssertRetEi(thrd != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_create() failed in nThreadCreate()."
    nErrorAssertRetEi(!pthread_create(thrd, NULL, start, data),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "thrd_create() failed in nThreadCreate()."
    nErrorAssertRetEi(thrd_create(thrd, start, data) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

#endif
    if (thread) *thread = thrd;
    return NSUCCESS;
}

nint_t nThreadJoin(nThread_t thread, nint_t *ret)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
    DWORD r = 0;
#  define einfoStr "WaitForSingleObject() failed in nThreadJoin()."
    nErrorAssertRetEi(WaitForSingleObject(thread, INFINITE) != WAIT_FAILED,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr
#  define einfoStr "GetExitCodeThread() failed in nThreadJoin()."
    nErrorAssertRetEi(GetExitCodeThread(thread, &r),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr
#  define einfoStr "CloseHandle() failed in nThreadJoin()."
    nErrorAssertRetEi(CloseHandle(thread),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
    int r;
    int *pr = &r;
#  define einfoStr "pthread_join() failed in nThreadJoin()."
    nErrorAssertRetEi(!pthread_join(thread, (void **) &pr),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
int r;
#  define einfoStr "thrd_join() failed in nThreadJoin()."
    nErrorAssertRetEi(thrd_join(thread, &r) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
    if (ret) *ret = (int) r;
    return NSUCCESS;
}

nint_t nThreadDetach(nThread_t thread)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CloseHandle() failed in nThreadDetach()."
    nErrorAssertRetE(CloseHandle(thread),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_detach() failed in nThreadDetach()."
    nErrorAssertRetE(!pthread_detach(thread),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "thrd_detach() failed in nThreadDetach()."
    nErrorAssertRetE(thrd_detach(thread) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

nint_t nThreadMutexCreate(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CreateMutex() failed in nThreadMutexCreate()."
    *mutex = CreateMutex(NULL, 0, NULL);
    nErrorAssertRetE(*mutex != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_init() failed in nThreadMutexCreate()."
    nErrorAssertRetE(!pthread_mutex_init(mutex, NULL),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_init() failed in nThreadMutexCreate()."
    nErrorAssertRetE(mtx_init(mutex, mtx_plain) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

nint_t nThreadMutexLock(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "WaitForSingleObject() failed in nThreadJoin()."
    nErrorAssertRetE(WaitForSingleObject(*mutex, INFINITE) != WAIT_FAILED,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_lock() failed in nThreadMutexLock()."
    nErrorAssertRetE(!pthread_mutex_lock(mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_lock() failed in nThreadMutexLock()."
    nErrorAssertRetE(mtx_lock(mutex) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

nint_t nThreadMutexUnlock(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "ReleaseMutex() failed in nThreadMutexUnlock()."
    nErrorAssertRetE(ReleaseMutex(*mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_unlock() failed in nThreadMutexUnlock()."
    nErrorAssertRetE(!pthread_mutex_unlock(mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_unlock() failed in nThreadMutexUnlock()."
    nErrorAssertRetE(mtx_unlock(mutex) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

nint_t nThreadMutexDestroy(nMutex_t *mutex)
{
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define einfoStr "CloseHandle() failed in nThreadMutexDestroy()."
    nErrorAssertRetE(CloseHandle(*mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
    return NSUCCESS;
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define einfoStr "pthread_mutex_destroy() failed in nThreadMutexDestroy()."
    nErrorAssertRetE(!pthread_mutex_destroy(mutex),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define einfoStr "mtx_destroy() failed in nThreadMutexDestroy()."
    nErrorAssertRetE(mtx_destroy(mutex) == thrd_success,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#  undef einfoStr

#endif
}

// Threads.c
