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

#define nErrMinStr               "NERROR_MIN"

/* NIMBLE */
#define nErrUnknownStr           "NERROR_UNKNOWN"
#define nErrInternalFailureStr   "NERROR_INTERNAL_FAILURE"
#define nErrNullStr              "NERROR_NULL"
#define nErrInvErrorStr          "NERROR_INV_ERROR"

/* SIGNUM */
#define nErrSigAbrtStr           "NERROR_SIGABRT"
#define nErrSigFpeStr            "NERROR_SIGFPE"
#define nErrSigIllStr            "NERROR_SIGILL"
#define nErrSigIntStr            "NERROR_SIGINT"
#define nErrSigSegvStr           "NERROR_SIGSEGV"
#define nErrSigTermStr           "NERROR_SIGTERM"

/* ERRNO */
#define nErrNoPermStr            "NERROR_NO_PERM"
#define nErrNoFileStr            "NERROR_NO_FILE"
#define nErrNoProcessStr         "NERROR_NO_PROCESS"
#define nErrInterruptStr         "NERROR_INTERRUPT"
#define nErrIOStr                "NERROR_IO"
#define nErrNoDeviceStr          "NERROR_NO_DEVICE"
#define nErrMaxArgsStr           "NERROR_MAX_ARGS"
#define nErrInvExecFormatStr     "NERROR_INV_EXEC_FORMAT"
#define nErrInvFPStr             "NERROR_INV_FP"
#define nErrNoChildStr           "NERROR_NO_CHILD"
#define nErrDeadlockStr          "NERROR_DEADLOCK"
#define nErrNoMemoryStr          "NERROR_NO_MEMORY"
#define nErrNoFilePermStr        "NERROR_NO_FILE_PERM"
#define nErrFaultStr             "NERROR_FAULT"
#define nErrNotBlockStr          "NERROR_NOT_BLOCK"
#define nErrDeviceBusyStr        "NERROR_DEVICE_BUSY"
#define nErrFileExistsStr        "NERROR_FILE_EXISTS"
#define nErrInvCrosslinkStr      "NERROR_INV_CROSSLINK"
#define nErrInvDeviceStr         "NERROR_INV_DEVICE"
#define nErrNotDirStr            "NERROR_NOT_DIR"
#define nErrIsDirStr             "NERROR_IS_DIR"
#define nErrInvArgStr            "NERROR_INV_ARG"
#define nErrMaxFileStr           "NERROR_MAX_FILE"
#define nErrMaxFileSysStr        "NERROR_MAX_FILE_SYS"
#define nErrInvIOCtlStr          "NERROR_INV_IOCTL"
#define nErrTextBusyStr          "NERROR_TEXT_BUSY"
#define nErrFileTooBigStr        "NERROR_FILE_TOO_BIG"
#define nErrNoSpaceStr           "NERROR_NO_SPACE"
#define nErrInvSeekStr           "NERROR_INV_SEEK"
#define nErrReadOnlyStr          "NERROR_READ_ONLY"
#define nErrMaxLinksStr          "NERROR_MAX_LINKS"
#define nErrInvPipeStr           "NERROR_INV_PIPE"
#define nErrDomainStr            "NERROR_DOMAIN"
#define nErrResultTooBigStr      "NERROR_RESULT_TOO_BIG"
#define nErrWouldBlockStr        "NERROR_WOULD_BLOCK"
#define nErrInProgressStr        "NERROR_IN_PROGRESS"
#define nErrAlreadyStr           "NERROR_ALREADY"
#define nErrNotSocketStr         "NERROR_NOT_SOCKET"
#define nErrMaxMessageStr        "NERROR_MAX_MESSAGE"
#define nErrInvProtoTypeStr      "NERROR_INV_PROTO_TYPE"
#define nErrInvProtoOptStr       "NERROR_INV_PROTO_OPT"
#define nErrInvPortocolStr       "NERROR_INV_PROTOCOL"
#define nErrInvSockTypeStr       "NERROR_INV_SOCK_TYPE"
#define nErrInvSockOptStr        "NERROR_INV_SOCK_OPR"
#define nErrInvProtoFamStr       "NERROR_INV_PROTO_FAM"
#define nErrInvAddrFamStr        "NERROR_INV_ADDR_FAM"
#define nErrAddrInUseStr         "NERROR_ADDR_IN_USE"
#define nErrAddrNotAvailableStr  "NERROR_ADDR_NOT_AVAILABLE"
#define nErrNetDownStr           "NERROR_NET_DOWN"
#define nErrNetUnreachableStr    "NERROR_NET_UNREACHABLE"
#define nErrNetResetStr          "NERROR_NET_RESET"
#define nErrConnAbortedStr       "NERROR_CONN_ABORTED"
#define nErrConnResetStr         "NERROR_CONN_RESET"
#define nErrNoBufferSpaceStr     "NERROR_NO_BUFFER_SPACE"
#define nErrAlreadyConnStr       "NERROR_ALREADY_CONN"
#define nErrNotConnStr           "NERROR_NOT_CONN"
#define nErrNoAddrStr            "NERROR_NO_ADDR"
#define nErrSockShutdownStr      "NERROR_SOCK_SHUTDOWN"
#define nErrMaxRefsStr           "NERROR_MAX_REFS"
#define nErrConnTimeoutStr       "NERROR_CONN_TIMEOUT"
#define nErrConnRefusedStr       "NERROR_CONN_REFUSED"
#define nErrLinkLoopStr          "NERROR_LINK_LOOP"
#define nErrMaxFileNameStr       "NERROR_MAX_FILENAME"
#define nErrHostDownStr          "NERROR_HOST_DOWN"
#define nErrHostUnreachableStr   "NERROR_HOST_UNREACHABLE"
#define nErrDirNotEmptyStr       "NERROR_DIR_NOT_EMPTY"
#define nErrMaxProcessStr        "NERROR_MAX_PROCESS"
#define nErrMaxUsersStr          "NERROR_MAX_USERS"
#define nErrMaxDiskQuotaStr      "NERROR_MAX_DISK_QUOTA"
#define nErrStaleStr             "NERROR_STALE"
#define nErrRemoteStr            "NERROR_REMOTE"
#define nErrInvRPCStr            "NERROR_INV_RPC"
#define nErrInvRPCVersionStr     "NERROR_INV_RPC_VERSION"
#define nErrInvRPCProgStr        "NERROR_INV_RPC_PROG"
#define nErrInvRPCProgVersionStr "NERROR_INV_RPC_PROG_VERSION"
#define nErrInvRPCProcStr        "NERROR_INV_RPC_PROC"
#define nErrNoFileLockStr        "NERROR_NO_FILE_LOCK"
#define nErrInvFileTypeStr       "NERROR_INV_FILE_TYPE"
#define nErrAuthStr              "NERROR_AUTH"
#define nErrNoAuthStr            "NERROR_NO_AUTH"
#define nErrFuncNotSupportedStr  "NERROR_FUNC_NOT_SUPPORTED"
#define nErrNotSupportStr        "NERROR_NOT_SUPPORTED"
#define nErrInvMultibyteStr      "NERROR_INV_MULTIBYTE"
#define nErrInvBackgroundStr     "NERROR_INV_BACKGROUND"
#define nErrTranslatorDiedStr    "NERROR_TRANSLATOR_DIED"
#define nErrJokeStr              "NERROR_JOKE"
#define nErrInvMessageStr        "NERROR_INV_MESSAGE"
#define nErrNoIdentifierStr      "NERROR_NO_IDENTIFIER"
#define nErrMultihopStr          "NERROR_MULTIHOP"
#define nErrNoDataStr            "NERROR_NO_DATA"
#define nErrNoLinkStr            "NERROR_NO_LINK"
#define nErrNoMessageStr         "NERROR_NO_MESSAGE"
#define nErrNoStreamResourcesStr "NERROR_NO_STREAM_RESOURCES"
#define nErrDeviceNotStreamStr   "NERROR_DEVICE_NOT_STREAM"
#define nErrOverflowStr          "NERROR_OVERFLOW"
#define nErrProtocolStr          "NERROR_PROTOCOL"
#define nErrTimerStr             "NERROR_TIMER"
#define nErrAsyncCancelStr       "NERROR_ASYNC_CANCEL"
#define nErrOwnerDiedStr         "NERROR_OWNER_DIED"
#define nErrNotRecoverableStr    "NERROR_NOT_RECOVERABLE"
#define nErrDeviceOffStr         "NERROR_DEVICE_OFF"
#define nErrDeviceErrorStr       "NERROR_DEVICE_ERROR"
#define nErrBadExecutableStr     "NERROR_INV_EXECUTABLE"
#define nErrInvArchitectureStr   "NERROR_INV_ARCHITECTURE"
#define nErrInvLibVersionStr     "NERROR_INV_LIB_VERSION"
#define nErrInvMachoStr          "NERROR_INV_MACHO"
#define nErrNoAttributeStr       "NERROR_NO_ATTRIBUTE"
#define nErrNoPolicyStr          "NERROR_NO_POLICY"
#define nErrMaxQueueStr          "NERROR_MAX_QUEUE"

#define nErrMaxStr               "NERROR_MAX"


