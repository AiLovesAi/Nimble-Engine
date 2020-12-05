#include "../NimbleLicense.h"
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

#include "../NimbleEngine.h"

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
    NERROR_NO_PERM = NERROR_ERRNO_START + EPERM, /**< Operation not permitted. */
    NERROR_NO_FILE = NERROR_ERRNO_START + ENOENT, /**< No such file or directory. */
    NERROR_NO_PROCESS = NERROR_ERRNO_START + ESRCH, /**< No such process. */
    NERROR_INTERRUPT = NERROR_ERRNO_START + EINTR, /**< Interrupted system call. */
    NERROR_IO = NERROR_ERRNO_START + EIO, /**< Input/output error. */
    NERROR_NO_DEVICE = NERROR_ERRNO_START + ENXIO, /**< No such device or address. */
    NERROR_MAX_ARGS = NERROR_ERRNO_START + E2BIG, /**< Argument list too long. */
    NERROR_INV_EXEC_FORMAT = NERROR_ERRNO_START + ENOEXEC, /**< Exec format error. */
    NERROR_INV_FP = NERROR_ERRNO_START + EBADF, /**< Bad file descriptor. */
    NERROR_NO_CHILD = NERROR_ERRNO_START + ECHILD, /**< No child process. */
    NERROR_DEADLOCK = NERROR_ERRNO_START + EDEADLK, /**< Resource deadlock avoided. */
    NERROR_NO_MEMORY = NERROR_ERRNO_START + ENOMEM, /**< Cannot allocate memory. */
    NERROR_NO_FILE_PERM = NERROR_ERRNO_START + EACCES, /**< Permission denied. */
    NERROR_FAULT = NERROR_ERRNO_START + EFAULT, /**< Bad address. */
    NERROR_NOT_BLOCK = NERROR_ERRNO_START + ENOTBLK, /**< Block device required. */
    NERROR_DEVICE_BUSY = NERROR_ERRNO_START + EBUSY, /**< Device or resource busy. */
    NERROR_FILE_EXISTS = NERROR_ERRNO_START + EEXIST, /**< File exists. */
    NERROR_INV_CROSSLINK = NERROR_ERRNO_START + EXDEV, /**< Invalid cross-device link. */
    NERROR_INV_DEVICE = NERROR_ERRNO_START + ENODEV, /**< No such device. */
    NERROR_NOT_DIR = NERROR_ERRNO_START + ENOTDIR, /**< Not a directory. */
    NERROR_IS_DIR = NERROR_ERRNO_START + EISDIR, /**< Is a directory. */
    NERROR_INV_ARG = NERROR_ERRNO_START + EINVAL, /**< Invalid argument. */
    NERROR_MAX_FILE = NERROR_ERRNO_START + EMFILE, /**< Too many open files. */
    NERROR_MAX_FILE_SYS = NERROR_ERRNO_START + ENFILE, /**< Too many open files in system. */
    NERROR_INV_IOCTL = NERROR_ERRNO_START + ENOTTY, /**< Inappropriate ioctl for device. */
    NERROR_TEXT_BUSY = NERROR_ERRNO_START + ETXTBSY, /**< Text file busy. */
    NERROR_FILE_TOO_BIG = NERROR_ERRNO_START + EFBIG, /**< File too large. */
    NERROR_NO_SPACE = NERROR_ERRNO_START + ENOSPC, /**< No space left on device. */
    NERROR_INV_SEEK = NERROR_ERRNO_START + ESPIPE, /**< Illegal seek. */
    NERROR_READ_ONLY = NERROR_ERRNO_START + EROFS, /**< Read-only file system. */
    NERROR_MAX_LINKS = NERROR_ERRNO_START + EMLINK, /**< Too many links. */
    NERROR_INV_PIPE = NERROR_ERRNO_START + EPIPE, /**< Broken pipe. */
    NERROR_DOMAIN = NERROR_ERRNO_START + EDOM, /**< Numerical argument out of domain. */
    NERROR_RESULT_TOO_BIG = NERROR_ERRNO_START + ERANGE, /**< Numerical result out of range. */
    NERROR_WOULD_BLOCK = NERROR_ERRNO_START + (EAGAIN & EWOULDBLOCK), /**< Resource temporarily unavailable; Operation would block. */
    NERROR_IN_PROGRESS = NERROR_ERRNO_START + EINPROGRESS, /**< Operation now in progress. */
    NERROR_ALREADY = NERROR_ERRNO_START + EALREADY, /**< Operation already in progress. */
    NERROR_NOT_SOCKET = NERROR_ERRNO_START + ENOTSOCK, /**< Socket operation on non-socket. */
    NERROR_MAX_MESSAGE = NERROR_ERRNO_START + EMSGSIZE, /**< Message too long. */
    NERROR_INV_PROTO_TYPE = NERROR_ERRNO_START + EPROTOTYPE, /**< Protocol wrong type for socket. */
    NERROR_INV_PROTO_OPT = NERROR_ERRNO_START + ENOPROTOOPT, /**< Protocol not available. */
    NERROR_INV_PROTOCOL = NERROR_ERRNO_START + EPROTONOSUPPORT, /**< Protocol not supported. */
    NERROR_INV_SOCK_TYPE = NERROR_ERRNO_START + ESOCKTNOSUPPORT, /**< Socket type not supported. */
    NERROR_INV_SOCK_OPR = NERROR_ERRNO_START + EOPNOTSUPP, /**< Operation not supported. */
    NERROR_INV_PROTO_FAM = NERROR_ERRNO_START + EPFNOSUPPORT, /**< Protocol family not supported. */
    NERROR_INV_ADDR_FAM = NERROR_ERRNO_START + EAFNOSUPPORT, /**< Address family not supported by protocol. */
    NERROR_ADDR_IN_USE = NERROR_ERRNO_START + EADDRINUSE, /**< Address already in use. */
    NERROR_ADDR_NOT_AVAILABLE = NERROR_ERRNO_START + EADDRNOTAVAIL, /**< Cannot assign requested address. */
    NERROR_NET_DOWN = NERROR_ERRNO_START + ENETDOWN, /**< Network is down. */
    NERROR_NET_UNREACHABLE = NERROR_ERRNO_START + ENETUNREACH, /**< Network is unreachable. */
    NERROR_NET_RESET = NERROR_ERRNO_START + ENETRESET, /**< Network dropped connection on reset. */
    NERROR_CONN_ABORTED = NERROR_ERRNO_START + ECONNABORTED, /**< Software caused connection abort. */
    NERROR_CONN_RESET = NERROR_ERRNO_START + ECONNRESET, /**< Connection reset by peer. */
    NERROR_NO_BUFFER_SPACE = NERROR_ERRNO_START + ENOBUFS, /**< No buffer space available. */
    NERROR_ALREADY_CONN = NERROR_ERRNO_START + EISCONN, /**< Transport endpoint is already connected. */
    NERROR_NOT_CONN = NERROR_ERRNO_START + ENOTCONN, /**< Transport endpoint is not connected. */
    NERROR_NO_ADDR = NERROR_ERRNO_START + EDESTADDRREQ, /**< Destination address required. */
    NERROR_SOCK_SHUTDOWN = NERROR_ERRNO_START + ESHUTDOWN, /**< Cannot send after transport endpoint shutdown. */
    NERROR_MAX_REFS = NERROR_ERRNO_START + ETOOMANYREFS, /**< Too many references: cannot splice. */
    NERROR_CONN_TIMEOUT = NERROR_ERRNO_START + ETIMEDOUT, /**< Connection timed out. */
    NERROR_CONN_REFUSED = NERROR_ERRNO_START + ECONNREFUSED, /**< Connection refused. */
    NERROR_LINK_LOOP = NERROR_ERRNO_START + ELOOP, /**< Too many levels of symbolic links. */
    NERROR_MAX_FILENAME = NERROR_ERRNO_START + ENAMETOOLONG, /**< File name too long. */
    NERROR_HOST_DOWN = NERROR_ERRNO_START + EHOSTDOWN, /**< Host is down. */
    NERROR_HOST_UNREACHABLE = NERROR_ERRNO_START + EHOSTUNREACH, /**< No route to host. */
    NERROR_DIR_NOT_EMPTY = NERROR_ERRNO_START + ENOTEMPTY, /**< Directory not empty. */
    NERROR_MAX_PROCESS = NERROR_ERRNO_START + EPROCLIM, /**< Too many processes. */
    NERROR_MAX_USERS = NERROR_ERRNO_START + EUSERS, /**< Too many users. */
    NERROR_MAX_DISK_QUOTA = NERROR_ERRNO_START + EDQUOT, /**< Disk quota exceeded. */
    NERROR_STALE = NERROR_ERRNO_START + ESTALE, /**< Stale file handle. */
    NERROR_REMOTE = NERROR_ERRNO_START + EREMOTE, /**< Object is remote. */
    NERROR_INV_RPC = NERROR_ERRNO_START + EBADRPC, /**< RPC struct is bad. */
    NERROR_INV_RPC_VERSION = NERROR_ERRNO_START + ERPCMISMATCH, /**< RPC version wrong. */
    NERROR_INV_RPC_PROG = NERROR_ERRNO_START + EPROGUNAVAIL, /**< RPC program not available. */
    NERROR_INV_RPC_PROG_VERSION = NERROR_ERRNO_START + EPROGMISMATCH, /**< RPC program version wrong. */
    NERROR_INV_RPC_PROC = NERROR_ERRNO_START + EPROCUNAVAIL, /**< RPC bad procedure for program. */
    NERROR_NO_FILE_LOCK = NERROR_ERRNO_START + ENOLCK, /**< No locks available. */
    NERROR_INV_FILE_TYPE = NERROR_ERRNO_START + EFTYPE, /**< Inappropriate file type or format. */
    NERROR_AUTH = NERROR_ERRNO_START + EAUTH, /**< Authentication error. */
    NERROR_NO_AUTH = NERROR_ERRNO_START + ENEEDAUTH, /**< Need authenticator. */
    NERROR_FUNC_NOT_SUPPORTED = NERROR_ERRNO_START + ENOSYS, /**< Function not implemented. */
    NERROR_NOT_SUPPORTED = NERROR_ERRNO_START + ENOTSUP, /**< Not supported. */
    NERROR_INV_MULTIBYTE = NERROR_ERRNO_START + EILSEQ, /**< Invalid or incomplete multibyte or wide character. */
    NERROR_INV_BACKGROUND = NERROR_ERRNO_START + EBACKGROUND, /**< Inappropriate operation for background process. */
    NERROR_TRANSLATOR_DIED = NERROR_ERRNO_START + EDIED, /**< Translator died. */
    NERROR_JOKE = NERROR_ERRNO_START + (ED & EGREGIOUS & EIEIO & EGRATUITOUS), /**< You really blew it this time. */
    NERROR_INV_MESSAGE = NERROR_ERRNO_START + EBADMSG, /**< Bad message. */
    NERROR_NO_IDENTIFIER = NERROR_ERRNO_START + EIDRM, /**< Identifier removed. */
    NERROR_MULTIHOP = NERROR_ERRNO_START + EMULTIHOP, /**< Multihop attempted. */
    NERROR_NO_DATA = NERROR_ERRNO_START + ENODATA, /**< No data available. */
    NERROR_NO_LINK = NERROR_ERRNO_START + ENOLINK, /**< Link has been severed. */
    NERROR_NO_MESSAGE = NERROR_ERRNO_START + ENOMSG, /**< No message of desired type. */
    NERROR_NO_STREAM_RESOURCES = NERROR_ERRNO_START + ENOSR, /**< Out of streams resources. */
    NERROR_DEVICE_NOT_STREAM = NERROR_ERRNO_START + ENOSTR, /**< Device not a stream. */
    NERROR_OVERFLOW = NERROR_ERRNO_START + EOVERFLOW, /**< Value too large for defined data type. */
    NERROR_PROTOCOL = NERROR_ERRNO_START + EPROTO, /**< Protocol error. */
    NERROR_TIMER = NERROR_ERRNO_START + ETIME, /**< Timer expired. */
    NERROR_ASYNC_CANCEL = NERROR_ERRNO_START + ECANCELED, /**< Operation canceled. */
    NERROR_OWNER_DIED = NERROR_ERRNO_START + EOWNERDEAD, /**< Owner died. */
    NERROR_NOT_RECOVERABLE = NERROR_ERRNO_START + ENOTRECOVERABLE, /**< State not recoverable. */
    NERROR_DEVICE_OFF = NERROR_ERRNO_START + EPWROFF, /**< Device power is off. */
    NERROR_DEVICE_ERROR = NERROR_ERRNO_START + EDEVERR, /**< Device error, e.g. paper out. */
    NERROR_INV_EXECUTABLE = NERROR_ERRNO_START + EBADEXEC, /**< Bad executable. */
    NERROR_INV_ARCHITECTURE = NERROR_ERRNO_START + EBADARCH, /**< Bad CPU type in executable. */
    NERROR_INV_LIB_VERSION = NERROR_ERRNO_START + ESHLIBVERS, /**< Shared library version mismatch. */
    NERROR_INV_MACHO = NERROR_ERRNO_START + EBADMACHO, /**< Malformed Macho file. */
    NERROR_NO_ATTRIBUTE = NERROR_ERRNO_START + ENOATTR, /**< Attribute not found. */
    NERROR_NO_POLICY = NERROR_ERRNO_START + ENOPOLICY, /**< No such policy registered. */
    NERROR_MAX_QUEUE = NERROR_ERRNO_START + EQFULL, /**< Interface output queue is full. */
    NERROR_MAX_CHANNEL = NERROR_ERRNO_START + ECHRNG, /**< Channel number out of range. */
    NERROR_LVL2_NO_SYNC = NERROR_ERRNO_START + EL2NSYNC, /**< Level 2 not synchronized. */
    NERROR_LVL3_HAULT = NERROR_ERRNO_START + EL3HLT, /**< Level 3 halted. */
    NERROR_LVL3_RESET = NERROR_ERRNO_START + EL3RST, /**< Level 3 reset. */
    NERROR_LINK_NUM = NERROR_ERRNO_START + ELNRNG, /**< Link number out of range. */
    NERROR_PROTO_UNATTACHED = NERROR_ERRNO_START + EUNATCH, /**< Protocol driver not attached. */
    NERROR_NO_CSI = NERROR_ERRNO_START + ENOCSI, /**< No CSI structure available. */
    NERROR_LVL2_HAULT = NERROR_ERRNO_START + EL2HLT, /**< Level 2 haulted. */
    NERROR_INV_EXCHANGE = NERROR_ERRNO_START + EBADE, /**< Invalid exchange. */
    NERROR_INV_REQUEST_DESC = NERROR_ERRNO_START + EBADR, /**< Invalid request descriptor. */
    NERROR_EXCHANGE_FULL = NERROR_ERRNO_START + EXFULL, /**< Exchange full. */
    NERROR_NO_ANODE = NERROR_ERRNO_START + ENOANO, /**< No anode. */
    NERROR_INV_REQUEST_CODE = NERROR_ERRNO_START + EBADRQC, /**< Invalid request code. */
    NERROR_INV_SLOT = NERROR_ERRNO_START + EBADSLT, /**< Invalid slot. */
    NERROR_INV_FONT = NERROR_ERRNO_START + EBFONT, /**< Bad font file format. */
    NERROR_NO_NETWORK = NERROR_ERRNO_START + ENONET, /**< Machine is not on the network. */
    NERROR_NO_PACKAGE = NERROR_ERRNO_START + ENOPKG, /**< Package not installed. */
    NERROR_ADVERTISE = NERROR_ERRNO_START + EADV, /**< Advertise error. */
    NERROR_SRMOUNT = NERROR_ERRNO_START + ESRMNT, /**< Srmount error. */
    NERROR_COMMUNICATION = NERROR_ERRNO_START + ECOMM, /**< Communication error on send. */
    NERROR_DOTDOT = NERROR_ERRNO_START + EDOTDOT, /**< RFS specific error. */
    NERROR_NOT_UNIQUE = NERROR_ERRNO_START + ENOTUNIQ, /**< Name not unique on network. */
    NERROR_INV_FD = NERROR_ERRNO_START + EBADFD, /**< File descriptor in bad state. */
    NERROR_REMOTE_CHANGE = NERROR_ERRNO_START + EREMCHG, /**< Remote address changed. */
    NERROR_NO_LIB = NERROR_ERRNO_START + ELIBACC, /**< Can not access a needed shared library. */
    NERROR_INV_LIB = NERROR_ERRNO_START + ELIBBAD, /**< Accessing a corrupted shared library. */
    NERROR_INV_LIB_SCAN = NERROR_ERRNO_START + ELIBSCN, /**< .lib section in a.out corrupted. */
    NERROR_MAX_LIB = NERROR_ERRNO_START + ELIBMAX, /**< Attempting to link in too many shared libraries. */
    NERROR_EXEC_LIB = NERROR_ERRNO_START + ELIBEXEC, /**< Cannot exec a shared library directly. */
    NERROR_RESTART_CALL = NERROR_ERRNO_START + ERESTART, /**< Interrupted system call should be restarted. */
    NERROR_STR_PIPE = NERROR_ERRNO_START + ESTRPIPE, /**< Streams pipe error. */
    NERROR_CLEAN_STRUCT = NERROR_ERRNO_START + EUCLEAN, /**< Structure needs cleaning. */
    NERROR_NOT_XENIX = NERROR_ERRNO_START + ENOTNAM, /**< Not a XENIX named type file. */
    NERROR_NO_XENIX_SEM = NERROR_ERRNO_START + ENAVAIL, /**< No XENIX semaphores available. */
    NERROR_NAMED = NERROR_ERRNO_START + EISNAM, /**< Is a named type file. */
    NERROR_REMOTE_IO = NERROR_ERRNO_START + EREMOTEIO, /**< Remote I/O error. */
    NERROR_NO_MEDIUM = NERROR_ERRNO_START + ENOMEDIUM, /**< No medium found. */
    NERROR_INV_MEDIUM = NERROR_ERRNO_START + EMEDIUMTYPE, /**< Wrong medium type. */
    NERROR_PROGRAMMER = NERROR_ERRNO_START + EDOOFUS, /**< Programming error. */
    NERROR_FD_INCAPABLE = NERROR_ERRNO_START + ENOTCAPABLE, /**< Capabilities insufficient. */
    NERROR_CAPABILITY_MODE = NERROR_ERRNO_START + ECAPMODE, /**< Not permitted in capability mode. */
    NERROR_INTEGRITY = NERROR_ERRNO_START + EINTEGRITY, /**< Integrity check failed. */
    NERROR_INODE_REMOTE = NERROR_ERRNO_START + ELBIN, /**< Inode is remote. */
    NERROR_NO_MORE_FILES = NERROR_ERRNO_START + ENMFILE, /**< No more files. */
    NERROR_NO_NET_PATH = NERROR_ERRNO_START + ENOSHARE, /**< No such host or network path. */
    NERROR_FILE_CASE = NNERROR_ERRNO_START + ECASECLASH, /**< Filename exists with different case. */
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
NIMBLE_EXTERN
const char * const nErrorStrings[];

