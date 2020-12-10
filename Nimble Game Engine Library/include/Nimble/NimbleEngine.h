#include "NimbleLicense.h"
/*
 * NimbleEngine.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-10.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file NimbleEngine.h
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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_H
#define NIMBLE_ENGINE_H /**< Header definition */

#include "Nimble.h"

#include "Network/Network.h"

#include "Output/Errors/Crash.h"
#include "Output/Errors/Errors.h"
#include "Output/Files.h"
#include "Output/Logging.h"

#include "System/CPUInfo.h"
#include "System/Threads.h"


#include <time.h>

/**
 * @brief The variable that is set after a successful initialization.
 */
NIMBLE_EXTERN
volatile _Bool NIMBLE_INITIALIZED;


/**
 * @brief Allocates a pointer.
 * Allocates a pointer and checks if it is successful.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char original[] = "Hello world.";
 *     char *new = nAlloc(sizeof(original) + 1);
 *     new[sizeof(original) - 1] = '\n';
 *     new[sizeof(original)] = '\0';
 *     puts(new);
 *     new = nFree(new);
 *     if (new)
 *     {
 *         puts("We will get here only if we use nFree(new) with no assignment!");
 *     }
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] size The size of the memory block in bytes.
 * @return The allocated pointer.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
void *
nAlloc(const size_t size)
__attribute__((warn_unused_result))
;

/**
 * @brief Reallocates a pointer.
 * Rellocates a pointer and checks if it is successful.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char original[] = "Hello world.";
 *     char *new;
 *     new = nRealloc(sizeof(original) + 1);
 *     new[sizeof(original) - 1] = '\n';
 *     new[sizeof(original)] = '\0';
 *     puts(new);
 *     new = nRealloc(sizeof(original) - 1);
 *     new[sizeof(original) - 2] = '\0';
 *     puts(new);
 *     new = nFree(new);
 *     if (new)
 *     {
 *         puts("We will get here only if we use nFree(new) with no assignment!");
 *     }
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in,out] ptr The pointer to reallocate.
 * @param[in] size The size of the new memory block in bytes.
 * @return The reallocated @p ptr.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
void *
nRealloc(void*ptr, const size_t size)
__attribute__((warn_unused_result))
;

/**
 * @brief Frees a pointer.
 * Frees a pointer and returns #NULL to allow the invoker to optionally nullify
 * the pointer. Should the freed pointer location be needed again, no assignment
 * is necessary.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char original[] = "Hello world.";
 *     char *new = nAlloc(sizeof(original) + 1);
 *     new[sizeof(original) - 1] = '\n';
 *     new[sizeof(original)] = '\0';
 *     puts(new);
 *     new = nFree(new);
 *     if (new)
 *     {
 *         puts("We will get here only if we use nFree(new) with no assignment!");
 *     }
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] ptr The pointer to free.
 * @return #NULL is always returned.
 */
NIMBLE_INLINE
void *
nFree(void *ptr)
{
	free(ptr);
	return NULL;
}

/**
 * @brief Copies @p len characters from @p src to @p dst.
 * Copies @p len characters from @p src to @p dst. The string is always null
 * terminated. If there is already a null terminator, no more characters are
 * copied.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char original[] = "Hello world.";
 *     char *new = nAlloc(sizeof(original));
 *     nStringCopy(original, new, NCONST_STR_LEN(original));
 *     printf("New string: %s\n", new);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The pointer to the destination.
 * @param[in] src The pointer to free.
 * @param[in] len The number of characters to copy. This must not include the
 * null terminator.
 * @return The number of successfully copied bytes is returned.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
size_t
nStringCopy(char *restrict dst,
            const char *restrict src,
            const size_t len
            );

/**
 * @brief Exits the game engine.
 * Exits the game engine by safely stopping threads
 *
 * @par Example:
 * @code
 * #include <inttypes.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     if (nEngineInit() == NSUCCESS)
 *     {
 *         nEngineExit();
 *     }
 *     fprintf(stderr, "Failed to initialize Nimble.");
 *     exit(EXIT_SUCCESS);
 * }
 * @endcode
 *
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
_Noreturn
void
nEngineExit(void);

/**
 * @brief Initialized the game engine.
 * Initializes the game engine by setting up the error/crash handlers, logger, and
 * thread manager.
 *
 * @par Example:
 * @code
 * #include <inttypes.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void errorCallback(const nint_t error, const time_t errorTime,
 *  char *errorDesc, nint_t errorDescLen, char *stack)
 * {
 *     ...
 * }
 * 
 * void crashCallback(const nint_t error, const time_t errorTime,
 *  char *errorDesc, nint_t errorDescLen, char *stack)
 * {
 *     ...
 * }
 * 
 * int main(int argc, char **argv)
 * {
 *     if (nEngineInit(&errorCallback, &crashCallback) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Failed to initialize Nimble.");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Successfully initialized game engine.");
 *     exit(EXIT_SUCCESS);
 * }
 * @endcode
 *
 * @param[in] errorCallback The error callback function that is called when an
 * error occurs. This can be #NULL to use the default callback.
 * @param[in] crashCallback The crash callback function that is called when the
 * engine crashes. This can be #NULL to use the default callback.
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
nint_t
nEngineInit(void (*errorCallback)(
                                  const nint_t error,
                                  const time_t errorTime,
                                  const char *errorDesc,
                                  const size_t errorDescLen,
                                  const char *stack,
                                  const size_t stackLen
                                  ),
            void (*crashCallback) (const nint_t error,
                                   const time_t errorTime,
                                   const char *errorDesc,
                                   const size_t errorDescLen,
                                   const char *stack,
                                   const size_t stackLen
                                   )
            );

#endif // NIMBLE_ENGINE_H

#ifdef __cplusplus
}
#endif

// NimbleEngine.h