NCONST_STR nErrorStrings[] = {
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
    nErrBadExecutableStr,
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
    nErrMaxFileNameStr,
    nErrNoFileLockStr,
    nErrFuncNotSupportedStr,
    nErrDirNotEmptyStr,
    nErrInvMultibyteStr,
    nErrAddrInUseStr,
    nErrAddrNotAvailableStr,
    nErrInvAddrFamStr,
    nErrAlreadyStr,
    nErrInvMessageStr,
    nErrAsyncCancelStr,
    nErrConnAbortedStr,
    nErrConnRefusedStr,
    nErrConnResetStr,
    nErrNoAddrStr,
    nErrHostUnreachableStr,
    nErrNoIdentifierStr,
    nErrInProgressStr,
    nErrAlreadyConnStr,
    nErrLinkLoopStr,
    nErrMaxMessageStr,
    nErrNetDownStr,
    nErrNetResetStr,
    nErrNetUnreachableStr,
    nErrNoBufferSpaceStr,
    nErrNoDataStr,
    nErrNoLinkStr,
    nErrNoMessageStr,
    nErrInvProtoOptStr,
    nErrNoStreamResourcesStr,
    nErrDeviceNotStreamStr,
    nErrNotConnStr,
    nErrNotRecoverableStr,
    nErrNotSocketStr,
    nErrNotSupportStr,
    nErrInvSockOptStr,
    nErrOverflowStr,
    nErrOwnerDiedStr,
    nErrProtocolStr,
    nErrInvPortocolStr,
    nErrInvProtoTypeStr,
    nErrTimerStr,
    nErrConnTimeoutStr,
    nErrTextBusyStr,

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
    nErrNoAddrStr,
    nErrMaxMessageStr,
    nErrInvProtoTypeStr,
    nErrInvProtoOptStr,
    nErrInvPortocolStr,
    nErrInvSockTypeStr,
    nErrNotSupportStr,
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
    nErrFuncNotSupportedStr,
    nErrInvFileTypeStr,
    nErrAuthStr,
    nErrNoAuthStr,
    nErrDeviceOffStr,
    nErrDeviceErrorStr,
    nErrOverflowStr,
    nErrBadExecutableStr,
    nErrInvArchitectureStr,
    nErrInvLibVersionStr,
    nErrInvMachoStr,
    nErrAsyncCancelStr,
    nErrNoIdentifierStr,
    nErrNoMessageStr,
    nErrInvMultibyteStr,
    nErrNoAttributeStr,
    nErrInvMessageStr,
    nErrMultihopStr,
    nErrNoDataStr,
    nErrNoLinkStr,
    nErrNoStreamResourcesStr,
    nErrDeviceNotStreamStr,
    nErrProtocolStr,
    nErrTimerStr,
    nErrInvSockOptStr,
    nErrNoPolicyStr,
    nErrNotRecoverableStr,
    nErrOwnerDiedStr,
    nErrMaxQueueStr,

    #elif NIMBLE_OS == NIMBLE_LINUX

    #elif NIMBLE_OS == NIMBLE_ANDROID

    #elif NIMBLE_OS == NIMBLE_POSIX

    #endif
    
    nErrMaxStr
};

