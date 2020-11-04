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

#include <errorno.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../../include/Nimble/NimbleEngine/Output/CrashHandler.h"

const char nErrMinStr[]             = "NERROR_MIN";

const char nErrUnknownStr[]         = "NERROR_UNKNOWN";
const char nErrInternalFailureStr[] = "NERROR_INTERNAL_FAILURE";
const char nErrNullStr[]            = "NERROR_NULL";
const char nErrInvErrorStr[]        = "NERROR_INV_ERROR";

//SIGNUM
const char nErrSigAbrtStr[]         = "NERROR_SIGABRT";
const char nErrSigFpeStr[]          = "NERROR_SIGFPE";
const char nErrSigIllStr[]          = "NERROR_SIGILL";
const char nErrSigIntStr[]          = "NERROR_SIGINT";
const char nErrSigSegvStr[]         = "NERROR_SIGSEGV";
const char nErrSigTermStr[]         = "NERROR_SIGTERM";

//ERRNO
const char nErrNoPermStr[]          = "NERROR_NO_PERM";
const char nErrNoFileStr[]          = "NERROR_NO_FILE";
const char nErrNoProcessStr[]       = "NERROR_NO_PROCESS";
const char nErrInterruptStr[]       = "NERROR_INTERRUPT";
const char nErrIOStr[]              = "NERROR_IO";
const char nErrNoDeviceStr[]        = "NERROR_NO_DEVICE";
const char nErrMaxArgsStr[]         = "NERROR_MAX_ARGS";
const char nErrInvExecFormatStr[]   = "NERROR_INV_EXEC_FORMAT";
const char nErrInvFPStr[]           = "NERROR_INV_FP";

const char nErrMaxStr[]             = "NERROR_MAX";


const char * nErrorStrings[] = {
    nErrMinStr,
    
    nErrUnknownStr,
    nErrInternalFailureStr,
    nErrNullStr,
    nErrInvErrorStr,
    
    nErrSigAbrtStr,
    nErrSigFpeStr,
    nErrSigIllStr,
    nErrSigIntStr,
    nErrSigSegvStr,
    nErrSigTermStr,
    
    nErrNoPermStr,
    nErrNoFileStr,
    nErrNoProcessStr,
    nErrInterruptStr,
    nErrIOStr,
    nErrNoDeviceStr,
    nErrMaxArgsStr,
    nErrInvExecFormatStr,
    
    nErrMaxStr
};
const nint_t nErrorStringLengths[] = {
    sizeof(nErrMinStr),
    
    sizeof(nErrUnknownStr),
    sizeof(nErrInternalFailureStr),
    sizeof(nErrNullStr),
    sizeof(nErrInvErrorStr),
    
    sizeof(nErrSigAbrtStr),
    sizeof(nErrSigFpeStr),
    sizeof(nErrSigIllStr),
    sizeof(nErrSigIntStr),
    sizeof(nErrSigSegvStr),
    sizeof(nErrSigTermStr),
    
    sizeof(nErrNoPermStr),
    sizeof(nErrNoFileStr),
    sizeof(nErrNoProcessStr),
    sizeof(nErrInterruptStr),
    sizeof(nErrIOStr),
    sizeof(nErrNoDeviceStr),
    sizeof(nErrMaxArgsStr),
    sizeof(nErrInvExecFormatStr),
    sizeof(nErrInvFPStr),
    
    sizeof(nErrMaxStr)
};

const char nErrDescMinStr[]            = "The minimum error value, likely "\
"caused by programmer error or a corruption issue.";

const char nErrDescUnknownStr[]        = "An unknown error occurred.";
const char nErrDecInternalFailureStr[] = "An internal error occurred within "\
"the Nimble game engine.";
const char nErrDescNullStr[]           = "A pointer was null when a nonnull "\
"pointer was expected.";
const char nErrDescInvErrorStr[]       = "An error passed to a function was "\
"not valid.";

const char nErrDescSigAbrtStr[]        = "Caught an abort signal.";
const char nErrDescSigFpeStr[]         = "Caught a floating point exception "\
"signal.";
const char nErrDescSigIllStr[]         = "Caught an illegal instruction signal.";
const char nErrDescSigIntStr[]         = "Caught an interrupt signal";
const char nErrDescSigSegvStr[]        = "Caught a memory address violation "\
"signal.";
const char nErrDescSigTermStr[]        = "Caught a termination signal.";

