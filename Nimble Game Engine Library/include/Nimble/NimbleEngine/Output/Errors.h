#include "../../NimbleLicense.h"
/*
 * Errors.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-14.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Errors.h
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
 * @date 2020-08-14
 *
 * @brief This class defines error values and error handling functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_ERRORS_H
#define NIMBLE_ENGINE_ERRORS_H /**< Header definition */

#include "../../NimbleEngine.h"

#include <inttypes.h>
#include <limits.h>
#include <time.h>

#define NSUCCESS (nint_t) 0 /**< Returned when a function succeeds. */
#define NERROR (nint_t) -1 /**< Returned when a function encounters an error. */

/**
 * @brief The possible error values used by ErrorHandler.h error handler.
 *
 * @note For more detailed info on an error, see the error descriptions in
 * Errors.c (#nErrorDescriptions).
 */
enum nErrors {
    NERROR_MIN = 0, /**< The mininum error number. */
    
    NERROR_UNKNOWN, /**< An nknown error occurred. */
    NERROR_INTERNAL_FAILURE, /**< An internal error occurred. */
    NERROR_NULL, /**< A pointer was null when a nonnull pointer was expected. */
    NERROR_INV_ERROR, /**< An error passed to a function was not valid. */
    
    NERROR_SIGNAL_START, /**< The start of the signal section. */
    NERROR_SIGABRT, /**< Caught abort signal. */
    NERROR_SIGFPE, /**< Caught floating point exception signal. */
    NERROR_SIGILL, /**< Caught illegal expression signal. */
    NERROR_SIGINT, /**< Caught interrupt signal. */
    NERROR_SIGSEGV, /**< Caught memory address violation signal. */
    NERROR_SIGTERM, /**< Caught termination signal. */
    NERROR_SIGNAL_END, /**< The end of the signal section. */
    