const size_t nErrorStrLengths[] = {
    sizeof(nErrMinStr) - 1,
    
    sizeof(nErrUnknownStr) - 1,
    sizeof(nErrInternalFailureStr) - 1,
    sizeof(nErrNullStr) - 1,
    sizeof(nErrInvErrorStr) - 1,
    
    sizeof(nErrSigAbrtStr) - 1,
    sizeof(nErrSigFpeStr) - 1,
    sizeof(nErrSigIllStr) - 1,
    sizeof(nErrSigIntStr) - 1,
    sizeof(nErrSigSegvStr) - 1,
    sizeof(nErrSigTermStr) - 1,
    
    #if 0
    sizeof(nErrNoPermStr) - 1,
    sizeof(nErrNoFileStr) - 1,
    sizeof(nErrNoProcessStr) - 1,
    sizeof(nErrInterruptStr) - 1,
    sizeof(nErrIOStr) - 1,
    sizeof(nErrNoDeviceStr) - 1,
    sizeof(nErrMaxArgsStr) - 1,
    sizeof(nErrInvExecFormatStr) - 1,
    sizeof(nErrNoChildStr) - 1,
    sizeof(nErrDeadlockStr) - 1,
    sizeof(nErrNoMemoryStr) - 1,
    sizeof(nErrNoFilePermStr) - 1,
    sizeof(nErrFaultStr) - 1,
    sizeof(nErrNotBlockStr) - 1,
    sizeof(nErrDeviceBusyStr) - 1,
    sizeof(nErrFileExistsStr) - 1,
    sizeof(nErrInvCrosslinkStr) - 1,
    sizeof(nErrInvDeviceStr) - 1,
    sizeof(nErrNotDirStr) - 1,
    sizeof(nErrIsDirStr) - 1,
    sizeof(nErrInvArgStr) - 1,
    sizeof(nErrMaxFileStr) - 1,
    sizeof(nErrMaxFileSysStr) - 1,
    sizeof(nErrInvIOCtlStr) - 1,
    sizeof(nErrTextBusyStr) - 1,
    sizeof(nErrFileTooBigStr) - 1,
    sizeof(nErrNoSpaceStr) - 1,
    sizeof(nErrInvSeekStr) - 1,
    sizeof(nErrReadOnlyStr) - 1,
    sizeof(nErrMaxLinksStr) - 1,
    sizeof(nErrInvPipeStr) - 1,
    sizeof(nErrDomainStr) - 1,
    sizeof(nErrResultTooBigStr) - 1,
    sizeof(nErrWouldBlockStr) - 1,
    sizeof(nErrInProgressStr) - 1,
    sizeof(nErrAlreadyStr) - 1,
    sizeof(nErrNotSocketStr) - 1,
    sizeof(nErrMaxMessageStr) - 1,
    sizeof(nErrInvProtoTypeStr) - 1,
    sizeof(nErrInvProtoOptStr) - 1,
    sizeof(nErrInvPortocolStr) - 1,
    sizeof(nErrInvSockTypeStr) - 1,
    sizeof(nErrInvSockOptStr) - 1,
    sizeof(nErrInvProtoFamStr) - 1,
    sizeof(nErrInvAddrFamStr) - 1,
    sizeof(nErrAddrInUseStr) - 1,
    sizeof(nErrAddrNotAvailableStr) - 1,
    sizeof(nErrNetDownStr) - 1,
    sizeof(nErrNetUnreachableStr) - 1,
    sizeof(nErrNetResetStr) - 1,
    sizeof(nErrConnAbortedStr) - 1,
    sizeof(nErrConnResetStr) - 1,
    sizeof(nErrNoBufferSpaceStr) - 1,
    sizeof(nErrAlreadyConnStr) - 1,
    sizeof(nErrNotConnStr) - 1,
    sizeof(nErrNoAddrStr) - 1,
    sizeof(nErrSockShutdownStr) - 1,
    sizeof(nErrMaxRefsStr) - 1,
    sizeof(nErrConnTimeoutStr) - 1,
    sizeof(nErrConnRefusedStr) - 1,
    sizeof(nErrLinkLoopStr) - 1,
    sizeof(nErrMaxFileNameStr) - 1,
    sizeof(nErrHostDownStr) - 1,
    sizeof(nErrHostUnreachableStr) - 1,
    sizeof(nErrDirNotEmptyStr) - 1,
    sizeof(nErrMaxProcessStr) - 1,
    sizeof(nErrMaxUsersStr) - 1,
    sizeof(nErrMaxDiskQuotaStr) - 1,
    sizeof(nErrStaleStr) - 1,
    sizeof(nErrRemoteStr) - 1,
    sizeof(nErrInvRPCStr) - 1,
    sizeof(nErrInvRPCVersionStr) - 1,
    sizeof(nErrInvRPCProgStr) - 1,
    sizeof(nErrInvRPCProgVersionStr) - 1,
    sizeof(nErrInvRPCProcStr) - 1,
    sizeof(nErrNoFileLockStr) - 1,
    sizeof(nErrInvFileTypeStr) - 1,
    sizeof(nErrAuthStr) - 1,
    sizeof(nErrNoAuthStr) - 1,
    sizeof(nErrFuncNotSupportedStr) - 1,
    sizeof(nErrNotSupportStr) - 1,
    sizeof(nErrInvMultibyteStr) - 1,
    sizeof(nErrInvBackgroundStr) - 1,
    sizeof(nErrTranslatorDiedStr) - 1,
    sizeof(nErrJokeStr) - 1,
    sizeof(nErrInvMessageStr) - 1,
    sizeof(nErrNoIdentifierStr) - 1,
    sizeof(nErrMultihopStr) - 1,
    sizeof(nErrNoDataStr) - 1,
    sizeof(nErrNoLinkStr) - 1,
    sizeof(nErrNoMessageStr) - 1,
    sizeof(nErrNoStreamResourcesStr) - 1,
    sizeof(nErrDeviceNotStreamStr) - 1,
    sizeof(nErrOverflowStr) - 1,
    sizeof(nErrProtocolStr) - 1,
    sizeof(nErrTimerStr) - 1,
    sizeof(nErrAsyncCancelStr) - 1,
    sizeof(nErrOwnerDiedStr) - 1,
    sizeof(nErrNotRecoverableStr) - 1,
    sizeof(nErrDeviceOffStr) - 1,
    sizeof(nErrDeviceErrorStr) - 1,
    sizeof(nErrBadExecutableStr) - 1,
    sizeof(nErrInvArchitectureStr) - 1,
    sizeof(nErrInvLibVersionStr) - 1,
    sizeof(nErrInvMachoStr) - 1,
    sizeof(nErrNoAttributeStr) - 1,
    sizeof(nErrNoPolicyStr) - 1,
    sizeof(nErrMaxQueueStr) - 1,
    #endif

    #if NIMBLE_OS == NIMBLE_WINDOWS
    sizeof(nErrNoPermStr) - 1,
    sizeof(nErrNoFileStr) - 1,
    sizeof(nErrNoProcessStr) - 1,
    sizeof(nErrInterruptStr) - 1,
    sizeof(nErrIOStr) - 1,
    sizeof(nErrNoDeviceStr) - 1,
    sizeof(nErrMaxArgsStr) - 1,
    sizeof(nErrInvExecFormatStr) - 1,
    sizeof(nErrNoChildStr) - 1,
    sizeof(nErrWouldBlockStr) - 1,
    sizeof(nErrNoMemoryStr) - 1,
    sizeof(nErrNoFilePermStr) - 1,
    sizeof(nErrFaultStr) - 1,
    sizeof(nErrDeviceBusyStr) - 1,
    sizeof(nErrFileExistsStr) - 1,
    sizeof(nErrInvCrosslinkStr) - 1,
    sizeof(nErrInvDeviceStr) - 1,
    sizeof(nErrNotDirStr) - 1,
    sizeof(nErrIsDirStr) - 1,
    sizeof(nErrInvArgStr) - 1,
    sizeof(nErrMaxFileSysStr) - 1,
    sizeof(nErrMaxFileStr) - 1,
    sizeof(nErrInvIOCtlStr) - 1,
    sizeof(nErrFileTooBigStr) - 1,
    sizeof(nErrNoSpaceStr) - 1,
    sizeof(nErrInvSeekStr) - 1,
    sizeof(nErrReadOnlyStr) - 1,
    sizeof(nErrMaxLinksStr) - 1,
    sizeof(nErrInvPipeStr) - 1,
    sizeof(nErrDomainStr) - 1,
    sizeof(nErrResultTooBigStr) - 1,
    sizeof(nErrDeadlockStr) - 1,
    sizeof(nErrMaxFileNameStr) - 1,
    sizeof(nErrNoFileLockStr) - 1,
    sizeof(nErrFuncNotSupportedStr) - 1,
    sizeof(nErrDirNotEmptyStr) - 1,
    sizeof(nErrInvMultibyteStr) - 1,
    sizeof(nErrAddrInUseStr) - 1,
    sizeof(nErrAddrNotAvailableStr) - 1,
    sizeof(nErrInvAddrFamStr) - 1,
    sizeof(nErrAlreadyStr) - 1,
    sizeof(nErrInvMessageStr) - 1,
    sizeof(nErrAsyncCancelStr) - 1,
    sizeof(nErrConnAbortedStr) - 1,
    sizeof(nErrConnRefusedStr) - 1,
    sizeof(nErrConnResetStr) - 1,
    sizeof(nErrNoAddrStr) - 1,
    sizeof(nErrHostUnreachableStr) - 1,
    sizeof(nErrNoIdentifierStr) - 1,
    sizeof(nErrInProgressStr) - 1,
    sizeof(nErrAlreadyConnStr) - 1,
    sizeof(nErrLinkLoopStr) - 1,
    sizeof(nErrMaxMessageStr) - 1,
    sizeof(nErrNetDownStr) - 1,
    sizeof(nErrNetResetStr) - 1,
    sizeof(nErrNetUnreachableStr) - 1,
    sizeof(nErrNoBufferSpaceStr) - 1,
    sizeof(nErrNoDataStr) - 1,
    sizeof(nErrNoLinkStr) - 1,
    sizeof(nErrNoMessageStr) - 1,
    sizeof(nErrInvProtoOptStr) - 1,
    sizeof(nErrNoStreamResourcesStr) - 1,
    sizeof(nErrDeviceNotStreamStr) - 1,
    sizeof(nErrNotConnStr) - 1,
    sizeof(nErrNotRecoverableStr) - 1,
    sizeof(nErrNotSocketStr) - 1,
    sizeof(nErrNotSupportStr) - 1,
    sizeof(nErrInvSockOptStr) - 1,
    sizeof(nErrOverflowStr) - 1,
    sizeof(nErrOwnerDiedStr) - 1,
    sizeof(nErrProtocolStr) - 1,
    sizeof(nErrInvPortocolStr) - 1,
    sizeof(nErrInvProtoTypeStr) - 1,
    sizeof(nErrTimerStr) - 1,
    sizeof(nErrConnTimeoutStr) - 1,
    sizeof(nErrTextBusyStr) - 1,

    #elif NIMBLE_OS == NIMBLE_MACOS
    sizeof(nErrNoPermStr) - 1,
    sizeof(nErrNoFileStr) - 1,
    sizeof(nErrNoProcessStr) - 1,
    sizeof(nErrInterruptStr) - 1,
    sizeof(nErrIOStr) - 1,
    sizeof(nErrNoDeviceStr) - 1,
    sizeof(nErrMaxArgsStr) - 1,
    sizeof(nErrInvExecFormatStr) - 1,
    sizeof(nErrInvFPStr) - 1,
    sizeof(nErrNoChildStr) - 1,
    sizeof(nErrDeadlockStr) - 1,
    sizeof(nErrNoMemoryStr) - 1,
    sizeof(nErrNoFilePermStr) - 1,
    sizeof(nErrFaultStr) - 1,
    sizeof(nErrNotBlockStr) - 1,
    sizeof(nErrDeviceBusyStr) - 1,
    sizeof(nErrFileExistsStr) - 1,
    sizeof(nErrInvCrosslinkStr) - 1,
    sizeof(nErrInvDeviceStr) - 1,
    sizeof(nErrNotDirStr) - 1,
    sizeof(nErrIsDirStr) - 1,
    sizeof(nErrInvArgStr) - 1,
    sizeof(nErrMaxFileStr) - 1,
    sizeof(nErrMaxFileSysStr) - 1,
    sizeof(nErrInvIOCtlStr) - 1,
    sizeof(nErrTextBusyStr) - 1,
    sizeof(nErrFileTooBigStr) - 1,
    sizeof(nErrNoSpaceStr) - 1,
    sizeof(nErrInvSeekStr) - 1,
    sizeof(nErrReadOnlyStr) - 1,
    sizeof(nErrMaxLinksStr) - 1,
    sizeof(nErrInvPipeStr) - 1,
    sizeof(nErrDomainStr) - 1,
    sizeof(nErrResultTooBigStr) - 1,
    sizeof(nErrWouldBlockStr) - 1,
    sizeof(nErrInProgressStr) - 1,
    sizeof(nErrAlreadyStr) - 1,
    sizeof(nErrNotSocketStr) - 1,
    sizeof(nErrNoAddrStr) - 1,
    sizeof(nErrMaxMessageStr) - 1,
    sizeof(nErrInvProtoTypeStr) - 1,
    sizeof(nErrInvProtoOptStr) - 1,
    sizeof(nErrInvPortocolStr) - 1,
    sizeof(nErrInvSockTypeStr) - 1,
    sizeof(nErrNotSupportStr) - 1,
    sizeof(nErrInvSockOptStr) - 1,
    sizeof(nErrInvProtoFamStr) - 1,
    sizeof(nErrInvAddrFamStr) - 1,
    sizeof(nErrAddrInUseStr) - 1,
    sizeof(nErrAddrNotAvailableStr) - 1,
    sizeof(nErrNetDownStr) - 1,
    sizeof(nErrNetUnreachableStr) - 1,
    sizeof(nErrNetResetStr) - 1,
    sizeof(nErrConnAbortedStr) - 1,
    sizeof(nErrConnResetStr) - 1,
    sizeof(nErrNoBufferSpaceStr) - 1,
    sizeof(nErrAlreadyConnStr) - 1,
    sizeof(nErrNotConnStr) - 1,
    sizeof(nErrSockShutdownStr) - 1,
    sizeof(nErrMaxRefsStr) - 1,
    sizeof(nErrConnTimeoutStr) - 1,
    sizeof(nErrConnRefusedStr) - 1,
    sizeof(nErrLinkLoopStr) - 1,
    sizeof(nErrMaxFileNameStr) - 1,
    sizeof(nErrHostDownStr) - 1,
    sizeof(nErrHostUnreachableStr) - 1,
    sizeof(nErrDirNotEmptyStr) - 1,
    sizeof(nErrMaxProcessStr) - 1,
    sizeof(nErrMaxUsersStr) - 1,
    sizeof(nErrMaxDiskQuotaStr) - 1,
    sizeof(nErrStaleStr) - 1,
    sizeof(nErrRemoteStr) - 1,
    sizeof(nErrInvRPCStr) - 1,
    sizeof(nErrInvRPCVersionStr) - 1,
    sizeof(nErrInvRPCProgStr) - 1,
    sizeof(nErrInvRPCProgVersionStr) - 1,
    sizeof(nErrInvRPCProcStr) - 1,
    sizeof(nErrNoFileLockStr) - 1,
    sizeof(nErrFuncNotSupportedStr) - 1,
    sizeof(nErrInvFileTypeStr) - 1,
    sizeof(nErrAuthStr) - 1,
    sizeof(nErrNoAuthStr) - 1,
    sizeof(nErrDeviceOffStr) - 1,
    sizeof(nErrDeviceErrorStr) - 1,
    sizeof(nErrOverflowStr) - 1,
    sizeof(nErrBadExecutableStr) - 1,
    sizeof(nErrInvArchitectureStr) - 1,
    sizeof(nErrInvLibVersionStr) - 1,
    sizeof(nErrInvMachoStr) - 1,
    sizeof(nErrAsyncCancelStr) - 1,
    sizeof(nErrNoIdentifierStr) - 1,
    sizeof(nErrNoMessageStr) - 1,
    sizeof(nErrInvMultibyteStr) - 1,
    sizeof(nErrNoAttributeStr) - 1,
    sizeof(nErrInvMessageStr) - 1,
    sizeof(nErrMultihopStr) - 1,
    sizeof(nErrNoDataStr) - 1,
    sizeof(nErrNoLinkStr) - 1,
    sizeof(nErrNoStreamResourcesStr) - 1,
    sizeof(nErrDeviceNotStreamStr) - 1,
    sizeof(nErrProtocolStr) - 1,
    sizeof(nErrTimerStr) - 1,
    sizeof(nErrInvSockOptStr) - 1,
    sizeof(nErrNoPolicyStr) - 1,
    sizeof(nErrNotRecoverableStr) - 1,
    sizeof(nErrOwnerDiedStr) - 1,
    sizeof(nErrMaxQueueStr) - 1,

    #elif NIMBLE_OS == NIMBLE_LINUX

    #elif NIMBLE_OS == NIMBLE_ANDROID

    #elif NIMBLE_OS == NIMBLE_POSIX

    #endif
    
    sizeof(nErrMaxStr) - 1
};

