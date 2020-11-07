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

/* NIMBLE */
const char nErrUnknownStr[]           = "NERROR_UNKNOWN";
const char nErrInternalFailureStr[]   = "NERROR_INTERNAL_FAILURE";
const char nErrNullStr[]              = "NERROR_NULL";
const char nErrInvErrorStr[]          = "NERROR_INV_ERROR";

/* SIGNUM */
const char nErrSigAbrtStr[]           = "NERROR_SIGABRT";
const char nErrSigFpeStr[]            = "NERROR_SIGFPE";
const char nErrSigIllStr[]            = "NERROR_SIGILL";
const char nErrSigIntStr[]            = "NERROR_SIGINT";
const char nErrSigSegvStr[]           = "NERROR_SIGSEGV";
const char nErrSigTermStr[]           = "NERROR_SIGTERM";

/* ERRNO */
const char nErrNoPermStr[]            = "NERROR_NO_PERM";
const char nErrNoFileStr[]            = "NERROR_NO_FILE";
const char nErrNoProcessStr[]         = "NERROR_NO_PROCESS";
const char nErrInterruptStr[]         = "NERROR_INTERRUPT";
const char nErrIOStr[]                = "NERROR_IO";
const char nErrNoDeviceStr[]          = "NERROR_NO_DEVICE";
const char nErrMaxArgsStr[]           = "NERROR_MAX_ARGS";
const char nErrInvExecFormatStr[]     = "NERROR_INV_EXEC_FORMAT";
const char nErrInvFPStr[]             = "NERROR_INV_FP";
const char nErrNoChildStr[]           = "NERROR_NO_CHILD";
const char nErrDeadlockStr[]          = "NERROR_DEADLOCK";
const char nErrNoMemoryStr[]          = "NERROR_NO_MEMORY";
const char nErrNoFilePermStr[]        = "NERROR_NO_FILE_PERM";
const char nErrFaultStr[]             = "NERROR_FAULT";
const char nErrNotBlockStr[]          = "NERROR_NOT_BLOCK";
const char nErrDeviceBusyStr[]        = "NERROR_DEVICE_BUSY";
const char nErrFileExistsStr[]        = "NERROR_FILE_EXISTS";
const char nErrInvCrosslinkStr[]      = "NERROR_INV_CROSSLINK";
const char nErrInvDeviceStr[]         = "NERROR_INV_DEVICE";
const char nErrNotDirStr[]            = "NERROR_NOT_DIR";
const char nErrIsDirStr[]             = "NERROR_IS_DIR";
const char nErrInvArgStr[]            = "NERROR_INV_ARG";
const char nErrMaxFileStr[]           = "NERROR_MAX_FILE";
const char nErrMaxFileSysStr[]        = "NERROR_MAX_FILE_SYS";
const char nErrInvIOCtlStr[]          = "NERROR_INV_IOCTL";
const char nErrTextBusyStr[]          = "NERROR_TEXT_BUSY";
const char nErrFileTooBigStr[]        = "NERROR_FILE_TOO_BIG";
const char nErrNoSpaceStr[]           = "NERROR_NO_SPACE";
const char nErrInvSeekStr[]           = "NERROR_INV_SEEK";
const char nErrReadOnlyStr[]          = "NERROR_READ_ONLY";
const char nErrMaxLinksStr[]          = "NERROR_MAX_LINKS";
const char nErrInvPipeStr[]           = "NERROR_INV_PIPE";
const char nErrDomainStr[]            = "NERROR_DOMAIN";
const char nErrResultTooBigStr[]      = "NERROR_RESULT_TOO_BIG";
const char nErrWouldBlockStr[]        = "NERROR_WOULD_BLOCK";
const char nErrInProgressStr[]        = "NERROR_IN_PROGRESS";
const char nErrAlreadyStr[]           = "NERROR_ALREADY";
const char nErrNotSocketStr[]         = "NERROR_NOT_SOCKET";
const char nErrMaxMessageStr[]        = "NERROR_MAX_MESSAGE";
const char nErrInvProtoTypeStr[]      = "NERROR_INV_PROTO_TYPE";
const char nErrInvProtoOptStr[]       = "NERROR_INV_PROTO_OPT";
const char nErrInvPortocolStr[]       = "NERROR_INV_PROTOCOL";
const char nErrInvSockTypeStr[]       = "NERROR_INV_SOCK_TYPE";
const char nErrInvSockOptStr[]        = "NERROR_INV_SOCK_OPR";
const char nErrInvProtoFamStr[]       = "NERROR_INV_PROTO_FAM";
const char nErrInvAddrFamStr[]        = "NERROR_INV_ADDR_FAM";
const char nErrAddrInUseStr[]         = "NERROR_ADDR_IN_USE";
const char nErrAddrNotAvailableStr[]  = "NERROR_ADDR_NOT_AVAILABLE";
const char nErrNetDownStr[]           = "NERROR_NET_DOWN";
const char nErrNetUnreachableStr[]    = "NERROR_NET_UNREACHABLE";
const char nErrNetResetStr[]          = "NERROR_NET_RESET";
const char nErrConnAbortedStr[]       = "NERROR_CONN_ABORTED";
const char nErrConnResetStr[]         = "NERROR_CONN_RESET";
const char nErrNoBufferSpaceStr[]     = "NERROR_NO_BUFFER_SPACE";
const char nErrAlreadyConnStr[]       = "NERROR_ALREADY_CONN";
const char nErrNotConnStr[]           = "NERROR_NOT_CONN";
const char nErrNoAddrStr[]            = "NERROR_NO_ADDR";
const char nErrSockShutdownStr[]      = "NERROR_SOCK_SHUTDOWN";
const char nErrMaxRefsStr[]           = "NERROR_MAX_REFS";
const char nErrConnTimeoutStr[]       = "NERROR_CONN_TIMEOUT";
const char nErrConnRefusedStr[]       = "NERROR_CONN_REFUSED";
const char nErrLinkLoopStr[]          = "NERROR_LINK_LOOP";
const char nErrMaxFileNameStr[]       = "NERROR_MAX_FILENAME";
const char nErrHostDownStr[]          = "NERROR_HOST_DOWN";
const char nErrHostUnreachableStr[]   = "NERROR_HOST_UNREACHABLE";
const char nErrDirNotEmptyStr[]       = "NERROR_DIR_NOT_EMPTY";
const char nErrMaxProcessStr[]        = "NERROR_MAX_PROCESS";
const char nErrMaxUsersStr[]          = "NERROR_MAX_USERS";
const char nErrMaxDiskQuotaStr[]      = "NERROR_MAX_DISK_QUOTA";
const char nErrStaleStr[]             = "NERROR_STALE";
const char nErrRemoteStr[]            = "NERROR_REMOTE";
const char nErrInvRPCStr[]            = "NERROR_INV_RPC";
const char nErrInvRPCVersionStr[]     = "NERROR_INV_RPC_VERSION";
const char nErrInvRPCProgStr[]        = "NERROR_INV_RPC_PROG";
const char nErrInvRPCProgVersionStr[] = "NERROR_INV_RPC_PROG_VERSION";
const char nErrInvRPCProcStr[]        = "NERROR_INV_RPC_PROC";
const char nErrNoFileLockStr[]        = "NERROR_NO_FILE_LOCK";
const char nErrInvFileTypeStr[]       = "NERROR_INV_FILE_TYPE";
const char nErrAuthStr[]              = "NERROR_AUTH";
const char nErrNoAuthStr[]            = "NERROR_NO_AUTH";
const char nErrFuncNotSupportedStr[]  = "NERROR_FUNC_NOT_SUPPORTED";
const char nErrNotSupportStr[]        = "NERROR_NOT_SUPPORTED";
const char nErrInvMultibyteStr[]      = "NERROR_INV_MULTIBYTE";
const char nErrInvBackgroundStr[]     = "NERROR_INV_BACKGROUND";
const char nErrTranslatorDiedStr[]    = "NERROR_TRANSLATOR_DIED";
const char nErrJokeStr[]              = "NERROR_JOKE";
const char nErrInvMessageStr[]        = "NERROR_INV_MESSAGE";
const char nErrNoIdentifierStr[]      = "NERROR_NO_IDENTIFIER";
const char nErrMultihopStr[]          = "NERROR_MULTIHOP";
const char nErrNoDataStr[]            = "NERROR_NO_DATA";
const char nErrNoLinkStr[]            = "NERROR_NO_LINK";
const char nErrNoMessageStr[]         = "NERROR_NO_MESSAGE";
const char nErrNoStreamResourcesStr[] = "NERROR_NO_STREAM_RESOURCES";
const char nErrDeviceNotStreamStr[]   = "NERROR_DEVICE_NOT_STREAM";
const char nErrOverflowStr[]          = "NERROR_OVERFLOW";
const char nErrProtocolStr[]          = "NERROR_PROTOCOL";
const char nErrTimerStr[]             = "NERROR_TIMER";
const char nErrAsyncCancelStr[]       = "NERROR_ASYNC_CANCEL";
const char nErrOwnerDiedStr[]         = "NERROR_OWNER_DIED";
const char nErrNotRecoverableStr[]    = "NERROR_NOT_RECOVERABLE";
const char nErrDeviceOffStr[]         = "NERROR_DEVICE_OFF";
const char nErrDeviceErrorStr[]       = "NERROR_DEVICE_ERROR";
const char nErrBadExecutableStr[]     = "NERROR_INV_EXECUTABLE";
const char nErrInvArchitectureStr[]   = "NERROR_INV_ARCHITECTURE";
const char nErrInvLibVersionStr[]     = "NERROR_INV_LIB_VERSION";
const char nErrInvMachoStr[]          = "NERROR_INV_MACHO";
const char nErrNoAttributeStr[]       = "NERROR_NO_ATTRIBUTE";
const char nErrNoPolicyStr[]          = "NERROR_NO_POLICY";
const char nErrMaxQueueStr[]          = "NERROR_MAX_QUEUE";

