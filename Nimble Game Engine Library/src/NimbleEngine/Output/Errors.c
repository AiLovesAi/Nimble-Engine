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
 * SOFTWARE.t
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

const char nErrMinStr[]             = "NERROR_MIN";

const char nErrUnknownStr[]         = "NERROR_UNKNOWN";
const char nErrInternalFailureStr[] = "NERROR_INTERNAL_FAILURE";
const char nErrNullStr[]            = "NERROR_NULL";
const char nErrErrorNotFoundStr[]   = "NERROR_ERROR_NOT_FOUND";

//SIGNUM
const char nErrSigAbrtStr[]         = "NERROR_SIGABRT";
const char nErrSigFpeStr[]          = "NERROR_SIGFPE";
const char nErrSigIllStr[]          = "NERROR_SIGILL";
const char nErrSigIntStr[]          = "NERROR_SIGINT";
const char nErrSigSegvStr[]         = "NERROR_SIGSEGV";
const char nErrSigTermStr[]         = "NERROR_SIGTERM";

//ERRNO /** @todo Errno values */
const char nErrFileNotFoundStr[]    = "NERROR_FILE_NOT_FOUND";

const char nErrMaxStr[]             = "NERROR_MAX";


const char * nErrorStrings[] = {
    nErrMinStr,
    
    nErrUnknownStr,
    nErrInternalFailureStr,
    nErrNullStr,
    nErrErrorNotFoundStr,
    
    nErrSigAbrtStr,
    nErrSigFpeStr,
    nErrSigIllStr,
    nErrSigIntStr,
    nErrSigSegvStr,
    nErrSigTermStr,
    
    nErrFileNotFoundStr,
    
    nErrMaxStr
};
const int32_t nErrorStringLengths[] = {
    sizeof(nErrMinStr),
    
    sizeof(nErrUnknownStr),
    sizeof(nErrInternalFailureStr),
    sizeof(nErrNullStr),
    sizeof(nErrErrorNotFoundStr),
    
    sizeof(nErrSigAbrtStr),
    sizeof(nErrSigFpeStr),
    sizeof(nErrSigIllStr),
    sizeof(nErrSigIntStr),
    sizeof(nErrSigSegvStr),
    sizeof(nErrSigTermStr),
    
    sizeof(nErrFileNotFoundStr),
    
    sizeof(nErrMaxStr)
};

const char nErrDescMinStr[]            = "NERROR_MIN - The minimum error "\
"value, likely caused by programmer error or a corruption issue";

const char nErrDescUnknownStr[]        = "NERROR_UNKNOWN - An unknown error "\
"occurred";
const char nErrDecInternalFailureStr[] = "NERROR_INTERNAL_FAILURE - An "\
"internal error occurred within the Nimble game engine";
const char nErrDescNullStr[]           = "NERROR_NULL - A pointer was null "\
"when a nonnull pointer was expected";
const char nErrDescErrorNotFoundStr[]  = "NERROR_ERROR_NOT_FOUND - An error "\
"passed to a function was not valid";

const char nErrDescSigAbrtStr[]        = "NERROR_SIGABRT - Caught an abort "\
"signal";
const char nErrDescSigFpeStr[]         = "NERROR_SIGFPE - Caught a floating "\
"point exception signal";
const char nErrDescSigIllStr[]         = "NERROR_SIGFPE - Caught an illegal "\
"instruction signal";
const char nErrDescSigIntStr[]         = "NERROR_SIGFPE - Caught an interrupt "\
"signal";
const char nErrDescSigSegvStr[]        = "NERROR_SIGFPE - Caught a memory "\
"address violation signal";
const char nErrDescSigTermStr[]        = "NERROR_SIGFPE - Caught a termination "\
"signal";

const char nErrDescFileNotFoundStr[]   = "NERROR_FILE_NOT_FOUND - A file was "\
"not found where specified";

const char nErrDescMaxStr[]            = "NERROR_MAX - The maximum error value, "\
"likely caused by programmer error or a corruption issue";


const char * nErrorDescriptions[] = {
    nErrDescMinStr,
    
    nErrDescUnknownStr,
    nErrDecInternalFailureStr,
    nErrDescNullStr,
    nErrDescErrorNotFoundStr,
    
    nErrDescSigAbrtStr,
    nErrDescSigFpeStr,
    nErrDescSigIllStr,
    nErrDescSigIntStr,
    nErrDescSigSegvStr,
    nErrDescSigTermStr,
    
    nErrDescFileNotFoundStr,
    
    nErrDescMaxStr
};
const int32_t nErrorStringLengths[] = {
    sizeof(nErrMinStr),
    
    sizeof(nErrUnknownStr),
    sizeof(nErrInternalFailureStr),
    sizeof(nErrNullStr),
    sizeof(nErrErrorNotFoundStr),
    
    sizeof(nErrSigAbrtStr),
    sizeof(nErrSigFpeStr),
    sizeof(nErrSigIllStr),
    sizeof(nErrSigIntStr),
    sizeof(nErrSigSegvStr),
    sizeof(nErrSigTermStr),
    
    sizeof(nErrFileNotFoundStr),
    
    sizeof(nErrMaxStr)
};


const char noInfoStr[] = "No info.";

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
        const char callbackStr[] = "Callback argument NULL in nErrorThrow().";
        char * crashErrorDesc;
        int32_t crashErrorDescLen;
        
        nErrorToString(crashErrorDesc, &crashErrorDescLen, NERROR_NULL,
         callbackStr, sizeof(callbackStr));
        nCrashSafe(NERROR_NULL, crashErrorDesc, crashErrorDescLen,
         crashErrorTime);
        /* NO RETURN */
    }
    
    char * errorDesc;
    int32_t errorDescLen;
    if (nErrorToString(errorDesc, &errorDescLen, error, info, infoLen) == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        const char parseStr[] = "Error not found in nErrorThrow().";
        char * crashErrorDesc;
        int32_t crashErrorDescLen;
        
        nErrorToString(crashErrorDesc, &crashErrorDescLen,
         NERROR_ERROR_NOT_FOUND, parseStr, sizeof(parseStr));
        nCrashSafe(NERROR_ERROR_NOT_FOUND, crashErrorDesc, crashErrorDescLen,
         crashErrorTime);
        /* NO RETURN */
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
    
    const char * errorDesc = NERROR_STRING(error);
    
    if (errorDesc == NULL)
    {
        nFree(dst);
        *errorLen = 0;
        return NERROR_ERROR_NOT_FOUND;
    }
    
    const int32_t descLen = NERROR_LENGTH(error);
    if (info == NULL)
    {
        *errorLen = descLen + sizeof(noInfoStr) - 1;
        dst = realloc(dst, *errorLen);
        memcpy(dst, errorDesc, descLen);
        memcpy(dst + descLen - 1, noInfoStr, sizeof(noInfoStr));
    }
    else
    {
        *errorLen = descLen + infoLen - 1;
        dst = realloc(dst, *errorLen);
        memcpy(dst, errorDesc, descLen);
        memcpy(dst + descLen - 1, info, infoLen);
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
        char * errorNumStr = malloc(errorNumLen);
        snprintf(errorNumStr, errorNumLen, "%d", error);
        
        nErrorThrow(NERROR_ERROR_NOT_FOUND, errorNumStr, *errorLen);
        nFree(errorNumStr);
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
        const char callbackStr[] = "Callback argument NULL in "\
                                      "nErrorSetCallback().";
        nErrorThrow(NERROR_NULL, callbackStr, sizeof(callbackStr));
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