#define nErrDescMinStr               "The minimum error value, likely "\
"caused by programmer error or a corruption issue."

#define nErrDescUnknownStr           "An unknown error occurred."
#define nErrDescInternalFailureStr   "An internal error occurred within "\
"the Nimble game engine."
#define nErrDescNullStr              "A pointer was null when a nonnull "\
"pointer was expected."
#define nErrDescInvErrorStr          "An error passed to a function was "\
"not valid."

#define nErrDescSigAbrtStr           "Abort. Abnormal termination, such "\
"as is initiated by the function."
#define nErrDescSigFpeStr            "Floating point exception. "\
"Erroneous arithmetic operation, such as zero divide or an operation resulting "\
"in overflow (not necessarily with a floating-point operation)."
#define nErrDescSigIllStr            "Illegal instruction. Invalid "\
"function image, such as an illegal instruction. This is generally due to a "\
"corruption in the code or to an attempt to execute data."
#define nErrDescSigIntStr            "System interrupt. Interactive "\
"attention signal. Generally generated by the application user."
#define nErrDescSigSegvStr           "Segmentation violation. Invalid "\
"access to memory storage. The program tried to read or write outside the "\
"memory it is allocated for it."
#define nErrDescSigTermStr           "System termination. Termination "\
"request sent to program."