const char nErrMaxStr[]               = "NERROR_MAX";


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
    
    #if 0
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
    nErrAlreadyStr,
    nErrNotSocketStr,
    nErrMaxMessageStr,
    nErrInvProtoTypeStr,
    nErrInvProtoOptStr,
    nErrInvPortocolStr,
    nErrInvSockTypeStr,
    nErrInvSockOptStr,
    nErrInvProtoFamStr,
    nErrInvAddrFamStr,
    nErrAddrInUseStr,
    nErrAddrNotAvailableStr,
    nErrNetDownStr,
    nErrNetUnreachableStr,
    nErrNetResetStr,
    nErrConnAbortedStr,
    nErrConnResetStr,
    nErrNoBufferSpaceStr,
    nErrAlreadyConnStr,
    nErrNotConnStr,
    nErrNoAddrStr,
    nErrSockShutdownStr,
    nErrMaxRefsStr,
    nErrConnTimeoutStr,
    nErrConnRefusedStr,
    nErrLinkLoopStr,
    nErrMaxFileNameStr,
    nErrHostDownStr,
    nErrHostUnreachableStr,
    nErrDirNotEmptyStr,
    nErrMaxProcessStr,
    nErrMaxUsersStr,
    nErrMaxDiskQuotaStr,
    nErrStaleStr,
    nErrRemoteStr,
    nErrInvRPCStr,
    nErrInvRPCVersionStr,
    nErrInvRPCProgStr,
    nErrInvRPCProgVersionStr,
    nErrInvRPCProcStr,
    nErrNoFileLockStr,
    nErrInvFileTypeStr,
    nErrAuthStr,
    nErrNoAuthStr,
    nErrFuncNotSupportedStr,
    nErrNotSupportStr,
    nErrInvMultibyteStr,
    nErrInvBackgroundStr,
    nErrTranslatorDiedStr,
    nErrJokeStr,
    nErrInvMessageStr,
    nErrNoIdentifierStr,
    nErrMultihopStr,
    nErrNoDataStr,
    nErrNoLinkStr,
    nErrNoMessageStr,
    nErrNoStreamResourcesStr,
    nErrDeviceNotStreamStr,
    nErrOverflowStr,
    nErrProtocolStr,
    nErrTimerStr,
    nErrAsyncCancelStr,
    nErrOwnerDiedStr,
    nErrNotRecoverableStr,
    nErrDeviceOffStr,
    nErrDeviceErrorStr,
    nErrInvArchitectureStr,
    nErrInvLibVersionStr,
    nErrInvMachoStr,
    nErrNoAttributeStr,
    nErrNoPolicyStr,
    nErrMaxQueueStr,
    #endif
    #if NIMBLE_OS == NIMBLE_WINDOWS
    nErrNoPermStr,
    nErrNoFileStr,
    nErrNoProcessStr,
    nErrInterruptStr,
    nErrIOStr,
    nErrNoDeviceStr,
    nErrMaxArgsStr,
    nErrInvExecFormatStr,
    nErrNoChildStr,
    nErrWouldBlockStr,
    nErrNoMemoryStr,
    nErrNoFilePermStr,
    nErrFaultStr,
    nErrDeviceBusyStr,
    nErrFileExistsStr,
    nErrInvCrosslinkStr,
    nErrInvDeviceStr,
    nErrNotDirStr,
    nErrIsDirStr,
    nErrInvArgStr,
    nErrMaxFileSysStr,
    nErrMaxFileStr,
    nErrInvIOCtlStr,
    nErrFileTooBigStr,
    nErrNoSpaceStr,
    nErrInvSeekStr,
    nErrReadOnlyStr,
    nErrMaxLinksStr,
    nErrInvPipeStr,
    nErrDomainStr,
    nErrResultTooBigStr,
    nErrDeadlockStr,
    #elif NIMBLE_OS == NIMBLE_MACOS
    nErrNoPermStr,
    nErrNoFileStr,
    nErrNoProcessStr,
    nErrInterruptStr,
    nErrIOStr,
    nErrNoDeviceStr,
    nErrMaxArgsStr,
    nErrInvExecFormatStr,
    nErrInvFPStr,
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
    nErrAlreadyStr,
    nErrNotSocketStr,
    #elif NIMBLE_OS == NIMBLE_LINUX
    #elif NIMBLE_OS == NIMBLE_ANDROID
    #elif defined(NIMBLE_POSIX)
    #endif
    
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
    
    #if 0
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
    sizeof(nErrAlreadyStr),
    sizeof(nErrNotSocketStr),
    sizeof(nErrMaxMessageStr),
    sizeof(nErrInvProtoTypeStr),
    sizeof(nErrInvProtoOptStr),
    sizeof(nErrInvPortocolStr),
    sizeof(nErrInvSockTypeStr),
    sizeof(nErrInvSockOptStr),
    sizeof(nErrInvProtoFamStr),
    sizeof(nErrInvAddrFamStr),
    sizeof(nErrAddrInUseStr),
    sizeof(nErrAddrNotAvailableStr),
    sizeof(nErrNetDownStr),
    sizeof(nErrNetUnreachableStr),
    sizeof(nErrNetResetStr),
    sizeof(nErrConnAbortedStr),
    sizeof(nErrConnResetStr),
    sizeof(nErrNoBufferSpaceStr),
    sizeof(nErrAlreadyConnStr),
    sizeof(nErrNotConnStr),
    sizeof(nErrNoAddrStr),
    sizeof(nErrSockShutdownStr),
    sizeof(nErrMaxRefsStr),
    sizeof(nErrConnTimeoutStr),
    sizeof(nErrConnRefusedStr),
    sizeof(nErrLinkLoopStr),
    sizeof(nErrMaxFileNameStr),
    sizeof(nErrHostDownStr),
    sizeof(nErrHostUnreachableStr),
    sizeof(nErrDirNotEmptyStr),
    sizeof(nErrMaxProcessStr),
    sizeof(nErrMaxUsersStr),
    sizeof(nErrMaxDiskQuotaStr),
    sizeof(nErrStaleStr),
    sizeof(nErrRemoteStr),
    sizeof(nErrInvRPCStr),
    sizeof(nErrInvRPCVersionStr),
    sizeof(nErrInvRPCProgStr),
    sizeof(nErrInvRPCProgVersionStr),
    sizeof(nErrInvRPCProcStr),
    sizeof(nErrNoFileLockStr),
    sizeof(nErrInvFileTypeStr),
    sizeof(nErrAuthStr),
    sizeof(nErrNoAuthStr),
    sizeof(nErrFuncNotSupportedStr),
    sizeof(nErrNotSupportStr),
    sizeof(nErrInvMultibyteStr),
    sizeof(nErrInvBackgroundStr),
    sizeof(nErrTranslatorDiedStr),
    sizeof(nErrJokeStr),
    sizeof(nErrInvMessageStr),
    sizeof(nErrNoIdentifierStr),
    sizeof(nErrMultihopStr),
    sizeof(nErrNoDataStr),
    sizeof(nErrNoLinkStr),
    sizeof(nErrNoMessageStr),
    sizeof(nErrNoStreamResourcesStr),
    sizeof(nErrDeviceNotStreamStr),
    sizeof(nErrOverflowStr),
    sizeof(nErrProtocolStr),
    sizeof(nErrTimerStr),
    sizeof(nErrAsyncCancelStr),
    sizeof(nErrOwnerDiedStr),
    sizeof(nErrNotRecoverableStr),
    sizeof(nErrDeviceOffStr),
    sizeof(nErrDeviceErrorStr),
    sizeof(nErrInvArchitectureStr),
    sizeof(nErrInvLibVersionStr),
    sizeof(nErrInvMachoStr),
    sizeof(nErrNoAttributeStr),
    sizeof(nErrNoPolicyStr),
    sizeof(nErrMaxQueueStr),
    #endif
    #if NIMBLE_OS == NIMBLE_WINDOWS
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
    sizeof(nErrWouldBlockStr),
    sizeof(nErrNoMemoryStr),
    sizeof(nErrNoFilePermStr),
    sizeof(nErrFaultStr),
    sizeof(nErrDeviceBusyStr),
    sizeof(nErrFileExistsStr),
    sizeof(nErrInvCrosslinkStr),
    sizeof(nErrInvDeviceStr),
    sizeof(nErrNotDirStr),
    sizeof(nErrIsDirStr),
    sizeof(nErrInvArgStr),
    sizeof(nErrMaxFileSysStr),
    sizeof(nErrMaxFileStr),
    sizeof(nErrInvIOCtlStr),
    sizeof(nErrFileTooBigStr),
    sizeof(nErrNoSpaceStr),
    sizeof(nErrInvSeekStr),
    sizeof(nErrReadOnlyStr),
    sizeof(nErrMaxLinksStr),
    sizeof(nErrInvPipeStr),
    sizeof(nErrDomainStr),
    sizeof(nErrResultTooBigStr),
    sizeof(nErrDeadlockStr),
    #elif NIMBLE_OS == NIMBLE_MACOS
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
    sizeof(nErrAlreadyStr),
    sizeof(nErrNotSocketStr),
    #elif NIMBLE_OS == NIMBLE_LINUX
    #elif NIMBLE_OS == NIMBLE_ANDROID
    #elif defined(NIMBLE_POSIX)
    #endif
    
    sizeof(nErrMaxStr)
};