/**
 * @brief The lengths of the strings used to represent error codes defined by #nErrors.
 */
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
#define nErrorStr(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorStrings[err] : nErrorStrings[NERROR_UNKNOWN])

/*
 * @brief Gets the length of the error code @p err from #nErrorStrings.
 *
 * @param[in] err The error code to determine the length of.
 * @return @p err's string translation length.
 */
#define nErrorStrLen(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorStrLengths[err] : nErrorStrLengths[NERROR_UNKNOWN])

/**
 * @brief The descriptions of the error codes defined by #nErrors.
 */
NIMBLE_EXTERN
const char * const nErrorDescriptions[];

/**
 * @brief The length of descriptions of the error codes defined by #nErrors.
 */
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
#define nErrorDesc(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorDescriptions[err] : nErrorDescriptions[NERROR_UNKNOWN])

/*
 * @brief Gets the length of the error description @p err from #nErrorDescriptions.
 *
 * @param[in] err The error description to determine the length of.
 * @return @p err's string translation length.
 */
#define nErrorDescLen(err) (((err >= NERROR_MIN) && (err <= NERROR_MAX)) ?\
 nErrorDescLengths[err] : nErrorDescLengths[NERROR_UNKNOWN])

/*
 * @brief Gets the error code of the signal value @p error.
 *
 * @param[in] error The signal value.
 * @return The NERROR version of @p error, or #NERROR_UNKNOWN if out of range.
 */