    NERROR_ERRNO_START, /**< The start of the errno section. */
    #if 0 /* Possible values */
    /* (IEEE and POSIX, please standardize the error values for goodness
     * sake, OS devs please follow said standard. It has taken me 20+ hours
     * to make a 2,000 line portable equivalent of:
     * return (NERROR_ERRNO_START + error);
     */
    NERROR_NO_PERM = EPERM, /**< Operation not permitted. */
    NERROR_NO_FILE = ENOENT, /**< No such file or directory. */
    NERROR_NO_PROCESS = ESRCH, /**< No such process. */
    NERROR_INTERRUPT = EINTR, /**< Interrupted system call. */
    NERROR_IO = EIO, /**< Input/output error. */
    NERROR_NO_DEVICE = ENXIO, /**< No such device or address. */
    NERROR_MAX_ARGS = E2BIG, /**< Argument list too long. */
    NERROR_INV_EXEC_FORMAT = ENOEXEC, /**< Exec format error. */
    NERROR_INV_FP = EBADF, /**< Bad file descriptor. */
    NERROR_NO_CHILD = ECHILD, /**< No child process. */
    NERROR_DEADLOCK = EDEADLK, /**< Resource deadlock avoided. */
    NERROR_NO_MEMORY = ENOMEM, /**< Cannot allocate memory. */
    NERROR_NO_FILE_PERM = EACCES, /**< Permission denied. */
    NERROR_FAULT = EFAULT, /**< Bad address. */
    NERROR_NOT_BLOCK = ENOTBLK, /**< Block device required. */
    NERROR_DEVICE_BUSY = EBUSY, /**< Device or resource busy. */
    NERROR_FILE_EXISTS = EEXIST, /**< File exists. */
    NERROR_INV_CROSSLINK = EXDEV, /**< Invalid cross-device link. */
    NERROR_INV_DEVICE = ENODEV, /**< No such device. */
    NERROR_NOT_DIR = ENOTDIR, /**< Not a directory. */
    NERROR_IS_DIR = EISDIR, /**< Is a directory. */
    NERROR_INV_ARG = EINVAL, /**< Invalid argument. */
    NERROR_MAX_FILE = EMFILE, /**< Too many open files. */
    NERROR_MAX_FILE_SYS = ENFILE, /**< Too many open files in system. */
    NERROR_INV_IOCTL = ENOTTY, /**< Inappropriate ioctl for device. */
    NERROR_TEXT_BUSY = ETXTBSY, /**< Text file busy. */
    NERROR_FILE_TOO_BIG = EFBIG, /**< File too large. */
    NERROR_NO_SPACE = ENOSPC, /**< No space left on device. */
    NERROR_INV_SEEK = ESPIPE, /**< Illegal seek. */
    NERROR_READ_ONLY = EROFS, /**< Read-only file system. */
    NERROR_MAX_LINKS = EMLINK, /**< Too many links. */
    NERROR_INV_PIPE = EPIPE, /**< Broken pipe. */
    NERROR_DOMAIN = EDOM, /**< Numerical argument out of domain. */
    NERROR_RESULT_TOO_BIG = ERANGE, /**< Numerical result out of range. */
    NERROR_WOULD_BLOCK = (EAGAIN & EWOULDBLOCK), /**< Resource temporarily unavailable; Operation would block. */
    NERROR_IN_PROGRESS = EINPROGRESS, /**< Operation now in progress. */
    NERROR_ALREADY = EALREADY, /**< Operation already in progress. */
    NERROR_NOT_SOCKET = ENOTSOCK, /**< Socket operation on non-socket. */
    NERROR_MAX_MESSAGE = EMSGSIZE, /**< Message too long. */
    NERROR_INV_PROTO_TYPE = EPROTOTYPE, /**< Protocol wrong type for socket. */
    NERROR_INV_PROTO_OPT = ENOPROTOOPT, /**< Protocol not available. */
    NERROR_INV_PROTOCOL = EPROTONOSUPPORT, /**< Protocol not supported. */
    NERROR_INV_SOCK_TYPE = ESOCKTNOSUPPORT, /**< Socket type not supported. */
    NERROR_INV_SOCK_OPR = EOPNOTSUPP, /**< Operation not supported. */
    NERROR_INV_PROTO_FAM = EPFNOSUPPORT, /**< Protocol family not supported. */
    NERROR_INV_ADDR_FAM = EAFNOSUPPORT, /**< Address family not supported by protocol. */
    NERROR_ADDR_IN_USE = EADDRINUSE, /**< Address already in use. */
    NERROR_ADDR_NOT_AVAILABLE = EADDRNOTAVAIL, /**< Cannot assign requested address. */
    NERROR_NET_DOWN = ENETDOWN, /**< Network is down. */
    NERROR_NET_UNREACHABLE = ENETUNREACH, /**< Network is unreachable. */
    NERROR_NET_RESET = ENETRESET, /**< Network dropped connection on reset. */
    NERROR_CONN_ABORTED = ECONNABORTED, /**< Software caused connection abort. */
    NERROR_CONN_RESET = ECONNRESET, /**< Connection reset by peer. */
    NERROR_NO_BUFFER_SPACE = ENOBUFS, /**< No buffer space available. */
    NERROR_ALREADY_CONN = EISCONN, /**< Transport endpoint is already connected. */
    NERROR_NOT_CONN = ENOTCONN, /**< Transport endpoint is not connected. */
    NERROR_NO_ADDR = EDESTADDRREQ, /**< Destination address required. */
    NERROR_SOCK_SHUTDOWN = ESHUTDOWN, /**< Cannot send after transport endpoint shutdown. */
    NERROR_MAX_REFS = ETOOMANYREFS, /**< Too many references: cannot splice. */
    NERROR_CONN_TIMEOUT = ETIMEDOUT, /**< Connection timed out. */
    NERROR_CONN_REFUSED = ECONNREFUSED, /**< Connection refused. */
    NERROR_LINK_LOOP = ELOOP, /**< Too many levels of symbolic links. */
    NERROR_MAX_FILENAME = ENAMETOOLONG, /**< File name too long. */
    NERROR_HOST_DOWN = EHOSTDOWN, /**< Host is down. */
    NERROR_HOST_UNREACHABLE = EHOSTUNREACH, /**< No route to host. */
    NERROR_DIR_NOT_EMPTY = ENOTEMPTY, /**< Directory not empty. */
    NERROR_MAX_PROCESS = EPROCLIM, /**< Too many processes. */
    NERROR_MAX_USERS = EUSERS, /**< Too many users. */
    NERROR_MAX_DISK_QUOTA = EDQUOT, /**< Disk quota exceeded. */
    NERROR_STALE = ESTALE, /**< Stale file handle. */
    NERROR_REMOTE = EREMOTE, /**< Object is remote. */
    NERROR_INV_RPC = EBADRPC, /**< RPC struct is bad. */
    NERROR_INV_RPC_VERSION = ERPCMISMATCH, /**< RPC version wrong. */
    NERROR_INV_RPC_PROG = EPROGUNAVAIL, /**< RPC program not available. */
    NERROR_INV_RPC_PROG_VERSION = EPROGMISMATCH, /**< RPC program version wrong. */
    NERROR_INV_RPC_PROC = EPROCUNAVAIL, /**< RPC bad procedure for program. */
    NERROR_NO_FILE_LOCK = ENOLCK, /**< No locks available. */
    NERROR_INV_FILE_TYPE = EFTYPE, /**< Inappropriate file type or format. */
    NERROR_AUTH = EAUTH, /**< Authentication error. */
    NERROR_NO_AUTH = ENEEDAUTH, /**< Need authenticator. */
    NERROR_FUNC_NOT_SUPPORTED = ENOSYS, /**< Function not implemented. */
    NERROR_NOT_SUPPORTED = ENOTSUP, /**< Not supported. */
    NERROR_INV_MULTIBYTE = EILSEQ, /**< Invalid or incomplete multibyte or wide character. */
    NERROR_INV_BACKGROUND = EBACKGROUND, /**< Inappropriate operation for background process. */
    NERROR_TRANSLATOR_DIED = EDIED, /**< Translator died. */
    NERROR_JOKE = (ED & EGREGIOUS & EIEIO & EGRATUITOUS), /**< You really blew it this time. */
    NERROR_INV_MESSAGE = EBADMSG, /**< Bad message. */
    NERROR_NO_IDENTIFIER = EIDRM, /**< Identifier removed. */
    NERROR_MULTIHOP = EMULTIHOP, /**< Multihop attempted. */
    NERROR_NO_DATA = ENODATA, /**< No data available. */
    NERROR_NO_LINK = ENOLINK, /**< Link has been severed. */
    NERROR_NO_MESSAGE = ENOMSG, /**< No message of desired type. */
    NERROR_NO_STREAM_RESOURCES = ENOSR, /**< Out of streams resources. */
    NERROR_DEVICE_NOT_STREAM = ENOSTR, /**< Device not a stream. */
    NERROR_OVERFLOW = EOVERFLOW, /**< Value too large for defined data type. */
    NERROR_PROTOCOL = EPROTO, /**< Protocol error. */
    NERROR_TIMER = ETIME, /**< Timer expired. */
    NERROR_ASYNC_CANCEL = ECANCELED, /**< Operation canceled. */
    NERROR_OWNER_DIED = EOWNERDEAD, /**< Owner died. */
    NERROR_NOT_RECOVERABLE = ENOTRECOVERABLE, /**< State not recoverable. */
    NERROR_DEVICE_OFF = EPWROFF, /**< Device power is off. */
    NERROR_DEVICE_ERROR = EDEVERR, /**< Device error, e.g. paper out. */
    NERROR_INV_EXECUTABLE = EBADEXEC, /**< Bad executable. */
    NERROR_INV_ARCHITECTURE = EBADARCH, /**< Bad CPU type in executable. */
    NERROR_INV_LIB_VERSION = ESHLIBVERS, /**< Shared library version mismatch. */
    NERROR_INV_MACHO = EBADMACHO, /**< Malformed Macho file. */
    NERROR_NO_ATTRIBUTE = ENOATTR, /**< Attribute not found. */
    NERROR_NO_POLICY = ENOPOLICY, /**< No such policy registered. */
    NERROR_MAX_QUEUE = EQFULL, /**< Interface output queue is full. */
    #endif
    #if NIMBLE_OS == NIMBLE_WINDOWS
    NERROR_NO_PERM, /**< Operation not permitted. */
    NERROR_NO_FILE, /**< No such file or directory. */
    NERROR_NO_PROCESS, /**< No such process. */
    NERROR_INTERRUPT, /**< Interrupted system call. */
    NERROR_IO, /**< Input/output error. */
    NERROR_NO_DEVICE, /**< No such device or address. */
    NERROR_MAX_ARGS, /**< Argument list too long. */
    NERROR_INV_EXEC_FORMAT, /**< Exec format error. */
    NERROR_INV_FP, /**< Bad file descriptor. */
    NERROR_NO_CHILD, /**< No child process. */
    NERROR_WOULD_BLOCK, /**< Resource temporarily unavailable; Operation would block. */
    NERROR_NO_MEMORY, /**< Cannot allocate memory. */
    NERROR_NO_FILE_PERM, /**< Permission denied. */
    NERROR_FAULT, /**< Bad address. */
    /* 15 */
    NERROR_DEVICE_BUSY, /**< Device or resource busy. */
    NERROR_FILE_EXISTS, /**< File exists. */
    NERROR_INV_CROSSLINK, /**< Invalid cross-device link. */
    NERROR_INV_DEVICE, /**< No such device. */
    NERROR_NOT_DIR, /**< Not a directory. */
    NERROR_IS_DIR, /**< Is a directory. */
    NERROR_INV_ARG, /**< Invalid argument. */
    NERROR_MAX_FILE_SYS, /**< Too many open files in system. */
    NERROR_MAX_FILE, /**< Too many open files. */
    NERROR_INV_IOCTL, /**< Inappropriate ioctl for device. */
    /* 26 */
    NERROR_FILE_TOO_BIG, /**< File too large. */
    NERROR_NO_SPACE, /**< No space left on device. */
    NERROR_INV_SEEK, /**< Illegal seek. */
    NERROR_READ_ONLY, /**< Read-only file system. */
    NERROR_MAX_LINKS, /**< Too many links. */
    NERROR_INV_PIPE, /**< Broken pipe. */
    NERROR_DOMAIN, /**< Numerical argument out of domain. */
    NERROR_RESULT_TOO_BIG, /**< Numerical result out of range. */
    /* 35 */
    NERROR_DEADLOCK, /**< Resource deadlock avoided. */
    /* 37 */
    NERROR_MAX_FILENAME, /**< File name too long. */
    NERROR_NO_FILE_LOCK, /**< No locks available. */
    NERROR_FUNC_NOT_SUPPORTED, /**< Function not implemented. */
    NERROR_DIR_NOT_EMPTY, /**< Directory not empty. */
    NERROR_INV_MULTIBYTE, /**< Invalid or incomplete multibyte or wide character. */
    /* 43-99 */
    NERROR_ADDR_IN_USE, /**< Address already in use. */
    NERROR_ADDR_NOT_AVAILABLE, /**< Cannot assign requested address. */
    NERROR_INV_ADDR_FAM, /**< Address family not supported by protocol. */
    NERROR_ALREADY, /**< Operation already in progress. */
    NERROR_INV_MESSAGE, /**< Bad message. */
    NERROR_ASYNC_CANCEL, /**< Operation canceled. */
    NERROR_CONN_ABORTED, /**< Software caused connection abort. */
    NERROR_CONN_REFUSED, /**< Connection refused. */
    NERROR_CONN_RESET, /**< Connection reset by peer. */
    NERROR_NO_ADDR, /**< Destination address required. */
    NERROR_HOST_UNREACHABLE, /**< No route to host. */
    NERROR_NO_IDENTIFIER, /**< Identifier removed. */
    NERROR_IN_PROGRESS, /**< Operation now in progress. */
    NERROR_ALREADY_CONN, /**< Transport endpoint is already connected. */
    NERROR_LINK_LOOP, /**< Too many levels of symbolic links. */
    NERROR_MAX_MESSAGE, /**< Message too long. */
    NERROR_NET_DOWN, /**< Network is down. */
    NERROR_NET_RESET, /**< Network dropped connection on reset. */
    NERROR_NET_UNREACHABLE, /**< Network is unreachable. */
    NERROR_NO_BUFFER_SPACE, /**< No buffer space available. */
    NERROR_NO_DATA, /**< No data available. */
    NERROR_NO_LINK, /**< Link has been severed. */
    NERROR_NO_MESSAGE, /**< No message of desired type. */
    NERROR_INV_PROTO_OPT, /**< Protocol not available. */
    NERROR_NO_STREAM_RESOURCES, /**< Out of streams resources. */
    NERROR_DEVICE_NOT_STREAM, /**< Device not a stream. */
    NERROR_NOT_CONN, /**< Transport endpoint is not connected. */
    NERROR_NOT_RECOVERABLE, /**< State not recoverable. */
    NERROR_NOT_SOCKET, /**< Socket operation on non-socket. */
    NERROR_NOT_SUPPORTED, /**< Not supported. */
    NERROR_INV_SOCK_OPR, /**< Operation not supported. */
    /* 131 */
    NERROR_OVERFLOW, /**< Value too large for defined data type. */
    NERROR_OWNER_DIED, /**< Owner died. */
    NERROR_PROTOCOL, /**< Protocol error. */
    NERROR_INV_PROTOCOL, /**< Protocol not supported. */
    NERROR_INV_PROTO_TYPE, /**< Protocol wrong type for socket. */
    NERROR_TIMER, /**< Timer expired. */
    NERROR_CONN_TIMEOUT, /**< Connection timed out. */
    NERROR_TEXT_BUSY, /**< Text file busy. */

