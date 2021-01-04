#include "../../include/Nimble/NimbleLicense.h"
/*
 * Files.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-07.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/Output/Files.h"

/**
 * @file Threads.c
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

char NEXEC[PATH_MAX + 1] = {0};
size_t NEXEC_LEN = 0;
char NCWD[PATH_MAX + 1] = {0};
size_t NCWD_LEN = 0;


int nFileOpen(const char *restrict file, int flags, int *restrict fd)
{
#define einfoStr "File argument was NULL in nFileOpen()."
    nErrorAssertRetEi(file != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
#define einfoStr "Descriptor argument was NULL in nFileOpen()."
    nErrorAssertRetEi(fd != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
    if ((flags & NFILE_F_WRITE) && !(flags & NFILE_F_READ))
    {
        flags ^= NFILE_F_WRITE | O_WRONLY;
    }
    int descriptor = open(file, flags);
    *fd = descriptor;
#define einfoStr "open() failed in nFileOpen()."
    nErrorAssertRetE(descriptor != -1,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
}

int nFileClose(int *fd)
{
#define einfoStr "Descriptor argument was NULL in nFileClose()."
    nErrorAssertRetEi(fd != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
#define einfoStr "close() failed in nFileClose()."
    nErrorAssertRetEi(!close(*fd),
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
    *fd = -1;
    return NSUCCESS;
}

ssize_t nFileRead(const int fd, void *dst, const size_t size)
{
#define einfoStr "dst argument was NULL in nFileRead()."
    nErrorAssertReti(dst != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr), -1);
#undef einfoStr

    int rd = read(fd, dst, size);
#define einfoStr "read() failed in nFileRead()."
    nErrorAssertReti(rd >= 0,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr), -1);
#undef einfoStr
    return rd;
}

ssize_t nFileWrite(const int fd, void *src, const size_t size)
{
#define einfoStr "src argument was NULL in nFileWrite()."
    nErrorAssertReti(src != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr), -1);
#undef einfoStr

    int wr = write(fd, src, size);
#define einfoStr "write() failed in nFileWrite()."
    nErrorAssertReti(wr >= 0,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr), -1);
#undef einfoStr
    return wr;
}

int nFileDelete(const char *file)
{
#define einfoStr "File argument was NULL in nFileDelete()."
    nErrorAssertRetEi(file != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
#define einfoStr "unlink() failed in nFileDelete()."
    nErrorAssertRetE(!unlink(file),
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
}

int nFileExists(const char *file)
{
#define einfoStr "File argument was NULL in nFileExists()."
    nErrorAssertRetEi(file != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
    nErrorAssertRetE(!access(file, F_OK),
     NERROR_INTERNAL_FAILURE, NULL, 0);
}

#if NIMBLE_OS == NIMBLE_WINDOWS
#  define NFILE_ABSOLUTE_PREFIX 3
#else
#  define NFILE_ABSOLUTE_PREFIX 1
#endif
int nFilePathIsAbsolute(const char *path, size_t len)
{
#define einfoStr "Path argument was NULL in nFilePathIsAbsolute()."
    nErrorAssertRetEi(path != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    if (!len)
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
    nAssert(getcwd(buffer, NCONST_STR_LEN(buffer)) != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    size_t len = strlen(buffer);
#define einfoStr "The current working directory length is greater than "\
 "PATH_MAX in nFileSetCWD()."
    nAssert(len < PATH_MAX,
    NERROR_MAX_FILENAME, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
    if ((buffer[len - 1] != NFILE_DIR_SEP))
    {
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
#define einfoStr "NIMBLE_ARGS was not set, causing nFileSetExecutablePath() "\
 "to fail."
    nAssert(NIMBLE_ARGS != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
    nAssert(NIMBLE_ARGS[0] != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    size_t len = strlen(NIMBLE_ARGS[0]);
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
    nAssert(realpath(buffer, NEXEC) != NULL,
     NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));
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
    nAssert(err == NSUCCESS,
     err, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    return NEXEC;
}

int nFileCopy(const char *restrict dst, const char *restrict src)
{
#define einfoStr "Dst argument was NULL in nFileCopy()."
    nErrorAssertRetEi(dst != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
#define einfoStr "Src argument was NULL in nFileCopy()."
    nErrorAssertRetEi(src != NULL,
     NERROR_NULL, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr
#define einfoStr "Dst argument was equal to src argument in nFileCopy()."
    nErrorAssertRetEi(dst != src,
     NERROR_INV_ARG, einfoStr, NCONST_STR_LEN(einfoStr));
#undef einfoStr

    int srcFile, dstFile, err;
    err = nFileOpen(src, NFILE_F_READ | NFILE_F_RAW, &srcFile);
    nErrorAssertRetEi(err != NSUCCESS, err, NULL, 0);
    err = nFileOpen(dst, NFILE_F_WRITE | NFILE_F_RAW | NFILE_F_CREATE | NFILE_F_CLEAR, &dstFile);
    nErrorAssertRetEi(err != NSUCCESS, err, NULL, 0);
    
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
                nErrorAssert(0,
                 NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr));  
#undef einfoStr
                goto closeLbl;
            }
        }
    }
    while (rd);

closeLbl:;
    err = nFileClose(&srcFile);
    nErrorAssert(err != NSUCCESS, err, NULL, 0);
    err = nFileClose(&dstFile);
    nErrorAssert(err != NSUCCESS, err, NULL, 0);
    return err;
}

// Files.c
