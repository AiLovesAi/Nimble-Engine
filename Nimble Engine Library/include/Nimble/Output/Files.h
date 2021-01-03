#include "../NimbleLicense.h"
/*
 * Files.h
 * Nimble Engine
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

#if NIMBLE_OS == NIMBLE_WINDOWS
#  define NFILE_DIR_SEP '\\'
#else
#  define NFILE_DIR_SEP '/'
#endif

/**
 * @brief The executable file path.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char NEXEC[PATH_MAX + 1];

/**
 * @brief The length of the executable file path.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
size_t NEXEC_LEN;

/**
 * @brief The current working directory.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char NCWD[PATH_MAX + 1];

/**
 * @brief The length of the current working directory.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
size_t NCWD_LEN;

/**
 * @brief Checks if a file exists.
 *
 * @param[in] path The name of the file to check.
 * @return #NSUCCESS is returned if the file exists; otherwise an error code is
 * returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nFileExists(const char *path);

/**
 * @brief Checks if the file is an absolute path.
 *
 * @param[in] path The file path to check if absolute.
 * @param[in] len The length of the path to check. This can be 0 to use
 * strlen().
 * @return #NSUCCESS is returned if successful; otherwise -1 or an error is returned.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
nint_t
nFilePathIsAbsolute(const char *path,
                    nint_t len);

/**
 * @brief Gets the current working directory path.
 * Gets the current working directory path and sets #NCWD and
 * #NCWD_LEN.
 *
 * @return #NCWD is returned if successful; otherwise the
 * engine crashes.
 * @note This function is not thread safe, as it is called during
 * initialization.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char *
nFileSetCWD(void);

/**
 * @brief Gets the current executable file path.
 * Gets the current executable file path and sets #NEXEC and
 * #NEXEC_LEN.
 *
 * @return #NEXEC is returned if successful; otherwise the
 * engine crashes.
 *
 * @note This function is not thread safe, as it is called during
 * initialization.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
char *
nFileSetExecutablePath(void);

#endif // NIMBLE_ENGINE_FILES_H

#ifdef __cplusplus
}
#endif

// Files.h