    #elif NIMBLE_OS == NIMBLE_MACOS
    NERROR_NO_PERM, /**< Operation not permitted. */
    NERROR_NO_FILE, /**< No such file or directory. */
    NERROR_NO_PROCESS, /**< No such process. */
    NERROR_INTERRUPT, /**< Interrupted system call. */
    NERROR_IO, /**< Input/output error. */
    NERROR_NO_DEVICE, /**< No such device or address. */
    NERROR_MAX_ARGS, /**< Argument list too long. */
    NERROR_INV_EXEC_FORMAT, /**< Exec format error. */
    NERROR_INV_FP, /**< Bad file descriptor. */
    NERROR_NO_CHILD, /**< No child process. */
    NERROR_DEADLOCK, /**< Resource deadlock avoided. */
    NERROR_NO_MEMORY, /**< Cannot allocate memory. */
    NERROR_NO_FILE_PERM, /**< Permission denied. */
    NERROR_FAULT, /**< Bad address. */
    NERROR_NOT_BLOCK, /**< Block device required. */
    NERROR_DEVICE_BUSY, /**< Device or resource busy. */
    NERROR_FILE_EXISTS, /**< File exists. */
    NERROR_INV_CROSSLINK, /**< Invalid cross-device link. */
    NERROR_INV_DEVICE, /**< No such device. */
    NERROR_NOT_DIR, /**< Not a directory. */
    NERROR_IS_DIR, /**< Is a directory. */
    NERROR_INV_ARG, /**< Invalid argument. */
    NERROR_MAX_FILE_SYS, /**< Too many open files in system. */
    NERROR_MAX_FILE, /**< Too many open files. */
    NERROR_INV_IOCTL, /**< Inappropriate ioctl for device. */
    NERROR_TEXT_BUSY, /**< Text file busy. */
    NERROR_FILE_TOO_BIG, /**< File too large. */
    NERROR_NO_SPACE, /**< No space left on device. */
    NERROR_INV_SEEK, /**< Illegal seek. */
    NERROR_READ_ONLY, /**< Read-only file system. */
    NERROR_MAX_LINKS, /**< Too many links. */
    NERROR_INV_PIPE, /**< Broken pipe. */
    NERROR_DOMAIN, /**< Numerical argument out of domain. */
    NERROR_RESULT_TOO_BIG, /**< Numerical result out of range. */
    NERROR_WOULD_BLOCK, /**< Resource temporarily unavailable; Operation would block. */
    NERROR_IN_PROGRESS, /**< Operation now in progress. */
    NERROR_ALREADY, /**< Operation already in progress. */
    NERROR_NOT_SOCKET, /**< Socket operation on non-socket. */
    NERROR_NO_ADDR, /**< Destination address required. */
    NERROR_MAX_MESSAGE, /**< Message too long. */
    NERROR_INV_PROTO_TYPE, /**< Protocol wrong type for socket. */
    NERROR_INV_PROTO_OPT, /**< Protocol not available. */
    NERROR_INV_PROTOCOL, /**< Protocol not supported. */
    NERROR_INV_SOCK_TYPE, /**< Socket type not supported. */
    NERROR_NOT_SUPPORTED, /**< Not supported. */
    NERROR_INV_SOCK_OPR, /**< Operation not supported. */
    NERROR_INV_PROTO_FAM, /**< Protocol family not supported. */
    NERROR_INV_ADDR_FAM, /**< Address family not supported by protocol. */
    NERROR_ADDR_IN_USE, /**< Address already in use. */
    NERROR_ADDR_NOT_AVAILABLE, /**< Cannot assign requested address. */
    NERROR_NET_DOWN, /**< Network is down. */
    NERROR_NET_UNREACHABLE, /**< Network is unreachable. */
    NERROR_NET_RESET, /**< Network dropped connection on reset. */
    NERROR_CONN_ABORTED, /**< Software caused connection abort. */
    NERROR_CONN_RESET, /**< Connection reset by peer. */
    NERROR_NO_BUFFER_SPACE, /**< No buffer space available. */
    NERROR_ALREADY_CONN, /**< Transport endpoint is already connected. */
    NERROR_NOT_CONN, /**< Transport endpoint is not connected. */
    NERROR_SOCK_SHUTDOWN, /**< Cannot send after transport endpoint shutdown. */
    NERROR_MAX_REFS, /**< Too many references: cannot splice. */
    NERROR_CONN_TIMEOUT, /**< Connection timed out. */
    NERROR_CONN_REFUSED, /**< Connection refused. */
    NERROR_LINK_LOOP, /**< Too many levels of symbolic links. */
    NERROR_MAX_FILENAME, /**< File name too long. */
    NERROR_HOST_DOWN, /**< Host is down. */
    NERROR_HOST_UNREACHABLE, /**< No route to host. */
    NERROR_DIR_NOT_EMPTY, /**< Directory not empty. */
    NERROR_MAX_PROCESS, /**< Too many processes. */
    NERROR_MAX_USERS, /**< Too many users. */
    NERROR_MAX_DISK_QUOTA, /**< Disk quota exceeded. */
    NERROR_STALE, /**< Stale file handle. */
    NERROR_REMOTE, /**< Object is remote. */
    NERROR_INV_RPC, /**< RPC struct is bad. */
    NERROR_INV_RPC_VERSION, /**< RPC version wrong. */
    NERROR_INV_RPC_PROG, /**< RPC program not available. */
    NERROR_INV_RPC_PROG_VERSION, /**< RPC program version wrong. */
    NERROR_INV_RPC_PROC, /**< RPC bad procedure for program. */
    NERROR_NO_FILE_LOCK, /**< No locks available. */
    NERROR_FUNC_NOT_SUPPORTED, /**< Function not implemented. */
    NERROR_INV_FILE_TYPE, /**< Inappropriate file type or format. */
    NERROR_AUTH, /**< Authentication error. */
    NERROR_NO_AUTH, /**< Need authenticator. */
    NERROR_DEVICE_OFF, /**< Device power is off. */
    NERROR_DEVICE_ERROR, /**< Device error, eg. paper out */
    NERROR_OVERFLOW, /**< Value too large for defined data type. */
    NERROR_INV_EXECUTABLE, /**< Bad executable. */
    NERROR_INV_ARCHITECTURE, /**< Bad CPU type in executable. */
    NERROR_INV_LIB_VERSION, /**< Shared library version mismatch */
    NERROR_INV_MACHO, /**< Malformed Macho file. */
    NERROR_ASYNC_CANCEL, /**< Operation canceled. */
    NERROR_NO_IDENTIFIER, /**< Identifier removed. */
    NERROR_NO_MESSAGE, /**< No message of desired type. */
    NERROR_INV_MULTIBYTE, /**< Invalid or incomplete multibyte or wide character. */
    NERROR_NO_ATTRIBUTE, /**< Attribute not found. */
    NERROR_INV_MESSAGE, /**< Bad message. */
    NERROR_MULTIHOP, /**< Multihop attempted. */
    NERROR_NO_DATA, /**< No data available. */
    NERROR_NO_LINK, /**< Link has been severed. */
    NERROR_NO_STREAM_RESOURCES, /**< Out of streams resources. */
    NERROR_DEVICE_NOT_STREAM, /**< Device not a stream. */
    NERROR_PROTOCOL, /**< Protocol error. */
    NERROR_TIMER, /**< Timer expired. */
    NERROR_INV_SOCK_OPR, /**< Operation not supported. */
    NERROR_NO_POLICY, /**< No such policy registered. */
    NERROR_NOT_RECOVERABLE, /**< State not recoverable. */
    NERROR_OWNER_DIED, /**< Owner died. */
    NERROR_MAX_QUEUE, /**< Interface output queue is full. */
    
