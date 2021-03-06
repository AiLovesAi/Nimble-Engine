#include "../NimbleLicense.h"
/*
 * ErrorValues.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-05.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

/**
 * @file ErrorValues.h
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
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
 * @date 2020-12-05
 *
 * @brief This class defines error values for error handling functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_ERRORVALUES_H
#define NIMBLE_ENGINE_ERRORVALUES_H /**< Header definition */

#include "../Nimble.h"


#define NSUCCESS 0 /**< Returned when a function succeeds. */

/**
 * @brief The possible error values used by ErrorHandler.h error handler.
 *
 * @note For more detailed info on an error, see the error descriptions in
 * Errors.c (#nErrorDescriptions).
 */
NIMBLE_EXPORT
enum nErrors {
    NERROR_MIN = 0, /**< The mininum error number. */
    
    NERROR_UNKNOWN, /**< An nknown error occurred. */
    NERROR_WARN, /**< A warning was triggered that requires attention by the user. */
    NERROR_INTERNAL_FAILURE, /**< An internal error occurred. */
    NERROR_NULL, /**< A pointer was null when a nonnull pointer was expected. */
    NERROR_STACK_OVERFLOW, /**< A stack overflow occurred. */
    NERROR_INV_ERROR, /**< An error passed to a function was not valid. */
    NERROR_BOUNDS_OVERFLOW, /**< Operation would overflow bounds of array or buffer. */
    NERROR_INV_RETRY, /**< Cannot retry. */
    NERROR_LOOP, /**< Looped to the start of a function before completion. */
    
#if NIMBLE_OS == NIMBLE_WINDOWS
    NERROR_INV_TYPE_ALIGNMENT, /**< Invalid type alignment. */
    NERROR_INV_PAGE, /**< Requested page is not present. */
    NERROR_NONCONTINUABLE, /**< Tried to continue execution after a noncontinuable exception occurred. */
#endif

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
    /* (IEEE or POSIX, please standardize the error values for goodness
     * sake, OS devs please follow said standard. It has taken me 30+ hours
     * to figure out and make a 3,000+ line portable equivalent of:
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
    NERROR_MAX_CHANNEL = ECHRNG, /**< Channel number out of range. */
    NERROR_LVL2_NO_SYNC = EL2NSYNC, /**< Level 2 not synchronized. */
    NERROR_LVL3_HAULT = EL3HLT, /**< Level 3 halted. */
    NERROR_LVL3_RESET = EL3RST, /**< Level 3 reset. */
    NERROR_LINK_NUM = ELNRNG, /**< Link number out of range. */
    NERROR_PROTO_UNATTACHED = EUNATCH, /**< Protocol driver not attached. */
    NERROR_NO_CSI = ENOCSI, /**< No CSI structure available. */
    NERROR_LVL2_HAULT = EL2HLT, /**< Level 2 haulted. */
    NERROR_INV_EXCHANGE = EBADE, /**< Invalid exchange. */
    NERROR_INV_REQUEST_DESC = EBADR, /**< Invalid request descriptor. */
    NERROR_EXCHANGE_FULL = EXFULL, /**< Exchange full. */
    NERROR_NO_ANODE = ENOANO, /**< No anode. */
    NERROR_INV_REQUEST_CODE = EBADRQC, /**< Invalid request code. */
    NERROR_INV_SLOT = EBADSLT, /**< Invalid slot. */
    NERROR_INV_FONT = EBFONT, /**< Bad font file format. */
    NERROR_NO_NETWORK = ENONET, /**< Machine is not on the network. */
    NERROR_NO_PACKAGE = ENOPKG, /**< Package not installed. */
    NERROR_ADVERTISE = EADV, /**< Advertise error. */
    NERROR_SRMOUNT = ESRMNT, /**< Srmount error. */
    NERROR_COMMUNICATION = ECOMM, /**< Communication error on send. */
    NERROR_DOTDOT = EDOTDOT, /**< RFS specific error. */
    NERROR_NOT_UNIQUE = ENOTUNIQ, /**< Name not unique on network. */
    NERROR_INV_FD = EBADFD, /**< File descriptor in bad state. */
    NERROR_REMOTE_CHANGE = EREMCHG, /**< Remote address changed. */
    NERROR_NO_LIB = ELIBACC, /**< Can not access a needed shared library. */
    NERROR_INV_LIB = ELIBBAD, /**< Accessing a corrupted shared library. */
    NERROR_INV_LIB_SCAN = ELIBSCN, /**< .lib section in a.out corrupted. */
    NERROR_MAX_LIB = ELIBMAX, /**< Attempting to link in too many shared libraries. */
    NERROR_EXEC_LIB = ELIBEXEC, /**< Cannot exec a shared library directly. */
    NERROR_RESTART_CALL = ERESTART, /**< Interrupted system call should be restarted. */
    NERROR_STR_PIPE = ESTRPIPE, /**< Streams pipe error. */
    NERROR_CLEAN_STRUCT = EUCLEAN, /**< Structure needs cleaning. */
    NERROR_NOT_XENIX = ENOTNAM, /**< Not a XENIX named type file. */
    NERROR_NO_XENIX_SEM = ENAVAIL, /**< No XENIX semaphores available. */
    NERROR_NAMED = EISNAM, /**< Is a named type file. */
    NERROR_REMOTE_IO = EREMOTEIO, /**< Remote I/O error. */
    NERROR_NO_MEDIUM = ENOMEDIUM, /**< No medium found. */
    NERROR_INV_MEDIUM = EMEDIUMTYPE, /**< Wrong medium type. */
    NERROR_PROGRAMMER = EDOOFUS, /**< Programming error. */
    NERROR_FD_INCAPABLE = ENOTCAPABLE, /**< Capabilities insufficient. */
    NERROR_CAPABILITY_MODE = ECAPMODE, /**< Not permitted in capability mode. */
    NERROR_INTEGRITY = EINTEGRITY, /**< Integrity check failed. */
    NERROR_INODE_REMOTE = ELBIN, /**< Inode is remote. */
    NERROR_NO_MORE_FILES = ENMFILE, /**< No more files. */
    NERROR_NO_NET_PATH = ENOSHARE, /**< No such host or network path. */
    NERROR_FILE_CASE = NECASECLASH, /**< Filename exists with different case. */
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
    NERROR_NO_POLICY, /**< No such policy registered. */
    NERROR_NOT_RECOVERABLE, /**< State not recoverable. */
    NERROR_OWNER_DIED, /**< Owner died. */
    NERROR_MAX_QUEUE, /**< Interface output queue is full. */
    
#elif NIMBLE_OS == NIMBLE_ANDROID
    NERROR_NO_PERM, /**< Operation not permitted. */
    NERROR_NO_FILE, /**< No such file or directory. */
    NERROR_NO_PROCESS, /**< No such process. */
    NERROR_INTERRUPT, /**< Interrupted system call. */
    NERROR_IO, /**< Input/output error. */
    NERROR_NO_DEVICE, /**< No such device or address. */
    NERROR_MAX_ARGS, /**< Argument list too long. */
    NERROR_INV_EXEC_FORMAT, /**< Exec format error. */
    NERROR_INV_FP, /**< Bad file descriptor. */
    NERROR_WOULD_BLOCK, /**< Resource temporarily unavailable; Operation would block. */
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
    NERROR_NO_MESSAGE, /**< No message of desired type. */
    NERROR_NO_IDENTIFIER, /**< Identifier removed. */
    NERROR_MAX_CHANNEL, /**< Channel number out of range. */
    NERROR_LVL2_NO_SYNC, /**< Level 2 not synchronized. */
    NERROR_LVL3_HAULT, /**< Level 3 halted. */
    NERROR_LVL3_RESET, /**< Level 3 reset. */
    NERROR_LINK_NUM, /**< Link number out of range. */
    NERROR_PROTO_UNATTACHED, /**< Protocol driver not attached. */
    NERROR_NO_CSI, /**< No CSI structure available. */
    NERROR_LVL2_HAULT, /**< Level 2 haulted. */
    NERROR_DEADLOCK, /**< Resource deadlock avoided. */
    NERROR_NO_FILE_LOCK, /**< No locks available. */
    NERROR_INV_EXCHANGE, /**< Invalid exchange. */
    NERROR_INV_REQUEST_DESC, /**< Invalid request descriptor. */
    NERROR_EXCHANGE_FULL, /**< Exchange full. */
    NERROR_NO_ANODE, /**< No anode. */
    NERROR_INV_REQUEST_CODE, /**< Invalid request code. */
    NERROR_INV_SLOT, /**< Invalid slot. */
    NERROR_INV_FONT, /**< Bad font file format. */
    NERROR_DEVICE_NOT_STREAM, /**< Device not a stream. */
    NERROR_NO_DATA, /**< No data available. */
    NERROR_TIMER, /**< Timer expired. */
    NERROR_NO_STREAM_RESOURCES, /**< Out of streams resources. */
    NERROR_NO_NETWORK, /**< Machine is not on the network. */
    NERROR_NO_PACKAGE, /**< Package not installed. */
    NERROR_REMOTE, /**< Object is remote. */
    NERROR_NO_LINK, /**< Link has been severed. */
    NERROR_ADVERTISE, /**< Advertise error. */
    NERROR_SRMOUNT, /**< Srmount error. */
    NERROR_COMMUNICATION, /**< Communication error on send. */
    NERROR_PROTOCOL, /**< Protocol error. */
    NERROR_MULTIHOP, /**< Multihop attempted. */
    NERROR_INODE_REMOTE, /**< Inode is remote. */
    NERROR_DOTDOT, /**< RFS specific error. */
    NERROR_INV_MESSAGE, /**< Bad message. */
    NERROR_INV_FILE_TYPE, /**< Inappropriate file type or format. */
    NERROR_NOT_UNIQUE, /**< Name not unique on network. */
    NERROR_INV_FD, /**< File descriptor in bad state. */
    NERROR_REMOTE_CHANGE, /**< Remote address changed. */
    NERROR_NO_LIB, /**< Can not access a needed shared library. */
    NERROR_INV_LIB, /**< Accessing a corrupted shared library. */
    NERROR_INV_LIB_SCAN, /**< .lib section in a.out corrupted. */
    NERROR_MAX_LIB, /**< Attempting to link in too many shared libraries. */
    NERROR_EXEC_LIB, /**< Cannot exec a shared library directly. */
    NERROR_FUNC_NOT_SUPPORTED, /**< Function not implemented. */
    NERROR_NO_MORE_FILES, /**< No more files. */
    NERROR_DIR_NOT_EMPTY, /**< Directory not empty. */
    NERROR_MAX_FILENAME, /**< File name too long. */
    NERROR_LINK_LOOP, /**< Too many levels of symbolic links. */
    NERROR_INV_SOCK_OPR, /**< Operation not supported. */
    NERROR_INV_PROTO_FAM, /**< Protocol family not supported. */
    NERROR_CONN_RESET, /**< Connection reset by peer. */
    NERROR_NO_BUFFER_SPACE, /**< No buffer space available. */
    NERROR_INV_ADDR_FAM, /**< Address family not supported by protocol. */
    NERROR_INV_PROTO_TYPE, /**< Protocol wrong type for socket. */
    NERROR_NOT_SOCKET, /**< Socket operation on non-socket. */
    NERROR_INV_PROTO_OPT, /**< Protocol not available. */
    NERROR_SOCK_SHUTDOWN, /**< Cannot send after transport endpoint shutdown. */
    NERROR_CONN_REFUSED, /**< Connection refused. */
    NERROR_ADDR_IN_USE, /**< Address already in use. */
    NERROR_CONN_ABORTED, /**< Software caused connection abort. */
    NERROR_NET_UNREACHABLE, /**< Network is unreachable. */
    NERROR_NET_DOWN, /**< Network is down. */
    NERROR_CONN_TIMEOUT, /**< Connection timed out. */
    NERROR_HOST_DOWN, /**< Host is down. */
    NERROR_HOST_UNREACHABLE, /**< No route to host. */
    NERROR_IN_PROGRESS, /**< Operation now in progress. */
    NERROR_ALREADY, /**< Operation already in progress. */
    NERROR_NO_ADDR, /**< Destination address required. */
    NERROR_MAX_MESSAGE, /**< Message too long. */
    NERROR_INV_PROTOCOL, /**< Protocol not supported. */
    NERROR_INV_SOCK_TYPE, /**< Socket type not supported. */
    NERROR_ADDR_NOT_AVAILABLE, /**< Cannot assign requested address. */
    NERROR_NET_RESET, /**< Network dropped connection on reset. */
    NERROR_ALREADY_CONN, /**< Transport endpoint is already connected. */
    NERROR_NOT_CONN, /**< Transport endpoint is not connected. */
    NERROR_MAX_REFS, /**< Too many references: cannot splice. */
    NERROR_MAX_PROCESS, /**< Too many processes. */
    NERROR_MAX_USERS, /**< Too many users. */
    NERROR_MAX_DISK_QUOTA, /**< Disk quota exceeded. */
    NERROR_STALE, /**< Stale file handle. */
    NERROR_NOT_SUPPORTED, /**< Not supported. */
    NERROR_NO_MEDIUM, /**< No medium found. */
    NERROR_NO_NET_PATH, /**< No such host or network path. */
    NERROR_FILE_CASE, /**< Filename exists with different case. */
    NERROR_INV_MULTIBYTE, /**< Invalid or incomplete multibyte or wide character. */
    NERROR_OVERFLOW, /**< Value too large for defined data type. */

#elif NIMBLE_OS == NIMBLE_BSD
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
    NERROR_NO_IDENTIFIER, /**< Identifier removed. */
    NERROR_NO_MESSAGE, /**< No message of desired type. */
    NERROR_OVERFLOW, /**< Value too large for defined data type. */
    NERROR_ASYNC_CANCEL, /**< Operation canceled. */
    NERROR_INV_MULTIBYTE, /**< Invalid or incomplete multibyte or wide character. */
    NERROR_NO_ATTRIBUTE, /**< Attribute not found. */
    NERROR_INV_MESSAGE, /**< Bad message. */
    NERROR_MULTIHOP, /**< Multihop attempted. */
    NERROR_NO_LINK, /**< Link has been severed. */
    NERROR_PROTOCOL, /**< Protocol error. */
    NERROR_FD_INCAPABLE, /**< Capabilities insufficient. */
    NERROR_CAPABILITY_MODE, /**< Not permitted in capability mode. */
    NERROR_NOT_RECOVERABLE, /**< State not recoverable. */
    NERROR_OWNER_DIED, /**< Owner died. */
    NERROR_INTEGRITY, /**< Integrity check failed. */

#elif (NIMBLE_OS == NIMBLE_LINUX) || (NIMBLE_OS == NIMBLE_UNIX)
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
    NERROR_DEADLOCK, /**< Resource deadlock avoided. */
    NERROR_MAX_FILENAME, /**< File name too long. */
    NERROR_NO_FILE_LOCK, /**< No locks available. */
    NERROR_FUNC_NOT_SUPPORTED, /**< Function not implemented. */
    NERROR_DIR_NOT_EMPTY, /**< Directory not empty. */
    NERROR_LINK_LOOP, /**< Too many levels of symbolic links. */
    NERROR_NO_MESSAGE, /**< No message of desired type. */
    NERROR_NO_IDENTIFIER, /**< Identifier removed. */
    NERROR_MAX_CHANNEL, /**< Channel number out of range. */
    NERROR_LVL2_NO_SYNC, /**< Level 2 not synchronized. */
    NERROR_LVL3_HAULT, /**< Level 3 halted. */
    NERROR_LVL3_RESET, /**< Level 3 reset. */
    NERROR_LINK_NUM, /**< Link number out of range. */
    NERROR_PROTO_UNATTACHED, /**< Protocol driver not attached. */
    NERROR_NO_CSI, /**< No CSI structure available. */
    NERROR_LVL2_HAULT, /**< Level 2 haulted. */
    NERROR_INV_EXCHANGE, /**< Invalid exchange. */
    NERROR_INV_REQUEST_DESC, /**< Invalid request descriptor. */
    NERROR_EXCHANGE_FULL, /**< Exchange full. */
    NERROR_NO_ANODE, /**< No anode. */
    NERROR_INV_REQUEST_CODE, /**< Invalid request code. */
    NERROR_INV_SLOT, /**< Invalid slot. */
    NERROR_INV_FONT, /**< Bad font file format. */
    NERROR_DEVICE_NOT_STREAM, /**< Device not a stream. */
    NERROR_NO_DATA, /**< No data available. */
    NERROR_TIMER, /**< Timer expired. */
    NERROR_NO_STREAM_RESOURCES, /**< Out of streams resources. */
    NERROR_NO_NETWORK, /**< Machine is not on the network. */
    NERROR_NO_PACKAGE, /**< Package not installed. */
    NERROR_REMOTE, /**< Object is remote. */
    NERROR_NO_LINK, /**< Link has been severed. */
    NERROR_ADVERTISE, /**< Advertise error. */
    NERROR_SRMOUNT, /**< Srmount error. */
    NERROR_COMMUNICATION, /**< Communication error on send. */
    NERROR_PROTOCOL, /**< Protocol error. */
    NERROR_MULTIHOP, /**< Multihop attempted. */
    NERROR_DOTDOT, /**< RFS specific error. */
    NERROR_INV_MESSAGE, /**< Bad message. */
    NERROR_OVERFLOW, /**< Value too large for defined data type. */
    NERROR_NOT_UNIQUE, /**< Name not unique on network. */
    NERROR_INV_FD, /**< File descriptor in bad state. */
    NERROR_REMOTE_CHANGE, /**< Remote address changed. */
    NERROR_NO_LIB, /**< Can not access a needed shared library. */
    NERROR_INV_LIB, /**< Accessing a corrupted shared library. */
    NERROR_INV_LIB_SCAN, /**< .lib section in a.out corrupted. */
    NERROR_MAX_LIB, /**< Attempting to link in too many shared libraries. */
    NERROR_EXEC_LIB, /**< Cannot exec a shared library directly. */
    NERROR_INV_MULTIBYTE, /**< Invalid or incomplete multibyte or wide character. */
    NERROR_RESTART_CALL, /**< Interrupted system call should be restarted. */
    NERROR_STR_PIPE, /**< Streams pipe error. */
    NERROR_MAX_USERS, /**< Too many users. */
    NERROR_NOT_SOCKET, /**< Socket operation on non-socket. */
    NERROR_NO_ADDR, /**< Destination address required. */
    NERROR_MAX_MESSAGE, /**< Message too long. */
    NERROR_INV_PROTO_TYPE, /**< Protocol wrong type for socket. */
    NERROR_INV_PROTO_OPT, /**< Protocol not available. */
    NERROR_INV_PROTOCOL, /**< Protocol not supported. */
    NERROR_INV_SOCK_TYPE, /**< Socket type not supported. */
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
    NERROR_HOST_DOWN, /**< Host is down. */
    NERROR_HOST_UNREACHABLE, /**< No route to host. */
    NERROR_ALREADY, /**< Operation already in progress. */
    NERROR_IN_PROGRESS, /**< Operation now in progress. */
    NERROR_STALE, /**< Stale file handle. */
    NERROR_CLEAN_STRUCT, /**< Structure needs cleaning. */
    NERROR_NOT_XENIX, /**< Not a XENIX named type file. */
    NERROR_NO_XENIX_SEM, /**< No XENIX semaphores available. */
    NERROR_NAMED, /**< Is a named type file. */
    NERROR_REMOTE_IO, /**< Remote I/O error. */
    NERROR_MAX_DISK_QUOTA, /**< Disk quota exceeded. */
    NERROR_NO_MEDIUM, /**< No medium found. */
    NERROR_INV_MEDIUM, /**< Wrong medium type. */
#else
#  error OS not supported.
#endif
    NERROR_ERRNO_END, /**< The end of the errno section. */
    
