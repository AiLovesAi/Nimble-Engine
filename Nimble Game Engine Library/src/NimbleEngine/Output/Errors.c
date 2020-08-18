#include "../../../include/Nimble/NimbleLicense.h"
/*
 * Errors.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-17.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../../include/Nimble/NimbleEngine/Output/Errors.h"

/**
 * @file Errors.c
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
 * @date 2020-08-17
 *
 * @brief This class defines error values and error handling functions.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../../../include/Nimble/NimbleEngine/Output/CrashHandler.h"

const char noInfoStr[]           = "No info.";
const char unknownErrStr[]       = "NERROR_UNKNOWN: An unknown error occurred: ";
const char nullErrStr[]          = "NERROR_NULL: A pointer was null when "\
                                   "a nonnull pointer was expected: ";
const char fileNotFoundErrStr[]  = "NERROR_FILE_NOT_FOUND: A file was not "\
                                   "found where specified: ";
const char errorNotFoundErrStr[] = "NERROR_ERROR_NOT_FOUND: An error passed to "\
                                   "a function was not valid: ";

/**
 * @brief The error callback function that gets defined by nErrorSetCallback().
 */
int32_t (*errorCallback) (const int32_t, const char *, const char *,
                          const time_t) = NULL;


int32_t nErrorThrow(const int32_t error, const char * info)
{
    time_t errorTime = time(NULL);
    
    if (errorCallback == NULL)
    {
        /** @todo Crash. */
        return NERROR;
    }

    char * errorDesc;
    int32_t errorDescLen;
    if (nErrorToString(errorDesc, &errorDescLen, error, info) == NULL)
    {
        /** @todo Crash. */
        return NERROR;
    }
    
    char * stack;
    int32_t size, levels;
    if (nErrorGetStacktrace(stack, &size, &levels) == NULL)
    {
        /** @todo Crash. */
        return NERROR;
    }
    
    errorCallback(error, errorDesc, stack, errorTime);
    return NSUCCESS;
}

char * nErrorToString(char * dst, int32_t * size, const int32_t error,
        const char * info)
{
    int32_t infoLen = 0;
    
    if (info != NULL)
    {
        infoLen = strlen(info);
    }
    
    switch (error)
    {
        case NERROR_UNKNOWN:
        {
            if (info != NULL)
            {
                dst = malloc(sizeof(void *) + sizeof(unknownErrStr) + infoLen);
                strncpy(dst, unknownErrStr, sizeof(unknownErrStr));
                strncat(dst, info, infoLen + 1);
            }
            else
            {
                dst = malloc(sizeof(void *) + sizeof(unknownErrStr) +
                       sizeof(noInfoStr) - 1);
                strncpy(dst, unknownErrStr, sizeof(unknownErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
        }
        break;
        case NERROR_NULL:
        {
            if (info != NULL)
            {
                dst = malloc(sizeof(void *) + sizeof(nullErrStr) + infoLen);
				strncpy(dst, nullErrStr, sizeof(nullErrStr));
				strncat(dst, info, infoLen + 1);
            }
            else
		    {
                dst = malloc(sizeof(void *) + sizeof(nullErrStr) +
                       sizeof(noInfoStr) - 1);
                strncpy(dst, nullErrStr, sizeof(nullErrStr));
				strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
        }
        break;
        case NERROR_FILE_NOT_FOUND:
        {
            if (info != NULL)
            {
                dst = malloc(sizeof(void *) + sizeof(fileNotFoundErrStr) +
                       infoLen);
                strncpy(dst, fileNotFoundErrStr, sizeof(fileNotFoundErrStr));
                strncat(dst, info, infoLen + 1);
            }
            else
            {
                dst = malloc(sizeof(void *) + sizeof(fileNotFoundErrStr) +
                       sizeof(noInfoStr) - 1);
                strncpy(dst, fileNotFoundErrStr, sizeof(fileNotFoundErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
        }
        break;
        case NERROR_ERROR_NOT_FOUND:
        {
            if (info != NULL)
		    {
                dst = malloc(sizeof(void *) + sizeof(errorNotFoundErrStr) +
                       infoLen);
                strncpy(dst, errorNotFoundErrStr, sizeof(errorNotFoundErrStr));
                strncat(dst, info, infoLen + 1);
            }
            else
            {
                dst = malloc(sizeof(void *) + sizeof(errorNotFoundErrStr) +
                       sizeof(noInfoStr) - 1);
                strncpy(dst, errorNotFoundErrStr, sizeof(errorNotFoundErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
        }
        break;
        default:
        {
            dst = NULL;
            int32_t errorNumLen = snprintf(NULL, 0, "%d", error) + 1;
            char * errorNumStr = malloc(sizeof(void *) + errorNumLen);
			snprintf(errorNumStr, errorNumLen, "%d", error);
            
            if (nErrorThrow(NERROR_ERROR_NOT_FOUND, errorNumStr) != NSUCCESS)
		    {
                /** @todo Crash. */
            }
        }
        break;
    }
    
    return dst;
}

int32_t nErrorSetCallback(int32_t (*callback)(const int32_t, const char *,
         const char *, const time_t))
{
    if (callback == NULL)
    {
        nErrorThrow(NERROR_NULL, "Callback parameter null in nErrorSetCallback().");
        return NERROR;
    }
    
    errorCallback = callback;
    return NSUCCESS;
}

char * nErrorGetStacktrace(char * dst, int32_t * size, int32_t * levels)
{
    /** @todo Get stack trace. */
    return dst;
}

// Errors.c
