#include "../../NimbleLicense.h"
/*
 * Threads.h
 * Nimble Game Engine
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

#include "../../NimbleEngine.h"

#ifdef (_WIN32)
#include <windows.h>
#define NTHREAD_WINAPI

typedef HANDLE nThread_t;
typedef HANDLE nMutex_t;

#elif defined(__unix__)
#define NTHREAD_PTHREAD
#include <pthread.h>

typedef pthread_t * nThread_t;
typedef pthread_mutex_t * nMutex_t;

#elif !defined(__STDC_NO_THREADS__)
#define NTHREAD_C11
#include <threads.h>

typedef thrd_t * nThread_t;
typedef mtx_t * nMutex_t;

#else
#error Compiler or OS does not support Windows, C11, or Pthread threads.
#endif

/**
 * @brief Creates a thread.
 * Creates a thread starting at @p start() where @p data is passed, whose
 * identity is stored in @p thread with @p attributes attributes.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void * func(void * data)
 * {
 *     int ret = *((int *) data);
 *     printf("%x\n", ret);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     nThread_t thread = NULL;
 *     int arg = 10;
 *     if (nThreadCreate(&thread, 0, func, (void *) &arg) != NSUCCESS)
 *     {
 *         printf("Could not create thread.\n");
 *         return EXIT_FAILURE;
 *     }
 *     printf("Successfully created thread.\n");
 *
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] thread The thread identity of the created thread.
 * @param[in] attributes The attribute flags for the thread creation, or 0 for
 * default attributes. @todo Figure out the attributes for this!
 * @param[in] start The start function for the thread to start in. This function
 * should take a @c void * argument, which @p data is sent to, and should
 * return its return value as a @c void *.
 * @param[in] data A pointer to the argument to pass to @p start.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
int32_t
nThreadCreate(nThread_t * thread,
              int32_t attributes,
              void * (*start)(void *),
              void * data
              );

/**
 * @brief Joins (or waits for) a thread until its completion.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void * func(void * data)
 * {
 *     int ret = *((int *) data);
 *     nThread_t thread = nThreadSelf();
 *     printf("New thread ID: %x\n", ret);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     nThread_t thread = NULL;
 *     int arg = 10;
 *     if (nThreadCreate(&thread, 0, func, (void *) &arg) != NSUCCESS)
 *     {
 *         printf("Could not create thread.\n");
 *         return EXIT_FAILURE;
 *     }
 *     printf("Successfully created thread.\n");
 *
 *     nThread_t thread = nThreadSelf();
 *
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @return The @c nThread_t of the invoking thread if successful; otherwise
 * #NERROR is returned and a corresponding error is sent to the error callback
 * set by nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
nThread_t
nThreadSelf(void
            );

/**
 * @brief Joins (or waits for) a thread until its completion.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void * func(void * data)
 * {
 *     nThread_t thread = nThreadSelf();
 *     int ret = *((int *) data);
 *     printf("New thread ID: %x\n", ret);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     nThread_t thread = NULL;
 *     int arg = 10;
 *     if (nThreadCreate(&thread, 0, func, (void *) &arg) != NSUCCESS)
 *     {
 *         printf("Could not create thread.\n");
 *         return EXIT_FAILURE;
 *     }
 *     printf("Successfully created thread.\n");
 *
 *     int ret;
 *     if (nThreadJoin(thread, (void *) &ret) != NSUCCESS)
 *     {
 *         printf("Could not join thread.\n");
 *         return EXIT_FAILURE;
 *     }
 *     printf("Successfully joined thread until its completion: %d\n", ret);
 *
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] thread The thread identity of the thread to join.
 * @param[out] ret The return value of the thread on its completion.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
int32_t
nThreadJoin(nThread_t thread,
            void * ret
            );

/**
 * @brief Initializes a #NULL mutex.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * nMutex_t mutex = NULL;
 *
 * void * func(void * data)
 * {
 *     nThreadMutexLock(mutex);
 *     puts("Mutex locked.\n");
 *
 *     nThread_t thread = nThreadSelf();
 *     int ret = *((int *) data);
 *     printf("New thread ID: %x\n", ret);
 *
 *     puts("Unlocking mutex.\n");
 *     nThreadMutexUnlock(mutex);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nThreadMutexCreate(mutex) != NSUCCESS)
 *     {
 *         printf("Could not create mutex.\n");
 *         return EXIT_FAILURE;
 *     }
 *
 *     nThread_t threads[3] = {NULL, NULL, NULL};
 *     char success[] = "Successfully created thread #0.\n";
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadCreate(&threads[i], 0, func, (void *) &i) != NSUCCESS)
 *         {
 *             printf("Could not create thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         success[sizeof(success) - 4]++;
 *         puts(success);
 *      }
 *
 *     int ret;
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadJoin(thread, (void *) &ret) != NSUCCESS)
 *         {
 *             printf("Could not join thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         printf("Successfully joined thread #%d until its completion.\n", ret);
 *     }
 *
 *     nThreadMutexDestroy(mutex);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] mutex The mutex to initialize.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
int32_t
nThreadMutexCreate(nMutex_t mutex
                   );
/**
 * @brief Locks a mutex, or waits or the already locked mutex to unlock.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * nMutex_t mutex = NULL;
 *
 * void * func(void * data)
 * {
 *     nThreadMutexLock(mutex);
 *     puts("Mutex locked.\n");
 *
 *     nThread_t thread = nThreadSelf();
 *     int ret = *((int *) data);
 *     printf("New thread ID: %x\n", ret);
 *
 *     puts("Unlocking mutex.\n");
 *     nThreadMutexUnlock(mutex);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nThreadMutexCreate(mutex) != NSUCCESS)
 *     {
 *         printf("Could not create mutex.\n");
 *         return EXIT_FAILURE;
 *     }
 *
 *     nThread_t threads[3] = {NULL, NULL, NULL};
 *     char success[] = "Successfully created thread #0.\n";
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadCreate(&threads[i], 0, func, (void *) &i) != NSUCCESS)
 *         {
 *             printf("Could not create thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         success[sizeof(success) - 4]++;
 *         puts(success);
 *      }
 *
 *     int ret;
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadJoin(thread, (void *) &ret) != NSUCCESS)
 *         {
 *             printf("Could not join thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         printf("Successfully joined thread #%d until its completion.\n", ret);
 *     }
 *
 *     nThreadMutexDestroy(mutex);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] mutex The mutex to lock.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 * @note The mutex must be initialized by nThreadMutexCreate() prior to use.
 */
