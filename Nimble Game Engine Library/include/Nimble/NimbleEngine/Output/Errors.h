#include "../../NimbleLicense.h"
/*
 * Errors.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-14.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Errors.h
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
 * @date 2020-08-14
 *
 * @brief This class defines error values and error handling functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_ERRORS_H
#define NIMBLE_ENGINE_ERRORS_H /**< Header definition */

#include "../../NimbleEngine.h"

#include <limits.h>
#include <stdint.h>
#include <time.h>

#define NSUCCESS (int32_t) 0 /**< Returned when a function succeeds. */
#define NERROR (int32_t) -1 /**< Returned when a function encounters an error. */

/**
 * @brief The possible error values used by ErrorHandler.h error handler.
 */
enum nErrors {
    NERROR_UNKNOWN = INT_MIN, /**< An nknown error occurred. */
    NERROR_NULL, /**< A pointer was null when a nonnull pointer was expected. */
	NERROR_FILE_NOT_FOUND, /**< A file was not found where specified. */
	NERROR_ERROR_NOT_FOUND /**< An error passed to a function was not valid. */
};


/**
 * @brief Sends an error to the error callback.
 * Sends an error to the error callback defined by
 * nErrorHandlerSetErrorCallback(), and determines whether or not crashing is
 * necessary.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char ** argv)
 * {
 *     char exampleFilePath[] = "example.txt";
 *     if (nErrorThrow(NERROR_FILE_NOT_FOUND, exampleFilePath,
           sizeof(exampleFilePath)) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Failed to throw error.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Successfully threw error.\n");
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] error The error to throw.
 * @param[in] info Relevant information, such as a file location, that could help
 * @param[in] infoLen The length of the @p info argument, including the null
 * character. A length of zero (0) uses strlen() to determine length.
 * diagnose the error. This can be #NULL.
 * @return #NSUCCESS is returned if successful; otherwise @c #NERROR is returned.
 */
NIMBLE_EXTERN
int32_t
nErrorThrow(const int32_t error,
            const char * info,
            int32_t infoLen
            );

/**
 * @brief Describes an error and returns a string.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char ** argv)
 * {
 *     char * errorStr;
 *     int32_t errorLen;
 *     char exampleFilePath[] = "example.txt";
 *     nErrorToString(errorStr, &errorLen, NERROR_FILE_NOT_FOUND, exampleFilePath,
 *      sizeof(exampleFilePath));
 *     if (errorStr == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_FILE_NOT_FOUND as string: %s\n", errorStr);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the string describing @p error.
 * @param[out] size The length of the string returned, including the null
 * character. This can be #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be #NULL.
 * @param[in] infoLen The length of the @p info argument, including the null
 * character. A length of zero (0) uses strlen() to determine length.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 */
NIMBLE_EXTERN
char *
nErrorToString(char * dst,
               int32_t * size,
               const int32_t error,
               const char * info,
               int32_t infoLen
               );

/**
 * @brief Sets the callback function to handle errors.
 *
 * Sets the callback function @p callback that gets called when an error occurs.
 *
 * @par Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <time.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void errorHandler(const int32_t error, const char * errorDesc,
 *       const char * stack, const time_t errorTime)
 * {
 *     struct tm * timeInfo = localtime(&errorTime);
 *     const char format[] = "%x %X %Z";
 *     const char example = "01/01/2020 16:30:45 GMT"
 *     char * timeString = malloc(sizeof(void *) + sizeof(example));
 *     if (timeString == NULL)
 *     {
 *         fprintf(stderr, "Failed to allocate to timeString.\n");
 *         return;
 *     }
 *     strftime(timeString, sizeof(example), format, timeInfo);
 *
 *     fprintf(stderr, "\nAn error occurred at %s:\nError description: "\
 *      "%s\nStack trace: %s\n\n", timeString, errorDesc, stack);
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nErrorHandlerSetErrorCallback(errorHandler) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Could not set error callback for Nimble.\n");
 *         return EXIT_FAILURE;
 *     }
 *     printf("Successfully set error callback for Nimble.\n");
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] callback The function that gets called when an error occurs.
 * @return #NSUCCESS is returned if successful; otherwise @c #NERROR is
 * returned.
 *
 * @note The callback parameters are <tt>error, errorDesc, stack, errorTime</tt>.
 */
NIMBLE_EXTERN
int32_t
nErrorSetCallback(int32_t (*callback)(
                                      const int32_t,
                                      const char *,
                                      const char *,
                                      const time_t
                                      )
                  );

/**
 * @brief Returns the current stack trace as a string.
 * Returns the current stack trace as a string, and sets @p 
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char ** argv)
 * {
 *     int32_t levels, size;
 *     char * stack;
 *     nErrorGetStacktrace(stack, &levels, &size);
 *     if (stack == NULL)
 *     {
 *         fprintf(stderr, "Failed to get stack trace.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Last %d levels of stack trace: %s\n", levels, stack);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the stacktrace string.
 * @param[out] size The length of the string returned, including the null
 * character. This can be #NULL.
 * @param[out] levels The number of levels of the stack. This can be #NULL.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned
 * and a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 *
 * @note Each time a function is called, it is added to the stack. When a
 * function returns, it is removed from the stack.
 */
NIMBLE_EXTERN
char *
nErrorGetStacktrace(char * dst,
                    int32_t * size,
                    int32_t * levels
                    );

#endif // NIMBLE_ENGINE_ERRORS_H

#ifdef __cplusplus
}
#endif

// Errors.h
