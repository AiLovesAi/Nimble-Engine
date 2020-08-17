#include "../../../../License/NimbleLicense.h"
/*
 * ErrorHandler.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-16.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file ErrorHandler.h
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
 * @date 2020-08-16
 *
 * @brief This class handles errors thrown by the engine.
 * This class handles errors thrown by the engine, and defines functions the
 * developer can send callback functions to.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_ERROR_HANDLER_H
#define NIMBLE_ENGINE_ERROR_HANDLER_H /**< Header definition */

#include "../../NimbleEngine.h"

#include <stdint.h>
#include <time.h>

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
 * void errorHandler(const char * error, const char * description,
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
 *     fprintf(stderr, "\nAn error occurred at %s:\nError name: %s\nError "\
 *      "description: %s\nStack trace: %s\n\n", timeString, error, description,
 *      stack);
 * }
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nErrorHandlerSetErrorCallback(errorHandler) == NERROR)
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
 */
NIMBLE_EXPORT
int32_t
nErrorHandlerSetErrorCallback(int32_t (*callback)(
                                                  const char *,
                                                  const char *,
                                                  const char *,
                                                  const time_t
                                                  ),
                              );

#endif // NIMBLE_ENGINE_ERROR_HANDLER_H

#ifdef __cplusplus
}
#endif

// ErrorHandler.h