#define nErrorFromSignal(err) (((err > NERROR_SIGNAL_START) && \
 (err < NERROR_SIGNAL_END)) ? (NERROR_SIGNAL_START + err) : NERROR_UNKNOWN)

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
            size_t infoLen
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
 *     size_t errorLen;
 *     char exampleFilePath[] = "example.txt";
 *     char *errorStr = nErrorToString(&errorLen, NERROR_FILE_NOT_FOUND,
 *      exampleFilePath, sizeof(exampleFilePath))
 *     if (errorStr == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("NERROR_FILE_NOT_FOUND as string: %s\n", errorStr);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @param[in] error The error to get described.
 * @param[in] info Relevant information, such as a file location, that could help
 * diagnose the error. This can be @c #NULL.
 * @param[in] infoLen The length of the @p info argument. A length of zero (0)
 * uses strlen() to determine length.
 * @return @p dst is returned if successful; otherwise @c #NULL is returned.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nErrorToString(size_t *errorLen,
               const nint_t error,
               const char *info,
               size_t infoLen
               )
#ifdef __GNUC__
__attribute__((warn_unused_result))
#endif
;

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
 *  const size_t errorDescLen, const time_t errorTime, const char * stack,
 *  const size_t stackLen)
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
                                    const size_t errorDescLen,
                                    const char *stack,
                                    const size_t stackLen
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
 *     size_t stackLen, stackLevels;
 *     char *stack = nErrorGetStacktrace(&stackLen, &stackLevels);
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
NIMBLE_FREEME
char *
nErrorGetStacktrace(size_t *stackLen,
                    size_t *stackLevels
                    )
#ifdef __GNUC__
__attribute__((warn_unused_result))
#endif
;

#endif // NIMBLE_ENGINE_ERRORS_H

#ifdef __cplusplus
}
#endif

// Errors.h
