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
 * @note Each time a function is called, it is added to the stack. When a
 * function returns, it is removed from the stack.
 */
NIMBLE_EXTERN
int32_t
nThreadCreate(nThread_t * thread,
              int32_t attributes,
              void * (*start)(void *),
              void * data
              );

/** @todo Thread and mutex functions */

#endif // NIMBLE_ENGINE_THREADS_H

#ifdef __cplusplus
}
#endif

// Errors.h
