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

#include <errno.h>
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
const char nErrNoChildStr[]         = "NERROR_NO_CHILD";
const char nErrDeadlockStr[]        = "NERROR_DEADLOCK";
const char nErrNoMemoryStr[]        = "NERROR_NO_MEMORY";
const char nErrNoFilePermStr[]      = "NERROR_NO_FILE_PERM";
const char nErrFaultStr[]           = "NERROR_FAULT";
const char nErrNotBlockStr[]        = "NERROR_NOT_BLOCK";
const char nErrDeviceBusyStr[]      = "NERROR_DEVICE_BUSY";
const char nErrFileExistsStr[]      = "NERROR_FILE_EXISTS";
const char nErrInvCrosslinkStr[]    = "NERROR_INV_CROSSLINK";
const char nErrInvDeviceStr[]       = "NERROR_INV_DEVICE";
const char nErrNotDirStr[]          = "NERROR_NOT_DIR";
const char nErrIsDirStr[]           = "NERROR_IS_DIR";
const char nErrInvArgStr[]          = "NERROR_INV_ARG";
const char nErrMaxFileStr[]         = "NERROR_MAX_FILE";
const char nErrMaxFileSysStr[]      = "NERROR_MAX_FILE_SYS";
const char nErrInvIOCtlStr[]        = "NERROR_INV_IOCTL";
const char nErrTextBusyStr[]        = "NERROR_TEXT_BUSY";
const char nErrFileTooBigStr[]      = "NERROR_FILE_TOO_BIG";
const char nErrNoSpaceStr[]         = "NERROR_NO_SPACE";
const char nErrInvSeekStr[]         = "NERROR_INV_SEEK";
const char nErrReadOnlyStr[]        = "NERROR_READ_ONLY";
const char nErrMaxLinksStr[]        = "NERROR_MAX_LINKS";
const char nErrInvPipeStr[]         = "NERROR_INV_PIPE";
const char nErrDomainStr[]          = "NERROR_DOMAIN";
const char nErrResultTooBigStr[]    = "NERROR_RESULT_TOO_BIG";
const char nErrWouldBlockStr[]      = "NERROR_WOULD_BLOCK";
const char nErrInProgressStr[]      = "NERROR_IN_PROGRESS";

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
    nErrNoChildStr,
    nErrDeadlockStr,
    nErrNoMemoryStr,
    nErrNoFilePermStr,
    nErrFaultStr,
    nErrNotBlockStr,
    nErrDeviceBusyStr,
    nErrFileExistsStr,
    nErrInvCrosslinkStr,
    nErrInvDeviceStr,
    nErrNotDirStr,
    nErrIsDirStr,
    nErrInvArgStr,
    nErrMaxFileStr,
    nErrMaxFileSysStr,
    nErrInvIOCtlStr,
    nErrTextBusyStr,
    nErrFileTooBigStr,
    nErrNoSpaceStr,
    nErrInvSeekStr,
    nErrReadOnlyStr,
    nErrMaxLinksStr,
    nErrInvPipeStr,
    nErrDomainStr,
    nErrResultTooBigStr,
    nErrWouldBlockStr,
    nErrInProgressStr,
    
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
    sizeof(nErrNoChildStr),
    sizeof(nErrDeadlockStr),
    sizeof(nErrNoMemoryStr),
    sizeof(nErrNoFilePermStr),
    sizeof(nErrFaultStr),
    sizeof(nErrNotBlockStr),
    sizeof(nErrDeviceBusyStr),
    sizeof(nErrFileExistsStr),
    sizeof(nErrInvCrosslinkStr),
    sizeof(nErrInvDeviceStr),
    sizeof(nErrNotDirStr),
    sizeof(nErrIsDirStr),
    sizeof(nErrInvArgStr),
    sizeof(nErrMaxFileStr),
    sizeof(nErrMaxFileSysStr),
    sizeof(nErrInvIOCtlStr),
    sizeof(nErrTextBusyStr),
    sizeof(nErrFileTooBigStr),
    sizeof(nErrNoSpaceStr),
    sizeof(nErrInvSeekStr),
    sizeof(nErrReadOnlyStr),
    sizeof(nErrMaxLinksStr),
    sizeof(nErrInvPipeStr),
    sizeof(nErrDomainStr),
    sizeof(nErrResultTooBigStr),
    sizeof(nErrWouldBlockStr),
    sizeof(nErrInProgressStr),
    
    sizeof(nErrMaxStr)
};

