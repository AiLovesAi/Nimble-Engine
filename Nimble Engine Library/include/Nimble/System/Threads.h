#include "../NimbleLicense.h"
/*
 * Threads.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-10-31 spooky.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Threads.h
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
 * @date 2020-10-31
 *
 * @brief This class defines thread types and functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_THREADS_H
#define NIMBLE_ENGINE_THREADS_H /**< Header definition */

#include "../NimbleEngine.h"

#define NIMBLE_THREADS_WINAPI  1
#define NIMBLE_THREADS_PTHREAD 2
#define NIMBLE_THREADS_C11     3

#if NIMBLE_OS == NIMBLE_WINDOWS
#  define NIMBLE_THREADS NIMBLE_THREADS_WINAPI
#include <windows.h>

typedef HANDLE nThread_t;
typedef DWORD nThreadRoutine_t;
typedef HANDLE nMutex_t;

#elif defined(NIMBLE_STD_POSIX)
#  define NIMBLE_THREADS NIMBLE_THREADS_PTHREAD
#include <pthread.h>

typedef pthread_t *nThread_t;
typedef void * nThreadRoutine_t;
typedef pthread_mutex_t *nMutex_t;

#elif !defined(__STDC_NO_THREADS__)
#  define NIMBLE_THREADS NIMBLE_THREADS_C11
#include <threads.h>

typedef thrd_t *nThread_t;
typedef thrd_start_t nThreadRoutine_t;
typedef mtx_t *nMutex_t;

#else
#  error Compiler or OS does not support Windows, C11, or Pthread threads.
#endif


/**
 * @brief Creates a thread.
 * 
 * Creates a thread starting at @p start() where @p data is passed, whose
 * identity is stored in @p thread with @p attributes attributes.
 *
 * @param[out] thread The thread identity of the created thread.
 * @param[in] start The start function for the thread to start in. This function
 * should take a @c void * argument, which @p data is sent to, and should
 * return its return value as a @c void *.
 * @param[in] data A pointer to the argument to pass to @p start.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 * 
 * @note If a thread is not later joined to check its result, call nThreadDetach().
 * To be fully portable, threads must return an integer value.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadCreate(nThread_t *thread,
              nThreadRoutine_t (*start)(void *),
              void *data
              );

/**
 * @brief Exits from the current thread with @p ret return value.
 *
 * @param[in] ret The return value of the exiting thread.
 */
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define nThreadExit(ret) ExitThread((DWORD) ret)
#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define nThreadExit(ret) pthread_exit((void *) &ret)
#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define nThreadExit(ret) thrd_exit(ret)
#endif

/**
 * @brief Gets the current thread.
 *
 * @return The @c nThread_t of the invoking thread if successful; otherwise
 * an error is returned and a corresponding error is sent to the error callback
 * set by nErrorHandlerSetErrorCallback().
 */
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define nThreadSelf GetCurrentThread
#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define nThreadSelf pthread_self
#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define nThreadSelf thrd_current
#endif

/**
 * @brief Checks if two thread types refer to the same thread.
 *
 * @param[in] thread1 The thread to compare to @p thread2.
 * @param[in] thread2 The thread to compare to @p thread1.
 * @return Returns 1 if the threads are equal and 0 otherwise.
 */
#if NIMBLE_THREADS == NIMBLE_THREADS_WINAPI
#  define nThreadEqual(thread1, thread2) CompareObjectHandles(thread1, thread2)
#elif NIMBLE_THREADS == NIMBLE_THREADS_PTHREAD
#  define nThreadEqual(thread1, thread2) pthread_self(thread1, thread2)
#elif NIMBLE_THREADS == NIMBLE_THREADS_C11
#  define nThreadEqual(thread1, thread2) thrd_current(thread1, thread2)
#endif

/**
 * @brief Joins (or waits for) a thread until its completion.
 *
 * @param[in] thread The thread identity of the thread to join.
 * @param[out] ret The return value of the thread on its completion.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadJoin(nThread_t thread,
            nint_t *ret
            );

/**
 * @brief Detaches a thread.
 * 
 * Detaches a thread, freeing its resources when it exits, instead of having to
 * wait for nThreadJoin() to do so.
 *
 * @param[in] thread The thread identity of the thread to detach.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadDetach(nThread_t thread
              );

/**
 * @brief Initializes a #NULL mutex.
 *
 * @param[in] mutex The mutex to initialize.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadMutexCreate(nMutex_t *mutex
                   );

/**
 * @brief Locks a mutex, or waits or the already locked mutex to unlock.
 *
 * @param[in] mutex The mutex to lock.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 * @note The mutex must be initialized by nThreadMutexCreate() prior to use.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadMutexLock(nMutex_t *mutex
                 );

/**
 * @brief Unlocks a mutex.
 *
 * @param[in] mutex The mutex to unlock.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 * @note The mutex must be initialized by nThreadMutexCreate() prior to use.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadMutexUnlock(nMutex_t *mutex
                   );

/**
 * @brief Destroys a mutex to prevent memory leaks.
 *
 * @param[in] mutex The mutex to destroy.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nThreadMutexDestroy(nMutex_t *mutex
                    );

/** @todo Thread and mutex functions */

#endif // NIMBLE_ENGINE_THREADS_H

#ifdef __cplusplus
}
#endif

// Errors.h