    #elif NIMBLE_OS == NIMBLE_LINUX
    #elif NIMBLE_OS == NIMBLE_ANDROID
    #elif defined(NIMBLE_POSIX)
    #else
    #error OS not supported.
    #endif /** @todo CONTINUE; Also figure out what to do with __FILE__ and __LINE__ etc. they will be useful  */
    NERROR_ERRNO_END, /**< The end of the errno section. */
    
    NERROR_MAX /**< The maximum error number. */
};


/**
 * @brief The strings used to represent error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const char *nErrorStrings[];

/**
 * @brief The length of the strings of the error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const nint_t nErrorDescLengths[];

/*
 * @brief Gets the error code @p err represented as a string from #nErrorStrings.
 *
 * @param[in] err The error code to translate to a string.
 * @return @p err translated to a string.
 * @note The returned string is a pointer to a constant string on the stack. This
 * means that one should not allocate or free the pointer. If editing is needed,
 * copy the result to dynamically allocated memory.
 */
#define nErrorStr(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
                        nErrorStrings[err] : nErrorStrings[NERROR_UNKNOWN])

/*
 * @brief Gets the length of the error code @p err from #nErrorStringLengths.
 *
 * @param[in] err The error code to determine the length of.
 * @return @p erorr's string translation length.
 */
