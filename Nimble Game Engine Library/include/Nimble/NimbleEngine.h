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

#include "NimbleEngine/Network/Network.h"

#include "NimbleEngine/Output/CrashHandler.h"
#include "NimbleEngine/Output/Errors.h"
#include "NimbleEngine/Output/Files.h"
#include "NimbleEngine/Output/Logging.h"

#include "NimbleEngine/System/Hardware.h"

#include "NimbleEngine/Threads/Threads.h"
#include "NimbleEngine/Threads/ThreadManager.h"


/**
 * @brief Exits the game engine.
 * Exits the game engine by safely stopping threads
 *
 * @par Example:
 * @code
 * #include <stdint.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char ** argv)
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
void
nEngineExit(void)
__attribute__((noreturn));

/**
 * @brief Initialized the game engine.
 * Initializes the game engine by setting up the error/crash handlers, logger, and
 * thread manager.
 *
 * @par Example:
 * @code
 * #include <stdint.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char ** argv)
 * {
 *     if (nEngineInit() != NSUCCESS)
 *     {
 *         fprintf(stderr, "Failed to initialize Nimble.");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Successfully initialized game engine.");
 *     exit(EXIT_SUCCESS);
 * }
 * @endcode
 *
 * @return #NSUCCESS is returned if successful; otherwise #NERROR is returned and
 * a corresponding error is sent to the error callback set by
 * nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
int32_t
nEngineInit(void (* errorCallback)(
                                   const int32_t error,
                                   const time_t errorTime,
                                   char * errorDesc,
                                   int32_t errorDescLen,
                                   char * stack,
                                   int32_t stackLen
                                   ),
            void (* crashCallback) (const int32_t error,
                                    const time_t errorTime,
                                    char * errorDesc,
                                    int32_t errorDescLen,
                                    char * stack,
                                    int32_t stackLen
                                    )
            ); /** @todo Make these callback functions the same through each file. */

#endif // NIMBLE_ENGINE_H

#ifdef __cplusplus
}
#endif

// NimbleEngine.h
