#include "../NimbleLicense.h"
/*
 * Files.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-12-07.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Files.h
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
 * @date 2020-12-07
 *
 * @brief This class defines file functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_FILES_H
#define NIMBLE_ENGINE_FILES_H /**< Header definition */

#include "../NimbleEngine.h"

#include <limits.h>

#if !defined(PATH_MAX) && defined(MAX_PATH)
#  define PATH_MAX MAX_PATH
#endif

/**
 * @brief The executable file directory.
 */
NIMBLE_EXTERN
char NEXECUTABLE[PATH_MAX];

/**
 * @brief Checks if a file exists.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     nint_t exists = nFileExists(argv[0]);
 *     switch (exists)
 *     {
 *         case 1:
 *             printf("%s exists!\n", argv[0]);
 *             break;
 *         case 0:
 *             printf("%s does not exist!\n", argv[0]);
 *             break;
 *         case NERROR:
 *             fputs(stderr, "Failed to check if file exists "\
 *              "using nFileExists().\n");
 *             break;
 *     }
 *
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] fileName The name of the file to check.
 * @return 1 is returned if the file exists, and 0 otherwise. If unsuccessful,
 * an error value is returned and a corresponding error is sent to the error
 * callback set by nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
nint_t
nFileExists(const char *fileName);

/**
 * @brief Gets the current executable file path.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     nint_t exists = nFileExists(argv[0]);
 *     switch (exists)
 *     {
 *         case 1:
 *             printf("%s exists!\n", argv[0]);
 *             break;
 *         case 0:
 *             printf("%s does not exist!\n", argv[0]);
 *             break;
 *         case NERROR:
 *             fputs(stderr, "Failed to check if file exists "\
 *              "using nFileExists().\n");
 *             break;
 *     }
 *
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @return A pointer to the executable file string is returned if successful;
 * otherwize, an #NULL is returned and a corresponding error is sent to the
 * error callback set by nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nFileGetExecutable(void);

#endif // NIMBLE_ENGINE_FILES_H

#ifdef __cplusplus
}
#endif

// Errors.h
