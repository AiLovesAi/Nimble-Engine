#include "../../include/Nimble/NimbleLicense.h"
/*
 * Memory.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-12-12.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/Memory.h"

/**
 * @file Memory.c
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
 * @date 2020-12-12
 *
 * @brief This class defines memory functions.
 */

#include <stdlib.h>

void *nAlloc(const size_t size)
{
    void *ptr = malloc(size);

    /* Check if successfully allocated. */
    if (!ptr)
    {
        nCrashSafe(NERROR_NO_MEMORY, time(NULL), NULL, 0);
        /* NO RETURN */
    }

    return ptr;
}

void *nRealloc(void *ptr, const size_t size)
{
    ptr = realloc(ptr, size);

    /* Check if successfully allocated. */
    if (!ptr)
    {
        nCrashSafe(NERROR_NO_MEMORY, time(NULL), NULL, 0);
         /* NO RETURN */
    }

    return ptr;
}

size_t nStringCopy(char *const restrict dst, const char *const restrict src,
 const size_t len)
{
    if (!src)
    {
        const char einfoNullStr[] = "Source string NULL in nStringCopy().";
        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, NERROR_NULL,
         einfoNullStr, NCONST_STR_LEN(einfoNullStr));
        nErrorThrow(NERROR_NULL, errorDescStr, errorDescLen);
        nFree(errorDescStr);
        return 0;
    }

    if (!dst)
    {
        const char einfoNullStr[] = "Destination string NULL in nStringCopy().";
        size_t errorDescLen;
        char *errorDescStr = nErrorToString(&errorDescLen, NERROR_NULL,
         einfoNullStr, NCONST_STR_LEN(einfoNullStr));
        nErrorThrow(NERROR_NULL, einfoNullStr, NCONST_STR_LEN(einfoNullStr));
        nFree(errorDescStr);
        return 0;
    }

    char *d = dst;
    const char *s = src;
    size_t l = len;

    /* For each character that is not equal to the null terminator,
     * src char = dst char. */
    while (l-- && (*s != '\0'))
    {
        *d++ = *s++;
    }
    
    /* Ensure the string is null-terminated. */
    dst[len] = '\0';

    return len - l;
}

// Memory.c