    NERROR_MAX /**< The maximum error number. */
};


/**
 * @brief The strings used to represent error codes defined by #nErrors.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
const char *const nErrorStrings[];

/**
 * @brief The lengths of the strings used to represent error codes defined by #nErrors.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
const size_t nErrorStrLengths[];

/*
 * @brief Gets the error code @p err represented as a string from #nErrorStrings.
 *
 * @param[in] err The error code to translate to a string.
 * @return @p err translated to a string.
 * @note The returned string is a pointer to a constant string on the stack. This
 * means that one should not allocate or free the pointer. If editing is needed,
 * copy the result to dynamically allocated memory.
 */
#ifdef NIMBLE_NO_ARG_CHECK
#  define nErrorStr(err) nErrorStrings[err]
#else
#  define nErrorStr(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorStrings[err] : nErrorStrings[NERROR_UNKNOWN])
#endif

/*
 * @brief Gets the length of the error code @p err from #nErrorStrings.
 *
 * @param[in] err The error code to determine the length of.
 * @return @p err's string translation length.
 */
#ifdef NIMBLE_NO_ARG_CHECK
#  define nErrorStrLen(err) nErrorStrLengths[err]
#else
#  define nErrorStrLen(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorStrLengths[err] : nErrorStrLengths[NERROR_UNKNOWN])
#endif