#define nErrorStrLen(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
                           nErrorStringLengths[err] :\
                           nErrorStringLengths[NERROR_UNKNOWN])

/**
 * @brief The descriptions of the error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const char *nErrorDescriptions[];

/**
 * @brief The length of the descriptions of the error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const nint_t nErrorDescLengths[];

/*
 * @brief Gets the error description of the error code @p err from #nErrorDescriptions.
 *
 * @param[in] err The error code to describe.
 * @return The description of @p err as a string.
 * @note The returned string is a pointer to a constant string on the stack. This
 * means that one should not allocate or free the pointer. If editing is needed,
 * copy the result to dynamically allocated memory.
 */
#define nErrorDesc(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
                         nErrorDescriptions[err] :\
                         nErrorDescriptions[NERROR_UNKNOWN])
/*
 * @brief Gets the length of the error code @p err from #nErrorDescLengths.
 *
 * @param[in] err The error code to determine the length of.
 * @return @p erorr's string translation length.
 */
#define nErrorDescLen(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
                            nErrorDescLengths[err] :\
                            nErrorDescLengths[NERROR_UNKNOWN])

/*
 * @brief Gets the error code of the signal value @p error.
 *
 * @param[in] error The signal value.
 * @return The NERROR version of @p error, or #NERROR_UNKNOWN if out of range.
 */