#define nErrDescNoPermStr            "Operation not permitted. Only the "\
"owner of the file (or other resource) or processes with special privileges "\
"can perform the operation."
#define nErrDescNoFileStr            "No such file or directory. This is "\
"a \"file doesn't exist\" error for ordinary files that are referenced in "\
"contexts where they are expected to already exist."
#define nErrDescNoProcessStr         "No such process. No process matches "\
"the specified process ID."
#define nErrDescInterruptStr         "Interrupted system call. An "\
"asynchronous signal occurred and prevented completion of the call. When this "\
"happens, you should try the call again."
#define nErrDescIOStr                "Input/output error. Usually used "\
"for physical read or write errors."
#define nErrDescNoDeviceStr          "No such device or address. The "\
"system tried to use the device represented by a file you specified, and it "\
"couldn't find the device. This can mean that the device file was installed "\
"incorrectly, or that the physical device is missing or not correctly attached "\
"to the computer."
#define nErrDescMaxArgsStr           "Argument list too long. Used when "\
"the arguments passed to a new program being executed with one of the exec "\
"functions occupy too much memory space."
#define nErrDescInvExecFormatStr     "Exec format error. Invalid "\
"executable file format. This condition is detected by the exec functions."
#define nErrDescInvFPStr            "Bad file descriptor. For example, "\
"I/O on a descriptor that has been closed or reading from a descriptor open "\
"only for writing (or vice versa)."
#define nErrDescNoChildStr           "No child process. This error "\
"happens on operations that are supposed to manipulate child processes, when "\
"there aren’t any processes to manipulate."
#define nErrDescDeadlockStr          "Resource deadlock avoided. This "\
"error happens on operations that are supposed to manipulate child "\
"processes, when there aren’t any processes to manipulate."
#define nErrDescNoMemoryStr          "Cannot allocate memory. The system "\
"cannot allocate more virtual memory because its capacity is full."
#define nErrDescNoFilePermStr        "Permission denied. The file "\
"permissions do not allow the attempted operation."
#define nErrDescFaultStr             "Bad address. An invalid pointer was "\
"detected."
#define nErrDescNotBlockStr          "Block device required. A file that "\
"isn’t a block special file was given in a situation that requires one. For "\
"example, trying to mount an ordinary file as a file system in Unix gives "\
"this error."
#define nErrDescDeviceBusyStr        "Device or resource busy. A system "\
"resource that can’t be shared is already in use. For example, if you try to "\
"delete a file that is the root of a currently mounted filesystem, you get "\
"this error."
#define nErrDescFileExistsStr        "File exists. An existing file was "\
"specified in a context where it only makes sense to specify a new file."
#define nErrDescInvCrosslinkStr      "Invalid cross-device link. An "\
"attempt to make an improper link across file systems was detected. This "\
"happens not only when you use link(), but also when you rename a file with "\
"rename()."
#define nErrDescInvDeviceStr         "No such device. The wrong type of "\
"device was given to a function that expects a particular sort of device."
#define nErrDescNotDirStr            "Not a directory. A file that isn’t "\
"a directory was specified when a directory is required."
#define nErrDescIsDirStr             "Is a directory. You cannot open a "\
"directory for writing, or create or remove hard links to it."
#define nErrDescInvArgStr            "Invalid argument. This is used to "\
"indicate various kinds of problems with passing the wrong argument to a "\
"library function."
#define nErrDescMaxFileStr           "Too many open files. The current "\
"process has too many files open and can’t open any more. Duplicate "\
"descriptors do count toward this limit."
#define nErrDescMaxFileSysStr        "Too many open files in system. "\
"There are too many distinct file openings in the entire system. Note that any "\
"number of linked channels count as just one file opening."
#define nErrDescInvIOCtlStr          "Inappropriate ioctl for device. "\
"Inappropriate I/O control operation, such as trying to set terminal modes on "\
"an ordinary file."
#define nErrDescTextBusyStr          "Text file busy. An attempt to "\
"execute a file that is currently open for writing, or write to a file that is "\
"currently being executed. Often using a debugger to run a program is "\
"considered having it open for writing and will cause this error."
#define nErrDescFileTooBigStr        "File too large. The size of a file "\
"would be larger than allowed by the system."
#define nErrDescNoSpaceStr           "No space left on device. Write "\
"operation on a file failed because the disk is full."
#define nErrDescInvSeekStr           "Illegal seek. Invalid seek "\
"operation (such as on a pipe)."
#define nErrDescReadOnlyStr          "Read-only file system. An attempt "\
"was made to modify something on a read-only file system."
#define nErrDescMaxLinksStr          "Too many links. The link count of a "\
"single file would become too large. rename() can cause this error if the file "\
"being renamed already has as many links as it can take"
#define nErrDescInvPipeStr           "Broken pipe. There is no process "\
"reading from the other end of a pipe."
#define nErrDescDomainStr            "Numerical argument out of domain. "\
"Used by mathematical functions when an argument value does not fall into the "\
"domain over which the function is defined."
#define nErrDescResultTooBigStr      "Numerical result out of range. Used "\
"by mathematical functions when the result value is not representable because "\
"of overflow or underflow."
#define nErrDescWouldBlockStr        "Resource temporarily unavailable; "\
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
"should report the error to the user and return to its command loop."
#define nErrDescInProgressStr        "Operation now in progress. An "\
"operation that cannot complete immediately was initiated on an object that "\
"has non-blocking mode selected. Some functions that must always block (such "\
"as connect()) never return NERROR_WOULD_BLOCK. Instead, they return "\
"NERROR_IN_PROGRESS to indicate that the operation has begun and will take "\
"some time. Attempts to manipulate the object before the call completes return "\
"NERROR_ALREADY. You can use the select function to find out when the pending "\
"operation has completed."
#define nErrDescAlreadyStr           "Operation already in progress. An "\
"operation is already in progress on an object that has non-blocking mode "\
"selected."
#define nErrDescNotSocketStr         "Socket operation on non-socket. A "\
"file that isn’t a socket was specified when a socket is required."
#define nErrDescMaxMessageStr        "Message too long. The size of a "\
"message sent on a socket was larger than the supported maximum size."
#define nErrDescInvProtoTypeStr      "Protocol wrong type for socket. The "\
"socket type does not support the requested communications protocol."
#define nErrDescInvProtoOptStr       "Protocol not available. You "\
"specified a socket option that doesn’t make sense for the particular protocol "\
"being used by the socket."
#define nErrDescInvPortocolStr       "Protocol not supported. The socket "\
"domain does not support the requested communications protocol (perhaps because "\
"the requested protocol is completely invalid)."
#define nErrDescInvSockTypeStr       "Socket type not supported. The "\
"socket type is not supported for this operation."
#define nErrDescInvSockOptStr        "Operation not supported. The "\
"operation you requested is not supported. Some socket functions don’t make "\
"sense for all types of sockets, and others may not be implemented for all "\
"communications protocols."
#define nErrDescInvProtoFamStr       "Protocol family not supported. The "\
"socket communications protocol family you requested is not supported."
#define nErrDescInvAddrFamStr        "Address family not supported by "\
"protocol. The address family specified for a socket is not supported; it is "\
"inconsistent with the protocol being used on the socket."
#define nErrDescAddrInUseStr         "The requested socket address is "\
"already in use."
#define nErrDescAddrNotAvailableStr  "Cannot assign requested address. "\
"The requested socket address is not available; for example, you tried to "\
"give a socket a name that doesn’t match the local host name."
#define nErrDescNetDownStr           "Network is down. A socket operation "\
"failed because the network was down."
#define nErrDescNetUnreachableStr    "Network is unreachable. A socket "\
"operation failed because the subnet containing the remote host was unreachable."
#define nErrDescNetResetStr          "Network dropped connection on "\
"reset. A network connection was reset because the remote host crashed."
#define nErrDescConnAbortedStr       "Software caused connection abort. A "\
"network connection was aborted locally."
#define nErrDescConnResetStr         "Connection reset by peer. A network "\
"connection was closed for reasons outside the control of the local host, such "\
"as by the remote machine rebooting or an unrecoverable protocol violation."
#define nErrDescNoBufferSpaceStr     "No buffer space available. The "\
"kernel’s buffers for I/O operations are all in use."
#define nErrDescAlreadyConnStr       "Transport endpoint is already "\
"connected. You tried to connect a socket that is already connected."
#define nErrDescNotConnStr           "Transport endpoint is not "\
"connected. The socket is not connected to anything. You get this error when "\
"you try to transmit data over a socket, without first specifying a destination "\
"for the data. For a connectionless socket (for datagram protocols, such as "\
"UDP), you get NERROR_NO_ADDR instead."
#define nErrDescNoAddrStr            "Destination address required. No "\
"default destination address was set for the socket. You get this error when "\
"you try to transmit data over a connectionless socket, without first specifying "\
"a destination for the data with connect()."
#define nErrDescSockShutdownStr      "Cannot send after transport endpoint "\
"shutdown. The socket has already been shut down."
#define nErrDescMaxRefsStr           "Too many references: cannot splice. "\
"The number of \"in-flight\" file descriptors exceeds the file resource limit "\
"and the caller does not have the CAP_SYS_RESOURCE capability. An in-flight "\
"file descriptor is one that has been sent using sendmsg() but has not yet been "\
"accepted in the recipient process using recvmsg()."
#define nErrDescConnTimeoutStr       "Connection timed out. A socket "\
"operation with a specified timeout received no response during the timeout "\
"period."
#define nErrDescConnRefusedStr       "Connection refused. A remote host "\
"refused to allow the network connection (typically because it is not running "\
"the requested service)."
#define nErrDescLinkLoopStr          "Too many levels of symbolic links. "\
"Too many levels of symbolic links were encountered in looking up a file name. "\
"This often indicates a cycle of symbolic links."
#define nErrDescMaxFileNameStr       "File name too long. Filename too "\
"long (longer than PATH_MAX) or host name too long (in gethostname() or "\
"sethostname())."
#define nErrDescHostDownStr          "Host is down. The remote host for "\
"a requested network connection is down."
#define nErrDescHostUnreachableStr   "No route to host. The remote host "\
"for a requested network connection is not reachable."
#define nErrDescDirNotEmptyStr       "Directory not empty. Directory not "\
"empty, where an empty directory was expected. Typically, this error occurs "\
"when you are trying to delete a directory."
#define nErrDescMaxProcessStr        "Too many processes. This means "\
"that the per-user limit on new process would be exceeded by an attempted "\
"fork()."
#define nErrDescMaxUsersStr          "Too many users. The file quota "\
"system is confused because there are too many users."
#define nErrDescMaxDiskQuotaStr      "Disk quota exceeded. The user’s "\
"disk quota was exceeded."
#define nErrDescStaleStr             "Stale file handle. This indicates "\
"an internal confusion in the file system which is due to file system "\
"rearrangements on the server host for NFS file systems or corruption in other "\
"file systems. Repairing this condition usually requires unmounting, possibly "\
"repairing and remounting the file system."
#define nErrDescRemoteStr            "Object is remote. An attempt was "\
"made to NFS-mount a remote file system with a file name that already "\
"specifies an NFS-mounted file."
#define nErrDescInvRPCStr            "RPC struct is bad. Exchange of "\
"RPC information was unsuccessful."
#define nErrDescInvRPCVersionStr     "RPC version wrong. The version "\
"of RPC on the remote peer is not compatible with the local version."
#define nErrDescInvRPCProgStr        "RPC program not available. The "\
"requested program is not registered on the remote host."
#define nErrDescInvRPCProgVersionStr "RPC program version wrong. The "\
"requested version of the program is not available on the remote host(RPC)."
#define nErrDescInvRPCProcStr        "RPC bad procedure for program. "\
"An RPC call was attempted for a procedure which doesn't exist in the remote "\
"program."
#define nErrDescNoFileLockStr        "No locks available. This is "\
"used by the file locking facilities. This can result from an operation to "\
"an NFS server running another operating system."
#define nErrDescInvFileTypeStr       "Inappropriate file type or "\
"format. The file was the wrong type for the operation, or a data file had "\
"the wrong format. On some systems chmod() returns this error if you try to "\
"set the sticky bit on a non - directory file"
#define nErrDescAuthStr              "Authentication error. Attempted "\
"to use an invalid authentica-tion authentication ticket to mount an NFS file "\
"system."
#define nErrDescNoAuthStr            "Need authenticator. An "\
"authentication ticket must be obtained before the given NFS file system may "\
"be mounted."
#define nErrDescFuncNotSupportedStr  "Function not implemented. This "\
"indicates that the function called is not implemented at all, either in the "\
"C library itself or in the operating system. When you get this error, you can "\
"be sure that this particular function will always fail with ENOSYS unless you "\
"install a new version of the C library or the operating system."
#define nErrDescNotSupportStr        "Not supported. A function returns "\
"this error when certain parameter values are valid, but the functionality "\
"they request is not available. This can mean that the function does not "\
"implement a particular command or option value or flag bit at all. For "\
"functions that operate on some object given in a parameter, such as a file "\
"descriptor or a port, it might instead mean that only that specific object "\
"(file descriptor, port, etc.) is unable to support the other parameters "\
"given; different file descriptors might support different ranges of parameter "\
"values. If the entire function is not available at all in the implementation, "\
"it returns NERROR_FUNC_NOT_SUPPORTED instead."
#define nErrDescInvMultibyteStr      "Invalid or incomplete multibyte "\
"or wide character. While decoding a multibyte character the function came "\
"along an invalid or an incomplete sequence of bytes or the given wide "\
"character is invalid."
#define nErrDescInvBackgroundStr     "Inappropriate operation for "\
"background process."
#define nErrDescTranslatorDiedStr    "Translator died. A file returns "\
"this error when the file is translated by a program and the translator "\
"program dies while starting up, before it has connected to the file."
#define nErrDescJokeStr              "You really blew it this time..."
#define nErrDescInvMessageStr        "Bad message. During a read(), "\
"getmsg(), getpmsg(), or ioctl() I_RECVFD request to a STREAMS device, a "\
"message arrived at the head of the STREAM that is inappropriate for the "\
"function receiving the message. Message waiting to be read on a STREAM is "\
"not a data message."
#define nErrDescNoIdentifierStr      "Identifier removed. The message "\
"queue was removed for msgrcv(), msgget(), or msgsnd()."
#define nErrDescMultihopStr          "Multihop attempted."
#define nErrDescNoDataStr            "No data available. No message was "\
"available to be received by the requested operation."
#define nErrDescNoLinkStr            "Link has been severed."
#define nErrDescNoMessageStr         "No message of desired type. An IPC "\
"message queue does not contain a message of the desired type, or a message "\
"catalog does not contain the requested message."
#define nErrDescNoStreamResourcesStr "Out of streams resources."
#define nErrDescDeviceNotStreamStr   "Device not a stream."
#define nErrDescOverflowStr          "Value too large for defined data type."
#define nErrDescProtocolStr          "Protocol error."
#define nErrDescTimerStr             "Timer expired."
#define nErrDescAsyncCancelStr       "Operation canceled."
#define nErrDescOwnerDiedStr         "Owner died."
#define nErrDescNotRecoverableStr    "State not recoverable."
#define nErrDescDeviceOffStr         "Device power is off. Cannot operate "\
"on a powered off device, such as a printer."
#define nErrDescDeviceErrorStr       "Device error. A device error has "\
"occurred, e.g. a printer running out of paper."
#define nErrDescBadExecutableStr     "Bad executable. The executable or "\
"shared library being referenced was malformed."
#define nErrDescInvArchitectureStr   "Bad CPU type in executable. The "\
"executable in question does not support the current CPU."
#define nErrDescInvLibVersionStr     "Shared library version mismatch. "\
"The version of the shared library on the system does not match the version "\
"which was expected."
#define nErrDescInvMachoStr          "Malformed Macho file. The Mach "\
"object file is malformed."
#define nErrDescNoAttributeStr       "Attribute not found. The specified "\
"extended attribute does not exist."
#define nErrDescNoPolicyStr          "No such policy registered."
#define nErrDescMaxQueueStr          "Interface output queue is full."

