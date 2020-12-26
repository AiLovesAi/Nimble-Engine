#include "../../include/Nimble/NimbleLicense.h"
/*
 * Files.c
 * Nimble Engine
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
#include <stdlib.h>

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
#ifndef realpath
#  define realpath(path, rltvPath) _fullpath(path, rltvPath, PATH_MAX)
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

#include <Windows.h>
#elif defined(NIMBLE_STD_UNIX)
#include <unistd.h>
#endif

char NEXEC[PATH_MAX + 1] = {0};
size_t NEXEC_LEN = 0;
char NCWD[PATH_MAX + 1] = {0};
size_t NCWD_LEN = 0;


nint_t nFileExists(const char *path)
{
    if (access(path, F_OK))
    {
        nint_t err;
        if (errno)
        {
            nErrorLastErrno(err);
            err = nErrorFromErrno(err);
        }
        else
        {
            err = NERROR_INTERNAL_FAILURE;
        }
        return err;
    }
    else
    {
        return NSUCCESS;
    }
}

#if NIMBLE_OS == NIMBLE_WINDOWS
#  define NFILE_ABSOLUTE_PREFIX 3
#else
#  define NFILE_ABSOLUTE_PREFIX 1
#endif
nint_t nFilePathIsAbsolute(const char *path, nint_t len)
{
    if (!len)
    {
        len = strlen(path);
    }

    if (len < (NFILE_ABSOLUTE_PREFIX + 1))
    {
        return NERROR;
    }

#if NIMBLE_OS == NIMBLE_WINDOWS
    return (NEXEC[1] == ':') ? NSUCCESS : NERROR;
#else
    return (NEXEC[0] == '/') ? NSUCCESS : NERROR;
#endif
}

char *nFileSetCWD(void)
{
    char buffer[PATH_MAX + 1];
    buffer[PATH_MAX] = '\0';
    if (!getcwd(buffer, NCONST_STR_LEN(buffer)))
    {
        const char einfoNoCWDStr[] = "getcwd() failed in "\
 "nFileSetCWD().";
        nint_t err;
        if (errno)
        {
            nErrorLastErrno(err);
            err = nErrorFromErrno(err);
        }
        else
        {
            err = NERROR_INTERNAL_FAILURE;
        }

        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, err, einfoNoCWDStr,
         NCONST_STR_LEN(einfoNoCWDStr));
        nCrashSafe(err, time(NULL), errorDescStr, errorDescLen);
        /* NO RETURN */
    }

    size_t len = strlen(buffer);
    if ((buffer[len - 1] != NFILE_DIR_SEP))
    {
        if (len == PATH_MAX)
        {
            const char einfoCWDTooLongStr[] = "The current working "\
 "directory length is greater than PATH_MAX in nFileSetCWD().";
            size_t errorDescLen;
            char *errorDescStr = nErrorToString(&errorDescLen,
             NERROR_MAX_FILENAME, einfoCWDTooLongStr,
             NCONST_STR_LEN(einfoCWDTooLongStr));
            nCrashSafe(NERROR_MAX_FILENAME, time(NULL), errorDescStr,
             errorDescLen);
            /* NO RETURN */
        }

        buffer[len] = NFILE_DIR_SEP;
        len++;
        buffer[len] = '\0';
    }

    nStringCopy(NCWD, buffer, len);
    NCWD_LEN = len;
    return NCWD;
}

char *nFileSetExecutablePath(void)
{
    if (!NIMBLE_ARGS || !NIMBLE_ARGS[0])
    {
        const char einfoNoArgsStr[] = "NIMBLE_ARGS was not set, causing "\
 "nFileSetExecutablePath() to fail.";
        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, NERROR_NULL,
         einfoNoArgsStr, NCONST_STR_LEN(einfoNoArgsStr));
        nCrashSafe(NERROR_NULL, time(NULL), errorDescStr, errorDescLen);
        /* NO RETURN */
    }

    if (!NCWD[0])
    {
        nFileSetCWD();
    }

    size_t len = strlen(NIMBLE_ARGS[0]);
    if ((NCWD_LEN + len) > PATH_MAX)
    {
        const char einfoExecTooLongStr[] = "The executable file path length is "\
 "greater than PATH_MAX in nFileSetExecutablePath().";
        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, NERROR_MAX_FILENAME,
         einfoExecTooLongStr, NCONST_STR_LEN(einfoExecTooLongStr));
        nCrashSafe(NERROR_MAX_FILENAME, time(NULL), errorDescStr, errorDescLen);
        /* NO RETURN */
    }

    nStringCopy(NEXEC, NCWD, NCWD_LEN);
    nStringCopy(NEXEC + NCWD_LEN, NIMBLE_ARGS[0], len);

    char buffer[PATH_MAX + 1];
    buffer[PATH_MAX] = '\0';
    if (!realpath(buffer, NEXEC))
    {
        const char einfoNoRealpathStr[] = "realpath() failed in "\
 "nFileSetExecutablePath().";
        nint_t err;
        if (errno)
        {
            nErrorLastErrno(err);
            err = nErrorFromErrno(err);
        }
        else
        {
            err = NERROR_INTERNAL_FAILURE;
        }

        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, err,
         einfoNoRealpathStr, NCONST_STR_LEN(einfoNoRealpathStr));
        nCrashSafe(err, time(NULL), errorDescStr, errorDescLen);
        /* NO RETURN */
    }

    len = strlen(buffer);
    if (strcmp(NEXEC, buffer))
    {
        nStringCopy(NEXEC, buffer, len);
    }
    NEXEC_LEN = len;

    if (nFileExists(NEXEC) != NSUCCESS)
    {
        const char einfoNoExecutableStr[] = "nFileSetExecutablePath() failed "\
 "to verify that the set executable path exists.";
        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen,
         NERROR_INTERNAL_FAILURE, einfoNoExecutableStr,
         NCONST_STR_LEN(einfoNoExecutableStr));
        nCrashSafe(NERROR_INTERNAL_FAILURE, time(NULL), errorDescStr,
         errorDescLen);
        /* NO RETURN */
    }

    return NEXEC;
}

// Files.c