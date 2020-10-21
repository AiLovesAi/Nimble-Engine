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
    NERROR_MIN = INT_MIN, /**< The mininum error number. */
    
    NERROR_UNKNOWN, /**< An nknown error occurred. */
    
    NERROR_SIGABRT, /**< Caught abort signal. */
    NERROR_SIGFPE, /**< Caught floating point exception signal. */
    NERROR_SIGILL, /**< Caught illegal expression signal. */
    NERROR_SIGINT, /**< Caught interrupt signal. */
    NERROR_SIGSEGV, /**< Caught memory address violation signal. */
    NERROR_SIGTERM, /**< Caught termination signal. */
    
    NERROR_NULL, /**< A pointer was null when a nonnull pointer was expected. */
    NERROR_FILE_NOT_FOUND, /**< A file was not found where specified. */
    NERROR_ERROR_NOT_FOUND, /**< An error passed to a function was not valid. */
    
    NERROR_MAX /**< The maximum error number. */
};


/**
 * @brief The strings used to represent error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const char * nErrorStrings[];

/*
 * @brief Gets the error code @p err represented as a string from #nErrorStrings.
 *
 * @param[in] err The error code to translate to a string.
 * @return @p err translated to a string.
 */
#define NERROR_STRING(err) (((err >= NERROR_MIN) && err <= (NERROR_MAX)) ?\
                            nErrorStrings[err - NERROR_MIN] :\
                            nErrorStrings[NERROR_UNKNOWN - NERROR_MIN])

/*
 * @brief Gets the length of the error code @p err from #nErrorStringLengths.
 *
 * @param[in] err The error code to determine the length of.
 * @return @p err's string translation length.
 */
#define NERROR_LENGTH(err) (((err >= NERROR_MIN) && err <= (NERROR_MAX)) ?\
                            nErrorStringLengths[err - NERROR_MIN] :\
                            nErrorStringLengths[NERROR_UNKNOWN - NERROR_MIN])

/**
 * @brief The descriptions of error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const char * nErrorDescriptions[];

/*
 * @brief Gets the error description of the error code @p err from #nErrorDescriptions.
 *
 * @param[in] err The error code to describe.
 * @return The description of @p err as a string.
 */
#define NERROR_DESCRIPTION(err) (((err >= NERROR_MIN) && err <= (NERROR_MAX)) ?\
                                 nErrorDescriptions[err - NERROR_MIN] :\
                                 nErrorDescriptions[NERROR_UNKNOWN - NERROR_MIN])


/**
 * @brief Describes an error and returns a string with no error handling.
 *
 * Example:
 * @todo Do this
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
 *     if (nErrorToStringLocal(errorStr, &errorLen, NERROR_FILE_NOT_FOUND,
 *          exampleFilePath, sizeof(exampleFilePath)) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_FILE_NOT_FOUND as string: %s\n", errorStr);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the string describing @p error. This
 * can be @c #NULL.
 * @param[out] errorLen The length of the string returned, including the null
 * character. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument, including the null
 * character. A length of zero (0) uses strlen() to determine length.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 *
 * @note This function is used by the game engine and is not expected to be used
 * by developers, but is optional.
 */
NIMBLE_EXTERN
int32_t
nErrorToStringLocal(char * dst,
                    int32_t * errorLen,
                    const int32_t error,
                    const char * info,
                    int32_t infoLen
                    );

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
 * diagnose the error. This can be @c #NULL.
 *
 * @note The program will crash if this is unsuccessful.
 */
NIMBLE_EXTERN
void
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
 *     if (nErrorToString(errorStr, &errorLen, NERROR_FILE_NOT_FOUND,
 *          exampleFilePath, sizeof(exampleFilePath)) == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_FILE_NOT_FOUND as string: %s\n", errorStr);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the string describing @p error. This
 * can be @c #NULL.
 * @param[out] errorLen The length of the string returned, including the null
 * character. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument, including the null
 * character. A length of zero (0) uses strlen() to determine length.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 */
NIMBLE_EXTERN
char *
nErrorToString(char * dst,
               int32_t * errorLen,
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
 *       const int32_t errorDescLen, const time_t errorTime, const char * stack,
 *       const int32_t stackLen)
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
 * @return @c #NSUCCESS is returned if successful; otherwise @c #NERROR is
 * returned.
 *
 * @note Check nErrorHandlerDefault() for parameter information.
 */
NIMBLE_EXTERN
int32_t
nErrorSetCallback(void (* callback)(
                                    const int32_t error,
                                    const time_t errorTime,
                                    const char * errorDesc,
                                    const int32_t errorDescLen,
                                    const char * stack,
                                    const int32_t stackLen
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
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char ** argv)
 * {
 *     int32_t stackLen, stackLevels;
 *     char * stack;
 *     nErrorGetStacktrace(stack, &stackLen, &stackLevels);
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
 * @param[out] dst The destination to store the stacktrace string. This can be
 * @c #NULL.
 * @param[out] stackLen The length of the string returned, including the null
 * character. This can be @c #NULL.
 * @param[out] stackLevels The number of levels of the stack. This can be @c #NULL.
 * @return @p dst is returned if successful; otherwise the program crashes.
 *
 * @note Each time a function is called, it is added to the stack. When a
 * function returns, it is removed from the stack.
 */
NIMBLE_EXTERN
char *
nErrorGetStacktrace(char * dst,
                    int32_t * stackLen,
                    int32_t * stackLevels
                    );

#endif // NIMBLE_ENGINE_ERRORS_H

#ifdef __cplusplus
}
#endif

// Errors.h