#define nErrorFromSignal(err) (((err > NERROR_SIGNAL_START) && \
                               (err < NERROR_SIGNAL_END)) ?\
                               (NERROR_SIGNAL_START + err) :\
                               NERROR_UNKNOWN)

/*
 * @brief Gets the error code of the errno value @p err.
 *
 * @param[in] err The errno value.
 * @return An NERROR version of @p err, or #NERROR_UNKNOWN if out of range.
 */
NIMBLE_EXTERN
nint_t
nErrorFromErrno(const nint_t err);


/**
 * @brief Sends an error to the error callback.
 * Sends an error to the error callback defined by
 * nErrorHandlerSetErrorCallback(), and determines whether or not crashing is
 * necessary.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char exampleFilePath[] = "example.txt";
 *     if (nErrorThrow(NERROR_FILE_NOT_FOUND, exampleFilePath,
            sizeof(exampleFilePath)) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Failed to throw error.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Successfully threw error.\n");
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] error The error to throw.
 * @param[in] info Relevant information, such as a file location, that could help
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * diagnose the error. This can be @c #NULL.
 *
 * @note The program will crash if this is unsuccessful.
 */
NIMBLE_EXTERN
void
nErrorThrow(const nint_t error,
            const char *info,
            nint_t infoLen
            );