const char nErrDescNoPermStr[]         = "Operation not permitted. Only the "\
"owner of the file (or other resource) or processes with special privileges "\
"can perform the operation.";
const char nErrDescNoFileStr[]         = "No such file or directory. This is a "\
"\"file doesn't exist\" error for ordinary files that are referenced in "\
"contexts where they are expected to already exist.";
const char nErrDescNoProcessStr[]      = "No such process. No process matches "\
"the specified process ID.";
const char nErrDescInterruptStr[]      = "Interrupted system call. An "\
"asynchronous signal occurred and prevented completion of the call. When this "\
"happens, you should try the call again.";
const char nErrDescIOStr[]             = "Input/output error. Usually used for "\
"physical read or write errors.";
const char nErrDescNoDeviceStr[]       = "No such device or address. The "\
"system tried to use the device represented by a file you specified, and it "\
"couldn't find the device. This can mean that the device file was installed "\
"incorrectly, or that the physical device is missing or not correctly attached "\
"to the computer.";
const char nErrDescMaxArgsStr[]        = "Argument list too long. Used when "\
"the arguments passed to a new program being executed with one of the exec "\
"functions occupy too much memory space.";
const char nErrDescInvExecFormatStr[]  = "Exec format error. Invalid "\
"executable file format. This condition is detected by the exec functions.";
const char nErrDescInvFPStr[]          = "Bad file descriptor. For example, "\
"I/O on a descriptor that has been closed or reading from a descriptor open "\
"only for writing (or vice versa).";

const char nErrDescMaxStr[]            = "The maximum error value, likely "\
"caused by programmer error or a corruption issue.";


