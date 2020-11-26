#include "../../NimbleLicense.h"
/*
 * CrashHandler.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-18.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file CrashHandler.h
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
 * @date 2020-08-18
 *
 * @brief This class defines crash handling functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_CRASH_HANDLER_H
#define NIMBLE_ENGINE_CRASH_HANDLER_H /**< Header definition */

#include "../../NimbleEngine.h"

#include <inttypes.h>
#include <time.h>

/**
 * @brief Sets the crash handler callback function.
 * Sets the callback function that gets called when the game crashes.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * @endcode
 *
 * @param[in] callback The function that gets called when a crash occurs.
 * @return @c #NSUCCESS is returned if successful; otherwise @c #NERROR is
 * returned.
 *
 * @note The callback function can only be called once. If an error occurs, the
 * program will abort with nCrashAbort(). Check nCrashHandlerDefault() for
 * parameter information.
 */
NIMBLE_EXTERN
nint_t
nCrashSetHandler(void (*callback) (const nint_t error,
                                   const time_t errorTime,
                                   char *errorDesc,
                                   nint_t errorDescLen,
                                   char *stack,
                                   nint_t stackLen
                                   )
                 );

/**
 * @brief Crashes the program safely.
 * Crashes the program safely by attempting to safely close threads, logging the
 * error that caused the crash to the file defined by @p crashFilePath.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     const time_t errorTime = time(NULL);
 *     const nint_t error = NERROR_NULL;
 *     char *errorDesc;
 *     nint_t errorDescLen;
 *     if (nErrorToString(errorDesc, &errorDescLen, error, NULL, 0) == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error description.\n");
 *         return(EXIT_FAILURE);
 *     }
 *
 *     nCrashSafe(error, errorDesc, errorDescLen, errorTime);
 * }
 * @endcode
 *
 * @param[in] error The error that caused the crash.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument. A length of
 * zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 *
 * @note This function does not return, and exits the program. If an error occurs,
 * the program will abort with nCrashAbort(). Also note that this function
 * automatically sets all the arguments if possible, so resetting them is not
 * needed and may cause more errors, though checking them is acceptable.
 */
NIMBLE_EXTERN
void
nCrashSafe(const nint_t error,
           time_t errorTime,
           const char *errorDesc,
           nint_t errorDescLen
           )
__attribute__((noreturn));

/**
 * @brief Calls nCrashSafe() to handle a caught signal.
 *
 * @param[in] signum The signal caught.
 *
 * @note This function is used by the game engine and is not expected to be used
 * by developers, but is optional.
 */
NIMBLE_EXTERN
void
nCrashSignal(const int signum
             )
__attribute__((noreturn));

/**
 * @brief Crashes the program without notifying the callback.
 *
 * Example:
 * @code
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     nCrashAbort(NERROR_NULL);
 * }
 * @endcode
 *
 * @param[in] error The error that caused the crash.
 *
 * @note This function does not return, and exits the program.
 */
NIMBLE_EXTERN
void
nCrashAbort(const nint_t error
            )
__attribute__((noreturn));

#endif // NIMBLE_ENGINE_CRASH_HANDLER_H

#ifdef __cplusplus
}
#endif

// CrashHandler.h