#define nErrDescMaxStr               "The maximum error value, likely "\
"caused by programmer error or a corruption issue."


NCONST_STR nErrorDescriptions[] = {
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
    nErrDescNoPolicyStr,
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
    nErrDescMaxFileNameStr,
    nErrDescNoFileLockStr,
    nErrDescFuncNotSupportedStr,
    nErrDescDirNotEmptyStr,
    nErrDescInvMultibyteStr,
    nErrDescAddrInUseStr,
    nErrDescAddrNotAvailableStr,
    nErrDescInvAddrFamStr,
    nErrDescAlreadyStr,
    nErrDescInvMessageStr,
    nErrDescAsyncCancelStr,
    nErrDescConnAbortedStr,
    nErrDescConnRefusedStr,
    nErrDescConnResetStr,
    nErrDescNoAddrStr,
    nErrDescHostUnreachableStr,
    nErrDescNoIdentifierStr,
    nErrDescInProgressStr,
    nErrDescAlreadyConnStr,
    nErrDescLinkLoopStr,
    nErrDescMaxMessageStr,
    nErrDescNetDownStr,
    nErrDescNetResetStr,
    nErrDescNetUnreachableStr,
    nErrDescNoBufferSpaceStr,
    nErrDescNoDataStr,
    nErrDescNoLinkStr,
    nErrDescNoMessageStr,
    nErrDescInvProtoOptStr,
    nErrDescNoStreamResourcesStr,
    nErrDescDeviceNotStreamStr,
    nErrDescNotConnStr,
    nErrDescNotRecoverableStr,
    nErrDescNotSocketStr,
    nErrDescNotSupportStr,
    nErrDescInvSockOptStr,
    nErrDescOverflowStr,
    nErrDescOwnerDiedStr,
    nErrDescProtocolStr,
    nErrDescInvPortocolStr,
    nErrDescInvProtoTypeStr,
    nErrDescTimerStr,
    nErrDescConnTimeoutStr,
    nErrDescTextBusyStr,

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
    nErrDescNoAddrStr,
    nErrDescMaxMessageStr,
    nErrDescInvProtoTypeStr,
    nErrDescInvProtoOptStr,
    nErrDescInvPortocolStr,
    nErrDescInvSockTypeStr,
    nErrDescNotSupportStr,
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
    nErrDescFuncNotSupportedStr,
    nErrDescInvFileTypeStr,
    nErrDescAuthStr,
    nErrDescNoAuthStr,
    nErrDescDeviceOffStr,
    nErrDescDeviceErrorStr,
    nErrDescOverflowStr,
    nErrDescBadExecutableStr,
    nErrDescInvArchitectureStr,
    nErrDescInvLibVersionStr,
    nErrDescInvMachoStr,
    nErrDescAsyncCancelStr,
    nErrDescNoIdentifierStr,
    nErrDescNoMessageStr,
    nErrDescInvMultibyteStr,
    nErrDescNoAttributeStr,
    nErrDescInvMessageStr,
    nErrDescMultihopStr,
    nErrDescNoDataStr,
    nErrDescNoLinkStr,
    nErrDescNoStreamResourcesStr,
    nErrDescDeviceNotStreamStr,
    nErrDescProtocolStr,
    nErrDescTimerStr,
    nErrDescInvSockOptStr,
    nErrDescNoPolicyStr,
    nErrDescNotRecoverableStr,
    nErrDescOwnerDiedStr,
    nErrDescMaxQueueStr,

    #elif NIMBLE_OS == NIMBLE_LINUX

    #elif NIMBLE_OS == NIMBLE_ANDROID

    #elif NIMBLE_OS == NIMBLE_POSIX

    #endif
    
    nErrDescMaxStr
};

