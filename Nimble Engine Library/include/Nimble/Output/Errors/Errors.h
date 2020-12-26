#include "../../NimbleLicense.h"
/*
 * Errors.h
 * Nimble Engine
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
 * @brief This class defines error handling functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_ERRORS_H
#define NIMBLE_ENGINE_ERRORS_H /**< Header definition */

#include "../../NimbleEngine.h"
#include "ErrorValues.h"

#include <time.h>


/**
 * @brief Sends an error to the error callback.
 * Sends an error to the error callback defined by
 * nErrorHandlerSetErrorCallback(), and determines whether or not crashing is
 * necessary.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char exampleFilePath[] = "example.txt";
 *     size_t errorDescLen;
 *     char *errorDescStr = nErrorToString(&errorDescLen,
 *      NERROR_FILE_NOT_FOUND, exampleFilePath,
 *      NCONST_STR_LEN(exampleFilePath));
 *     nErrorThrow(NERROR_FILE_NOT_FOUND, errorDescStr, errorDescLen);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] error The error to throw.
 * @param[in] errorDescStr Relevant information, such as a file location, that
 * could help diagnose the error. This can be @c #NULL.
 * @param[in] errorDescStrLen The length of the @p info argument. A length of
 * zero (0) uses strlen() to determine length.
 *
 * @note The program will crash if this is unsuccessful.
 */
NIMBLE_EXTERN
void
nErrorThrow(const nint_t error,
            char *errorDescStr,
            size_t errorDescLen
            );

/**
 * @brief Sets the last errno error to @p err.
 */
#  define nErrorLastErrno(err) ({\
    err = errno;\
    errno = 0;\
})

/**
 * @brief Describes an error and returns a string.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     size_t errorLen;
 *     char exampleFilePath[] = "example.txt";
 *     char *errorStr = nErrorToString(&errorLen, NERROR_FILE_NOT_FOUND,
 *      exampleFilePath, sizeof(exampleFilePath))
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
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return A pointer to the string describing @p error is returned.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nErrorToString(size_t *errorLen,
               const nint_t error,
               const char *info,
               size_t infoLen
               )
__attribute__((warn_unused_result));

#if NIMBLE_OS == NIMBLE_WINDOWS
/**
 * @brief Sets the last Windows error to @p err.
 */
#  define nErrorLastWindows(err) ({\
    err = GetLastError();\
    SetLastError(ERROR_SUCCESS);\
})

/**
 * @brief Describes a Windows error and returns a string.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     size_t errorLen;
 *     char exampleFilePath[] = "example.txt";
 *     char *errorStr = nErrorToString(&errorLen, GetLastError(),
 *      exampleFilePath, NCONST_STR_LEN(exampleFilePath))
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
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return A pointer to the string describing @p error is returned if successful;
 * otherwise @c #NULL is returned.
 */
NIMBLE_EXTERN
char *
nErrorToStringWindows(size_t *errorLen,
                      const nint_t error,
                      const char *info,
                      size_t infoLen
                      )
__attribute__((warn_unused_result));
#endif

/**
 * @brief Sets the callback function to handle errors.
 *
 * Sets the callback function @p callback that gets called when an error occurs.
 *
 * @par Example:
 * @code
 * #include <stdio.h>
 * #include <time.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void errorHandler(const nint_t error, const char * errorDesc,
 *  const size_t errorDescLen, const time_t errorTime, const char * stack,
 *  const size_t stackLen)
 * {
 *     struct tm *timeInfo = localtime(&errorTime);
 *     const char format[] = "%x %X %Z";
 *     const char example = "01/01/2020 16:30:45 GMT"
 *     char *timeStr = nAlloc(sizeof(example));
 *     if (timeStr == NULL)
 *     {
 *         fprintf(stderr, "Failed to allocate to timeStr.\n");
 *         return;
 *     }
 *     strftime(timeStr, sizeof(example), format, timeInfo);
 *
 *     fprintf(stderr, "\nAn error occurred at %s:\nError description: "\
 *      "%s\nStack trace: %s\n\n", timeStr, errorDesc, stack);
 *     nFree(timeStr);
 * }
 *
 * int main(int argc, char **argv)
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
 * @return @c #NSUCCESS is returned if successful; otherwise @c #NERROR is
 * returned.
 *
 * @note Check nErrorHandlerDefault() for parameter information.
 */
NIMBLE_EXTERN
nint_t
nErrorSetCallback(void (*callback)(
                                   const nint_t error,
                                   const time_t errorTime,
                                   const char *errorDesc,
                                   const size_t errorDescLen,
                                   const char *stack,
                                   const size_t stackLen
                                   )
                  );

/**
 * @brief Returns the current stack trace as a string.
 * Returns the current stack trace as a string, and sets the @p stackLen of the
 * string and @p levels of the stack.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     size_t stackLen, stackLevels;
 *     char *stack = nErrorGetStacktrace(&stackLen, &stackLevels);
 *     if (stack == NULL)
 *     {
 *         fprintf(stderr, "Failed to get stack trace.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Last %d levels of stack trace: %s\n", stackLevels, stack);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] stackLen The length of the string returned. This can be @c #NULL.
 * @param[in,out] stackLevels The number of levels found on the stack. If the
 * value of this is nonzero when passed, it will act as the maximum number of
 * stack levels to be returned. This can be @c #NULL.
 * @return A pointer to the string of the stack is returned if successful;
 * otherwise @c #NULL is returned.
 *
 * @note Each time a function is called, it is added to the stack. When a
 * function returns, it is removed from the stack.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nErrorGetStacktrace(size_t *stackLen,
                    size_t *stackLevels
                    )
__attribute__((warn_unused_result));

#endif // NIMBLE_ENGINE_ERRORS_H

#ifdef __cplusplus
}
#endif

// Errors.h