/**
 * @brief The descriptions of the error codes defined by #nErrors.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
const char *const nErrorDescriptions[];

/**
 * @brief The length of descriptions of the error codes defined by #nErrors.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
const size_t nErrorDescLengths[];

/*
 * @brief Gets the error description of the error code @p err from #nErrorDescriptions.
 *
 * @param[in] err The error code to describe.
 * @return The description of @p err as a string.
 * @note The returned string is a pointer to a constant string on the stack. This
 * means that one should not allocate or free the pointer. If editing is needed,
 * copy the result to dynamically allocated memory.
 */
#ifdef NIMBLE_NO_ARG_CHECK
#  define nErrorDesc(err) nErrorDescriptions[err]
#else
#  define nErrorDesc(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorDescriptions[err] : nErrorDescriptions[NERROR_UNKNOWN])
#endif

/*
 * @brief Gets the length of the error description @p err from #nErrorDescriptions.
 *
 * @param[in] err The error description to determine the length of.
 * @return @p err's string translation length.
 */
#ifdef NIMBLE_NO_ARG_CHECK
#  define nErrorDescLen(err) nErrorDescLengths[err]
#else
#  define nErrorDescLen(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorDescLengths[err] : nErrorDescLengths[NERROR_UNKNOWN])
#endif

/*
 * @brief Gets the error code of the signal value @p error.
 *
 * @param[in] signum The signal value.
 * @return The NERROR version of @p error, or #NERROR_UNKNOWN if out of range.
 * @todo Fix this for windows, it uses completely weird values as usual, so it'll have to be a switch/case...
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nErrorFromSignal(const int signum);

/*
 * @brief Gets the error code of the errno value @p err.
 *
 * @param[in] err The errno value.
 * @return An NERROR version of @p err, or #NERROR_UNKNOWN if out of range.
 */
NIMBLE_EXPORT
NIMBLE_EXTERN
int nErrorFromErrno(const int err);

#endif // NIMBLE_ENGINE_ERRORVALUES_H

#ifdef __cplusplus
}
#endif

// ErrorValues.h