const char nErrDescMinStr[]               = "The minimum error value, likely "\
"caused by programmer error or a corruption issue.";

const char nErrDescUnknownStr[]           = "An unknown error occurred.";
const char nErrDescInternalFailureStr[]   = "An internal error occurred within "\
"the Nimble game engine.";
const char nErrDescNullStr[]              = "A pointer was null when a nonnull "\
"pointer was expected.";
const char nErrDescInvErrorStr[]          = "An error passed to a function was "\
"not valid.";

const char nErrDescSigAbrtStr[]           = "Abort. Abnormal termination, such "\
"as is initiated by the function.";
const char nErrDescSigFpeStr[]            = "Floating point exception. "\
"Erroneous arithmetic operation, such as zero divide or an operation resulting "\
"in overflow (not necessarily with a floating-point operation).";
const char nErrDescSigIllStr[]            = "Illegal instruction. Invalid "\
"function image, such as an illegal instruction. This is generally due to a "\
"corruption in the code or to an attempt to execute data.";
const char nErrDescSigIntStr[]            = "System interrupt. Interactive "\
"attention signal. Generally generated by the application user.";
const char nErrDescSigSegvStr[]           = "Segmentation violation. Invalid "\
"access to memory storage. The program tried to read or write outside the "\
"memory it is allocated for it.";
const char nErrDescSigTermStr[]           = "System termination. Termination "\
"request sent to program.";