const char nErrDescMinStr[]             = "The minimum error value, likely "\
"caused by programmer error or a corruption issue.";

const char nErrDescUnknownStr[]         = "An unknown error occurred.";
const char nErrDescInternalFailureStr[] = "An internal error occurred within "\
"the Nimble game engine.";
const char nErrDescNullStr[]            = "A pointer was null when a nonnull "\
"pointer was expected.";
const char nErrDescInvErrorStr[]        = "An error passed to a function was "\
"not valid.";

const char nErrDescSigAbrtStr[]         = "Caught an abort signal.";
const char nErrDescSigFpeStr[]          = "Caught a floating point exception "\
"signal.";
const char nErrDescSigIllStr[]          = "Caught an illegal instruction "\
"signal.";
const char nErrDescSigIntStr[]          = "Caught an interrupt signal";
const char nErrDescSigSegvStr[]         = "Caught a memory address violation "\
"signal.";
const char nErrDescSigTermStr[]         = "Caught a termination signal.";

const char nErrDescNoPermStr[]          = "Operation not permitted. Only the "\
"owner of the file (or other resource) or processes with special privileges "\
"can perform the operation.";
const char nErrDescNoFileStr[]          = "No such file or directory. This is "\
"a \"file doesn't exist\" error for ordinary files that are referenced in "\
"contexts where they are expected to already exist.";
const char nErrDescNoProcessStr[]       = "No such process. No process matches "\
"the specified process ID.";
const char nErrDescInterruptStr[]       = "Interrupted system call. An "\
"asynchronous signal occurred and prevented completion of the call. When this "\
"happens, you should try the call again.";
const char nErrDescIOStr[]              = "Input/output error. Usually used "\
"for physical read or write errors.";
const char nErrDescNoDeviceStr[]        = "No such device or address. The "\
"system tried to use the device represented by a file you specified, and it "\
"couldn't find the device. This can mean that the device file was installed "\
"incorrectly, or that the physical device is missing or not correctly attached "\
"to the computer.";
const char nErrDescMaxArgsStr[]         = "Argument list too long. Used when "\
"the arguments passed to a new program being executed with one of the exec "\
"functions occupy too much memory space.";
const char nErrDescInvExecFormatStr[]   = "Exec format error. Invalid "\
"executable file format. This condition is detected by the exec functions.";
const char nErrDescInvFPStr[]           = "Bad file descriptor. For example, "\
"I/O on a descriptor that has been closed or reading from a descriptor open "\
"only for writing (or vice versa).";
const char nErrDescNoChildStr[]         = "No child process. This error "\
"happens on operations that are supposed to manipulate child processes, when "\
"there aren’t any processes to manipulate.";
const char nErrDescDeadlockStr[]        = "Resource deadlock avoided. This "\
"error happens on operations that are supposed to manipulate child "\
"processes, when there aren’t any processes to manipulate.";
const char nErrDescNoMemoryStr[]        = "Cannot allocate memory. The system "\
"cannot allocate more virtual memory because its capacity is full.";
const char nErrDescNoFilePermStr[]      = "Permission denied. The file "\
"permissions do not allow the attempted operation.";
const char nErrDescFaultStr[]           = "Bad address. An invalid pointer was "\
"detected.";
const char nErrDescNotBlockStr[]        = "Block device required. A file that "\
"isn’t a block special file was given in a situation that requires one. For "\
"example, trying to mount an ordinary file as a file system in Unix gives "\
"this error.";
const char nErrDescDeviceBusyStr[]      = "Device or resource busy. A system "\
"resource that can’t be shared is already in use. For example, if you try to "\
"delete a file that is the root of a currently mounted filesystem, you get "\
"this error.";
const char nErrDescFileExistsStr[]      = "File exists. An existing file was "\
"specified in a context where it only makes sense to specify a new file.";
const char nErrDescInvCrosslinkStr[]    = "Invalid cross-device link. An "\
"attempt to make an improper link across file systems was detected. This "\
"happens not only when you use link(), but also when you rename a file with "\
"rename().";
const char nErrDescInvDeviceStr[]       = "No such device. The wrong type of "\
"device was given to a function that expects a particular sort of device.";
const char nErrDescNotDirStr[]          = "Not a directory. A file that isn’t "\
"a directory was specified when a directory is required.";
const char nErrDescIsDirStr[]           = "Is a directory. You cannot open a "\
"directory for writing, or create or remove hard links to it.";
const char nErrDescInvArgStr[]          = "Invalid argument. This is used to "\
"indicate various kinds of problems with passing the wrong argument to a "\
"library function.";
const char nErrDescMaxFileStr[]         = "Too many open files. The current "\
"process has too many files open and can’t open any more. Duplicate "\
"descriptors do count toward this limit.";
const char nErrDescMaxFileSysStr[]      = "Too many open files in system. "\
"There are too many distinct file openings in the entire system. Note that any "\
"number of linked channels count as just one file opening.";
const char nErrDescInvIOCtlStr[]        = "Inappropriate ioctl for device. "\
"Inappropriate I/O control operation, such as trying to set terminal modes on "\
"an ordinary file.";
const char nErrDescTextBusyStr[]        = "Text file busy. An attempt to "\
"execute a file that is currently open for writing, or write to a file that is "\
"currently being executed. Often using a debugger to run a program is "\
"considered having it open for writing and will cause this error.";
const char nErrDescFileTooBigStr[]      = "File too large. The size of a file "\
"would be larger than allowed by the system.";
const char nErrDescNoSpaceStr[]         = "No space left on device. Write "\
"operation on a file failed because the disk is full.";
const char nErrDescInvSeekStr[]         = "Illegal seek. Invalid seek "\
"operation (such as on a pipe).";
const char nErrDescReadOnlyStr[]        = "Read-only file system. An attempt "\
"was made to modify something on a read-only file system.";
const char nErrDescMaxLinksStr[]        = "Too many links. The link count of a "\
"single file would become too large. rename() can cause this error if the file "\
"being renamed already has as many links as it can take";
const char nErrDescInvPipeStr[]         = "Broken pipe. There is no process "\
"reading from the other end of a pipe.";
const char nErrDescDomainStr[]          = "Numerical argument out of domain. "\
"Used by mathematical functions when an argument value does not fall into the "\
"domain over which the function is defined.";
const char nErrDescResultTooBigStr[]    = "Numerical result out of range. Used "\
"by mathematical functions when the result value is not representable because "\
"of overflow or underflow.";
const char nErrDescWouldBlockStr[]      = "Resource temporarily unavailable; "\
"Operation would block. The call might work if you try again later. This error "\
"can happen in a few different situations:\n"\
"1) An operation that would block was attempted on an object that has "\
"non-blocking mode selected. Trying the same operation again will block until "\
"some external condition makes it possible to read, write, or connect "\
"(whatever the operation). You can use select() to find out when the operation "\
"will be possible.\n"\
"2) A temporary resource shortage made an operation impossible. fork() can "\
"return this error. It indicates that the shortage is expected to pass, so "\
"your program can try the call again later and it may succeed. It is probably "\
"a good idea to delay for a few seconds before trying it again, to allow time "\
"for other processes to release scarce resources. Such shortages are usually "\
"fairly serious and affect the whole system, so usually an interactive program "\
"should report the error to the user and return to its command loop.";
const char nErrDescInProgressStr[]      = "Operation now in progress. An "\
"operation that cannot complete immediately was initiated on an object that "\
"has non-blocking mode selected. Some functions that must always block (such "\
"as connect()) never return EAGAIN. Instead, they return EINPROGRESS to "\
"indicate that the operation has begun and will take some time. Attempts to "\
"manipulate the object before the call completes return EALREADY. You can use "\
"the select function to find out when the pending operation has completed.";