NIMBLE_EXTERN
int32_t
nThreadMutexLock(nMutex_t mutex
                 );

/**
 * @brief Unlocks a mutex.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * nMutex_t mutex = NULL;
 *
 * void * func(void * data)
 * {
 *     nThreadMutexLock(mutex);
 *     puts("Mutex locked.\n");
 *
 *     nThread_t thread = nThreadSelf();
 *     int ret = *((int *) data);
 *     printf("New thread ID: %x\n", ret);
 *
 *     puts("Unlocking mutex.\n");
 *     nThreadMutexUnlock(mutex);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nThreadMutexCreate(mutex) != NSUCCESS)
 *     {
 *         printf("Could not create mutex.\n");
 *         return EXIT_FAILURE;
 *     }
 *
 *     nThread_t threads[3] = {NULL, NULL, NULL};
 *     char success[] = "Successfully created thread #0.\n";
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadCreate(&threads[i], 0, func, (void *) &i) != NSUCCESS)
 *         {
 *             printf("Could not create thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         success[sizeof(success) - 4]++;
 *         puts(success);
 *      }
 *
 *     int ret;
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadJoin(thread, (void *) &ret) != NSUCCESS)
 *         {
 *             printf("Could not join thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         printf("Successfully joined thread #%d until its completion.\n", ret);
 *     }
 *
 *     nThreadMutexDestroy(mutex);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] mutex The mutex to unlock.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 * @note The mutex must be initialized by nThreadMutexCreate() prior to use.
 */
NIMBLE_EXTERN
int32_t
nThreadMutexUnlock(nMutex_t mutex
                   );

/**
 * @brief Destroys a mutex to prevent memory leaks.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * nMutex_t mutex = NULL;
 *
 * void * func(void * data)
 * {
 *     nThreadMutexLock(mutex);
 *     puts("Mutex locked.\n");
 *
 *     nThread_t thread = nThreadSelf();
 *     int ret = *((int *) data);
 *     printf("New thread ID: %x\n", ret);
 *
 *     puts("Unlocking mutex.\n");
 *     nThreadMutexUnlock(mutex);
 *     return &ret;
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nThreadMutexCreate(mutex) != NSUCCESS)
 *     {
 *         printf("Could not create mutex.\n");
 *         return EXIT_FAILURE;
 *     }
 *
 *     nThread_t threads[3] = {NULL, NULL, NULL};
 *     char success[] = "Successfully created thread #0.\n";
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadCreate(&threads[i], 0, func, (void *) &i) != NSUCCESS)
 *         {
 *             printf("Could not create thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         success[sizeof(success) - 4]++;
 *         puts(success);
 *      }
 *
 *     int ret;
 *     for (int i = 0; i < (sizeof(threads) / sizeof(nThread_t)); i++)
 *     {
 *         if (nThreadJoin(thread, (void *) &ret) != NSUCCESS)
 *         {
 *             printf("Could not join thread.\n");
 *             return EXIT_FAILURE;
 *         }
 *         printf("Successfully joined thread #%d until its completion.\n", ret);
 *     }
 *
 *     nThreadMutexDestroy(mutex);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] mutex The mutex to destroy.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
int32_t
nThreadMutexDestroy(nMutex_t mutex
                    );

/** @todo Thread and mutex functions */

#endif // NIMBLE_ENGINE_THREADS_H

#ifdef __cplusplus
}
#endif

// Errors.h