const char nErrDescNoPermStr[]            = "Operation not permitted. Only the "\
"owner of the file (or other resource) or processes with special privileges "\
"can perform the operation.";
const char nErrDescNoFileStr[]            = "No such file or directory. This is "\
"a \"file doesn't exist\" error for ordinary files that are referenced in "\
"contexts where they are expected to already exist.";
const char nErrDescNoProcessStr[]         = "No such process. No process matches "\
"the specified process ID.";
const char nErrDescInterruptStr[]         = "Interrupted system call. An "\
"asynchronous signal occurred and prevented completion of the call. When this "\
"happens, you should try the call again.";
const char nErrDescIOStr[]                = "Input/output error. Usually used "\
"for physical read or write errors.";
const char nErrDescNoDeviceStr[]          = "No such device or address. The "\
"system tried to use the device represented by a file you specified, and it "\
"couldn't find the device. This can mean that the device file was installed "\
"incorrectly, or that the physical device is missing or not correctly attached "\
"to the computer.";
const char nErrDescMaxArgsStr[]           = "Argument list too long. Used when "\
"the arguments passed to a new program being executed with one of the exec "\
"functions occupy too much memory space.";
const char nErrDescInvExecFormatStr[]     = "Exec format error. Invalid "\
"executable file format. This condition is detected by the exec functions.";
const char nErrDescInvFPStr[]            = "Bad file descriptor. For example, "\
"I/O on a descriptor that has been closed or reading from a descriptor open "\
"only for writing (or vice versa).";
const char nErrDescNoChildStr[]           = "No child process. This error "\
"happens on operations that are supposed to manipulate child processes, when "\
"there aren’t any processes to manipulate.";
const char nErrDescDeadlockStr[]          = "Resource deadlock avoided. This "\
"error happens on operations that are supposed to manipulate child "\
"processes, when there aren’t any processes to manipulate.";
const char nErrDescNoMemoryStr[]          = "Cannot allocate memory. The system "\
"cannot allocate more virtual memory because its capacity is full.";
const char nErrDescNoFilePermStr[]        = "Permission denied. The file "\
"permissions do not allow the attempted operation.";
const char nErrDescFaultStr[]             = "Bad address. An invalid pointer was "\
"detected.";
const char nErrDescNotBlockStr[]          = "Block device required. A file that "\
"isn’t a block special file was given in a situation that requires one. For "\
"example, trying to mount an ordinary file as a file system in Unix gives "\
"this error.";
const char nErrDescDeviceBusyStr[]        = "Device or resource busy. A system "\
"resource that can’t be shared is already in use. For example, if you try to "\
"delete a file that is the root of a currently mounted filesystem, you get "\
"this error.";
const char nErrDescFileExistsStr[]        = "File exists. An existing file was "\
"specified in a context where it only makes sense to specify a new file.";
const char nErrDescInvCrosslinkStr[]      = "Invalid cross-device link. An "\
"attempt to make an improper link across file systems was detected. This "\
"happens not only when you use link(), but also when you rename a file with "\
"rename().";
const char nErrDescInvDeviceStr[]         = "No such device. The wrong type of "\
"device was given to a function that expects a particular sort of device.";
const char nErrDescNotDirStr[]            = "Not a directory. A file that isn’t "\
"a directory was specified when a directory is required.";
const char nErrDescIsDirStr[]             = "Is a directory. You cannot open a "\
"directory for writing, or create or remove hard links to it.";
const char nErrDescInvArgStr[]            = "Invalid argument. This is used to "\
"indicate various kinds of problems with passing the wrong argument to a "\
"library function.";
const char nErrDescMaxFileStr[]           = "Too many open files. The current "\
"process has too many files open and can’t open any more. Duplicate "\
"descriptors do count toward this limit.";
const char nErrDescMaxFileSysStr[]        = "Too many open files in system. "\
"There are too many distinct file openings in the entire system. Note that any "\
"number of linked channels count as just one file opening.";
const char nErrDescInvIOCtlStr[]          = "Inappropriate ioctl for device. "\
"Inappropriate I/O control operation, such as trying to set terminal modes on "\
"an ordinary file.";
const char nErrDescTextBusyStr[]          = "Text file busy. An attempt to "\
"execute a file that is currently open for writing, or write to a file that is "\
"currently being executed. Often using a debugger to run a program is "\
"considered having it open for writing and will cause this error.";
const char nErrDescFileTooBigStr[]        = "File too large. The size of a file "\
"would be larger than allowed by the system.";
const char nErrDescNoSpaceStr[]           = "No space left on device. Write "\
"operation on a file failed because the disk is full.";
const char nErrDescInvSeekStr[]           = "Illegal seek. Invalid seek "\
"operation (such as on a pipe).";
const char nErrDescReadOnlyStr[]          = "Read-only file system. An attempt "\
"was made to modify something on a read-only file system.";
const char nErrDescMaxLinksStr[]          = "Too many links. The link count of a "\
"single file would become too large. rename() can cause this error if the file "\
"being renamed already has as many links as it can take";
const char nErrDescInvPipeStr[]           = "Broken pipe. There is no process "\
"reading from the other end of a pipe.";
const char nErrDescDomainStr[]            = "Numerical argument out of domain. "\
"Used by mathematical functions when an argument value does not fall into the "\
"domain over which the function is defined.";
const char nErrDescResultTooBigStr[]      = "Numerical result out of range. Used "\
"by mathematical functions when the result value is not representable because "\
"of overflow or underflow.";
const char nErrDescWouldBlockStr[]        = "Resource temporarily unavailable; "\
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
const char nErrDescInProgressStr[]        = "Operation now in progress. An "\
"operation that cannot complete immediately was initiated on an object that "\
"has non-blocking mode selected. Some functions that must always block (such "\
"as connect()) never return NERROR_WOULD_BLOCK. Instead, they return "\
"NERROR_IN_PROGRESS to indicate that the operation has begun and will take "\
"some time. Attempts to manipulate the object before the call completes return "\
"NERROR_ALREADY. You can use the select function to find out when the pending "\
"operation has completed.";
const char nErrDescAlreadyStr[]           = "Operation already in progress. An "\
"operation is already in progress on an object that has non-blocking mode "\
"selected.";
const char nErrDescNotSocketStr[]         = "Socket operation on non-socket. A "\
"file that isn’t a socket was specified when a socket is required.";
const char nErrDescMaxMessageStr[]        = "Message too long. The size of a "\
"message sent on a socket was larger than the supported maximum size.";
const char nErrDescInvProtoTypeStr[]      = "Protocol wrong type for socket. The "\
"socket type does not support the requested communications protocol.";
const char nErrDescInvProtoOptStr[]       = "Protocol not available. You "\
"specified a socket option that doesn’t make sense for the particular protocol "\
"being used by the socket.";
const char nErrDescInvPortocolStr[]       = "Protocol not supported. The socket "\
"domain does not support the requested communications protocol (perhaps because "\
"the requested protocol is completely invalid).";
const char nErrDescInvSockTypeStr[]       = "Socket type not supported. The "\
"socket type is not supported for this operation.";
const char nErrDescInvSockOptStr[]        = "Operation not supported. The "\
"operation you requested is not supported. Some socket functions don’t make "\
"sense for all types of sockets, and others may not be implemented for all "\
"communications protocols.";
const char nErrDescInvProtoFamStr[]       = "Protocol family not supported. The "\
"socket communications protocol family you requested is not supported.";
const char nErrDescInvAddrFamStr[]        = "Address family not supported by "\
"protocol. The address family specified for a socket is not supported; it is "\
"inconsistent with the protocol being used on the socket.";
const char nErrDescAddrInUseStr[]         = "The requested socket address is "\
"already in use.";
const char nErrDescAddrNotAvailableStr[]  = "Cannot assign requested address. "\
"The requested socket address is not available; for example, you tried to "\
"give a socket a name that doesn’t match the local host name.";
const char nErrDescNetDownStr[]           = "Network is down. A socket operation "\
"failed because the network was down.";
const char nErrDescNetUnreachableStr[]    = "Network is unreachable. A socket "\
"operation failed because the subnet containing the remote host was unreachable.";
const char nErrDescNetResetStr[]          = "Network dropped connection on "\
"reset. A network connection was reset because the remote host crashed.";
const char nErrDescConnAbortedStr[]       = "Software caused connection abort. A "\
"network connection was aborted locally.";
const char nErrDescConnResetStr[]         = "Connection reset by peer. A network "\
"connection was closed for reasons outside the control of the local host, such "\
"as by the remote machine rebooting or an unrecoverable protocol violation.";
const char nErrDescNoBufferSpaceStr[]     = "No buffer space available. The "\
"kernel’s buffers for I/O operations are all in use.";
const char nErrDescAlreadyConnStr[]       = "Transport endpoint is already "\
"connected. You tried to connect a socket that is already connected.";
const char nErrDescNotConnStr[]           = "Transport endpoint is not "\
"connected. The socket is not connected to anything. You get this error when "\
"you try to transmit data over a socket, without first specifying a destination "\
"for the data. For a connectionless socket (for datagram protocols, such as "\
"UDP), you get NERROR_NO_ADDR instead.";
const char nErrDescNoAddrStr[]            = "Destination address required. No "\
"default destination address was set for the socket. You get this error when "\
"you try to transmit data over a connectionless socket, without first specifying "\
"a destination for the data with connect().";
const char nErrDescSockShutdownStr[]      = "Cannot send after transport endpoint "\
"shutdown. The socket has already been shut down.";
const char nErrDescMaxRefsStr[]           = "Too many references: cannot splice. "\
"The number of \"in-flight\" file descriptors exceeds the file resource limit "\
"and the caller does not have the CAP_SYS_RESOURCE capability. An in-flight "\
"file descriptor is one that has been sent using sendmsg() but has not yet been "\
"accepted in the recipient process using recvmsg().";
const char nErrDescConnTimeoutStr[]       = "Connection timed out. A socket "\
"operation with a specified timeout received no response during the timeout "\
"period.";
const char nErrDescConnRefusedStr[]       = "Connection refused. A remote host "\
"refused to allow the network connection (typically because it is not running "\
"the requested service).";
const char nErrDescLinkLoopStr[]          = "Too many levels of symbolic links. "\
"Too many levels of symbolic links were encountered in looking up a file name. "\
"This often indicates a cycle of symbolic links.";
const char nErrDescMaxFileNameStr[]       = "File name too long. Filename too "\
"long (longer than PATH_MAX) or host name too long (in gethostname() or "\
"sethostname()).";
const char nErrDescHostDownStr[]          = "Host is down. The remote host for "\
"a requested network connection is down.";
const char nErrDescHostUnreachableStr[]   = "No route to host. The remote host "\
"for a requested network connection is not reachable.";
const char nErrDescDirNotEmptyStr[]       = "Directory not empty. Directory not "\
"empty, where an empty directory was expected. Typically, this error occurs "\
"when you are trying to delete a directory.";
const char nErrDescMaxProcessStr[]        = "Too many processes. This means "\
"that the per-user limit on new process would be exceeded by an attempted "\
"fork().";
const char nErrDescMaxUsersStr[]          = "Too many users. The file quota "\
"system is confused because there are too many users.";
const char nErrDescMaxDiskQuotaStr[]      = "Disk quota exceeded. The user’s "\
"disk quota was exceeded.";
const char nErrDescStaleStr[]             = "Stale file handle. This indicates "\
"an internal confusion in the file system which is due to file system "\
"rearrangements on the server host for NFS file systems or corruption in other "\
"file systems. Repairing this condition usually requires unmounting, possibly "\
"repairing and remounting the file system.";
const char nErrDescRemoteStr[]            = "Object is remote. An attempt was "\
"made to NFS-mount a remote file system with a file name that already "\
"specifies an NFS-mounted file.";
const char nErrDescInvRPCStr[]            = "RPC struct is bad. Exchange of "\
"RPC information was unsuccessful.";
const char nErrDescInvRPCVersionStr[]     = "RPC version wrong. The version "\
"of RPC on the remote peer is not compatible with the local version.";
const char nErrDescInvRPCProgStr[]        = "RPC program not available. The "\
"requested program is not registered on the remote host.";
const char nErrDescInvRPCProgVersionStr[] = "RPC program version wrong. The "\
"requested version of the program is not available on the remote host(RPC).";
const char nErrDescInvRPCProcStr[]        = "RPC bad procedure for program. "\
"An RPC call was attempted for a procedure which doesn't exist in the remote "\
"program.";
const char nErrDescNoFileLockStr[]        = "No locks available. This is "\
"used by the file locking facilities. This can result from an operation to "\
"an NFS server running another operating system.";
const char nErrDescInvFileTypeStr[]       = "Inappropriate file type or "\
"format. The file was the wrong type for the operation, or a data file had "\
"the wrong format. On some systems chmod() returns this error if you try to "\
"set the sticky bit on a non - directory file";
const char nErrDescAuthStr[]              = "Authentication error. Attempted "\
"to use an invalid authentica-tion authentication ticket to mount an NFS file "\
"system.";
const char nErrDescNoAuthStr[]            = "Need authenticator. An "\
"authentication ticket must be obtained before the given NFS file system may "\
"be mounted.";
const char nErrDescFuncNotSupportedStr[]  = "Function not implemented. This "\
"indicates that the function called is not implemented at all, either in the "\
"C library itself or in the operating system. When you get this error, you can "\
"be sure that this particular function will always fail with ENOSYS unless you "\
"install a new version of the C library or the operating system.";
const char nErrDescNotSupportStr[]        = "Not supported. A function returns "\
"this error when certain parameter values are valid, but the functionality "\
"they request is not available. This can mean that the function does not "\
"implement a particular command or option value or flag bit at all. For "\
"functions that operate on some object given in a parameter, such as a file "\
"descriptor or a port, it might instead mean that only that specific object "\
"(file descriptor, port, etc.) is unable to support the other parameters "\
"given; different file descriptors might support different ranges of parameter "\
"values. If the entire function is not available at all in the implementation, "\
"it returns NERROR_FUNC_NOT_SUPPORTED instead.";
const char nErrDescInvMultibyteStr[]      = "Invalid or incomplete multibyte "\
"or wide character. While decoding a multibyte character the function came "\
"along an invalid or an incomplete sequence of bytes or the given wide "\
"character is invalid.";
const char nErrDescInvBackgroundStr[]     = "Inappropriate operation for "\
"background process.";
const char nErrDescTranslatorDiedStr[]    = "Translator died. A file returns "\
"this error when the file is translated by a program and the translator "\
"program dies while starting up, before it has connected to the file.";
const char nErrDescJokeStr[]              = "You really blew it this time...";
const char nErrDescInvMessageStr[]        = "Bad message. During a read(), "\
"getmsg(), getpmsg(), or ioctl() I_RECVFD request to a STREAMS device, a "\
"message arrived at the head of the STREAM that is inappropriate for the "\
"function receiving the message. Message waiting to be read on a STREAM is "\
"not a data message.";
const char nErrDescNoIdentifierStr[]      = "Identifier removed. The message "\
"queue was removed for msgrcv(), msgget(), or msgsnd().";
const char nErrDescMultihopStr[]          = "Multihop attempted.";
const char nErrDescNoDataStr[]            = "No data available. No message was "\
"available to be received by the requested operation.";
const char nErrDescNoLinkStr[]            = "Link has been severed.";
const char nErrDescNoMessageStr[]         = "No message of desired type. An IPC "\
"message queue does not contain a message of the desired type, or a message "\
"catalog does not contain the requested message.";
const char nErrDescNoStreamResourcesStr[] = "Out of streams resources.";
const char nErrDescDeviceNotStreamStr[]   = "Device not a stream.";
const char nErrDescOverflowStr[]          = "Value too large for defined data type.";
const char nErrDescProtocolStr[]          = "Protocol error.";
const char nErrDescTimerStr[]             = "Timer expired.";
const char nErrDescAsyncCancelStr[]       = "Operation canceled.";
const char nErrDescOwnerDiedStr[]         = "Owner died.";
const char nErrDescNotRecoverableStr[]    = "State not recoverable.";
const char nErrDescDeviceOffStr[]         = "Device power is off. Cannot operate "\
"on a powered off device, such as a printer.";
const char nErrDescDeviceErrorStr[]       = "Device error. A device error has "\
"occurred, e.g. a printer running out of paper.";
const char nErrDescBadExecutableStr[]     = "Bad executable. The executable or "\
"shared library being referenced was malformed.";
const char nErrDescInvArchitectureStr[]   = "Bad CPU type in executable. The "\
"executable in question does not support the current CPU.";
const char nErrDescInvLibVersionStr[]     = "Shared library version mismatch. "\
"The version of the shared library on the system does not match the version "\
"which was expected.";
const char nErrDescInvMachoStr[]          = "Malformed Macho file. The Mach "\
"object file is malformed.";
const char nErrDescNoAttributeStr[]       = "Attribute not found. The specified "\
"extended attribute does not exist.";
const char nErrDescNoPolicyStr[]          = "No such policy registered.";
const char nErrDescMaxQueueStr[]          = "Interface output queue is full.";