/**
 * @brief Describes an error and returns a string with no error handling.
 *
 * Example:
 * @todo Do this
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char *errorStr;
 *     nint_t errorLen;
 *     char exampleFilePath[] = "example.txt";
 *     if (nErrorToStringLocal(errorStr, &errorLen, NERROR_FILE_NOT_FOUND,
 *          exampleFilePath, sizeof(exampleFilePath)) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_FILE_NOT_FOUND as string: %s\n", errorStr);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the string describing @p error. This
 * can be @c #NULL.
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 *
 * @note This function is used by the game engine and is not expected to be used
 * by developers, but is optional.
 */
NIMBLE_EXTERN
nint_t
nErrorToStringLocal(char *dst,
                    nint_t *errorLen,
                    const nint_t error,
                    const char *info,
                    nint_t infoLen
                    );

/**
 * @brief Describes an error and returns a string.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char *errorStr;
 *     nint_t errorLen;
 *     char exampleFilePath[] = "example.txt";
 *     if (nErrorToString(errorStr, &errorLen, NERROR_FILE_NOT_FOUND,
 *          exampleFilePath, sizeof(exampleFilePath)) == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_FILE_NOT_FOUND as string: %s\n", errorStr);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the string describing @p error. This
 * can be @c #NULL.
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 */
NIMBLE_EXTERN
char *
nErrorToString(char *dst,
               nint_t *errorLen,
               const nint_t error,
               const char *info,
               nint_t infoLen
               );