const size_t nErrorDescLengths[] = {
    sizeof(nErrDescMinStr) - 1,
    
    sizeof(nErrDescUnknownStr) - 1,
    sizeof(nErrDescInternalFailureStr) - 1,
    sizeof(nErrDescNullStr) - 1,
    sizeof(nErrDescInvErrorStr) - 1,
    
    sizeof(nErrDescSigAbrtStr) - 1,
    sizeof(nErrDescSigFpeStr) - 1,
    sizeof(nErrDescSigIllStr) - 1,
    sizeof(nErrDescSigIntStr) - 1,
    sizeof(nErrDescSigSegvStr) - 1,
    sizeof(nErrDescSigTermStr) - 1,
    
    #if 0
    sizeof(nErrDescNoPermStr) - 1,
    sizeof(nErrDescNoFileStr) - 1,
    sizeof(nErrDescNoProcessStr) - 1,
    sizeof(nErrDescInterruptStr) - 1,
    sizeof(nErrDescIOStr) - 1,
    sizeof(nErrDescMaxArgsStr) - 1,
    sizeof(nErrDescInvExecFormatStr) - 1,
    sizeof(nErrDescInvFPStr) - 1,
    sizeof(nErrDescNoChildStr) - 1,
    sizeof(nErrDescDeadlockStr) - 1,
    sizeof(nErrDescNoMemoryStr) - 1,
    sizeof(nErrDescNoFilePermStr) - 1,
    sizeof(nErrDescFaultStr) - 1,
    sizeof(nErrDescNotBlockStr) - 1,
    sizeof(nErrDescDeviceBusyStr) - 1,
    sizeof(nErrDescFileExistsStr) - 1,
    sizeof(nErrDescInvCrosslinkStr) - 1,
    sizeof(nErrDescInvDeviceStr) - 1,
    sizeof(nErrDescNotDirStr) - 1,
    sizeof(nErrDescIsDirStr) - 1,
    sizeof(nErrDescInvArgStr) - 1,
    sizeof(nErrDescMaxFileStr) - 1,
    sizeof(nErrDescMaxFileSysStr) - 1,
    sizeof(nErrDescInvIOCtlStr) - 1,
    sizeof(nErrDescTextBusyStr) - 1,
    sizeof(nErrDescFileTooBigStr) - 1,
    sizeof(nErrDescNoSpaceStr) - 1,
    sizeof(nErrDescInvSeekStr) - 1,
    sizeof(nErrDescReadOnlyStr) - 1,
    sizeof(nErrDescMaxLinksStr) - 1,
    sizeof(nErrDescInvPipeStr) - 1,
    sizeof(nErrDescDomainStr) - 1,
    sizeof(nErrDescResultTooBigStr) - 1,
    sizeof(nErrDescWouldBlockStr) - 1,
    sizeof(nErrDescInProgressStr) - 1,
    sizeof(nErrDescAlreadyStr) - 1,
    sizeof(nErrDescNotSocketStr) - 1,
    sizeof(nErrDescMaxMessageStr) - 1,
    sizeof(nErrDescInvProtoTypeStr) - 1,
    sizeof(nErrDescInvProtoOptStr) - 1,
    sizeof(nErrDescInvPortocolStr) - 1,
    sizeof(nErrDescInvSockTypeStr) - 1,
    sizeof(nErrDescInvSockOptStr) - 1,
    sizeof(nErrDescInvProtoFamStr) - 1,
    sizeof(nErrDescInvAddrFamStr) - 1,
    sizeof(nErrDescAddrInUseStr) - 1,
    sizeof(nErrDescAddrNotAvailableStr) - 1,
    sizeof(nErrDescNetDownStr) - 1,
    sizeof(nErrDescNetUnreachableStr) - 1,
    sizeof(nErrDescNetResetStr) - 1,
    sizeof(nErrDescConnAbortedStr) - 1,
    sizeof(nErrDescConnResetStr) - 1,
    sizeof(nErrDescNoBufferSpaceStr) - 1,
    sizeof(nErrDescAlreadyConnStr) - 1,
    sizeof(nErrDescNotConnStr) - 1,
    sizeof(nErrDescNoAddrStr) - 1,
    sizeof(nErrDescSockShutdownStr) - 1,
    sizeof(nErrDescMaxRefsStr) - 1,
    sizeof(nErrDescConnTimeoutStr) - 1,
    sizeof(nErrDescConnRefusedStr) - 1,
    sizeof(nErrDescLinkLoopStr) - 1,
    sizeof(nErrDescMaxFileNameStr) - 1,
    sizeof(nErrDescHostDownStr) - 1,
    sizeof(nErrDescHostUnreachableStr) - 1,
    sizeof(nErrDescDirNotEmptyStr) - 1,
    sizeof(nErrDescMaxProcessStr) - 1,
    sizeof(nErrDescMaxUsersStr) - 1,
    sizeof(nErrDescMaxDiskQuotaStr) - 1,
    sizeof(nErrDescStaleStr) - 1,
    sizeof(nErrDescRemoteStr) - 1,
    sizeof(nErrDescInvRPCStr) - 1,
    sizeof(nErrDescInvRPCVersionStr) - 1,
    sizeof(nErrDescInvRPCProgStr) - 1,
    sizeof(nErrDescInvRPCProgVersionStr) - 1,
    sizeof(nErrDescInvRPCProcStr) - 1,
    sizeof(nErrDescNoFileLockStr) - 1,
    sizeof(nErrDescInvFileTypeStr) - 1,
    sizeof(nErrDescAuthStr) - 1,
    sizeof(nErrDescNoAuthStr) - 1,
    sizeof(nErrDescFuncNotSupportedStr) - 1,
    sizeof(nErrDescNotSupportStr) - 1,
    sizeof(nErrDescInvMultibyteStr) - 1,
    sizeof(nErrDescInvBackgroundStr) - 1,
    sizeof(nErrDescTranslatorDiedStr) - 1,
    sizeof(nErrDescJokeStr) - 1,
    sizeof(nErrDescInvMessageStr) - 1,
    sizeof(nErrDescNoIdentifierStr) - 1,
    sizeof(nErrDescMultihopStr) - 1,
    sizeof(nErrDescNoDataStr) - 1,
    sizeof(nErrDescNoLinkStr) - 1,
    sizeof(nErrDescNoMessageStr) - 1,
    sizeof(nErrDescNoStreamResourcesStr) - 1,
    sizeof(nErrDescDeviceNotStreamStr) - 1,
    sizeof(nErrDescOverflowStr) - 1,
    sizeof(nErrDescProtocolStr) - 1,
    sizeof(nErrDescTimerStr) - 1,
    sizeof(nErrDescAsyncCancelStr) - 1,
    sizeof(nErrDescOwnerDiedStr) - 1,
    sizeof(nErrDescNotRecoverableStr) - 1,
    sizeof(nErrDescDeviceOffStr) - 1,
    sizeof(nErrDescDeviceErrorStr) - 1,
    sizeof(nErrDescBadExecutableStr) - 1,
    sizeof(nErrDescInvArchitectureStr) - 1,
    sizeof(nErrDescInvLibVersionStr) - 1,
    sizeof(nErrDescInvMachoStr) - 1,
    sizeof(nErrDescNoAttributeStr) - 1,
    sizeof(nErrDescNoPolicyStr) - 1,
    sizeof(nErrDescMaxQueueStr) - 1,
    #endif

    #if NIMBLE_OS == NIMBLE_WINDOWS
    sizeof(nErrDescNoPermStr) - 1,
    sizeof(nErrDescNoFileStr) - 1,
    sizeof(nErrDescNoProcessStr) - 1,
    sizeof(nErrDescInterruptStr) - 1,
    sizeof(nErrDescIOStr) - 1,
    sizeof(nErrDescMaxArgsStr) - 1,
    sizeof(nErrDescInvExecFormatStr) - 1,
    sizeof(nErrDescInvFPStr) - 1,
    sizeof(nErrDescNoChildStr) - 1,
    sizeof(nErrDescWouldBlockStr) - 1,
    sizeof(nErrDescNoMemoryStr) - 1,
    sizeof(nErrDescNoFilePermStr) - 1,
    sizeof(nErrDescFaultStr) - 1,
    sizeof(nErrDescDeviceBusyStr) - 1,
    sizeof(nErrDescFileExistsStr) - 1,
    sizeof(nErrDescInvCrosslinkStr) - 1,
    sizeof(nErrDescInvDeviceStr) - 1,
    sizeof(nErrDescNotDirStr) - 1,
    sizeof(nErrDescIsDirStr) - 1,
    sizeof(nErrDescInvArgStr) - 1,
    sizeof(nErrDescMaxFileSysStr) - 1,
    sizeof(nErrDescMaxFileStr) - 1,
    sizeof(nErrDescInvIOCtlStr) - 1,
    sizeof(nErrDescFileTooBigStr) - 1,
    sizeof(nErrDescNoSpaceStr) - 1,
    sizeof(nErrDescInvSeekStr) - 1,
    sizeof(nErrDescReadOnlyStr) - 1,
    sizeof(nErrDescMaxLinksStr) - 1,
    sizeof(nErrDescInvPipeStr) - 1,
    sizeof(nErrDescDomainStr) - 1,
    sizeof(nErrDescResultTooBigStr) - 1,
    sizeof(nErrDescDeadlockStr) - 1,
    sizeof(nErrDescMaxFileNameStr) - 1,
    sizeof(nErrDescNoFileLockStr) - 1,
    sizeof(nErrDescFuncNotSupportedStr) - 1,
    sizeof(nErrDescDirNotEmptyStr) - 1,
    sizeof(nErrDescInvMultibyteStr) - 1,
    sizeof(nErrDescAddrInUseStr) - 1,
    sizeof(nErrDescAddrNotAvailableStr) - 1,
    sizeof(nErrDescInvAddrFamStr) - 1,
    sizeof(nErrDescAlreadyStr) - 1,
    sizeof(nErrDescInvMessageStr) - 1,
    sizeof(nErrDescAsyncCancelStr) - 1,
    sizeof(nErrDescConnAbortedStr) - 1,
    sizeof(nErrDescConnRefusedStr) - 1,
    sizeof(nErrDescConnResetStr) - 1,
    sizeof(nErrDescNoAddrStr) - 1,
    sizeof(nErrDescHostUnreachableStr) - 1,
    sizeof(nErrDescNoIdentifierStr) - 1,
    sizeof(nErrDescInProgressStr) - 1,
    sizeof(nErrDescAlreadyConnStr) - 1,
    sizeof(nErrDescLinkLoopStr) - 1,
    sizeof(nErrDescMaxMessageStr) - 1,
    sizeof(nErrDescNetDownStr) - 1,
    sizeof(nErrDescNetResetStr) - 1,
    sizeof(nErrDescNetUnreachableStr) - 1,
    sizeof(nErrDescNoBufferSpaceStr) - 1,
    sizeof(nErrDescNoDataStr) - 1,
    sizeof(nErrDescNoLinkStr) - 1,
    sizeof(nErrDescNoMessageStr) - 1,
    sizeof(nErrDescInvProtoOptStr) - 1,
    sizeof(nErrDescNoStreamResourcesStr) - 1,
    sizeof(nErrDescDeviceNotStreamStr) - 1,
    sizeof(nErrDescNotConnStr) - 1,
    sizeof(nErrDescNotRecoverableStr) - 1,
    sizeof(nErrDescNotSocketStr) - 1,
    sizeof(nErrDescNotSupportStr) - 1,
    sizeof(nErrDescInvSockOptStr) - 1,
    sizeof(nErrDescOverflowStr) - 1,
    sizeof(nErrDescOwnerDiedStr) - 1,
    sizeof(nErrDescProtocolStr) - 1,
    sizeof(nErrDescInvPortocolStr) - 1,
    sizeof(nErrDescInvProtoTypeStr) - 1,
    sizeof(nErrDescTimerStr) - 1,
    sizeof(nErrDescConnTimeoutStr) - 1,
    sizeof(nErrDescTextBusyStr) - 1,

    #elif NIMBLE_OS == NIMBLE_MACOS
    sizeof(nErrDescNoPermStr) - 1,
    sizeof(nErrDescNoFileStr) - 1,
    sizeof(nErrDescNoProcessStr) - 1,
    sizeof(nErrDescInterruptStr) - 1,
    sizeof(nErrDescIOStr) - 1,
    sizeof(nErrDescNoDeviceStr) - 1,
    sizeof(nErrDescMaxArgsStr) - 1,
    sizeof(nErrDescInvExecFormatStr) - 1,
    sizeof(nErrDescInvFPStr) - 1,
    sizeof(nErrDescNoChildStr) - 1,
    sizeof(nErrDescDeadlockStr) - 1,
    sizeof(nErrDescNoMemoryStr) - 1,
    sizeof(nErrDescNoFilePermStr) - 1,
    sizeof(nErrDescFaultStr) - 1,
    sizeof(nErrDescNotBlockStr) - 1,
    sizeof(nErrDescDeviceBusyStr) - 1,
    sizeof(nErrDescFileExistsStr) - 1,
    sizeof(nErrDescInvCrosslinkStr) - 1,
    sizeof(nErrDescInvDeviceStr) - 1,
    sizeof(nErrDescNotDirStr) - 1,
    sizeof(nErrDescIsDirStr) - 1,
    sizeof(nErrDescInvArgStr) - 1,
    sizeof(nErrDescMaxFileStr) - 1,
    sizeof(nErrDescMaxFileSysStr) - 1,
    sizeof(nErrDescInvIOCtlStr) - 1,
    sizeof(nErrDescTextBusyStr) - 1,
    sizeof(nErrDescFileTooBigStr) - 1,
    sizeof(nErrDescNoSpaceStr) - 1,
    sizeof(nErrDescInvSeekStr) - 1,
    sizeof(nErrDescReadOnlyStr) - 1,
    sizeof(nErrDescMaxLinksStr) - 1,
    sizeof(nErrDescInvPipeStr) - 1,
    sizeof(nErrDescDomainStr) - 1,
    sizeof(nErrDescResultTooBigStr) - 1,
    sizeof(nErrDescWouldBlockStr) - 1,
    sizeof(nErrDescInProgressStr) - 1,
    sizeof(nErrDescAlreadyStr) - 1,
    sizeof(nErrDescNotSocketStr) - 1,
    sizeof(nErrDescNoAddrStr) - 1,
    sizeof(nErrDescMaxMessageStr) - 1,
    sizeof(nErrDescInvProtoTypeStr) - 1,
    sizeof(nErrDescInvProtoOptStr) - 1,
    sizeof(nErrDescInvPortocolStr) - 1,
    sizeof(nErrDescInvSockTypeStr) - 1,
    sizeof(nErrDescNotSupportStr) - 1,
    sizeof(nErrDescInvSockOptStr) - 1,
    sizeof(nErrDescInvProtoFamStr) - 1,
    sizeof(nErrDescInvAddrFamStr) - 1,
    sizeof(nErrDescAddrInUseStr) - 1,
    sizeof(nErrDescAddrNotAvailableStr) - 1,
    sizeof(nErrDescNetDownStr) - 1,
    sizeof(nErrDescNetUnreachableStr) - 1,
    sizeof(nErrDescNetResetStr) - 1,
    sizeof(nErrDescConnAbortedStr) - 1,
    sizeof(nErrDescConnResetStr) - 1,
    sizeof(nErrDescNoBufferSpaceStr) - 1,
    sizeof(nErrDescAlreadyConnStr) - 1,
    sizeof(nErrDescNotConnStr) - 1,
    sizeof(nErrDescSockShutdownStr) - 1,
    sizeof(nErrDescMaxRefsStr) - 1,
    sizeof(nErrDescConnTimeoutStr) - 1,
    sizeof(nErrDescConnRefusedStr) - 1,
    sizeof(nErrDescLinkLoopStr) - 1,
    sizeof(nErrDescMaxFileNameStr) - 1,
    sizeof(nErrDescHostDownStr) - 1,
    sizeof(nErrDescHostUnreachableStr) - 1,
    sizeof(nErrDescDirNotEmptyStr) - 1,
    sizeof(nErrDescMaxProcessStr) - 1,
    sizeof(nErrDescMaxUsersStr) - 1,
    sizeof(nErrDescMaxDiskQuotaStr) - 1,
    sizeof(nErrDescStaleStr) - 1,
    sizeof(nErrDescRemoteStr) - 1,
    sizeof(nErrDescInvRPCStr) - 1,
    sizeof(nErrDescInvRPCVersionStr) - 1,
    sizeof(nErrDescInvRPCProgStr) - 1,
    sizeof(nErrDescInvRPCProgVersionStr) - 1,
    sizeof(nErrDescInvRPCProcStr) - 1,
    sizeof(nErrDescNoFileLockStr) - 1,
    sizeof(nErrDescFuncNotSupportedStr) - 1,
    sizeof(nErrDescInvFileTypeStr) - 1,
    sizeof(nErrDescAuthStr) - 1,
    sizeof(nErrDescNoAuthStr) - 1,
    sizeof(nErrDescDeviceOffStr) - 1,
    sizeof(nErrDescDeviceErrorStr) - 1,
    sizeof(nErrDescOverflowStr) - 1,
    sizeof(nErrDescBadExecutableStr) - 1,
    sizeof(nErrDescInvArchitectureStr) - 1,
    sizeof(nErrDescInvLibVersionStr) - 1,
    sizeof(nErrDescInvMachoStr) - 1,
    sizeof(nErrDescAsyncCancelStr) - 1,
    sizeof(nErrDescNoIdentifierStr) - 1,
    sizeof(nErrDescNoMessageStr) - 1,
    sizeof(nErrDescInvMultibyteStr) - 1,
    sizeof(nErrDescNoAttributeStr) - 1,
    sizeof(nErrDescInvMessageStr) - 1,
    sizeof(nErrDescMultihopStr) - 1,
    sizeof(nErrDescNoDataStr) - 1,
    sizeof(nErrDescNoLinkStr) - 1,
    sizeof(nErrDescNoStreamResourcesStr) - 1,
    sizeof(nErrDescDeviceNotStreamStr) - 1,
    sizeof(nErrDescProtocolStr) - 1,
    sizeof(nErrDescTimerStr) - 1,
    sizeof(nErrDescInvSockOptStr) - 1,
    sizeof(nErrDescNoPolicyStr) - 1,
    sizeof(nErrDescNotRecoverableStr) - 1,
    sizeof(nErrDescOwnerDiedStr) - 1,
    sizeof(nErrDescMaxQueueStr) - 1,

    #elif NIMBLE_OS == NIMBLE_LINUX

    #elif NIMBLE_OS == NIMBLE_ANDROID

    #elif NIMBLE_OS == NIMBLE_POSIX

    #endif
    
    sizeof(nErrDescMaxStr) - 1
};