const char nErrDescMaxStr[]               = "The maximum error value, likely "\
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
    
    #if 0
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
    nErrDescAlreadyStr,
    nErrDescNotSocketStr,
    nErrDescMaxMessageStr,
    nErrDescInvProtoTypeStr,
    nErrDescInvProtoOptStr,
    nErrDescInvPortocolStr,
    nErrDescInvSockTypeStr,
    nErrDescInvSockOptStr,
    nErrDescInvProtoFamStr,
    nErrDescInvAddrFamStr,
    nErrDescAddrInUseStr,
    nErrDescAddrNotAvailableStr,
    nErrDescNetDownStr,
    nErrDescNetUnreachableStr,
    nErrDescNetResetStr,
    nErrDescConnAbortedStr,
    nErrDescConnResetStr,
    nErrDescNoBufferSpaceStr,
    nErrDescAlreadyConnStr,
    nErrDescNotConnStr,
    nErrDescNoAddrStr,
    nErrDescSockShutdownStr,
    nErrDescMaxRefsStr,
    nErrDescConnTimeoutStr,
    nErrDescConnRefusedStr,
    nErrDescLinkLoopStr,
    nErrDescMaxFileNameStr,
    nErrDescHostDownStr,
    nErrDescHostUnreachableStr,
    nErrDescDirNotEmptyStr,
    nErrDescMaxProcessStr,
    nErrDescMaxUsersStr,
    nErrDescMaxDiskQuotaStr,
    nErrDescStaleStr,
    nErrDescRemoteStr,
    nErrDescInvRPCStr,
    nErrDescInvRPCVersionStr,
    nErrDescInvRPCProgStr,
    nErrDescInvRPCProgVersionStr,
    nErrDescInvRPCProcStr,
    nErrDescNoFileLockStr,
    nErrDescInvFileTypeStr,
    nErrDescAuthStr,
    nErrDescNoAuthStr,
    nErrDescFuncNotSupportedStr,
    nErrDescNotSupportStr,
    nErrDescInvMultibyteStr,
    nErrDescInvBackgroundStr,
    nErrDescTranslatorDiedStr,
    nErrDescJokeStr,
    nErrDescInvMessageStr,
    nErrDescNoIdentifierStr,
    nErrDescMultihopStr,
    nErrDescNoDataStr,
    nErrDescNoLinkStr,
    nErrDescNoMessageStr,
    nErrDescNoStreamResourcesStr,
    nErrDescDeviceNotStreamStr,
    nErrDescOverflowStr,
    nErrDescProtocolStr,
    nErrDescTimerStr,
    nErrDescAsyncCancelStr,
    nErrDescOwnerDiedStr,
    nErrDescNotRecoverableStr,
    nErrDescDeviceOffStr,
    nErrDescDeviceErrorStr,
    nErrDescBadExecutableStr,
    nErrDescInvArchitectureStr,
    nErrDescInvLibVersionStr,
    nErrDescInvMachoStr,
    nErrDescNoAttributeStr,
    nerrDescNoPolicyStr,
    nErrDescMaxQueueStr,
    #endif
    #if NIMBLE_OS == NIMBLE_WINDOWS
    nErrDescNoPermStr,
    nErrDescNoFileStr,
    nErrDescNoProcessStr,
    nErrDescInterruptStr,
    nErrDescIOStr,
    nErrDescMaxArgsStr,
    nErrDescInvExecFormatStr,
    nErrDescInvFPStr,
    nErrDescNoChildStr,
    nErrDescWouldBlockStr,
    nErrDescNoMemoryStr,
    nErrDescNoFilePermStr,
    nErrDescFaultStr,
    nErrDescDeviceBusyStr,
    nErrDescFileExistsStr,
    nErrDescInvCrosslinkStr,
    nErrDescInvDeviceStr,
    nErrDescNotDirStr,
    nErrDescIsDirStr,
    nErrDescInvArgStr,
    nErrDescMaxFileSysStr,
    nErrDescMaxFileStr,
    nErrDescInvIOCtlStr,
    nErrDescFileTooBigStr,
    nErrDescNoSpaceStr,
    nErrDescInvSeekStr,
    nErrDescReadOnlyStr,
    nErrDescMaxLinksStr,
    nErrDescInvPipeStr,
    nErrDescDomainStr,
    nErrDescResultTooBigStr,
    nErrDescDeadlockStr,
    #elif NIMBLE_OS == NIMBLE_MACOS
    nErrDescNoPermStr,
    nErrDescNoFileStr,
    nErrDescNoProcessStr,
    nErrDescInterruptStr,
    nErrDescIOStr,
    nErrDescNoDeviceStr,
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
    nErrDescAlreadyStr,
    nErrDescNotSocketStr,
    #elif NIMBLE_OS == NIMBLE_LINUX
    #elif NIMBLE_OS == NIMBLE_ANDROID
    #elif defined(NIMBLE_POSIX)
    #endif
    
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
    
    #if 0
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
    sizeof(nErrDescAlreadyStr),
    sizeof(nErrDescNotSocketStr),
    sizeof(nErrDescMaxMessageStr),
    sizeof(nErrDescInvProtoTypeStr),
    sizeof(nErrDescInvProtoOptStr),
    sizeof(nErrDescInvPortocolStr),
    sizeof(nErrDescInvSockTypeStr),
    sizeof(nErrDescInvSockOptStr),
    sizeof(nErrDescInvProtoFamStr),
    sizeof(nErrDescInvAddrFamStr),
    sizeof(nErrDescAddrInUseStr),
    sizeof(nErrDescAddrNotAvailableStr),
    sizeof(nErrDescNetDownStr),
    sizeof(nErrDescNetUnreachableStr),
    sizeof(nErrDescNetResetStr),
    sizeof(nErrDescConnAbortedStr),
    sizeof(nErrDescConnResetStr),
    sizeof(nErrDescNoBufferSpaceStr),
    sizeof(nErrDescAlreadyConnStr),
    sizeof(nErrDescNotConnStr),
    sizeof(nErrDescNoAddrStr),
    sizeof(nErrDescSockShutdownStr),
    sizeof(nErrDescMaxRefsStr),
    sizeof(nErrDescConnTimeoutStr),
    sizeof(nErrDescConnRefusedStr),
    sizeof(nErrDescLinkLoopStr),
    sizeof(nErrDescMaxFileNameStr),
    sizeof(nErrDescHostDownStr),
    sizeof(nErrDescHostUnreachableStr),
    sizeof(nErrDescDirNotEmptyStr),
    sizeof(nErrDescMaxProcessStr),
    sizeof(nErrDescMaxUsersStr),
    sizeof(nErrDescMaxDiskQuotaStr),
    sizeof(nErrDescStaleStr),
    sizeof(nErrDescRemoteStr),
    sizeof(nErrDescInvRPCStr),
    sizeof(nErrDescInvRPCVersionStr),
    sizeof(nErrDescInvRPCProgStr),
    sizeof(nErrDescInvRPCProgVersionStr),
    sizeof(nErrDescInvRPCProcStr),
    sizeof(nErrDescNoFileLockStr),
    sizeof(nErrDescInvFileTypeStr),
    sizeof(nErrDescAuthStr),
    sizeof(nErrDescNoAuthStr),
    sizeof(nErrDescFuncNotSupportedStr),
    sizeof(nErrDescNotSupportStr),
    sizeof(nErrDescInvMultibyteStr),
    sizeof(nErrDescInvBackgroundStr),
    sizeof(nErrDescTranslatorDiedStr),
    sizeof(nErrDescJokeStr),
    sizeof(nErrDescInvMessageStr),
    sizeof(nErrDescNoIdentifierStr),
    sizeof(nErrDescMultihopStr),
    sizeof(nErrDescNoDataStr),
    sizeof(nErrDescNoLinkStr),
    sizeof(nErrDescNoMessageStr),
    sizeof(nErrDescNoStreamResourcesStr),
    sizeof(nErrDescDeviceNotStreamStr),
    sizeof(nErrDescOverflowStr),
    sizeof(nErrDescProtocolStr),
    sizeof(nErrDescTimerStr),
    sizeof(nErrDescAsyncCancelStr),
    sizeof(nErrDescOwnerDiedStr),
    sizeof(nErrDescNotRecoverableStr),
    sizeof(nErrDescDeviceOffStr),
    sizeof(nErrDescDeviceErrorStr),
    sizeof(nErrDescBadExecutableStr),
    sizeof(nErrDescInvArchitectureStr),
    sizeof(nErrDescInvLibVersionStr),
    sizeof(nErrDescInvMachoStr),
    sizeof(nErrDescNoAttributeStr),
    sizeof(nErrDescNoPolicyStr),
    sizeof(nErrDescMaxQueueStr),
    #endif
    #if NIMBLE_OS == NIMBLE_WINDOWS
    sizeof(nErrDescNoPermStr),
    sizeof(nErrDescNoFileStr),
    sizeof(nErrDescNoProcessStr),
    sizeof(nErrDescInterruptStr),
    sizeof(nErrDescIOStr),
    sizeof(nErrDescMaxArgsStr),
    sizeof(nErrDescInvExecFormatStr),
    sizeof(nErrDescInvFPStr),
    sizeof(nErrDescNoChildStr),
    sizeof(nErrDescWouldBlockStr),
    sizeof(nErrDescNoMemoryStr),
    sizeof(nErrDescNoFilePermStr),
    sizeof(nErrDescFaultStr),
    sizeof(nErrDescDeviceBusyStr),
    sizeof(nErrDescFileExistsStr),
    sizeof(nErrDescInvCrosslinkStr),
    sizeof(nErrDescInvDeviceStr),
    sizeof(nErrDescNotDirStr),
    sizeof(nErrDescIsDirStr),
    sizeof(nErrDescInvArgStr),
    sizeof(nErrDescMaxFileSysStr),
    sizeof(nErrDescMaxFileStr),
    sizeof(nErrDescInvIOCtlStr),
    sizeof(nErrDescFileTooBigStr),
    sizeof(nErrDescNoSpaceStr),
    sizeof(nErrDescInvSeekStr),
    sizeof(nErrDescReadOnlyStr),
    sizeof(nErrDescMaxLinksStr),
    sizeof(nErrDescInvPipeStr),
    sizeof(nErrDescDomainStr),
    sizeof(nErrDescResultTooBigStr),
    sizeof(nErrDescDeadlockStr),
    #elif NIMBLE_OS == NIMBLE_MACOS
    sizeof(nErrDescNoPermStr),
    sizeof(nErrDescNoFileStr),
    sizeof(nErrDescNoProcessStr),
    sizeof(nErrDescInterruptStr),
    sizeof(nErrDescIOStr),
    sizeof(nErrDescNoDeviceStr),
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
    sizeof(nErrDescAlreadyStr),
    sizeof(nErrDescNotSocketStr),
    #elif NIMBLE_OS == NIMBLE_LINUX
    #elif NIMBLE_OS == NIMBLE_ANDROID
    #elif defined(NIMBLE_POSIX)
    #endif
    
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


