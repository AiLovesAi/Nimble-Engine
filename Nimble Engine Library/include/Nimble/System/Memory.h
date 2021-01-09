#include "../NimbleLicense.h"
/*
 * Memory.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-07.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Memory.h
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
 * @date 2020-12-07
 *
 * @brief This class defines memory functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_MEMORY_H
#define NIMBLE_ENGINE_MEMORY_H /**< Header definition */

#include "../NimbleEngine.h"

/**
 * @brief Allocates a pointer.
 * Allocates a pointer and checks if it is successful.
 *
 * @param[in] size The size of the memory block in bytes.
 * @return The allocated pointer.
 */
NIMBLE_EXPORT
NIMBLE_USE_RESULT
NIMBLE_EXTERN
void *
nAlloc(const size_t size);

/**
 * @brief Reallocates a pointer.
 * Rellocates a pointer and checks if it is successful.
 *
 * @param[in,out] ptr The pointer to reallocate.
 * @param[in] size The size of the new memory block in bytes.
 * @return The reallocated @p ptr.
 */
NIMBLE_EXPORT
NIMBLE_USE_RESULT
NIMBLE_EXTERN
void *
nRealloc(void*ptr, const size_t size);

/**
 * @brief Frees a pointer.
 * Frees a pointer and returns #NULL to allow the invoker to optionally nullify
 * the pointer. Should the freed pointer location be needed again, no assignment
 * is necessary.
 *
 * @param[in] ptr The pointer to free.
 * @return #NULL is always returned.
 */
NIMBLE_INLINE
void nFree(void **ptr)
{
    if (ptr)
    {
	    free(*ptr);
	    *ptr = NULL;
    }
}

/**
 * @brief Copies @p len characters from @p src to @p dst.
 * Copies @p len characters from @p src to @p dst. The string is always null
 * terminated. If there is already a null terminator, no more characters are
 * copied.
 *
 * @param[out] dst The pointer to the destination.
 * @param[in] src The pointer to free.
 * @param[in] len The number of characters to copy. This must not include the
 * null terminator.
 * @return The number of successfully copied bytes is returned, or -1 if an error
 * occurs.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
ssize_t
nStringCopy(char *const restrict dst,
            const char *const restrict src,
            const size_t len
            );

/**
 * @brief Returns a newly allocated string identical to @p src.
 * 
 * @param[in] src The string to copy and return.
 * @return Returns a newly allocated string duplicated from @p src.
 */
NIMBLE_EXPORT
NIMBLE_USE_RESULT
NIMBLE_EXTERN
char *nStringDuplicate(const char *const src,
                       size_t len);

#endif // NIMBLE_ENGINE_MEMORY_H

#ifdef __cplusplus
}
#endif

// Memory.h