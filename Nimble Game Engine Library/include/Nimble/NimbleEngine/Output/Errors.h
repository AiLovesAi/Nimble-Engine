#include "../../../../License/NimbleLicense.h"
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
 * @brief This class defines error values and has error parsing functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_ERRORS_H
#define NIMBLE_ENGINE_ERRORS_H /**< Header definition */

#include "../../NimbleEngine.h"

#include <limits.h>
#include <stdint.h>

#define NSUCCESS (int32_t) 0 /**< Returned when a function succeeds. */
#define NERROR (int32_t) -1 /**< Returned when a function encounters an error. */

/**
 * @brief The possible error values used by ErrorHandler.h error handler.
 */
enum nErrors {
    NERROR_UNKNOWN = INT_MIN, /**< Unknown error. */
    NERROR_NULL, /**< A variable was null when it was expecting a value. */
	NERROR_FILE_NOT_FOUND /**< A file was not found where specified. */
};


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
 *     char * errorString;
 *     nErrorToString(errorString, NERROR_NULL);
 *     if (errorString == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_NULL as string: %s\n", errorString);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the string describing @p error.
 * @param[in] error The error to get described.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 */
NIMBLE_EXPORT
char *
nErrorToString(char * dst,
               const int32_t error
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
 * character. This can be NULL.
 * @param[out] levels The number of levels of the stack. This can be NULL.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned
 * and a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 *
 * @note Each time a function is called, it is added to the stack. When a
 * function returns, it is removed from the stack.
 */
NIMBLE_EXPORT
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