NCONST_STR noInfoStr = "No info.";

/**
 * @brief The default error handler callback.
 * @param[in] error The error number.
 * @param[in] errorDesc The description of @p error.
 * @param[in] errorDescLen The length of the @p errorDesc argument. A length of
 * zero (0) uses strlen() to determine length.
 * @param[in] errorTime The time the error was thrown.
 * @param[in] stack The stacktrace of the thread that caused the crash.
 * @param[in] stackLen The length of the @p stack argument. A length of zero (0)
 * uses strlen() to determine length.
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

void nErrorThrow(const nint_t error, const char *info, nint_t infoLen)
{
    const time_t errorTime = time(NULL);
    
    if (errorCallback == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        NCONST_STR einfoCallbackStr = "Callback argument NULL in nErrorThrow().";
        char *crashErrorDesc;
        nint_t crashErrorDescLen;
        
        nErrorToString(crashErrorDesc, &crashErrorDescLen, NERROR_NULL,
         einfoCallbackStr, NCONST_STR_LEN(einfoCallbackStr));
        nCrashSafe(NERROR_NULL, crashErrorTime, crashErrorDesc,
         crashErrorDescLen);
        /*NO RETURN */
    }
    
    char *errorDesc;
    nint_t errorDescLen;
    if (nErrorToString(errorDesc, &errorDescLen, error, info, infoLen) == NULL)
    {
        const time_t crashErrorTime = time(NULL);
        NCONST_STR einfoParseStr = "Error not found in nErrorThrow().";
        char *crashErrorDesc;
        nint_t crashErrorDescLen;
        
        nErrorToString(crashErrorDesc, &crashErrorDescLen,
         NERROR_INV_ERROR, einfoParseStr, NCONST_STR_LEN(einfoParseStr));
        nCrashSafe(NERROR_INV_ERROR, crashErrorTime, crashErrorDesc,
         crashErrorDescLen);
        /* NO RETURN */
    }
    
    char *stack;
    nint_t stackLen, stackLevels;
    nErrorGetStacktrace(stack, &stackLen, &stackLevels);
    
    errorCallback(error, errorTime, errorDesc, errorDescLen, stack, stackLen);
}

nint_t nErrorToStringLocal(char *dst, nint_t *errorLen,
         const nint_t error, const char *info, nint_t infoLen)
{
    if ((info != NULL) && (infoLen == 0))
    {
        infoLen = strlen(info);
    }
    
    const char *errorDesc = nErrorDesc(error);
    const nint_t descLen = nErrorDescLen(error);
    nint_t errLen;
    if (info == NULL)
    {
        errLen = descLen + NCONST_STR_LEN(noInfoStr);
        dst = nRealloc(dst, errLen + 1);
        nStringCopy(dst, errorDesc, descLen);
        nStringCopy(dst + descLen, noInfoStr, NCONST_STR_LEN(noInfoStr));
    }
    else
    {
        errLen = descLen + infoLen;
        dst = nRealloc(dst, errLen);
        nStringCopy(dst, errorDesc, descLen);
        nStringCopy(dst + descLen, info, infoLen);
    }
    
    if (errorLen != NULL)
    {
        *errorLen = errLen;
    }
    
    return NSUCCESS;
}

char *nErrorToString(char *dst, nint_t *errorLen, const nint_t error,
        const char *info, nint_t infoLen)
{
    nint_t result = nErrorToStringLocal(dst, errorLen, error, info, infoLen);
    if (result != NSUCCESS)
    {
        nint_t errorNumLen = snprintf(NULL, 0, "%d", error) + 1;
        char *errorNumStr = nAlloc(errorNumLen);
        snprintf(errorNumStr, errorNumLen, "%d", error);
        
        nErrorThrow(NERROR_INV_ERROR, errorNumStr, errorNumLen);
        errorNumStr = nFree(errorNumStr);
        return dst;
    }
    
    return dst;
}

nint_t nErrorSetCallback(void (*callback)(const nint_t error,
         const time_t errorTime, const char *errorDesc,
         const nint_t errorDescLen, const char *stack, const nint_t stackLen))
{
    if (callback == NULL)
    {
        NCONST_STR einfoCallbackStr = "Callback argument NULL in "\
         "nErrorSetCallback().";
        nErrorThrow(NERROR_NULL, einfoCallbackStr, NCONST_STR_LEN(einfoCallbackStr));
        return NERROR;
    }
    
    errorCallback = callback;
    return NSUCCESS;
}

char *nErrorGetStacktrace(char *dst, nint_t *stackLen, nint_t *stackLevels)
{
    /** @todo Get stack trace. Remember *stackLevels is max levels */
    return dst;
}

// Errors.c
