#include "../../include/Nimble/NimbleLicense.h"
/*
 * Files.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-07.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

#include "../../include/Nimble/Output/Files.h"

/**
 * @file Threads.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
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

#include "../../include/Nimble/NimbleEngine.h"
#include "../../include/Nimble/System/Memory.h"
#include "../../include/Nimble/Output/Errors/Errors.h"
#include "../../include/Nimble/Output/Errors/Crash.h"

char NEXEC[PATH_MAX + 1] = {0};
size_t NEXEC_LEN = 0;
char NCWD[PATH_MAX + 1] = {0};
size_t NCWD_LEN = 0;


int nFileOpen(const char *restrict file, int flags, int *restrict fd)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "File argument was NULL in nFileOpen()."
    if (nErrorAssert(
     file != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#  define einfoStr "Descriptor argument was NULL in nFileOpen()."
    if (nErrorAssert(
     fd != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#endif
    if ((flags & NFILE_F_WRITE) && !(flags & NFILE_F_READ))
    {
        flags ^= NFILE_F_WRITE | O_WRONLY;
    }
    int descriptor = open(file, flags, S_IREAD | S_IWRITE | S_IEXEC);
    *fd = descriptor;
#define einfoStr "open() failed in nFileOpen()."
    return nErrorAssert(
     descriptor >= 0,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr
}

int nFileClose(int *fd)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "Descriptor argument was NULL in nFileClose()."
    if (nErrorAssert(
     fd != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#endif
#define einfoStr "close() failed in nFileClose()."
    if (nErrorAssert(
     !close(*fd),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_INTERNAL_FAILURE;
#undef einfoStr
    *fd = -1;
    return NSUCCESS;
}

ssize_t nFileRead(const int fd, void *dst, const size_t size)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "dst argument was NULL in nFileRead()."
    if (nErrorAssert(
     dst != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#  undef einfoStr
#endif

    int rd = read(fd, dst, size);
#define einfoStr "read() failed in nFileRead()."
    if (nErrorAssert(
     rd >= 0,
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#undef einfoStr
    return rd;
}

ssize_t nFileWrite(const int fd, void *src, const size_t size)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "src argument was NULL in nFileWrite()."
    if (nErrorAssert(
     src != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#  undef einfoStr
#endif

    int wr = write(fd, src, size);
#define einfoStr "write() failed in nFileWrite()."
    if (nErrorAssert(
     wr >= 0,
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#undef einfoStr
    return wr;
}

int nFileDelete(const char *file)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "File argument was NULL in nFileDelete()."
    if (nErrorAssert(
     file != NULL,
     NERROR_NULL, 
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#endif

#define einfoStr "unlink() failed in nFileDelete()."
    return nErrorAssert(
     !unlink(file),
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr
}

int nFileRename(const char *restrict oldPath, const char *restrict newPath)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "OldPath argument was NULL in nFileDelete()."
    if (nErrorAssert(
     oldPath != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#  define einfoStr "NewPath argument was NULL in nFileDelete()."
    if (nErrorAssert(
     newPath != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#endif

#define einfoStr "OldPath argument equals newPath argument in "\
 "nFileDelete()."
    if (nErrorAssert(
     newPath != NULL,
     NERROR_INV_ARG,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_INV_ARG;
#undef einfoStr

    int err = rename(oldPath, newPath);
    if (!err) return NSUCCESS;
    
#define einfoStr "rename() failed in nFileRename()."
    err = nErrorAssert(
     errno == EXDEV,
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
    if (err) return err;
#undef einfoStr

    err = nFileCopy(oldPath, newPath);
    if (err) return err;
    err = nFileDelete(oldPath);
    return err;
}

int nFileExists(const char *file)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "File argument was NULL in nFileExists()."
    if (nErrorAssert(
     file != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#endif

    return nErrorAssert(
     !access(file, F_OK),
     NERROR_INTERNAL_FAILURE,
     NULL,
     0
    );
}

#if NIMBLE_OS == NIMBLE_WINDOWS
#  define NFILE_ABSOLUTE_PREFIX 3
#else
#  define NFILE_ABSOLUTE_PREFIX 1
#endif
int nFilePathIsAbsolute(const char *path, size_t len)
{
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "Path argument was NULL in nFilePathIsAbsolute()."
    if (nErrorAssert(
     path != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return NERROR_NULL;
#  undef einfoStr
#endif

    if (len <= 0)
    {
        len = strlen(path);
    }

    if (len < (NFILE_ABSOLUTE_PREFIX + 1))
    {
        return -1;
    }

#if NIMBLE_OS == NIMBLE_WINDOWS
    return (path[1] == ':') ? NSUCCESS : -1;
#else
    return (path[0] == '/') ? NSUCCESS : -1;
#endif
}

char *nFileSetCWD(void)
{
    char buffer[PATH_MAX + 1];
    buffer[PATH_MAX] = '\0';
#define einfoStr "getcwd() failed in nFileSetCWD()."
    nAssert(
     getcwd(buffer, NCONST_STR_LEN(buffer)) != NULL,
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr

    size_t len = strlen(buffer);
#define einfoStr "The current working directory length is greater than "\
 "PATH_MAX in nFileSetCWD()."
    nAssert(
     len < PATH_MAX,
     NERROR_MAX_FILENAME,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr
    if ((buffer[len - 1] != NFILE_DIR_SEP))
    {
        buffer[len++] = NFILE_DIR_SEP;
        buffer[len] = '\0';
    }

    nStringCopy(NCWD, buffer, len);
    NCWD_LEN = len;
    return NCWD;
}

char *nFileSetExecutablePath(void)
{
    if (NEXEC[0]) return NEXEC;
#define einfoStr "NIMBLE_ARGS was not set, causing nFileSetExecutablePath() "\
 "to fail."
    nAssert(
     NIMBLE_ARGS != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
    nAssert(
     NIMBLE_ARGS[0] != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr

    size_t len = strlen(NIMBLE_ARGS[0]);
#define einfoStr "NIMBLE_ARGS was not set, causing nFileSetExecutablePath() "\
 "to fail."
    nAssert(
     len <= PATH_MAX,
     NERROR_BUFFER_OVERFLOW,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr
    if (nFilePathIsAbsolute(NIMBLE_ARGS[0], len) == NSUCCESS)
    {
        nStringCopy(NEXEC, NIMBLE_ARGS[0], len);
    }
    else
    {
        if (!NCWD[0])
        {
            nFileSetCWD();
        }
        nStringCopy(NEXEC, NCWD, NCWD_LEN);
        nStringCopy(NEXEC + NCWD_LEN, NIMBLE_ARGS[0], len);
    }

    char buffer[PATH_MAX + 1];
    buffer[PATH_MAX] = '\0';
#define einfoStr "realpath() failed in nFileSetExecutablePath()."
    nAssert(
     realpath(buffer, NEXEC) != NULL,
     NERROR_INTERNAL_FAILURE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr

    len = strlen(buffer);
    if (strcmp(NEXEC, buffer))
    {
        nStringCopy(NEXEC, buffer, len);
    }
    NEXEC_LEN = len;

#define einfoStr "nFileSetExecutablePath() failed to verify that the set "\
 "executable path exists."
    int err = nFileExists(NEXEC);
    nAssert(
     !err,
     NERROR_NO_FILE,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
#undef einfoStr

    return NEXEC;
}

int nFileCopy(const char *restrict src, const char *restrict dst)
{
    int err;
#ifndef NIMBLE_NO_ARG_CHECK
#  define einfoStr "Src argument was NULL in nFileCopy()."
    err = nErrorAssert(
     src != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
    if (err) return err;
#  undef einfoStr
#  define einfoStr "Dst argument was NULL in nFileCopy()."
    err = nErrorAssert(
     dst != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
    if (err) return err;
#  undef einfoStr
#  define einfoStr "Src argument equals dst argument in nFileCopy()."
    err = nErrorAssert(
     src != dst,
     NERROR_INV_ARG,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    );
    if (err) return err;
#  undef einfoStr
#endif

    int srcFile, dstFile;
    err = nFileOpen(src, NFILE_F_READ | NFILE_F_RAW, &srcFile);
    if (err) return err;
    err = nFileOpen(dst, NFILE_F_WRITE | NFILE_F_RAW | NFILE_F_CREATE | NFILE_F_CLEAR, &dstFile);
    if (err) return err;
    
    char buffer[NFILE_BUFFER_SIZE];
    ssize_t rd = 0, wr = 0;
    do
    {
        rd = nFileRead(srcFile, buffer, sizeof(buffer));
        if (rd < 0)
        {
            goto closeLbl;
        }

        if (rd)
        {
            wr = nFileWrite(dstFile, buffer, rd);
            if(wr < 0)
            {
                goto closeLbl;
            }
            if (wr != rd)
            {
#define einfoStr "nFileWrite() wrote less bytes than read by nFileRead() in "\
 "nFileCopy()."
                nErrorThrow(NERROR_INTERNAL_FAILURE,
                 einfoStr, NCONST_STR_LEN(einfoStr), 1);
#undef einfoStr
                goto closeLbl;
            }
        }
    }
    while (rd);

closeLbl:;
    err = nFileClose(&srcFile);
    if (err) return err;
    err = nFileClose(&dstFile);
    if (err) return err;
    return err;
}

// Files.c
