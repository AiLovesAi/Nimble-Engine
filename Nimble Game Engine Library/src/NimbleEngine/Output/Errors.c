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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
 * @brief The default error handler callback.
 * @param[in] error The error number.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument, including the
 * null character. A length of zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 * @param[in] stack The stacktrace of the thread that caused the crash.
 * @param[in] stackLen The length of the @p stack argument, including the null
 * character. A length of zero (0) uses strlen() to determine length.
 */
void nErrorHandlerDefault(const int32_t error,
                          const char * errorDesc,
                          const int32_t errorDescLen,
                          const time_t errorTime,
                          const char * stack,
                          const int32_t stackLen
                          );

/**
 * @brief The error callback function that gets defined by nErrorSetCallback().
 */
void (* errorCallback) (const int32_t error, const char * errorDesc, 
         const int32_t errorDescLen, const time_t errorTime, const char * stack,
         const int32_t stackLen) = nErrorHandlerDefault;


void nErrorHandlerDefault(const int32_t error, const char * errorDesc,
      const int32_t errorDescLen, const time_t errorTime, const char * stack,
      const int32_t stackLen)
{
    /** @todo Make default callback. */
}

void nErrorThrow(const int32_t error, const char * info, int32_t infoLen)
{
    const time_t errorTime = time(NULL);
    
    if (errorCallback == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        const char callbackErrStr[] = "Callback argument NULL in nErrorThrow().";
        /** @todo Append info  */
        char * crashErrorDesc;
        int32_t crashErrorDescLen;
        
        if (nErrorToString(crashErrorDesc, &crashErrorDescLen, NERROR_NULL,
             callbackErrStr, sizeof(callbackErrStr)) == NULL)
        {
            /** @todo Figure out case. */
        }
        
        nCrashSafe(NERROR_NULL, crashErrorDesc, crashErrorDescLen,
         crashErrorTime);
    }
    
    char * errorDesc;
    int32_t errorDescLen;
    if (nErrorToString(errorDesc, &errorDescLen, error, info, infoLen) == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        const char parseErrStr[] = "Error not found in nErrorThrow().";
        /** @todo Append info  */
        char * crashErrorDesc;
        int32_t crashErrorDescLen;
        
        if (nErrorToString(crashErrorDesc, &crashErrorDescLen,
             NERROR_ERROR_NOT_FOUND, parseErrStr, sizeof(parseErrStr)) == NULL)
        {
            /** @todo Figure out case. */
        }
        
        nCrashSafe(NERROR_ERROR_NOT_FOUND, crashErrorDesc, crashErrorDescLen,
         crashErrorTime);
    }
    
    char * stack;
    int32_t stackLen, stackLevels;
    nErrorGetStacktrace(stack, &stackLen, &stackLevels);
    
    errorCallback(error, errorDesc, errorDescLen, errorTime, stack, stackLen);
}

int32_t nErrorToStringLocal(char * dst, int32_t * errorLen,
         const int32_t error, const char * info, int32_t infoLen)
{
    if ((info != NULL) && (infoLen == 0))
    {
        infoLen = strlen(info) + 1;
    }
    
    switch (error)
    {
        case NERROR_UNKNOWN:
        {
            if (info != NULL)
            {
                *errorLen = sizeof(unknownErrStr) + infoLen - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, unknownErrStr, sizeof(unknownErrStr));
                strncat(dst, info, infoLen);
            }
            else
            {
                *errorLen = sizeof(unknownErrStr) + sizeof(noInfoStr) - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, unknownErrStr, sizeof(unknownErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
            dst[*errorLen - 1] = '\0';
        }
        break;
        case NERROR_NULL:
        {
            if (info != NULL)
            {
                *errorLen =  sizeof(nullErrStr) + infoLen - 1;
                dst = malloc(sizeof(void *) + *errorLen);
				strncpy(dst, nullErrStr, sizeof(nullErrStr));
				strncat(dst, info, infoLen);
            }
            else
		    {
                *errorLen = sizeof(nullErrStr) + sizeof(noInfoStr) - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, nullErrStr, sizeof(nullErrStr));
				strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
            dst[*errorLen - 1] = '\0';
        }
        break;
        case NERROR_FILE_NOT_FOUND:
        {
            if (info != NULL)
            {
                *errorLen = sizeof(fileNotFoundErrStr) + infoLen - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, fileNotFoundErrStr, sizeof(fileNotFoundErrStr));
                strncat(dst, info, infoLen);
            }
            else
            {
                *errorLen = sizeof(fileNotFoundErrStr) + sizeof(noInfoStr) - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, fileNotFoundErrStr, sizeof(fileNotFoundErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
            dst[*errorLen - 1] = '\0';
        }
        break;
        case NERROR_ERROR_NOT_FOUND:
        {
            if (info != NULL)
		    {
                *errorLen = sizeof(errorNotFoundErrStr) + infoLen - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, errorNotFoundErrStr, sizeof(errorNotFoundErrStr));
                strncat(dst, info, infoLen);
            }
            else
            {
                *errorLen = sizeof(errorNotFoundErrStr) + sizeof(noInfoStr) - 1;
                dst = malloc(sizeof(void *) + *errorLen);
                strncpy(dst, errorNotFoundErrStr, sizeof(errorNotFoundErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
            dst[*errorLen - 1] = '\0';
        }
        break;
        default:
        {
            dst = NULL;
            *errorLen = 0;
            return NERROR_ERROR_NOT_FOUND;
        }
        break;
    }
    
    return NSUCCESS;
}

char * nErrorToString(char * dst, int32_t * errorLen, const int32_t error,
        const char * info, int32_t infoLen)
{
    int32_t result = nErrorToStringLocal(dst, errorLen, error, info, infoLen);
    if (result != NSUCCESS)
    {
        int32_t errorNumLen = snprintf(NULL, 0, "%d", error) + 1;
        char * errorNumStr = malloc(sizeof(void *) + errorNumLen);
        snprintf(errorNumStr, errorNumLen, "%d", error);
        
        nErrorThrow(NERROR_ERROR_NOT_FOUND, errorNumStr, *errorLen);
        return dst;
    }
    
    return dst;
}

int32_t nErrorSetCallback(void (* callback)(const int32_t error,
         const char * errorDesc, const int32_t errorDescLen,
         const time_t errorTime, const char * stack, const int32_t stackLen))
{
    if (callback == NULL)
    {
        const char callbackErrStr[] = "Callback argument NULL in "\
                                      "nErrorSetCallback().";
        nErrorThrow(NERROR_NULL, callbackErrStr, sizeof(callbackErrStr));
        return NERROR;
    }
    
    errorCallback = callback;
    return NSUCCESS;
}

char * nErrorGetStacktrace(char * dst, int32_t * errorLen, int32_t * stackLevels)
{
    /** @todo Get stack trace. */
    return dst;
}

// Errors.c
