#include "../../include/Nimble/NimbleLicense.h"
/*
 * Files.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-12-07.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/Output/Files.h"

/**
 * @file Threads.c
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
 * SOFTWARE.t
 * @endparblock
 * @date 2020-12-07
 *
 * @brief This class defines file functions.
 */

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>

#if NIMBLE_OS == NIMBLE_WINDOWS
#include <stdlib.h>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h> /* for _getcwd() and _chdir() */

#define srandom srand
#define random rand

/* Values for the second argument to access.
   These may be OR'd together.  */
#ifndef R_OK
#  define R_OK 4 /* Test for read permission.  */
#endif
#ifndef W_OK
#  define W_OK 2 /* Test for write permission.  */
#endif
#ifndef X_OK
#  define X_OK 1 /* execute permission - unsupported in windows*/
#endif
#ifndef F_OK
#  define F_OK 0 /* Test for existence.  */
#endif

#ifndef access
#  define access _access
#endif
#ifndef dup2
#  define dup2 _dup2
#endif
#ifndef execve
#  define execve _execve
#endif
#ifndef ftruncate
#  define ftruncate _chsize
#endif
#ifndef unlink
#  define unlink _unlink
#endif
#ifndef fileno
#  define fileno _fileno
#endif
#ifndef getcwd
#  define getcwd _getcwd
#endif
#ifndef chdir
#  define chdir _chdir
#endif
#ifndef isatty
#  define isatty _isatty
#endif
#ifndef lseek
#  define lseek _lseek
#endif
/* read, write, and close are NOT being #defined here, because while there are file handle specific versions for Windows, they probably don't work for sockets. You need to look at your app and consider whether to call e.g. closesocket(). */

#ifndef ssize_t
#  ifdef _WIN64
#    define ssize_t __int64
#  else
#    define ssize_t long
#  endif
#endif

#ifndef STDIN_FILENO
#  define STDIN_FILENO  0
#endif
#ifndef STDOUT_FILENO
#  define STDOUT_FILENO 1
#endif
#ifndef STDERR_FILENO
#  define STDERR_FILENO 2
#endif

#elif defined(__unix__) || defined(__unix)
#include <unistd.h>
#endif

char NEXECUTABLE[PATH_MAX] = {0};


nint_t nFileExists(const char *fileName)
{
    if (access(fileName, F_OK))
    {
        const nint_t err = nErrorFromErrno(errno);
        errno = 0;
        return (err == NERROR_NO_FILE) ? 0 : err;
    }
    else
    {
        return 1;
    }
}

NIMBLE_FREEME char *nFileGetExecutable(void)
{
    /** @todo Make executable finder function. */
    return NULL;
}

// Files.c
