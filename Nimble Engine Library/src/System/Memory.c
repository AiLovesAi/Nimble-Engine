#include "../../include/Nimble/NimbleLicense.h"
/*
 * Memory.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-12.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/Memory.h"

/**
 * @file Memory.c
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
 * @date 2020-12-12
 *
 * @brief This class defines memory functions.
 */

#include <stdlib.h>

#include "../../include/Nimble/Output/Errors/Errors.h"

ssize_t nStringCopy(char *const restrict dst, const char *const restrict src,
 const size_t len)
{
#define einfoStr "Src argument NULL in nStringCopy()."
    if (nErrorAssert(
     src != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#undef einfoStr
#define einfoStr "Dst argument NULL in nStringCopy()."
    if (nErrorAssert(
     src != NULL,
     NERROR_NULL,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#undef einfoStr
#define einfoStr "Dst argument equals src argument in nStringCopy()."
    if (nErrorAssert(
     dst != src,
     NERROR_INV_ARG,
     einfoStr,
     NCONST_STR_LEN(einfoStr)
    )) return -1;
#undef einfoStr

    char *d = dst;
    const char *s = src;
    size_t l;
    if (len > 0)
    {
        l = len;
    }
    else
    {
        l = strlen(src);
    }

    /* For each character that is not equal to the null terminator,
     * src char = dst char. */
    while ((*s != '\0') && l--)
    {
        *d++ = *s++;
    }
    
    /* Ensure the string is null-terminated. */
    dst[len] = '\0';

    return len - l;
}

char *nStringDuplicate(const char *const src, size_t len)
{
    if (len <= 0)
    {
#define einfoStr "Length argument <= 0 in nStringDuplicate()."
        if (nErrorAssert(
         src != NULL,
         NERROR_INV_ARG,
         einfoStr,
         NCONST_STR_LEN(einfoStr)
        )) return NULL;
#undef einfoStr
        len = strlen(src);
    }

    char *dst = nAlloc(len + 1);
    nStringCopy(dst, src, len);
    return dst;
}

// Memory.c