nint_t nErrorFromErrno(const nint_t err)
{
#if NIMBLE_OS == NIMBLE_WINDOWS
    if (err < 15)
    {
        return NERROR_ERRNO_START + err;
    }
    else if ((err > 15) && (err < 26))
    {
        return NERROR_ERRNO_START + err - 1;
    }
    else if ((err > 26) && (err < 35))
    {
        return NERROR_ERRNO_START + err - 2;
    }
    else if (err == NERROR_DEADLOCK)
    {
        return NERROR_DEADLOCK;
    }
    else if ((err > 37) && (err < 43))
    {
        return NERROR_ERRNO_START + err - 4;
    }
    else if ((err > 99) && (err < 131))
    {
        return NERROR_ERRNO_START + err - 57;
    }
    else if ((err > 131) && (err < 140))
    {
        return NERROR_ERRNO_START + err - 58;
    }
    else if (err == 140)
    {
        return NERROR_WOULD_BLOCK;
    }
    else
    {
        return NERROR_UNKNOWN;
    }
    #elif NIMBLE_OS == NIMBLE_MACOS
    return NERROR_ERRNO_START + err;
    #elif NIMBLE_OS == NIMBLE_LINUX
    #elif NIMBLE_OS == NIMBLE_ANDROID
    #elif defined(NIMBLE_POSIX)
    #else
    #error OS not supported.
    #endif
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
        dst = nRealloc(dst, errLen);
        memcpy(dst, errorDesc, descLen);
        memcpy(dst + descLen - 1, noInfoStr, sizeof(noInfoStr));
    }
    else
    {
        errLen = descLen + infoLen - 1;
        dst = nRealloc(dst, errLen);
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
        char * errorNumStr = nAlloc(errorNumLen);
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
