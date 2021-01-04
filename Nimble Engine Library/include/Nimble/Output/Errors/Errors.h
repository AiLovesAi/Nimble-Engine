#include "../../NimbleLicense.h"
/*
 * Errors.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-14.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Errors.h
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


#ifndef NERRORS_MAX_STACK
#  define NERRORS_MAX_STACK 512 /**< The maximum stack levels to take from nErrorGetStacktrace(). */
#endif

/**
 * @brief Throws an error with @p info if @p check is equal to zero.
 * 
 * @param[in] check The statement to check if true.
 * @param[in] error The default error to crash with (overridden if errno is set).
 * @param[in] info The info string to crash with if false. This can be #NULL to
 * not throw an error.
 * @param[in] infoLen The length of @p info.
 * 
 * @return #NSUCCESS or an error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int
nErrorAssert(const int check,
             const int error,
             const char *info,
             const size_t infoLen);

/**
 * @brief Throws an error with @p info and returns if @p check is equal to zero.
 * 
 * Throws an error with @p info and returns from calling function with
 * @p ret if @p check is equal to zero.
 * 
 * @param[in] check The statement to check if true.
 * @param[in] error The default error to crash with (overridden if errno is set).
 * @param[in] info The info string to crash with if false. This can be #NULL to
 * not throw an error.
 * @param[in] infoLen The length of @p info.
 * @param[in] ret The return value to return if false.
 */
#define nErrorAssertRet(check, error, info, infoLen, ret) ({\
    nErrorAssert(check, error, info, infoLen);\
    return ret;\
})

/**
 * @brief Throws an error with @p info and returns only if @p check is equal to zero.
 * 
 * Throws an error with @p info and returns from calling function with
 * @p ret only if @p check is equal to zero.
 * 
 * @param[in] check The statement to check if true.
 * @param[in] error The default error to crash with (overridden if errno is set).
 * @param[in] info The info string to crash with if false. This can be #NULL to
 * not throw an error.
 * @param[in] infoLen The length of @p info.
 * @param[in] ret The return value to return if false.
 */
#define nErrorAssertReti(check, error, info, infoLen, ret) ({\
    if (nErrorAssert(check, error, info, infoLen)) return ret;\
})

/**
 * @brief Throws an error with @p info and returns if @p check is equal to zero.
 * 
 * Throws an error with @p info and returns from calling function with the
 * result if @p check is equal to zero.
 * 
 * @param[in] check The statement to check if true.
 * @param[in] error The default error to crash with (overridden if errno is set).
 * @param[in] info The info string to crash with if false. This can be #NULL to
 * not throw an error.
 * @param[in] infoLen The length of @p info.
 */
#define nErrorAssertRetE(check, error, info, infoLen) ({\
    return nErrorAssert(check, error, info, infoLen);\
})

/**
 * @brief Throws an error with @p info and returns only if @p check is equal to zero.
 * 
 * Throws an error with @p info and returns from calling function with the
 * result only if @p check is equal to zero.
 * 
 * @param[in] check The statement to check if true.
 * @param[in] error The default error to crash with (overridden if errno is set).
 * @param[in] info The info string to crash with if false. This can be #NULL to
 * not throw an error.
 * @param[in] infoLen The length of @p info.
 */
#define nErrorAssertRetEi(check, error, info, infoLen) ({\
    int n_err = nErrorAssert(check, error, info, infoLen);\
    if (n_err) return n_err;\
})

/**
 * @brief Sends an error to the error callback.
 * 
 * Sends an error to the error callback defined by
 * nErrorHandlerSetErrorCallback(), and determines whether or not crashing is
 * necessary.
 *
 * @param[in] error The error to throw.
 * @param[in] errorDescStr Relevant information, such as a file location, that
 * could help diagnose the error. This can be @c #NULL.
 * @param[in] errorDescStrLen The length of the @p info argument. A length of
 * zero (0) uses strlen() to determine length.
 *
 * @note The program will crash if this is unsuccessful.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
void
nErrorThrow(const int error,
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
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return A pointer to the string describing @p error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nErrorToString(size_t *restrict errorLen,
               const int error,
               const char *restrict info,
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
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return A pointer to the string describing @p error is returned if successful;
 * otherwise @c #NULL is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char *
nErrorToStringWindows(size_t *restrict errorLen,
                      const int error,
                      const char *restrict info,
                      size_t infoLen
                      )
__attribute__((warn_unused_result));
#endif

/**
 * @brief Sets the callback function to handle errors.
 * 
 * Sets the callback function @p callback that gets called when an error occurs.
 *
 * @param[in] callback The function that gets called when an error occurs. This
 * can be #NULL to use the default callback.
 * @return @c #NSUCCESS is returned if successful.
 *
 * @note Check nErrorHandlerDefault() for parameter information.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int
nErrorSetCallback(void (*callback)(
                                   const int error,
                                   const time_t errorTime,
                                   const char *restrict errorDesc,
                                   const size_t errorDescLen,
                                   const char *restrict stack,
                                   const size_t stackLen
                                   )
                  );

/**
 * @brief Returns the current stack trace as a string.
 * 
 * Returns the current stack trace as a string, and sets the @p stackLen of the
 * string and @p levels of the stack.
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
NIMBLE_EXPORT
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nErrorGetStacktrace(size_t *restrict stackLen,
                    size_t *restrict stackLevels
                    )
__attribute__((warn_unused_result));

#endif // NIMBLE_ENGINE_ERRORS_H

#ifdef __cplusplus
}
#endif

// Errors.h