/**
 * @brief Sets the callback function to handle errors.
 *
 * Sets the callback function @p callback that gets called when an error occurs.
 *
 * @par Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <time.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * void errorHandler(const nint_t error, const char * errorDesc,
 *       const nint_t errorDescLen, const time_t errorTime, const char * stack,
 *       const nint_t stackLen)
 * {
 *     struct tm *timeInfo = localtime(&errorTime);
 *     const char format[] = "%x %X %Z";
 *     const char example = "01/01/2020 16:30:45 GMT"
 *     char *timeString = nAlloc(sizeof(example));
 *     if (timeString == NULL)
 *     {
 *         fprintf(stderr, "Failed to allocate to timeString.\n");
 *         return;
 *     }
 *     strftime(timeString, sizeof(example), format, timeInfo);
 *
 *     fprintf(stderr, "\nAn error occurred at %s:\nError description: "\
 *      "%s\nStack trace: %s\n\n", timeString, errorDesc, stack);
 * }
 *
 * int main(int argc, char **argv)
 * {
 *     if (nErrorHandlerSetErrorCallback(errorHandler) != NSUCCESS)
 *     {
 *         fprintf(stderr, "Could not set error callback for Nimble.\n");
 *         return EXIT_FAILURE;
 *     }
 *     printf("Successfully set error callback for Nimble.\n");
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[in] callback The function that gets called when an error occurs.
 * @return @c #NSUCCESS is returned if successful; otherwise @c #NERROR is
 * returned.
 *
 * @note Check nErrorHandlerDefault() for parameter information.
 */
NIMBLE_EXTERN
nint_t
nErrorSetCallback(void (*callback)(
                                    const nint_t error,
                                    const time_t errorTime,
                                    const char *errorDesc,
                                    const nint_t errorDescLen,
                                    const char *stack,
                                    const nint_t stackLen
                                    )
                  );

/**
 * @brief Returns the current stack trace as a string.
 * Returns the current stack trace as a string, and sets the @p stackLen of the
 * string and @p levels of the stack.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     nint_t stackLen, stackLevels;
 *     char *stack;
 *     nErrorGetStacktrace(stack, &stackLen, &stackLevels);
 *     if (stack == NULL)
 *     {
 *         fprintf(stderr, "Failed to get stack trace.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Last %d levels of stack trace: %s\n", stackLevels, stack);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] dst The destination to store the stacktrace string. This can be
 * @c #NULL.
 * @param[out] stackLen The length of the string returned. This can be @c #NULL.
 * @param[in,out] stackLevels The number of levels found on the stack. If the
 * value of this is nonzero when passed, it will act as the maximum number of
 * stack levels to be returned in @p dst. This can be @c #NULL.
 * @return @p dst is returned if successful; otherwise the program crashes.
 *
 * @note Each time a function is called, it is added to the stack. When a
 * function returns, it is removed from the stack.
 */
NIMBLE_EXTERN
char *
nErrorGetStacktrace(char *dst,
                    nint_t *stackLen,
                    nint_t *stackLevels
                    );

#endif // NIMBLE_ENGINE_ERRORS_H

#ifdef __cplusplus
}
#endif

// Errors.h