const char nErrDescMaxStr[]             = "The maximum error value, likely "\
"caused by programmer error or a corruption issue.";


const char * nErrorDescriptions[] = {
    nErrDescMinStr,
    
    nErrDescUnknownStr,
    nErrDescInternalFailureStr,
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
    nErrDescNoChildStr,
    nErrDescDeadlockStr,
    nErrDescNoMemoryStr,
    nErrDescNoFilePermStr,
    nErrDescFaultStr,
    nErrDescNotBlockStr,
    nErrDescDeviceBusyStr,
    nErrDescFileExistsStr,
    nErrDescInvCrosslinkStr,
    nErrDescInvDeviceStr,
    nErrDescNotDirStr,
    nErrDescIsDirStr,
    nErrDescInvArgStr,
    nErrDescMaxFileStr,
    nErrDescMaxFileSysStr,
    nErrDescInvIOCtlStr,
    nErrDescTextBusyStr,
    nErrDescFileTooBigStr,
    nErrDescNoSpaceStr,
    nErrDescInvSeekStr,
    nErrDescReadOnlyStr,
    nErrDescMaxLinksStr,
    nErrDescInvPipeStr,
    nErrDescDomainStr,
    nErrDescResultTooBigStr,
    nErrDescWouldBlockStr,
    nErrDescInProgressStr,
    
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
    sizeof(nErrDescNoChildStr),
    sizeof(nErrDescDeadlockStr),
    sizeof(nErrDescNoMemoryStr),
    sizeof(nErrDescNoFilePermStr),
    sizeof(nErrDescFaultStr),
    sizeof(nErrDescNotBlockStr),
    sizeof(nErrDescDeviceBusyStr),
    sizeof(nErrDescFileExistsStr),
    sizeof(nErrDescInvCrosslinkStr),
    sizeof(nErrDescInvDeviceStr),
    sizeof(nErrDescNotDirStr),
    sizeof(nErrDescIsDirStr),
    sizeof(nErrDescInvArgStr),
    sizeof(nErrDescMaxFileStr),
    sizeof(nErrDescMaxFileSysStr),
    sizeof(nErrDescInvIOCtlStr),
    sizeof(nErrDescTextBusyStr),
    sizeof(nErrDescFileTooBigStr),
    sizeof(nErrDescNoSpaceStr),
    sizeof(nErrDescInvSeekStr),
    sizeof(nErrDescReadOnlyStr),
    sizeof(nErrDescMaxLinksStr),
    sizeof(nErrDescInvPipeStr),
    sizeof(nErrDescDomainStr),
    sizeof(nErrDescResultTooBigStr),
    sizeof(nErrDescWouldBlockStr),
    sizeof(nErrDescInProgressStr),
    
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
        #if defined(EDEADLK) || defined(EDEADLOCK)
        #ifdef EDEADLK
        case EDEAKLK:
        #endif
        #ifdef EDEADLOCK
        case EDEADLOCK:
        #endif
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
        #ifdef ETXTBSY
        case ETXTBSY:
        {
            return NERROR_TEXT_BUSY;
        }
        break;
        #endif
        #ifdef EFBIG
        case EFBIG:
        {
            return NERROR_FILE_TOO_BIG;
        }
        break;
        #endif
        #ifdef ENOSPC
        case ENOSPC:
        {
            return NERROR_NO_SPACE;
        }
        break;
        #endif
        #ifdef ESPIPE
        case ESPIPE:
        {
            return NERROR_INV_SEEK;
        }
        break;
        #endif
        #ifdef EROFS
        case EROFS:
        {
            return NERROR_READ_ONLY;
        }
        break;
        #endif
        #ifdef EMLINK
        case EMLINK:
        {
            return NERROR_MAX_LINKS;
        }
        break;
        #endif
        #ifdef EPIPE
        case EPIPE:
        {
            return NERROR_INV_PIPE;
        }
        break;
        #endif
        #ifdef EDOM
        case EDOM:
        {
            return NERROR_DOMAIN;
        }
        break;
        #endif
        #ifdef ERANGE
        case ERANGE:
        {
            return NERROR_RESULT_TOO_BIG;
        }
        break;
        #endif
        #if defined(EAGAIN) || defined(EWOULDBLOCK)
        #ifdef EAGAIN
        case EAGAIN:
        #endif
        #ifdef EWOULDBLOCK
        case EWOULDBLOCK:
        #endif
        {
            return NERROR_WOULD_BLOCK;
        }
        break;
        #endif
        #ifdef EINPROGRESS
        case EINPROGRESS:
        {
            return NERROR_IN_PROGRESS;
        }
        break;
        #endif
        #ifdef EALREADY
        case EALREADY:
        {
            return NERROR_ALREADY;
        }
        break;
        #endif
        #ifdef ENOTSOCK
        case ENOTSOCK:
        {
            return NERROR_NOT_SOCKET;
        }
        break;
        #endif
        #ifdef EMSGSIZE
        case EMSGSIZE:
        {
            return NERROR_MAX_MESSAGE;
        }
        break;
        #endif
        #ifdef EPROTOTYPE
        case EPROTOTYPE:
        {
            return NERROR_INV_PROTO_TYPE;
        }
        break;
        #endif
        #ifdef ENOPROTOOPT
        case ENOPROTOOPT:
        {
            return NERROR_INV_PROTO_OPT;
        }
        break;
        #endif
        #ifdef EPROTONOSUPPORT
        case EPROTONOSUPPORT:
        {
            return NERROR_INV_PROTOCOL;
        }
        break;
        #endif
        #ifdef ESOCKTNOSUPPORT
        case ESOCKTNOSUPPORT:
        {
            return NERROR_INV_SOCK_TYPE;
        }
        break;
        #endif
        #ifdef EOPNOTSUPP
        case EOPNOTSUPP:
        {
            return NERROR_INV_SOCK_OPR;
        }
        break;
        #endif
        #ifdef EPFNOSUPPORT
        case EPFNOSUPPORT:
        {
            return NERROR_INV_ADDR_FAM;
        }
        break;
        #endif
        #ifdef EADDRINUSE
        case EADDRINUSE:
        {
            return NERROR_ADDR_IN_USE;
        }
        break;
        #endif
        #ifdef EADDRNOTAVAIL
        case EADDRNOTAVAIL:
        {
            return NERROR_ADDR_NOT_AVAILABLE;
        }
        break;
        #endif
        #ifdef ENETDOWN
        case ENETDOWN:
        {
            return NERROR_NET_DOWN;
        }
        break;
        #endif
        #ifdef ENETUNREACH:
        case ENETUNREACH:
        {
            return NERROR_NET_UNREACHABLE;
        }
        break;
        #endif
        #ifdef ENETRESET
        case ENETRESET:
        {
            return NERROR_NET_RESET;
        }
        break;
        #endif
        #ifdef ECONNABORTED
        case ECONNABORTED:
        {
            return NERROR_CONN_ABORTED;
        }
        break;
        #endif
        #ifdef ECONNRESET
        case ECONNRESET:
        {
            return NERROR_CONN_RESET;
        }
        break;
        #endif
        #ifdef ENOBUFS
        case ENOBUFS:
        {
            return NERROR_NO_BUFFER_SPACE;
        }
        break;
        #endif
        #ifdef EISCONN
        case EISCONN:
        {
            return NERROR_ALREADY_CONN;
        }
        break;
        #endif
        #ifdef ENOTCONN
        case ENOTCONN:
        {
            return NERROR_NOT_CONN;
        }
        break;
        #endif
        #ifdef EDESTADDRREQ
        case EDESTADDRREQ:
        {
            return NERROR_NO_ADDR;
        }
        break;
        #endif
        #ifdef ESHUTDOWN
        case ESHUTDOWN:
        {
            return NERROR_SOCK_SHUTDOWN;
        }
        break;
        #endif
        #ifdef ETOOMANYREFS
        case ETOOMANYREFS:
        {
            return NERROR_MAX_REFS;
        }
        break;
        #endif
        #ifdef ETIMEDOUT
        case ETIMEDOUT:
        {
            return NERROR_CONN_TIMEOUT;
        }
        break;
        #endif
        #ifdef ECONNREFUSED
        case ECONNREFUSED:
        {
            return NERROR_CONN_REFUSED;
        }
        break;
        #endif
        #ifdef ELOOP
        case ELOOP:
        {
            return NERROR_LINK_LOOP;
        }
        break;
        #endif
        #ifdef ENAMETOOLONG
        case ENAMETOOLONG:
        {
            return NERROR_MAX_FILENAME;
        }
        break;
        #endif
        #ifdef EHOSTDOWN
        case EHOSTDOWN:
        {
            return NERROR_HOST_DOWN;
        }
        break;
        #endif
        #ifdef EHOSTUNREACH
        case EHOSTUNREACH:
        {
            return NERROR_HOST_UNREACHABLE;
        }
        break;
        #endif
        #ifdef ENOTEMPTY
        case ENOTEMPTY:
        {
            return NERROR_DIR_NOT_EMPTY;
        }
        break;
        #endif
        #ifdef EPROCLIM
        case EPROCLIM:
        {
            return NERROR_MAX_PROCESS;
        }
        break;
        #endif
        #ifdef EUSERS
        case EUSERS:
        {
            return NERROR_MAX_USERS;
        }
        break;
        #endif
        #ifdef EDQUOT
        case EDQUOT:
        {
            return NERROR_MAX_DISK_QUOTA;
        }
        break;
        #endif
        #ifdef ESTALE
        case ESTALE:
        {
            return NERROR_STALE;
        }
        break;
        #endif
        #ifdef EREMOTE
        case EREMOTE:
        {
            return NERROR_REMOTE;
        }
        break;
        #endif
        #ifdef EBADRPC
        case EBADRPC:
        {
            return NERROR_INV_RPC;
        }
        break;
        #endif
        #ifdef ERPCMISMATCH
        case ERPCMISMATCH:
        {
            return NERROR_INV_RPC_VERSION;
        }
        break;
        #endif
        #ifdef EPROGUNAVAIL
        case EPROGUNAVAIL:
        {
            return NERROR_INV_RPC_PROG;
        }
        break;
        #endif
        #ifdef EPROGMISMATCH
        case EPROGMISMATCH:
        {
            return NERROR_INV_RPC_PROG_VERSION;
        }
        break;
        #endif
        #ifdef EPROCUNAVAIL
        case EPROCUNAVAIL:
        {
            return NERROR_INV_RPC_PROC;
        }
        break;
        #endif
        #ifdef ENOLOCK
        case ENOLOCK:
        {
            return NERROR_NO_FILE_LOCK;
        }
        break;
        #endif
        #ifdef EFTYPE
        case EFTYPE:
        {
            return NERROR_INV_FILE_TYPE;
        }
        break;
        #endif
        #ifdef EAUTH
        case EAUTH:
        {
            return NERROR_AUTH;
        }
        break;
        #endif
        #ifdef ENEEDAUTH
        case ENEEDAUTH:
        {
            return NERROR_NEED_AUTH;
        }
        break;
        #endif
        #ifdef ENOSYS
        case ENOSYS:
        {
            return NERROR_FUNC_NOT_SUPPORTED;
        }
        break;
        #endif
        #ifdef ENOTSUP
        case ENOTSUP:
        {
            return NERROR_NOT_SUPPORTED;
        }
        break;
        #endif
        #ifdef EILSEQ
        case EILSEQ:
        {
            return NERROR_INV_MULTIBYTE;
        }
        break;
        #endif
        #ifdef EBACKGROUND
        case EBACKGROUND:
        {
            return NERROR_INV_BACKGROUND;
        }
        break;
        #endif
        #ifdef EDIED
        case EDIED:
        {
            return NERROR_TRANSLATOR_DIED;
        }
        break;
        #endif
        #if defined(ED) || defined(EGREGIOUS) || defined(EIEIO) || defined(EGRATUITOUS)
        #ifdef ED
        case ED:
        #endif
        #ifdef EGREGIOUS
        case EGREGIOUS:
        #endif
        #ifdef EIEIO:
        case EIEIO:
        #endif
        #ifdef EGRATUITOUS
        case EGRATUITOUS:
        #endif
        {
            return NERROR_JOKE;
        }
        break;
        #endif
        #ifdef EBADMSG
        case EBADMSG:
        {
            return NERROR_INV_MESSAGE;
        }
        break;
        #endif
        #ifdef EIDRM
        case EIDRM:
        {
            return NERROR_NO_IDENTIFIER;
        }
        break;
        #endif
        #ifdef EMULTIHOP
        case EMULTIHOP:
        {
            return NERROR_MULTIHOP;
        }
        break;
        #endif
        #ifdef ENODATA
        case ENODATA:
        {
            return NERROR_NO_DATA;
        }
        break;
        #endif
        #ifdef ENOLINK
        case ENOLINK:
        {
            return NERROR_NO_LINK;
        }
        break;
        #endif
        #ifdef ENOMSG
        case ENOMSG:
        {
            return NERROR_NO_MESSAGE;
        }
        break;
        #endif
        #ifdef ENOSR
        case ENOSR:
        {
            return NERROR_NO_STREAM_RESOURCES;
        }
        break;
        #endif
        #ifdef ENOSTR
        case ENOSTR:
        {
            return NERROR_DEVICE_NOT_STREAM;
        }
        break;
        #endif
        #ifdef EOVERFLOW
        case EOVERFLOW:
        {
            return NERROR_OVERFLOW;
        }
        break;
        #endif
        #ifdef EPROTO
        case EPROTO:
        {
            return NERROR_PROTOCOL;
        }
        break;
        #endif
        #ifdef ETIME
        case ETIME:
        {
            return NERROR_TIMER;
        }
        break;
        #endif
        #ifdef ECANCELED
        case ECANCELED:
        {
            return NERROR_ASYNC_CANCEL;
        }
        break;
        #endif
        #ifdef EOWNERDEAD
        case EOWNERDEAD:
        {
            return NERROR_OWNED_DIED;
        }
        break;
        #endif
        #ifdef ENOTRECOVERABLE
        case ENOTRECOVERABLE:
        {
            return NERROR_NOT_RECOVERABLE;
        }
        break;
        #endif
        #ifdef ERESTART
        case ERESTART:
        {
            return NERROR_SYSCALL_RESTART;
        }
        break;
        #endif
        #ifdef ECHRNG
        case ECHRNG:
        {
            return NERROR_CHANNEL_RANGE;
        }
        break;
        #endif
        #ifdef EL2NSYNC
        case EL2NSYNC:
        {
            return NERROR_LVL2_NOT_SYNC;
        }
        break;
        #endif
        #ifdef EL3HLT
        case EL3HLT:
        {
            return NERROR_LVL3_HAULT;
        }
        break;
        #endif
        #ifdef EL3RST
        case EL3RST:
        {
            return NERROR_LVL3_RESET;
        }
        break;
        #endif
        #ifdef ELNRNG
        case ELNRNG:
        {
            return NERROR_LINK_RANGE;
        }
        break;
        #endif
        #ifdef EUNATCH
        case EUNATCH:
        {
            return NERROR_PROTO_UNATTACHED;
        }
        break;
        #endif
        #ifdef ENOCSI
        case ENOCSI:
        {
            return NERROR_NO_CSI;
        }
        break;
        #endif
        #ifdef EL2HLT
        case EL2HLT:
        {
            return NERROR_LVL2_HAULT;
        }
        break;
        #endif
        #ifdef EBADE
        case EBADE:
        {
            return NERROR_INV_EXCHANGE;
        }
        break;
        #endif
        #ifdef EBADR
        case EBADR:
        {
            return NERROR_INV_REQUEST_DESCRIPTOR;
        }
        break;
        #endif
        #ifdef EXFULL
        case EXFULL:
        {
            return NERROR_EXCHANGE_FULL;
        }
        break;
        #endif
        #ifdef ENOANO
        case ENOANO:
        {
            return NERROR_NO_ANODE;
        }
        break;
        #endif
        #ifdef EBADRQC
        case EBADRQC:
        {
            return NERROR_INV_REQUEST_CODE;
        }
        break;
        #endif
        #ifdef EBADSLT
        case EBADSLT:
        {
            return NERROR_INV_SLOT;
        }
        break;
        #endif
        #ifdef EBFONT
        case EBFONT:
        {
            return NERROR_INV_FONT_FORMAT;
        }
        break;
        #endif
        #ifdef ENONET
        case ENONET:
        {
            return NERROR_NO_NET;
        }
        break;
        #endif
        #ifdef ENOPKG
        case ENOPKG:
        {
            return NERROR_NO_PACKAGE;
        }
        break;
        #endif
        #ifdef EADV
        case EADV:
        {
            return NERROR_ADVERTISE;
        }
        break;
        #endif
        #ifdef ESRMNT
        case ESRMNT:
        {
            return NERROR_SRMOUNT;
        }
        break;
        #endif
        #ifdef ECOMM
        case ECOMM:
        {
            return NERROR_COMM;
        }
        break;
        #endif
        #ifdef EDOTDOT
        case EDOTDOT:
        {
            return NERROR_RFS_DOTDOT;
        }
        break;
        #endif
        #ifdef ENOTUNIQ
        case ENOTUNIQ:
        {
            return NERROR_NAME_NOT_UNIQUE;
        }
        break;
        #endif
        #ifdef EBADFD
        case EBADFD:
        {
            return NERROR_INV_FILE_DESCRIPTOR;
        }
        break;
        #endif
        #ifdef EREMCHG
        case EREMCHG:
        {
            return NERROR_REMOTE_ADDR_CHANGED;
        }
        break;
        #endif
        #ifdef ELIBACC
        case ELIBACC:
        {
            return NERROR_NO_LIB_ACCESS;
        }
        break;
        #endif
        #ifdef ELIBBAD
        case ELIBBAD:
        {
            return NERROR_INV_LIB;
        }
        break;
        #endif
        #ifdef ELIBSCN
        case ELIBSCN:
        {
            return NERROR_INV_LIB_SECTION;
        }
        break;
        #endif
        #ifdef ELIBMAX
        case ELIBMAX:
        {
            return NERROR_MAX_LIB;
        }
        break;
        #endif
        #ifdef ELIBEXEC
        case ELIBEXEC:
        {
            return NERROR_EXEC_LIB;
        }
        break;
        #endif
        #ifdef ESTRPIPE
        case ESTRPIPE:
        {
            return NERROR_STREAM_PIPE;
        }
        break;
        #endif
        #ifdef EUCLEAN
        case EUCLEAN:
        {
            return NERROR_STRUCT_CLEAN;
        }
        break;
        #endif
        #ifdef ENOTNAM
        case ENOTNAM:
        {
            return NERROR_NOT_TYPE_FILE;
        }
        break;
        #endif
        #ifdef ENAVAIL
        case ENAVAIL:
        {
            return NERROR_NO_SEMAPHORES;
        }
        break;
        #endif
        #ifdef EISNAM
        case EISNAM:
        {
            return NERROR_TYPE_FILE;
        }
        break;
        #endif
        #ifdef EREMOTEIO
        case EREMOTEIO:
        {
            return NERROR_REMOTE_IO;
        }
        break;
        #endif
        #ifdef ENOMEDIUM
        case ENOMEDIUM:
        {
            return NERROR_NO_MEDIUM;
        }
        break;
        #endif
        #ifdef EMEDIUMTYPE
        case EMEDIUMTYPE:
        {
            return NERROR_INV_MEDIUM_TYPE;
        }
        break;
        #endif
        #ifdef ENOKEY
        case ENOKEY:
        {
            return NERROR_NO_KEY;
        }
        break;
        #endif
        #ifdef EKEYEXPIRED
        case EKEYEXPIRED:
        {
            return NERROR_KEY_EXPIRED;
        }
        break;
        #endif
        #ifdef EKEYREVOKED
        case EKEYREVOKED:
        {
            return NERROR_KEY_REVOKED;
        }
        break;
        #endif
        #ifdef EKEYREJECTED
        case EKEYREJECTED:
        {
            return NERROR_KEY_REJECTED;
        }
        break;
        #endif
        #ifdef ERFKILL
        case ERFKILL:
        {
            return NERROR_RF_KILL;
        }
        break;
        #endif
        #ifdef EHWPOISON
        case EHWPOISON:
        {
            return NERROR_MEM_HARDWARE;
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
    
    const char * errorDesc = nErrorDesc(error);
    
    if (errorDesc == NULL)
    {
        
        if (errorLen != NULL)
        {
            *errorLen = 0;
        }
        
        dst = nFree(dst);
        return NERROR_INV_ERROR;
    }
    
    const nint_t descLen = nErrorDescLen(error);
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