const char * nErrorDescriptions[] = {
    nErrDescMinStr,
    
    nErrDescUnknownStr,
    nErrDecInternalFailureStr,
    nErrDescNullStr,
    nErrDescInvErrorStr,
    
    nErrDescSigAbrtStr,
    nErrDescSigFpeStr,
    nErrDescSigIllStr,
    nErrDescSigIntStr,
    nErrDescSigSegvStr,
    nErrDescSigTermStr,
    
    nErrDescNoPermStr,
    nErrDescNoFileStr,
    nErrDescNoProcessStr,
    nErrDescInterruptStr,
    nErrDescIOStr,
    nErrDescMaxArgsStr,
    nErrDescInvExecFormatStr,
    nErrDescInvFPStr,
    
    nErrDescMaxStr
};
const nint_t nErrorDescLengths[] = {
    sizeof(nErrDescMinStr),
    
    sizeof(nErrDescUnknownStr),
    sizeof(nErrDescInternalFailureStr),
    sizeof(nErrDescNullStr),
    sizeof(nErrDescInvErrorStr),
    
    sizeof(nErrDescSigAbrtStr),
    sizeof(nErrDescSigFpeStr),
    sizeof(nErrDescSigIllStr),
    sizeof(nErrDescSigIntStr),
    sizeof(nErrDescSigSegvStr),
    sizeof(nErrDescSigTermStr),
    
    sizeof(nErrDescNoPermStr),
    sizeof(nErrDescNoFileStr),
    sizeof(nErrDescNoProcessStr),
    sizeof(nErrDescInterruptStr),
    sizeof(nErrDescIOStr),
    sizeof(nErrDescMaxArgsStr),
    sizeof(nErrDescInvExecFormatStr),
    sizeof(nErrDescInvFPStr),
    
    sizeof(nErrDescMaxStr)
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
void nErrorHandlerDefault(const nint_t error,
                          const time_t errorTime,
                          const char * errorDesc,
                          const nint_t errorDescLen,
                          const char * stack,
                          const nint_t stackLen
                          );

/**
 * @brief The error callback function that gets defined by nErrorSetCallback().
 */
void (* errorCallback) (const nint_t error, const time_t errorTime,
         const char * errorDesc, const nint_t errorDescLen, const char * stack,
         const nint_t stackLen) = nErrorHandlerDefault;


void nErrorHandlerDefault(const nint_t error, const time_t errorTime,
      const char * errorDesc, const nint_t errorDescLen, const char * stack,
      const nint_t stackLen)
{
    /** @todo Make default callback. */
}

nint_t nErrorFromSignal(const int error)
{
    switch (error)
    {
        #ifdef SIGABRT
        case SIGABRT:
        {
            return NERROR_SIGABRT;
        }
        break;
        #endif
        #ifdef SIGFPE
        case SIGFPE:
        {
            return NERROR_SIGFPE;
        }
        break;
        #endif
        #ifdef SIGILL
        case SIGILL:
        {
            return NERROR_SIGILL;
        }
        break;
        #endif
        #ifdef SIGINT
        case SIGINT:
        {
            return NERROR_SIGINT;
        }
        break;
        #endif
        #ifdef SIGSEGV
        case SIGSEGV:
        {
            return NERROR_SIGSEGV;
        }
        break;
        #endif
        #ifdef SIGTERM
        case SIGTERM:
        {
            return NERROR_SIGTERM;
        }
        break;
        #endif
        default:
        {
            return NERROR_INV_ERROR;
        }
        break;
    }
}

nint_t nErrorFromErrno(const int error)
{
    switch (error)
    {
        #ifdef EPERM
        case EPERM:
        {
            return NERROR_NO_PERM;
        }
        break;
        #endif
        #ifdef ENOENT
        case ENOENT:
        {
            return NERROR_NO_FILE;
        }
        break;
        #endif
        #ifdef ESRCH
        case ESRCH:
        {
            return NERROR_NO_PROCESS;
        }
        break;
        #endif
        #ifdef EINTR
        case EINTR:
        {
            return NERROR_INTERRUPT;
        }
        break;
        #endif
        #ifdef EIO
        case EIO:
        {
            return NERROR_IO;
        }
        break;
        #endif
        #ifdef ENXIO
        case ENXIO:
        {
            return NERROR_NO_DEVICE;
        }
        break;
        #endif
        #ifdef E2BIG
        case E2BIG:
        {
            return NERROR_MAX_ARGS;
        }
        break;
        #endif
        #ifdef ENOEXEC
        case ENOEXEC:
        {
            return NERROR_INV_EXEC_FORMAT;
        }
        break;
        #endif
        #ifdef EBADF
        case EBADF:
        {
            return NERROR_INV_FP;
        }
        break;
        #endif
        #ifdef ECHILD
        case ECHILD:
        {
            return NERROR_NO_CHILD;
        }
        break;
        #endif
        #ifdef EDEADLK
        case EDEAKLK:
        {
            return NERROR_DEADLOCK;
        }
        break;
        #endif
        #ifdef ENOMEM
        case ENOMEM:
        {
            return NERROR_NO_MEMORY;
        }
        break;
        #endif
        #ifdef EACCESS
        case EACCESS:
        {
            return NERROR_NO_FILE_PERM;
        }
        break;
        #endif
        #ifdef EFAULT
        case EFAULT:
        {
            return NERROR_FAULT;
        }
        break;
        #endif
        #ifdef ENOTBLK
        case ENOTBLK:
        {
            return NERROR_NOT_BLOCK;
        }
        break;
        #endif
        #ifdef EBUSY
        case EBUSY:
        {
            return NERROR_DEVICE_BUSY;
        }
        break;
        #endif
        #ifdef EEXIST
        case EEXIST:
        {
            return NERROR_FILE_EXISTS;
        }
        break;
        #endif
        #ifdef EXDEV
        case EXDEV:
        {
            return NERROR_INV_CROSSLINK;
        }
        break;
        #endif
        #ifdef ENODEV
        case ENODEV:
        {
            return NERROR_INV_DEVICE;
        }
        break;
        #endif
        #ifdef ENOTDIR
        case ENOTDIR:
        {
            return NERROR_NOT_DIR;
        }
        break;
        #endif
        #ifdef EISDIR
        case EISDIR:
        {
            return NERROR_IS_DIR;
        }
        break;
        #endif
        #ifdef EINVAL
        case EINVAL:
        {
            return NERROR_INV_ARG;
        }
        break;
        #endif
        #ifdef EMFILE
        case EMFILE:
        {
            return NERROR_MAX_FILE;
        }
        break;
        #endif
        #ifdef ENFILE
        case ENFILE:
        {
            return NERROR_MAX_FILE_SYS;
        }
        break;
        #endif
        #ifdef ENOTTY
        case ENOTTY:
        {
            return NERROR_INV_IOCTL;
        }
        break;
        #endif
        /// @todo Continue with errnos from https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
        default:
        {
            return NERROR_INV_ERROR;
        }
        break;
    }
}

void nErrorThrow(const nint_t error, const char * info, nint_t infoLen)
{
    const time_t errorTime = time(NULL);
    
    if (errorCallback == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        const char callbackStr[] = "Callback argument NULL in nErrorThrow().";
        char * crashErrorDesc;
        nint_t crashErrorDescLen;
        
        nErrorToString(crashErrorDesc, &crashErrorDescLen, NERROR_NULL,
         callbackStr, sizeof(callbackStr));
        nCrashSafe(NERROR_NULL, crashErrorTime, crashErrorDesc,
         crashErrorDescLen);
        /* NO RETURN */
    }
    
    char * errorDesc;
    nint_t errorDescLen;
    if (nErrorToString(errorDesc, &errorDescLen, error, info, infoLen) == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        const char parseStr[] = "Error not found in nErrorThrow().";
        char * crashErrorDesc;
        nint_t crashErrorDescLen;
        
        nErrorToString(crashErrorDesc, &crashErrorDescLen,
         NERROR_INV_ERROR, parseStr, sizeof(parseStr));
        nCrashSafe(NERROR_INV_ERROR, crashErrorTime, crashErrorDesc,
         crashErrorDescLen);
        /* NO RETURN */
    }
    
    char * stack;
    nint_t stackLen, stackLevels;
    nErrorGetStacktrace(stack, &stackLen, &stackLevels);
    
    errorCallback(error, errorTime, errorDesc, errorDescLen, stack, stackLen);
}

nint_t nErrorToStringLocal(char * dst, nint_t * errorLen,
         const nint_t error, const char * info, nint_t infoLen)
{
    if ((info != NULL) && (infoLen == 0))
    {
        infoLen = strlen(info) + 1;
    }
    
    const char errorDesc[] = nErrDesc(error);
    
    if (errorDesc == NULL)
    {
        
        if (errorLen != NULL)
        {
            *errorLen = 0;
        }
        
        dst = nFree(dst);
        return NERROR_INV_ERROR;
    }
    
    const nint_t descLen = nErrDescLen(error);
    nint_t errLen;
    if (info == NULL)
    {
        errLen = descLen + sizeof(noInfoStr) - 1;
        dst = realloc(dst, errLen);
        memcpy(dst, errorDesc, descLen);
        memcpy(dst + descLen - 1, noInfoStr, sizeof(noInfoStr));
    }
    else
    {
        errLen = descLen + infoLen - 1;
        dst = realloc(dst, errLen);
        memcpy(dst, errorDesc, descLen);
        memcpy(dst + descLen - 1, info, infoLen);
    }
    
    if (errorLen != NULL)
    {
        *errorLen = errLen;
    }
    
    return NSUCCESS;
}

char * nErrorToString(char * dst, nint_t * errorLen, const nint_t error,
        const char * info, nint_t infoLen)
{
    nint_t result = nErrorToStringLocal(dst, errorLen, error, info, infoLen);
    if (result != NSUCCESS)
    {
        nint_t errorNumLen = snprintf(NULL, 0, "%d", error) + 1;
        char * errorNumStr = malloc(errorNumLen);
        snprintf(errorNumStr, errorNumLen, "%d", error);
        
        nErrorThrow(NERROR_INV_ERROR, errorNumStr, errorNumLen);
        errorNumStr = nFree(errorNumStr);
        return dst;
    }
    
    return dst;
}

nint_t nErrorSetCallback(void (* callback)(const nint_t error,
         const time_t errorTime, const char * errorDesc,
         const nint_t errorDescLen, const char * stack, const nint_t stackLen))
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

char * nErrorGetStacktrace(char * dst, nint_t * stackLen, nint_t * stackLevels)
{
    /** @todo Get stack trace. Remember *stackLevels is max levels */
    return dst;
}

// Errors.c
