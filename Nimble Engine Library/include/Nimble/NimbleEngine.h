#include "NimbleLicense.h"
/*
 * NimbleEngine.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-08-10.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file NimbleEngine.h
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
#include "Output/Errors/ErrorValues.h"
#include "Output/Files.h"
#include "Output/Logging.h"

#include "System/CPUInfo.h"
#include "System/Memory.h"
#include "System/Threads.h"


#include <time.h>

/**
 * @brief The variable that is set after a successful initialization.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
volatile _Bool NIMBLE_INITIALIZED;

/**
 * @brief The arguments passed to the program.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char **NIMBLE_ARGS;

/**
 * @brief The count of arguments in #NIMBLE_ARGS.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int NIMBLE_ARGC;

/**
 * @brief Initialized the game engine.
 * 
 * Initializes the game engine by setting up the error/crash handlers, logger, and
 * thread manager.
 *
 * @param[in] args The arguments past to main (usually argv).
 * @param[in] argc The argument count of @p args.
 * @param[in] errorCallback The error callback function that is called when an
 * error occurs. This can be #NULL to use the default callback.
 * @param[in] crashCallback The crash callback function that is called when the
 * engine crashes. This can be #NULL to use the default callback.
 * @return #NSUCCESS is returned if successful; otherwise an error is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int
nEngineInit(char **args,
            const int argc,
            void (*errorCallback) (const nErrorInfo_t errorInfo),
            void (*crashCallback) (const nErrorInfo_t errorInfo)
            );

#endif // NIMBLE_ENGINE_H

#ifdef __cplusplus
}
#endif

// NimbleEngine.h
