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
#define nErrSignalStartStr       "NERROR_SIGNAL_START"
#define nErrSigAbrtStr           "NERROR_SIGABRT"
#define nErrSigFpeStr            "NERROR_SIGFPE"
#define nErrSigIllStr            "NERROR_SIGILL"
#define nErrSigIntStr            "NERROR_SIGINT"
#define nErrSigSegvStr           "NERROR_SIGSEGV"
#define nErrSigTermStr           "NERROR_SIGTERM"
#define nErrSignalEndStr         "NERROR_SIGNAL_END"

/* ERRNO */
#define nErrErrnoStartStr        "NERROR_ERRNO_START"
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
#define nErrInvProtocolStr       "NERROR_INV_PROTOCOL"
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
#define nErrNotSupportedStr      "NERROR_NOT_SUPPORTED"
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
#define nErrMaxChannelStr        "NERROR_MAX_CHANNEL"
#define nErrLvl2NoSyncStr        "NERROR_LVL2_NO_SYNC"
#define nErrLvl3HaultStr         "NERROR_LVL3_HAULT"
#define nErrLvl3ResetStr         "NERROR_LVL3_RESET"
#define nErrLinkNumStr           "NERROR_LINK_NUM"
#define nErrProtoUnattachedStr   "NERROR_PROTO_UNATTACHED"
#define nErrNoCSIStr             "NERROR_NO_CSI"
#define nErrLvl2HaultStr         "NERROR_LVL2_HAULT"
#define nErrInvExchangeStr       "NERROR_INV_EXCHANGE"
#define nErrInvRequestDescStr    "NERROR_INV_REQUEST_DESC"
#define nErrExchangeFullStr      "NERROR_EXCHANGE_FULL"
#define nErrNoAnodeStr           "NERROR_NO_ANODE"
#define nErrInvRequestCodeStr    "NERROR_INV_REQUEST_CODE"
#define nErrInvSlotStr           "NERROR_INV_SLOT"
#define nErrInvFontStr           "NERROR_INV_FONT"
#define nErrNoNetworkStr         "NERROR_NO_NETWORK"
#define nErrNoPackageStr         "NERROR_NO_PACKAGE"
#define nErrAdvertiseStr         "NERROR_ADVERTISE"
#define nErrSrmountStr           "NERROR_SRMOUNT"
#define nErrCommunicationStr     "NERROR_COMMUNICATION"
#define nErrDotDotStr            "NERROR_DOTDOT"
#define nErrNotUniqueStr         "NERROR_NOT_UNIQUE"
#define nErrInvFDStr             "NERROR_INV_FD"
#define nErrRemoteChangeStr      "NERROR_REMOTE_CHANGE"
#define nErrNoLibStr             "NERROR_NO_LIB"
#define nErrInvLibStr            "NERROR_INV_LIB"
#define nErrInvLibScanStr        "NERROR_INV_LIB_SCAN"
#define nErrMaxLibStr            "NERROR_MAX_LIB"
#define nErrExecLibStr           "NERROR_EXEC_LIB"
#define nErrRestartCallStr       "NERROR_RESTART_CALL"
#define nErrStrPipeStr           "NERROR_STR_PIPE"
#define nErrCleanStructStr       "NERROR_CLEAN_STRUCT"
#define nErrNotXenixStr          "NERROR_NOT_XENIX"
#define nErrNoXenixSemStr        "NERROR_NO_XENIX_SEM"
#define nErrNamedStr             "NERROR_NAMED"
#define nErrRemoteIOStr          "NERROR_REMOTE_IO"
#define nErrNoMediumStr          "NERROR_NO_MEDIUM"
#define nErrInvMediumStr         "NERROR_INV_MEDIUM"
#define nErrProgrammerStr        "NERROR_PROGRAMMER"
#define nErrFDIncapableStr       "NERROR_FD_INCAPABLE"
#define nErrCapabilityModeStr    "NERROR_CAPABILITY_MODE"
#define nErrIntegrityStr         "NERROR_INTEGRITY"
#define nErrInodeRemoteStr       "NERROR_INODE_REMOTE"
#define nErrNoMoreFilesStr       "NERROR_NO_MORE_FILES"
#define nErrNoNetPathStr         "NERROR_NO_NET_PATH"
#define nErrFileCaseStr          "NERROR_FILE_CASE"
#define nErrErrnoEndStr          "NERROR_ERRNO_END"

#define nErrMaxStr               "NERROR_MAX"


NCONST_STR * const nErrorStrings[] = {
    nErrMinStr,
    
    nErrUnknownStr,
    nErrInternalFailureStr,
    nErrNullStr,
    nErrInvErrorStr,
    
    nErrSignalStartStr,
    nErrSigAbrtStr,
    nErrSigFpeStr,
    nErrSigIllStr,
    nErrSigIntStr,
    nErrSigSegvStr,
    nErrSigTermStr,
    nErrSignalEndStr,
    
    nErrErrnoStartStr,
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
    nErrInvProtocolStr,
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
    nErrNotSupportedStr,
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
    nErrMaxChannelStr,
    nErrLvl2NoSyncStr,
    nErrLvl3HaultStr,
    nErrLvl3ResetStr,
    nErrLinkNumStr,
    nErrProtoUnattachedStr,
    nErrNoCSIStr,
    nErrLvl2HaultStr,
    nErrInvExchangeStr,
    nErrInvRequestDescStr,
    nErrExchangeFullStr,
    nErrNoAnodeStr,
    nErrInvRequestCodeStr,
    nErrInvSlotStr,
    nErrInvFontStr,
    nErrNoNetworkStr,
    nErrNoPackageStr,
    nErrAdvertiseStr,
    nErrSrmountStr,
    nErrCommunicationStr,
    nErrDotDotStr,
    nErrNotUniqueStr,
    nErrInvFDStr,
    nErrRemoteChangeStr,
    nErrNoLibStr,
    nErrInvLibStr,
    nErrInvLibScanStr,
    nErrMaxLibStr,
    nErrExecLibStr,
    nErrRestartCallStr,
    nErrStrPipeStr,
    nErrCleanStructStr,
    nErrNotXenixStr,
    nErrNoXenixSemStr,
    nErrNamedStr,
    nErrRemoteIOStr,
    nErrNoMediumStr,
    nErrInvMediumStr,
    nErrProgrammerStr,
    nErrFDIncapableStr,
    nErrCapabilityModeStr,
    nErrIntegrityStr,
    nErrInodeRemoteStr,
    nErrNoMoreFilesStr,
    nErrNoNetPathStr,
    nErrFileCaseStr,
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
    nErrInvFPStr,
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
    nErrNotSupportedStr,
    nErrInvSockOptStr,
    nErrOverflowStr,
    nErrOwnerDiedStr,
    nErrProtocolStr,
    nErrInvProtocolStr,
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
    nErrInvProtocolStr,
    nErrInvSockTypeStr,
    nErrNotSupportedStr,
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
    
#elif NIMBLE_OS == NIMBLE_ANDROID
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
    nErrWouldBlockStr,
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
    nErrNoMessageStr,
    nErrNoIdentifierStr,
    nErrMaxChannelStr,
    nErrLvl2NoSyncStr,
    nErrLvl3HaultStr,
    nErrLvl3ResetStr,
    nErrLinkNumStr,
    nErrProtoUnattachedStr,
    nErrNoCSIStr,
    nErrLvl2HaultStr,
    nErrDeadlockStr,
    nErrNoFileLockStr,
    nErrInvExchangeStr,
    nErrInvRequestDescStr,
    nErrExchangeFullStr,
    nErrNoAnodeStr,
    nErrInvRequestCodeStr,
    nErrInvSlotStr,
    nErrInvFontStr,
    nErrDeviceNotStreamStr,
    nErrNoDataStr,
    nErrTimerStr,
    nErrNoStreamResourcesStr,
    nErrNoNetworkStr,
    nErrNoPackageStr,
    nErrRemoteStr,
    nErrNoLinkStr,
    nErrAdvertiseStr,
    nErrSrmountStr,
    nErrCommunicationStr,
    nErrProtocolStr,
    nErrMultihopStr,
    nErrInodeRemoteStr,
    nErrDotDotStr,
    nErrInvMessageStr,
    nErrInvFileTypeStr,
    nErrNotUniqueStr,
    nErrInvFDStr,
    nErrRemoteChangeStr,
    nErrNoLibStr,
    nErrInvLibStr,
    nErrInvLibScanStr,
    nErrMaxLibStr,
    nErrExecLibStr,
    nErrFuncNotSupportedStr,
    nErrNoMoreFilesStr,
    nErrDirNotEmptyStr,
    nErrMaxFileNameStr,
    nErrLinkLoopStr,
    nErrInvSockOptStr,
    nErrInvProtoFamStr,
    nErrConnResetStr,
    nErrNoBufferSpaceStr,
    nErrInvAddrFamStr,
    nErrInvProtoTypeStr,
    nErrNotSocketStr,
    nErrInvProtoOptStr,
    nErrSockShutdownStr,
    nErrConnRefusedStr,
    nErrAddrInUseStr,
    nErrConnAbortedStr,
    nErrNetUnreachableStr,
    nErrNetDownStr,
    nErrConnTimeoutStr,
    nErrHostDownStr,
    nErrHostUnreachableStr,
    nErrInProgressStr,
    nErrAlreadyStr,
    nErrNoAddrStr,
    nErrMaxMessageStr,
    nErrInvProtocolStr,
    nErrInvSockTypeStr,
    nErrAddrNotAvailableStr,
    nErrNetResetStr,
    nErrAlreadyConnStr,
    nErrNotConnStr,
    nErrMaxRefsStr,
    nErrMaxProcessStr,
    nErrMaxUsersStr,
    nErrMaxDiskQuotaStr,
    nErrStaleStr,
    nErrNotSupportedStr,
    nErrNoMediumStr,
    nErrNoNetPathStr,
    nErrFileCaseStr,
    nErrInvMultibyteStr,
    nErrOverflowStr,

#elif NIMBLE_OS == NIMBLE_BSD
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
    nErrInvProtocolStr,
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
    nErrSockShutdownStr,
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
    nErrNoIdentifierStr,
    nErrNoMessageStr,
    nErrOverflowStr,
    nErrAsyncCancelStr,
    nErrInvMultibyteStr,
    nErrNoAttributeStr,
    nErrInvMessageStr,
    nErrMultihopStr,
    nErrNoLinkStr,
    nErrProtocolStr,
    nErrFDIncapableStr,
    nErrCapabilityModeStr,
    nErrNotRecoverableStr,
    nErrOwnerDiedStr,
    nErrIntegrityStr,

#elif (NIMBLE_OS == NIMBLE_LINUX) || (NIMBLE_OS == NIMBLE_UNIX)
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
    nErrWouldBlockStr,
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
    nErrDeadlockStr,
    nErrMaxFileNameStr,
    nErrNoFileLockStr,
    nErrFuncNotSupportedStr,
    nErrDirNotEmptyStr,
    nErrLinkLoopStr,
    nErrNoMessageStr,
    nErrNoIdentifierStr,
    nErrMaxChannelStr,
    nErrLvl2NoSyncStr,
    nErrLvl3HaultStr,
    nErrLvl3ResetStr,
    nErrLinkNumStr,
    nErrProtoUnattachedStr,
    nErrNoCSIStr,
    nErrLvl2HaultStr,
    nErrInvExchangeStr,
    nErrInvRequestDescStr,
    nErrExchangeFullStr,
    nErrNoAnodeStr,
    nErrInvRequestCodeStr,
    nErrInvSlotStr,
    nErrInvFontStr,
    nErrDeviceNotStreamStr,
    nErrNoDataStr,
    nErrTimerStr,
    nErrNoStreamResourcesStr,
    nErrNoNetworkStr,
    nErrNoPackageStr,
    nErrRemoteStr,
    nErrNoLinkStr,
    nErrAdvertiseStr,
    nErrSrmountStr,
    nErrCommunicationStr,
    nErrProtocolStr,
    nErrMultihopStr,
    nErrDotDotStr,
    nErrInvMessageStr,
    nErrOverflowStr,
    nErrNotUniqueStr,
    nErrInvFDStr,
    nErrRemoteChangeStr,
    nErrNoLibStr,
    nErrInvLibStr,
    nErrInvLibScanStr,
    nErrMaxLibStr,
    nErrExecLibStr,
    nErrInvMultibyteStr,
    nErrRestartCallStr,
    nErrStrPipeStr,
    nErrMaxUsersStr,
    nErrNotSocketStr,
    nErrNoAddrStr,
    nErrMaxMessageStr,
    nErrInvProtoTypeStr,
    nErrInvProtoOptStr,
    nErrInvProtocolStr,
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
    nErrSockShutdownStr,
    nErrMaxRefsStr,
    nErrConnTimeoutStr,
    nErrConnRefusedStr,
    nErrHostDownStr,
    nErrHostUnreachableStr,
    nErrAlreadyStr,
    nErrInProgressStr,
    nErrStaleStr,
    nErrCleanStructStr,
    nErrNotXenixStr,
    nErrNoXenixSemStr,
    nErrNamedStr,
    nErrRemoteIOStr,
    nErrMaxDiskQuotaStr,
    nErrNoMediumStr,
    nErrInvMediumStr,

#endif
    nErrErrnoEndStr,
    
    nErrMaxStr
};

const size_t nErrorStrLengths[] = {
    NCONST_STR_LEN(nErrMinStr),
    
    NCONST_STR_LEN(nErrUnknownStr),
    NCONST_STR_LEN(nErrInternalFailureStr),
    NCONST_STR_LEN(nErrNullStr),
    NCONST_STR_LEN(nErrInvErrorStr),
    
    NCONST_STR_LEN(nErrSignalStartStr),
    NCONST_STR_LEN(nErrSigAbrtStr),
    NCONST_STR_LEN(nErrSigFpeStr),
    NCONST_STR_LEN(nErrSigIllStr),
    NCONST_STR_LEN(nErrSigIntStr),
    NCONST_STR_LEN(nErrSigSegvStr),
    NCONST_STR_LEN(nErrSigTermStr),
    NCONST_STR_LEN(nErrSignalEndStr),
    
    NCONST_STR_LEN(nErrErrnoStartStr),
#if 0
    NCONST_STR_LEN(nErrNoPermStr),
    NCONST_STR_LEN(nErrNoFileStr),
    NCONST_STR_LEN(nErrNoProcessStr),
    NCONST_STR_LEN(nErrInterruptStr),
    NCONST_STR_LEN(nErrIOStr),
    NCONST_STR_LEN(nErrNoDeviceStr),
    NCONST_STR_LEN(nErrMaxArgsStr),
    NCONST_STR_LEN(nErrInvExecFormatStr),
    NCONST_STR_LEN(nErrNoChildStr),
    NCONST_STR_LEN(nErrDeadlockStr),
    NCONST_STR_LEN(nErrNoMemoryStr),
    NCONST_STR_LEN(nErrNoFilePermStr),
    NCONST_STR_LEN(nErrFaultStr),
    NCONST_STR_LEN(nErrNotBlockStr),
    NCONST_STR_LEN(nErrDeviceBusyStr),
    NCONST_STR_LEN(nErrFileExistsStr),
    NCONST_STR_LEN(nErrInvCrosslinkStr),
    NCONST_STR_LEN(nErrInvDeviceStr),
    NCONST_STR_LEN(nErrNotDirStr),
    NCONST_STR_LEN(nErrIsDirStr),
    NCONST_STR_LEN(nErrInvArgStr),
    NCONST_STR_LEN(nErrMaxFileStr),
    NCONST_STR_LEN(nErrMaxFileSysStr),
    NCONST_STR_LEN(nErrInvIOCtlStr),
    NCONST_STR_LEN(nErrTextBusyStr),
    NCONST_STR_LEN(nErrFileTooBigStr),
    NCONST_STR_LEN(nErrNoSpaceStr),
    NCONST_STR_LEN(nErrInvSeekStr),
    NCONST_STR_LEN(nErrReadOnlyStr),
    NCONST_STR_LEN(nErrMaxLinksStr),
    NCONST_STR_LEN(nErrInvPipeStr),
    NCONST_STR_LEN(nErrDomainStr),
    NCONST_STR_LEN(nErrResultTooBigStr),
    NCONST_STR_LEN(nErrWouldBlockStr),
    NCONST_STR_LEN(nErrInProgressStr),
    NCONST_STR_LEN(nErrAlreadyStr),
    NCONST_STR_LEN(nErrNotSocketStr),
    NCONST_STR_LEN(nErrMaxMessageStr),
    NCONST_STR_LEN(nErrInvProtoTypeStr),
    NCONST_STR_LEN(nErrInvProtoOptStr),
    NCONST_STR_LEN(nErrInvProtocolStr),
    NCONST_STR_LEN(nErrInvSockTypeStr),
    NCONST_STR_LEN(nErrInvSockOptStr),
    NCONST_STR_LEN(nErrInvProtoFamStr),
    NCONST_STR_LEN(nErrInvAddrFamStr),
    NCONST_STR_LEN(nErrAddrInUseStr),
    NCONST_STR_LEN(nErrAddrNotAvailableStr),
    NCONST_STR_LEN(nErrNetDownStr),
    NCONST_STR_LEN(nErrNetUnreachableStr),
    NCONST_STR_LEN(nErrNetResetStr),
    NCONST_STR_LEN(nErrConnAbortedStr),
    NCONST_STR_LEN(nErrConnResetStr),
    NCONST_STR_LEN(nErrNoBufferSpaceStr),
    NCONST_STR_LEN(nErrAlreadyConnStr),
    NCONST_STR_LEN(nErrNotConnStr),
    NCONST_STR_LEN(nErrNoAddrStr),
    NCONST_STR_LEN(nErrSockShutdownStr),
    NCONST_STR_LEN(nErrMaxRefsStr),
    NCONST_STR_LEN(nErrConnTimeoutStr),
    NCONST_STR_LEN(nErrConnRefusedStr),
    NCONST_STR_LEN(nErrLinkLoopStr),
    NCONST_STR_LEN(nErrMaxFileNameStr),
    NCONST_STR_LEN(nErrHostDownStr),
    NCONST_STR_LEN(nErrHostUnreachableStr),
    NCONST_STR_LEN(nErrDirNotEmptyStr),
    NCONST_STR_LEN(nErrMaxProcessStr),
    NCONST_STR_LEN(nErrMaxUsersStr),
    NCONST_STR_LEN(nErrMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrStaleStr),
    NCONST_STR_LEN(nErrRemoteStr),
    NCONST_STR_LEN(nErrInvRPCStr),
    NCONST_STR_LEN(nErrInvRPCVersionStr),
    NCONST_STR_LEN(nErrInvRPCProgStr),
    NCONST_STR_LEN(nErrInvRPCProgVersionStr),
    NCONST_STR_LEN(nErrInvRPCProcStr),
    NCONST_STR_LEN(nErrNoFileLockStr),
    NCONST_STR_LEN(nErrInvFileTypeStr),
    NCONST_STR_LEN(nErrAuthStr),
    NCONST_STR_LEN(nErrNoAuthStr),
    NCONST_STR_LEN(nErrFuncNotSupportedStr),
    NCONST_STR_LEN(nErrNotSupportedStr),
    NCONST_STR_LEN(nErrInvMultibyteStr),
    NCONST_STR_LEN(nErrInvBackgroundStr),
    NCONST_STR_LEN(nErrTranslatorDiedStr),
    NCONST_STR_LEN(nErrJokeStr),
    NCONST_STR_LEN(nErrInvMessageStr),
    NCONST_STR_LEN(nErrNoIdentifierStr),
    NCONST_STR_LEN(nErrMultihopStr),
    NCONST_STR_LEN(nErrNoDataStr),
    NCONST_STR_LEN(nErrNoLinkStr),
    NCONST_STR_LEN(nErrNoMessageStr),
    NCONST_STR_LEN(nErrNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDeviceNotStreamStr),
    NCONST_STR_LEN(nErrOverflowStr),
    NCONST_STR_LEN(nErrProtocolStr),
    NCONST_STR_LEN(nErrTimerStr),
    NCONST_STR_LEN(nErrAsyncCancelStr),
    NCONST_STR_LEN(nErrOwnerDiedStr),
    NCONST_STR_LEN(nErrNotRecoverableStr),
    NCONST_STR_LEN(nErrDeviceOffStr),
    NCONST_STR_LEN(nErrDeviceErrorStr),
    NCONST_STR_LEN(nErrBadExecutableStr),
    NCONST_STR_LEN(nErrInvArchitectureStr),
    NCONST_STR_LEN(nErrInvLibVersionStr),
    NCONST_STR_LEN(nErrInvMachoStr),
    NCONST_STR_LEN(nErrNoAttributeStr),
    NCONST_STR_LEN(nErrNoPolicyStr),
    NCONST_STR_LEN(nErrMaxQueueStr),
    NCONST_STR_LEN(nErrMaxChannelStr),
    NCONST_STR_LEN(nErrLvl2NoSyncStr),
    NCONST_STR_LEN(nErrLvl3HaultStr),
    NCONST_STR_LEN(nErrLvl3ResetStr),
    NCONST_STR_LEN(nErrLinkNumStr),
    NCONST_STR_LEN(nErrProtoUnattachedStr),
    NCONST_STR_LEN(nErrNoCSIStr),
    NCONST_STR_LEN(nErrLvl2HaultStr),
    NCONST_STR_LEN(nErrInvExchangeStr),
    NCONST_STR_LEN(nErrInvRequestDescStr),
    NCONST_STR_LEN(nErrExchangeFullStr),
    NCONST_STR_LEN(nErrNoAnodeStr),
    NCONST_STR_LEN(nErrInvRequestCodeStr),
    NCONST_STR_LEN(nErrInvSlotStr),
    NCONST_STR_LEN(nErrInvFontStr),
    NCONST_STR_LEN(nErrNoNetworkStr),
    NCONST_STR_LEN(nErrNoPackageStr),
    NCONST_STR_LEN(nErrAdvertiseStr),
    NCONST_STR_LEN(nErrSrmountStr),
    NCONST_STR_LEN(nErrCommunicationStr),
    NCONST_STR_LEN(nErrDotDotStr),
    NCONST_STR_LEN(nErrNotUniqueStr),
    NCONST_STR_LEN(nErrInvFDStr),
    NCONST_STR_LEN(nErrRemoteChangeStr),
    NCONST_STR_LEN(nErrNoLibStr),
    NCONST_STR_LEN(nErrInvLibStr),
    NCONST_STR_LEN(nErrInvLibScanStr),
    NCONST_STR_LEN(nErrMaxLibStr),
    NCONST_STR_LEN(nErrExecLibStr),
    NCONST_STR_LEN(nErrRestartCallStr),
    NCONST_STR_LEN(nErrStrPipeStr),
    NCONST_STR_LEN(nErrCleanStructStr),
    NCONST_STR_LEN(nErrNotXenixStr),
    NCONST_STR_LEN(nErrNoXenixSemStr),
    NCONST_STR_LEN(nErrNamedStr),
    NCONST_STR_LEN(nErrRemoteIOStr),
    NCONST_STR_LEN(nErrNoMediumStr),
    NCONST_STR_LEN(nErrInvMediumStr),
    NCONST_STR_LEN(nErrProgrammerStr),
    NCONST_STR_LEN(nErrFDIncapableStr),
    NCONST_STR_LEN(nErrCapabilityModeStr),
    NCONST_STR_LEN(nErrIntegrityStr),
    NCONST_STR_LEN(nErrInodeRemoteStr),
    NCONST_STR_LEN(nErrNoMoreFilesStr),
    NCONST_STR_LEN(nErrNoNetPathStr),
    NCONST_STR_LEN(nErrFileCaseStr),
#endif

#if NIMBLE_OS == NIMBLE_WINDOWS
    NCONST_STR_LEN(nErrNoPermStr),
    NCONST_STR_LEN(nErrNoFileStr),
    NCONST_STR_LEN(nErrNoProcessStr),
    NCONST_STR_LEN(nErrInterruptStr),
    NCONST_STR_LEN(nErrIOStr),
    NCONST_STR_LEN(nErrNoDeviceStr),
    NCONST_STR_LEN(nErrMaxArgsStr),
    NCONST_STR_LEN(nErrInvExecFormatStr),
    NCONST_STR_LEN(nErrInvFPStr),
    NCONST_STR_LEN(nErrNoChildStr),
    NCONST_STR_LEN(nErrWouldBlockStr),
    NCONST_STR_LEN(nErrNoMemoryStr),
    NCONST_STR_LEN(nErrNoFilePermStr),
    NCONST_STR_LEN(nErrFaultStr),
    NCONST_STR_LEN(nErrDeviceBusyStr),
    NCONST_STR_LEN(nErrFileExistsStr),
    NCONST_STR_LEN(nErrInvCrosslinkStr),
    NCONST_STR_LEN(nErrInvDeviceStr),
    NCONST_STR_LEN(nErrNotDirStr),
    NCONST_STR_LEN(nErrIsDirStr),
    NCONST_STR_LEN(nErrInvArgStr),
    NCONST_STR_LEN(nErrMaxFileSysStr),
    NCONST_STR_LEN(nErrMaxFileStr),
    NCONST_STR_LEN(nErrInvIOCtlStr),
    NCONST_STR_LEN(nErrFileTooBigStr),
    NCONST_STR_LEN(nErrNoSpaceStr),
    NCONST_STR_LEN(nErrInvSeekStr),
    NCONST_STR_LEN(nErrReadOnlyStr),
    NCONST_STR_LEN(nErrMaxLinksStr),
    NCONST_STR_LEN(nErrInvPipeStr),
    NCONST_STR_LEN(nErrDomainStr),
    NCONST_STR_LEN(nErrResultTooBigStr),
    NCONST_STR_LEN(nErrDeadlockStr),
    NCONST_STR_LEN(nErrMaxFileNameStr),
    NCONST_STR_LEN(nErrNoFileLockStr),
    NCONST_STR_LEN(nErrFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDirNotEmptyStr),
    NCONST_STR_LEN(nErrInvMultibyteStr),
    NCONST_STR_LEN(nErrAddrInUseStr),
    NCONST_STR_LEN(nErrAddrNotAvailableStr),
    NCONST_STR_LEN(nErrInvAddrFamStr),
    NCONST_STR_LEN(nErrAlreadyStr),
    NCONST_STR_LEN(nErrInvMessageStr),
    NCONST_STR_LEN(nErrAsyncCancelStr),
    NCONST_STR_LEN(nErrConnAbortedStr),
    NCONST_STR_LEN(nErrConnRefusedStr),
    NCONST_STR_LEN(nErrConnResetStr),
    NCONST_STR_LEN(nErrNoAddrStr),
    NCONST_STR_LEN(nErrHostUnreachableStr),
    NCONST_STR_LEN(nErrNoIdentifierStr),
    NCONST_STR_LEN(nErrInProgressStr),
    NCONST_STR_LEN(nErrAlreadyConnStr),
    NCONST_STR_LEN(nErrLinkLoopStr),
    NCONST_STR_LEN(nErrMaxMessageStr),
    NCONST_STR_LEN(nErrNetDownStr),
    NCONST_STR_LEN(nErrNetResetStr),
    NCONST_STR_LEN(nErrNetUnreachableStr),
    NCONST_STR_LEN(nErrNoBufferSpaceStr),
    NCONST_STR_LEN(nErrNoDataStr),
    NCONST_STR_LEN(nErrNoLinkStr),
    NCONST_STR_LEN(nErrNoMessageStr),
    NCONST_STR_LEN(nErrInvProtoOptStr),
    NCONST_STR_LEN(nErrNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDeviceNotStreamStr),
    NCONST_STR_LEN(nErrNotConnStr),
    NCONST_STR_LEN(nErrNotRecoverableStr),
    NCONST_STR_LEN(nErrNotSocketStr),
    NCONST_STR_LEN(nErrNotSupportedStr),
    NCONST_STR_LEN(nErrInvSockOptStr),
    NCONST_STR_LEN(nErrOverflowStr),
    NCONST_STR_LEN(nErrOwnerDiedStr),
    NCONST_STR_LEN(nErrProtocolStr),
    NCONST_STR_LEN(nErrInvProtocolStr),
    NCONST_STR_LEN(nErrInvProtoTypeStr),
    NCONST_STR_LEN(nErrTimerStr),
    NCONST_STR_LEN(nErrConnTimeoutStr),
    NCONST_STR_LEN(nErrTextBusyStr),

#elif NIMBLE_OS == NIMBLE_MACOS
    NCONST_STR_LEN(nErrNoPermStr),
    NCONST_STR_LEN(nErrNoFileStr),
    NCONST_STR_LEN(nErrNoProcessStr),
    NCONST_STR_LEN(nErrInterruptStr),
    NCONST_STR_LEN(nErrIOStr),
    NCONST_STR_LEN(nErrNoDeviceStr),
    NCONST_STR_LEN(nErrMaxArgsStr),
    NCONST_STR_LEN(nErrInvExecFormatStr),
    NCONST_STR_LEN(nErrInvFPStr),
    NCONST_STR_LEN(nErrNoChildStr),
    NCONST_STR_LEN(nErrDeadlockStr),
    NCONST_STR_LEN(nErrNoMemoryStr),
    NCONST_STR_LEN(nErrNoFilePermStr),
    NCONST_STR_LEN(nErrFaultStr),
    NCONST_STR_LEN(nErrNotBlockStr),
    NCONST_STR_LEN(nErrDeviceBusyStr),
    NCONST_STR_LEN(nErrFileExistsStr),
    NCONST_STR_LEN(nErrInvCrosslinkStr),
    NCONST_STR_LEN(nErrInvDeviceStr),
    NCONST_STR_LEN(nErrNotDirStr),
    NCONST_STR_LEN(nErrIsDirStr),
    NCONST_STR_LEN(nErrInvArgStr),
    NCONST_STR_LEN(nErrMaxFileStr),
    NCONST_STR_LEN(nErrMaxFileSysStr),
    NCONST_STR_LEN(nErrInvIOCtlStr),
    NCONST_STR_LEN(nErrTextBusyStr),
    NCONST_STR_LEN(nErrFileTooBigStr),
    NCONST_STR_LEN(nErrNoSpaceStr),
    NCONST_STR_LEN(nErrInvSeekStr),
    NCONST_STR_LEN(nErrReadOnlyStr),
    NCONST_STR_LEN(nErrMaxLinksStr),
    NCONST_STR_LEN(nErrInvPipeStr),
    NCONST_STR_LEN(nErrDomainStr),
    NCONST_STR_LEN(nErrResultTooBigStr),
    NCONST_STR_LEN(nErrWouldBlockStr),
    NCONST_STR_LEN(nErrInProgressStr),
    NCONST_STR_LEN(nErrAlreadyStr),
    NCONST_STR_LEN(nErrNotSocketStr),
    NCONST_STR_LEN(nErrNoAddrStr),
    NCONST_STR_LEN(nErrMaxMessageStr),
    NCONST_STR_LEN(nErrInvProtoTypeStr),
    NCONST_STR_LEN(nErrInvProtoOptStr),
    NCONST_STR_LEN(nErrInvProtocolStr),
    NCONST_STR_LEN(nErrInvSockTypeStr),
    NCONST_STR_LEN(nErrNotSupportedStr),
    NCONST_STR_LEN(nErrInvSockOptStr),
    NCONST_STR_LEN(nErrInvProtoFamStr),
    NCONST_STR_LEN(nErrInvAddrFamStr),
    NCONST_STR_LEN(nErrAddrInUseStr),
    NCONST_STR_LEN(nErrAddrNotAvailableStr),
    NCONST_STR_LEN(nErrNetDownStr),
    NCONST_STR_LEN(nErrNetUnreachableStr),
    NCONST_STR_LEN(nErrNetResetStr),
    NCONST_STR_LEN(nErrConnAbortedStr),
    NCONST_STR_LEN(nErrConnResetStr),
    NCONST_STR_LEN(nErrNoBufferSpaceStr),
    NCONST_STR_LEN(nErrAlreadyConnStr),
    NCONST_STR_LEN(nErrNotConnStr),
    NCONST_STR_LEN(nErrSockShutdownStr),
    NCONST_STR_LEN(nErrMaxRefsStr),
    NCONST_STR_LEN(nErrConnTimeoutStr),
    NCONST_STR_LEN(nErrConnRefusedStr),
    NCONST_STR_LEN(nErrLinkLoopStr),
    NCONST_STR_LEN(nErrMaxFileNameStr),
    NCONST_STR_LEN(nErrHostDownStr),
    NCONST_STR_LEN(nErrHostUnreachableStr),
    NCONST_STR_LEN(nErrDirNotEmptyStr),
    NCONST_STR_LEN(nErrMaxProcessStr),
    NCONST_STR_LEN(nErrMaxUsersStr),
    NCONST_STR_LEN(nErrMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrStaleStr),
    NCONST_STR_LEN(nErrRemoteStr),
    NCONST_STR_LEN(nErrInvRPCStr),
    NCONST_STR_LEN(nErrInvRPCVersionStr),
    NCONST_STR_LEN(nErrInvRPCProgStr),
    NCONST_STR_LEN(nErrInvRPCProgVersionStr),
    NCONST_STR_LEN(nErrInvRPCProcStr),
    NCONST_STR_LEN(nErrNoFileLockStr),
    NCONST_STR_LEN(nErrFuncNotSupportedStr),
    NCONST_STR_LEN(nErrInvFileTypeStr),
    NCONST_STR_LEN(nErrAuthStr),
    NCONST_STR_LEN(nErrNoAuthStr),
    NCONST_STR_LEN(nErrDeviceOffStr),
    NCONST_STR_LEN(nErrDeviceErrorStr),
    NCONST_STR_LEN(nErrOverflowStr),
    NCONST_STR_LEN(nErrBadExecutableStr),
    NCONST_STR_LEN(nErrInvArchitectureStr),
    NCONST_STR_LEN(nErrInvLibVersionStr),
    NCONST_STR_LEN(nErrInvMachoStr),
    NCONST_STR_LEN(nErrAsyncCancelStr),
    NCONST_STR_LEN(nErrNoIdentifierStr),
    NCONST_STR_LEN(nErrNoMessageStr),
    NCONST_STR_LEN(nErrInvMultibyteStr),
    NCONST_STR_LEN(nErrNoAttributeStr),
    NCONST_STR_LEN(nErrInvMessageStr),
    NCONST_STR_LEN(nErrMultihopStr),
    NCONST_STR_LEN(nErrNoDataStr),
    NCONST_STR_LEN(nErrNoLinkStr),
    NCONST_STR_LEN(nErrNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDeviceNotStreamStr),
    NCONST_STR_LEN(nErrProtocolStr),
    NCONST_STR_LEN(nErrTimerStr),
    NCONST_STR_LEN(nErrInvSockOptStr),
    NCONST_STR_LEN(nErrNoPolicyStr),
    NCONST_STR_LEN(nErrNotRecoverableStr),
    NCONST_STR_LEN(nErrOwnerDiedStr),
    NCONST_STR_LEN(nErrMaxQueueStr),
    
#elif NIMBLE_OS == NIMBLE_ANDROID
    NCONST_STR_LEN(nErrNoPermStr),
    NCONST_STR_LEN(nErrNoFileStr),
    NCONST_STR_LEN(nErrNoProcessStr),
    NCONST_STR_LEN(nErrInterruptStr),
    NCONST_STR_LEN(nErrIOStr),
    NCONST_STR_LEN(nErrNoDeviceStr),
    NCONST_STR_LEN(nErrMaxArgsStr),
    NCONST_STR_LEN(nErrInvExecFormatStr),
    NCONST_STR_LEN(nErrInvFPStr),
    NCONST_STR_LEN(nErrNoChildStr),
    NCONST_STR_LEN(nErrWouldBlockStr),
    NCONST_STR_LEN(nErrNoMemoryStr),
    NCONST_STR_LEN(nErrNoFilePermStr),
    NCONST_STR_LEN(nErrFaultStr),
    NCONST_STR_LEN(nErrNotBlockStr),
    NCONST_STR_LEN(nErrDeviceBusyStr),
    NCONST_STR_LEN(nErrFileExistsStr),
    NCONST_STR_LEN(nErrInvCrosslinkStr),
    NCONST_STR_LEN(nErrInvDeviceStr),
    NCONST_STR_LEN(nErrNotDirStr),
    NCONST_STR_LEN(nErrIsDirStr),
    NCONST_STR_LEN(nErrInvArgStr),
    NCONST_STR_LEN(nErrMaxFileStr),
    NCONST_STR_LEN(nErrMaxFileSysStr),
    NCONST_STR_LEN(nErrInvIOCtlStr),
    NCONST_STR_LEN(nErrTextBusyStr),
    NCONST_STR_LEN(nErrFileTooBigStr),
    NCONST_STR_LEN(nErrNoSpaceStr),
    NCONST_STR_LEN(nErrInvSeekStr),
    NCONST_STR_LEN(nErrReadOnlyStr),
    NCONST_STR_LEN(nErrMaxLinksStr),
    NCONST_STR_LEN(nErrInvPipeStr),
    NCONST_STR_LEN(nErrDomainStr),
    NCONST_STR_LEN(nErrResultTooBigStr),
    NCONST_STR_LEN(nErrNoMessageStr),
    NCONST_STR_LEN(nErrNoIdentifierStr),
    NCONST_STR_LEN(nErrMaxChannelStr),
    NCONST_STR_LEN(nErrLvl2NoSyncStr),
    NCONST_STR_LEN(nErrLvl3HaultStr),
    NCONST_STR_LEN(nErrLvl3ResetStr),
    NCONST_STR_LEN(nErrLinkNumStr),
    NCONST_STR_LEN(nErrProtoUnattachedStr),
    NCONST_STR_LEN(nErrNoCSIStr),
    NCONST_STR_LEN(nErrLvl2HaultStr),
    NCONST_STR_LEN(nErrDeadlockStr),
    NCONST_STR_LEN(nErrNoFileLockStr),
    NCONST_STR_LEN(nErrInvExchangeStr),
    NCONST_STR_LEN(nErrInvRequestDescStr),
    NCONST_STR_LEN(nErrExchangeFullStr),
    NCONST_STR_LEN(nErrNoAnodeStr),
    NCONST_STR_LEN(nErrInvRequestCodeStr),
    NCONST_STR_LEN(nErrInvSlotStr),
    NCONST_STR_LEN(nErrInvFontStr),
    NCONST_STR_LEN(nErrDeviceNotStreamStr),
    NCONST_STR_LEN(nErrNoDataStr),
    NCONST_STR_LEN(nErrTimerStr),
    NCONST_STR_LEN(nErrNoStreamResourcesStr),
    NCONST_STR_LEN(nErrNoNetworkStr),
    NCONST_STR_LEN(nErrNoPackageStr),
    NCONST_STR_LEN(nErrRemoteStr),
    NCONST_STR_LEN(nErrNoLinkStr),
    NCONST_STR_LEN(nErrAdvertiseStr),
    NCONST_STR_LEN(nErrSrmountStr),
    NCONST_STR_LEN(nErrCommunicationStr),
    NCONST_STR_LEN(nErrProtocolStr),
    NCONST_STR_LEN(nErrMultihopStr),
    NCONST_STR_LEN(nErrInodeRemoteStr),
    NCONST_STR_LEN(nErrDotDotStr),
    NCONST_STR_LEN(nErrInvMessageStr),
    NCONST_STR_LEN(nErrInvFileTypeStr),
    NCONST_STR_LEN(nErrNotUniqueStr),
    NCONST_STR_LEN(nErrInvFDStr),
    NCONST_STR_LEN(nErrRemoteChangeStr),
    NCONST_STR_LEN(nErrNoLibStr),
    NCONST_STR_LEN(nErrInvLibStr),
    NCONST_STR_LEN(nErrInvLibScanStr),
    NCONST_STR_LEN(nErrMaxLibStr),
    NCONST_STR_LEN(nErrExecLibStr),
    NCONST_STR_LEN(nErrFuncNotSupportedStr),
    NCONST_STR_LEN(nErrNoMoreFilesStr),
    NCONST_STR_LEN(nErrDirNotEmptyStr),
    NCONST_STR_LEN(nErrMaxFileNameStr),
    NCONST_STR_LEN(nErrLinkLoopStr),
    NCONST_STR_LEN(nErrInvSockOptStr),
    NCONST_STR_LEN(nErrInvProtoFamStr),
    NCONST_STR_LEN(nErrConnResetStr),
    NCONST_STR_LEN(nErrNoBufferSpaceStr),
    NCONST_STR_LEN(nErrInvAddrFamStr),
    NCONST_STR_LEN(nErrInvProtoTypeStr),
    NCONST_STR_LEN(nErrNotSocketStr),
    NCONST_STR_LEN(nErrInvProtoOptStr),
    NCONST_STR_LEN(nErrSockShutdownStr),
    NCONST_STR_LEN(nErrConnRefusedStr),
    NCONST_STR_LEN(nErrAddrInUseStr),
    NCONST_STR_LEN(nErrConnAbortedStr),
    NCONST_STR_LEN(nErrNetUnreachableStr),
    NCONST_STR_LEN(nErrNetDownStr),
    NCONST_STR_LEN(nErrConnTimeoutStr),
    NCONST_STR_LEN(nErrHostDownStr),
    NCONST_STR_LEN(nErrHostUnreachableStr),
    NCONST_STR_LEN(nErrInProgressStr),
    NCONST_STR_LEN(nErrAlreadyStr),
    NCONST_STR_LEN(nErrNoAddrStr),
    NCONST_STR_LEN(nErrMaxMessageStr),
    NCONST_STR_LEN(nErrInvProtocolStr),
    NCONST_STR_LEN(nErrInvSockTypeStr),
    NCONST_STR_LEN(nErrAddrNotAvailableStr),
    NCONST_STR_LEN(nErrNetResetStr),
    NCONST_STR_LEN(nErrAlreadyConnStr),
    NCONST_STR_LEN(nErrNotConnStr),
    NCONST_STR_LEN(nErrMaxRefsStr),
    NCONST_STR_LEN(nErrMaxProcessStr),
    NCONST_STR_LEN(nErrMaxUsersStr),
    NCONST_STR_LEN(nErrMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrStaleStr),
    NCONST_STR_LEN(nErrNotSupportedStr),
    NCONST_STR_LEN(nErrNoMediumStr),
    NCONST_STR_LEN(nErrNoNetPathStr),
    NCONST_STR_LEN(nErrFileCaseStr),
    NCONST_STR_LEN(nErrInvMultibyteStr),
    NCONST_STR_LEN(nErrOverflowStr),

#elif NIMBLE_OS == NIMBLE_BSD
     NCONST_STR_LEN(nErrNoPermStr),
     NCONST_STR_LEN(nErrNoFileStr),
     NCONST_STR_LEN(nErrNoProcessStr),
     NCONST_STR_LEN(nErrInterruptStr),
     NCONST_STR_LEN(nErrIOStr),
     NCONST_STR_LEN(nErrNoDeviceStr),
     NCONST_STR_LEN(nErrMaxArgsStr),
     NCONST_STR_LEN(nErrInvExecFormatStr),
     NCONST_STR_LEN(nErrInvFPStr),
     NCONST_STR_LEN(nErrNoChildStr),
     NCONST_STR_LEN(nErrDeadlockStr),
     NCONST_STR_LEN(nErrNoMemoryStr),
     NCONST_STR_LEN(nErrNoFilePermStr),
     NCONST_STR_LEN(nErrFaultStr),
     NCONST_STR_LEN(nErrNotBlockStr),
     NCONST_STR_LEN(nErrDeviceBusyStr),
     NCONST_STR_LEN(nErrFileExistsStr),
     NCONST_STR_LEN(nErrInvCrosslinkStr),
     NCONST_STR_LEN(nErrInvDeviceStr),
     NCONST_STR_LEN(nErrNotDirStr),
     NCONST_STR_LEN(nErrIsDirStr),
     NCONST_STR_LEN(nErrInvArgStr),
     NCONST_STR_LEN(nErrMaxFileStr),
     NCONST_STR_LEN(nErrMaxFileSysStr),
     NCONST_STR_LEN(nErrInvIOCtlStr),
     NCONST_STR_LEN(nErrTextBusyStr),
     NCONST_STR_LEN(nErrFileTooBigStr),
     NCONST_STR_LEN(nErrNoSpaceStr),
     NCONST_STR_LEN(nErrInvSeekStr),
     NCONST_STR_LEN(nErrReadOnlyStr),
     NCONST_STR_LEN(nErrMaxLinksStr),
     NCONST_STR_LEN(nErrInvPipeStr),
     NCONST_STR_LEN(nErrDomainStr),
     NCONST_STR_LEN(nErrResultTooBigStr),
     NCONST_STR_LEN(nErrWouldBlockStr),
     NCONST_STR_LEN(nErrInProgressStr),
     NCONST_STR_LEN(nErrAlreadyStr),
     NCONST_STR_LEN(nErrNotSocketStr),
     NCONST_STR_LEN(nErrNoAddrStr),
     NCONST_STR_LEN(nErrMaxMessageStr),
     NCONST_STR_LEN(nErrInvProtoTypeStr),
     NCONST_STR_LEN(nErrInvProtoOptStr),
     NCONST_STR_LEN(nErrInvProtocolStr),
     NCONST_STR_LEN(nErrInvSockTypeStr),
     NCONST_STR_LEN(nErrInvSockOptStr),
     NCONST_STR_LEN(nErrInvProtoFamStr),
     NCONST_STR_LEN(nErrInvAddrFamStr),
     NCONST_STR_LEN(nErrAddrInUseStr),
     NCONST_STR_LEN(nErrAddrNotAvailableStr),
     NCONST_STR_LEN(nErrNetDownStr),
     NCONST_STR_LEN(nErrNetUnreachableStr),
     NCONST_STR_LEN(nErrNetResetStr),
     NCONST_STR_LEN(nErrConnAbortedStr),
     NCONST_STR_LEN(nErrConnResetStr),
     NCONST_STR_LEN(nErrNoBufferSpaceStr),
     NCONST_STR_LEN(nErrAlreadyConnStr),
     NCONST_STR_LEN(nErrNotConnStr),
     NCONST_STR_LEN(nErrSockShutdownStr),
     NCONST_STR_LEN(nErrConnTimeoutStr),
     NCONST_STR_LEN(nErrConnRefusedStr),
     NCONST_STR_LEN(nErrLinkLoopStr),
     NCONST_STR_LEN(nErrMaxFileNameStr),
     NCONST_STR_LEN(nErrHostDownStr),
     NCONST_STR_LEN(nErrHostUnreachableStr),
     NCONST_STR_LEN(nErrDirNotEmptyStr),
     NCONST_STR_LEN(nErrMaxProcessStr),
     NCONST_STR_LEN(nErrMaxUsersStr),
     NCONST_STR_LEN(nErrMaxDiskQuotaStr),
     NCONST_STR_LEN(nErrStaleStr),
     NCONST_STR_LEN(nErrInvRPCStr),
     NCONST_STR_LEN(nErrInvRPCVersionStr),
     NCONST_STR_LEN(nErrInvRPCProgStr),
     NCONST_STR_LEN(nErrInvRPCProgVersionStr),
     NCONST_STR_LEN(nErrInvRPCProcStr),
     NCONST_STR_LEN(nErrNoFileLockStr),
     NCONST_STR_LEN(nErrFuncNotSupportedStr),
     NCONST_STR_LEN(nErrInvFileTypeStr),
     NCONST_STR_LEN(nErrAuthStr),
     NCONST_STR_LEN(nErrNoAuthStr),
     NCONST_STR_LEN(nErrNoIdentifierStr),
     NCONST_STR_LEN(nErrNoMessageStr),
     NCONST_STR_LEN(nErrOverflowStr),
     NCONST_STR_LEN(nErrAsyncCancelStr),
     NCONST_STR_LEN(nErrInvMultibyteStr),
     NCONST_STR_LEN(nErrNoAttributeStr),
     NCONST_STR_LEN(nErrInvMessageStr),
     NCONST_STR_LEN(nErrMultihopStr),
     NCONST_STR_LEN(nErrNoLinkStr),
     NCONST_STR_LEN(nErrProtocolStr),
     NCONST_STR_LEN(nErrFDIncapableStr),
     NCONST_STR_LEN(nErrCapabilityModeStr),
     NCONST_STR_LEN(nErrNotRecoverableStr),
     NCONST_STR_LEN(nErrOwnerDiedStr),
     NCONST_STR_LEN(nErrIntegrityStr),

#elif (NIMBLE_OS == NIMBLE_LINUX) || (NIMBLE_OS == NIMBLE_UNIX)
    NCONST_STR_LEN(nErrNoPermStr),
    NCONST_STR_LEN(nErrNoFileStr),
    NCONST_STR_LEN(nErrNoProcessStr),
    NCONST_STR_LEN(nErrInterruptStr),
    NCONST_STR_LEN(nErrIOStr),
    NCONST_STR_LEN(nErrNoDeviceStr),
    NCONST_STR_LEN(nErrMaxArgsStr),
    NCONST_STR_LEN(nErrInvExecFormatStr),
    NCONST_STR_LEN(nErrInvFPStr),
    NCONST_STR_LEN(nErrNoChildStr),
    NCONST_STR_LEN(nErrWouldBlockStr),
    NCONST_STR_LEN(nErrNoMemoryStr),
    NCONST_STR_LEN(nErrNoFilePermStr),
    NCONST_STR_LEN(nErrFaultStr),
    NCONST_STR_LEN(nErrNotBlockStr),
    NCONST_STR_LEN(nErrDeviceBusyStr),
    NCONST_STR_LEN(nErrFileExistsStr),
    NCONST_STR_LEN(nErrInvCrosslinkStr),
    NCONST_STR_LEN(nErrInvDeviceStr),
    NCONST_STR_LEN(nErrNotDirStr),
    NCONST_STR_LEN(nErrIsDirStr),
    NCONST_STR_LEN(nErrInvArgStr),
    NCONST_STR_LEN(nErrMaxFileStr),
    NCONST_STR_LEN(nErrMaxFileSysStr),
    NCONST_STR_LEN(nErrInvIOCtlStr),
    NCONST_STR_LEN(nErrTextBusyStr),
    NCONST_STR_LEN(nErrFileTooBigStr),
    NCONST_STR_LEN(nErrNoSpaceStr),
    NCONST_STR_LEN(nErrInvSeekStr),
    NCONST_STR_LEN(nErrReadOnlyStr),
    NCONST_STR_LEN(nErrMaxLinksStr),
    NCONST_STR_LEN(nErrInvPipeStr),
    NCONST_STR_LEN(nErrDomainStr),
    NCONST_STR_LEN(nErrResultTooBigStr),
    NCONST_STR_LEN(nErrDeadlockStr),
    NCONST_STR_LEN(nErrMaxFileNameStr),
    NCONST_STR_LEN(nErrNoFileLockStr),
    NCONST_STR_LEN(nErrFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDirNotEmptyStr),
    NCONST_STR_LEN(nErrLinkLoopStr),
    NCONST_STR_LEN(nErrNoMessageStr),
    NCONST_STR_LEN(nErrNoIdentifierStr),
    NCONST_STR_LEN(nErrMaxChannelStr),
    NCONST_STR_LEN(nErrLvl2NoSyncStr),
    NCONST_STR_LEN(nErrLvl3HaultStr),
    NCONST_STR_LEN(nErrLvl3ResetStr),
    NCONST_STR_LEN(nErrLinkNumStr),
    NCONST_STR_LEN(nErrProtoUnattachedStr),
    NCONST_STR_LEN(nErrNoCSIStr),
    NCONST_STR_LEN(nErrLvl2HaultStr),
    NCONST_STR_LEN(nErrInvExchangeStr),
    NCONST_STR_LEN(nErrInvRequestDescStr),
    NCONST_STR_LEN(nErrExchangeFullStr),
    NCONST_STR_LEN(nErrNoAnodeStr),
    NCONST_STR_LEN(nErrInvRequestCodeStr),
    NCONST_STR_LEN(nErrInvSlotStr),
    NCONST_STR_LEN(nErrInvFontStr),
    NCONST_STR_LEN(nErrDeviceNotStreamStr),
    NCONST_STR_LEN(nErrNoDataStr),
    NCONST_STR_LEN(nErrTimerStr),
    NCONST_STR_LEN(nErrNoStreamResourcesStr),
    NCONST_STR_LEN(nErrNoNetworkStr),
    NCONST_STR_LEN(nErrNoPackageStr),
    NCONST_STR_LEN(nErrRemoteStr),
    NCONST_STR_LEN(nErrNoLinkStr),
    NCONST_STR_LEN(nErrAdvertiseStr),
    NCONST_STR_LEN(nErrSrmountStr),
    NCONST_STR_LEN(nErrCommunicationStr),
    NCONST_STR_LEN(nErrProtocolStr),
    NCONST_STR_LEN(nErrMultihopStr),
    NCONST_STR_LEN(nErrDotDotStr),
    NCONST_STR_LEN(nErrInvMessageStr),
    NCONST_STR_LEN(nErrOverflowStr),
    NCONST_STR_LEN(nErrNotUniqueStr),
    NCONST_STR_LEN(nErrInvFDStr),
    NCONST_STR_LEN(nErrRemoteChangeStr),
    NCONST_STR_LEN(nErrNoLibStr),
    NCONST_STR_LEN(nErrInvLibStr),
    NCONST_STR_LEN(nErrInvLibScanStr),
    NCONST_STR_LEN(nErrMaxLibStr),
    NCONST_STR_LEN(nErrExecLibStr),
    NCONST_STR_LEN(nErrInvMultibyteStr),
    NCONST_STR_LEN(nErrRestartCallStr),
    NCONST_STR_LEN(nErrStrPipeStr),
    NCONST_STR_LEN(nErrMaxUsersStr),
    NCONST_STR_LEN(nErrNotSocketStr),
    NCONST_STR_LEN(nErrNoAddrStr),
    NCONST_STR_LEN(nErrMaxMessageStr),
    NCONST_STR_LEN(nErrInvProtoTypeStr),
    NCONST_STR_LEN(nErrInvProtoOptStr),
    NCONST_STR_LEN(nErrInvProtocolStr),
    NCONST_STR_LEN(nErrInvSockTypeStr),
    NCONST_STR_LEN(nErrInvSockOptStr),
    NCONST_STR_LEN(nErrInvProtoFamStr),
    NCONST_STR_LEN(nErrInvAddrFamStr),
    NCONST_STR_LEN(nErrAddrInUseStr),
    NCONST_STR_LEN(nErrAddrNotAvailableStr),
    NCONST_STR_LEN(nErrNetDownStr),
    NCONST_STR_LEN(nErrNetUnreachableStr),
    NCONST_STR_LEN(nErrNetResetStr),
    NCONST_STR_LEN(nErrConnAbortedStr),
    NCONST_STR_LEN(nErrConnResetStr),
    NCONST_STR_LEN(nErrNoBufferSpaceStr),
    NCONST_STR_LEN(nErrAlreadyConnStr),
    NCONST_STR_LEN(nErrNotConnStr),
    NCONST_STR_LEN(nErrSockShutdownStr),
    NCONST_STR_LEN(nErrMaxRefsStr),
    NCONST_STR_LEN(nErrConnTimeoutStr),
    NCONST_STR_LEN(nErrConnRefusedStr),
    NCONST_STR_LEN(nErrHostDownStr),
    NCONST_STR_LEN(nErrHostUnreachableStr),
    NCONST_STR_LEN(nErrAlreadyStr),
    NCONST_STR_LEN(nErrInProgressStr),
    NCONST_STR_LEN(nErrStaleStr),
    NCONST_STR_LEN(nErrCleanStructStr),
    NCONST_STR_LEN(nErrNotXenixStr),
    NCONST_STR_LEN(nErrNoXenixSemStr),
    NCONST_STR_LEN(nErrNamedStr),
    NCONST_STR_LEN(nErrRemoteIOStr),
    NCONST_STR_LEN(nErrMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrNoMediumStr),
    NCONST_STR_LEN(nErrInvMediumStr),

#endif
    NCONST_STR_LEN(nErrErrnoEndStr),
    
    NCONST_STR_LEN(nErrMaxStr)
};

#define nErrDescMinStr               "The minimum error value; likely "\
"caused by programmer error or a memory corruption issue."

#define nErrDescUnknownStr           "An unknown error occurred."
#define nErrDescInternalFailureStr   "An internal error occurred within "\
"the Nimble game engine."
#define nErrDescNullStr              "A pointer was null when a nonnull "\
"pointer was expected."
#define nErrDescInvErrorStr          "An error passed to a function was "\
"not valid."

#define nErrDescSignalStartStr       "The start of the signal error section; "\
"likely caused by programmer error or a memory corruption issue."
#define nErrDescSigAbrtStr           "Abort. Abnormal termination, such "\
"as is initiated by the function."
#define nErrDescSigFpeStr            "Floating point exception. "\
"Erroneous arithmetic operation, such as zero divide or an operation "\
"resulting in overflow (not necessarily with a floating-point operation)."
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
#define nErrDescSignalEndStr          "The end of the signal error section; "\
"likely caused by programmer error or a memory corruption issue."

#define nErrDescErrnoStartStr          "The start of the signal error section; "\
"likely caused by programmer error or a memory corruption issue."
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
"there aren't any processes to manipulate."
#define nErrDescDeadlockStr          "Resource deadlock avoided. This "\
"error happens on operations that are supposed to manipulate child "\
"processes, when there aren't any processes to manipulate."
#define nErrDescNoMemoryStr          "Cannot allocate memory. The system "\
"cannot allocate more virtual memory because its capacity is full."
#define nErrDescNoFilePermStr        "Permission denied. The file "\
"permissions do not allow the attempted operation."
#define nErrDescFaultStr             "Bad address. An invalid pointer was "\
"detected."
#define nErrDescNotBlockStr          "Block device required. A file that "\
"isn't a block special file was given in a situation that requires one. For "\
"example, trying to mount an ordinary file as a file system in Unix gives "\
"this error."
#define nErrDescDeviceBusyStr        "Device or resource busy. A system "\
"resource that can't be shared is already in use. For example, if you try to "\
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
#define nErrDescNotDirStr            "Not a directory. A file that isn't "\
"a directory was specified when a directory is required."
#define nErrDescIsDirStr             "Is a directory. You cannot open a "\
"directory for writing, or create or remove hard links to it."
#define nErrDescInvArgStr            "Invalid argument. This is used to "\
"indicate various kinds of problems with passing the wrong argument to a "\
"library function."
#define nErrDescMaxFileStr           "Too many open files. The current "\
"process has too many files open and can't open any more. Duplicate "\
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
"file that isn't a socket was specified when a socket is required."
#define nErrDescMaxMessageStr        "Message too long. The size of a "\
"message sent on a socket was larger than the supported maximum size."
#define nErrDescInvProtoTypeStr      "Protocol wrong type for socket. The "\
"socket type does not support the requested communications protocol."
#define nErrDescInvProtoOptStr       "Protocol not available. You "\
"specified a socket option that doesn't make sense for the particular protocol "\
"being used by the socket."
#define nErrDescInvProtocolStr       "Protocol not supported. The socket "\
"domain does not support the requested communications protocol (perhaps because "\
"the requested protocol is completely invalid)."
#define nErrDescInvSockTypeStr       "Socket type not supported. The "\
"socket type is not supported for this operation."
#define nErrDescInvSockOptStr        "Operation not supported. The "\
"operation you requested is not supported. Some socket functions don't make "\
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
"give a socket a name that doesn't match the local host name."
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
"kernel's buffers for I/O operations are all in use."
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
#define nErrDescMaxDiskQuotaStr      "Disk quota exceeded. The user's "\
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
#define nErrDescNotSupportedStr      "Not supported. A function returns "\
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
#define nErrDescMaxChannelStr        "Channel number out of range."
#define nErrDescLvl2NoSyncStr        "Level 2 not synchronized."
#define nErrDescLvl3HaultStr         "Level 3 haulted."
#define nErrDescLvl3ResetStr         "Level 3 reset."
#define nErrDescLinkNumStr           "Link number out of range."
#define nErrDescProtoUnattachedStr   "Protocol driver not attached."
#define nErrDescNoCSIStr             "No CSI structure available."
#define nErrDescLvl2HaultStr         "Level 2 haulted."
#define nErrDescInvExchangeStr       "Invalid exchange."
#define nErrDescInvRequestDescStr    "Invalid request descriptor."
#define nErrDescExchangeFullStr      "Exchange full."
#define nErrDescNoAnodeStr           "No anode."
#define nErrDescInvRequestCodeStr    "Invalid request code."
#define nErrDescInvSlotStr           "Invalid slot."
#define nErrDescInvFontStr           "Bad font file format."
#define nErrDescNoNetworkStr         "Machine is not on the network."
#define nErrDescNoPackageStr         "Package not installed."
#define nErrDescAdvertiseStr         "Advertise error."
#define nErrDescSrmountStr           "Srmount error."
#define nErrDescCommunicationStr     "Communication error on send."
#define nErrDescDotDotStr            "RFS specific error."
#define nErrDescNotUniqueStr         "Name not unique on network."
#define nErrDescInvFDStr             "File descriptor in bad state."
#define nErrDescRemoteChangeStr      "Remote address changed."
#define nErrDescNoLibStr             "Can not access a needed shared library."
#define nErrDescInvLibStr            "Accessing a corrupted shared library."
#define nErrDescInvLibScanStr        ".lib section in a.out corrupted."
#define nErrDescMaxLibStr            "Attempting to link in too many shared "\
"libraries."
#define nErrDescExecLibStr           "Cannot exec a shared library directly."
#define nErrDescRestartCallStr       "Interrupted system call should be "\
"restarted."
#define nErrDescStrPipeStr           "Streams pipe error."
#define nErrDescCleanStructStr       "Structure needs cleaning."
#define nErrDescNotXenixStr          "Not a XENIX named type file."
#define nErrDescNoXenixSemStr        "No XENIX semaphores available."
#define nErrDescNamedStr             "Is a named type file."
#define nErrDescRemoteIOStr          "Remote I/O error."
#define nErrDescNoMediumStr          "No medium found."
#define nErrDescInvMediumStr         "Wrong medium type."
#define nErrDescProgrammerStr        "Programming error. A function or API "\
"is being abused in a way which could only be detected at run-time."
#define nErrDescFDIncapableStr       "Capabilities insufficient. An "\
"operation on a capability file descriptor requires greater privilege than "\
"the capability allows."
#define nErrDescCapabilityModeStr    "Not permitted in capability mode. The "\
"system call or operation is not permitted for capability mode processes."
#define nErrDescIntegrityStr         "Integrity check failed. An integrity "\
"check such as a check-hash or a cross-correlation failed. The integrity "\
"error falls between NERROR_INV_ARG that identifies errors in parameters to "\
"a system call and NERROR_IO that identifies errors with the underlying "\
"storage media. It is typically raised by intermediate kernel layers such as "\
"a filesystem or an in-kernel GEOM subsystem when they detect "\
"inconsistencies. Uses include allowing the mount() command to return a "\
"different exit value to automate the running of fsck() during a system boot."
#define nErrDescInodeRemoteStr       "Inode is remote."
#define nErrDescNoMoreFilesStr       "No more files."
#define nErrDescNoNetPathStr         "No such host or network path."
#define nErrDescFileCaseStr          "Filename exists with different case."
#define nErrDescErrnoEndStr          "The end of the errno error section; "\
"likely caused by programmer error or a memory corruption issue."

#define nErrDescMaxStr               "The maximum error value; likely "\
"caused by programmer error or a memory corruption issue."


NCONST_STR * const nErrorDescriptions[] = {
    nErrDescMinStr,
    
    nErrDescUnknownStr,
    nErrDescInternalFailureStr,
    nErrDescNullStr,
    nErrDescInvErrorStr,
    
    nErrDescSignalStartStr,
    nErrDescSigAbrtStr,
    nErrDescSigFpeStr,
    nErrDescSigIllStr,
    nErrDescSigIntStr,
    nErrDescSigSegvStr,
    nErrDescSigTermStr,
    nErrDescSignalEndStr,
    
    nErrDescErrnoStartStr,
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
    nErrDescInvProtocolStr,
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
    nErrDescNotSupportedStr,
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
    nErrDescMaxChannelStr,
    nErrDescLvl2NoSyncStr,
    nErrDescLvl3HaultStr,
    nErrDescLvl3ResetStr,
    nErrDescLinkNumStr,
    nErrDescProtoUnattachedStr,
    nErrDescNoCSIStr,
    nErrDescLvl2HaultStr,
    nErrDescInvExchangeStr,
    nErrDescInvRequestDescStr,
    nErrDescExchangeFullStr,
    nErrDescNoAnodeStr,
    nErrDescInvRequestCodeStr,
    nErrDescInvSlotStr,
    nErrDescInvFontStr,
    nErrDescNoNetworkStr,
    nErrDescNoPackageStr,
    nErrDescAdvertiseStr,
    nErrDescSrmountStr,
    nErrDescCommunicationStr,
    nErrDescDotDotStr,
    nErrDescNotUniqueStr,
    nErrDescInvFDStr,
    nErrDescRemoteChangeStr,
    nErrDescNoLibStr,
    nErrDescInvLibStr,
    nErrDescInvLibScanStr,
    nErrDescMaxLibStr,
    nErrDescExecLibStr,
    nErrDescRestartCallStr,
    nErrDescStrPipeStr,
    nErrDescCleanStructStr,
    nErrDescNotXenixStr,
    nErrDescNoXenixSemStr,
    nErrDescNamedStr,
    nErrDescRemoteIOStr,
    nErrDescNoMediumStr,
    nErrDescInvMediumStr,
    nErrDescProgrammerStr,
    nErrDescFDIncapableStr,
    nErrDescCapabilityModeStr,
    nErrDescIntegrityStr,
    nErrDescInodeRemoteStr,
    nErrDescNoMoreFilesStr,
    nErrDescNoNetPathStr,
    nErrDescFileCaseStr,
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
    nErrDescNotSupportedStr,
    nErrDescInvSockOptStr,
    nErrDescOverflowStr,
    nErrDescOwnerDiedStr,
    nErrDescProtocolStr,
    nErrDescInvProtocolStr,
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
    nErrDescInvProtocolStr,
    nErrDescInvSockTypeStr,
    nErrDescNotSupportedStr,
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
    
#elif NIMBLE_OS == NIMBLE_ANDROID
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
    nErrDescWouldBlockStr,
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
    nErrDescNoMessageStr,
    nErrDescNoIdentifierStr,
    nErrDescMaxChannelStr,
    nErrDescLvl2NoSyncStr,
    nErrDescLvl3HaultStr,
    nErrDescLvl3ResetStr,
    nErrDescLinkNumStr,
    nErrDescProtoUnattachedStr,
    nErrDescNoCSIStr,
    nErrDescLvl2HaultStr,
    nErrDescDeadlockStr,
    nErrDescNoFileLockStr,
    nErrDescInvExchangeStr,
    nErrDescInvRequestDescStr,
    nErrDescExchangeFullStr,
    nErrDescNoAnodeStr,
    nErrDescInvRequestCodeStr,
    nErrDescInvSlotStr,
    nErrDescInvFontStr,
    nErrDescDeviceNotStreamStr,
    nErrDescNoDataStr,
    nErrDescTimerStr,
    nErrDescNoStreamResourcesStr,
    nErrDescNoNetworkStr,
    nErrDescNoPackageStr,
    nErrDescRemoteStr,
    nErrDescNoLinkStr,
    nErrDescAdvertiseStr,
    nErrDescSrmountStr,
    nErrDescCommunicationStr,
    nErrDescProtocolStr,
    nErrDescMultihopStr,
    nErrDescInodeRemoteStr,
    nErrDescDotDotStr,
    nErrDescInvMessageStr,
    nErrDescInvFileTypeStr,
    nErrDescNotUniqueStr,
    nErrDescInvFDStr,
    nErrDescRemoteChangeStr,
    nErrDescNoLibStr,
    nErrDescInvLibStr,
    nErrDescInvLibScanStr,
    nErrDescMaxLibStr,
    nErrDescExecLibStr,
    nErrDescFuncNotSupportedStr,
    nErrDescNoMoreFilesStr,
    nErrDescDirNotEmptyStr,
    nErrDescMaxFileNameStr,
    nErrDescLinkLoopStr,
    nErrDescInvSockOptStr,
    nErrDescInvProtoFamStr,
    nErrDescConnResetStr,
    nErrDescNoBufferSpaceStr,
    nErrDescInvAddrFamStr,
    nErrDescInvProtoTypeStr,
    nErrDescNotSocketStr,
    nErrDescInvProtoOptStr,
    nErrDescSockShutdownStr,
    nErrDescConnRefusedStr,
    nErrDescAddrInUseStr,
    nErrDescConnAbortedStr,
    nErrDescNetUnreachableStr,
    nErrDescNetDownStr,
    nErrDescConnTimeoutStr,
    nErrDescHostDownStr,
    nErrDescHostUnreachableStr,
    nErrDescInProgressStr,
    nErrDescAlreadyStr,
    nErrDescNoAddrStr,
    nErrDescMaxMessageStr,
    nErrDescInvProtocolStr,
    nErrDescInvSockTypeStr,
    nErrDescAddrNotAvailableStr,
    nErrDescNetResetStr,
    nErrDescAlreadyConnStr,
    nErrDescNotConnStr,
    nErrDescMaxRefsStr,
    nErrDescMaxProcessStr,
    nErrDescMaxUsersStr,
    nErrDescMaxDiskQuotaStr,
    nErrDescStaleStr,
    nErrDescNotSupportedStr,
    nErrDescNoMediumStr,
    nErrDescNoNetPathStr,
    nErrDescFileCaseStr,
    nErrDescInvMultibyteStr,
    nErrDescOverflowStr,

#elif NIMBLE_OS == NIMBLE_BSD
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
    nErrDescInvProtocolStr,
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
    nErrDescSockShutdownStr,
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
    nErrDescNoIdentifierStr,
    nErrDescNoMessageStr,
    nErrDescOverflowStr,
    nErrDescAsyncCancelStr,
    nErrDescInvMultibyteStr,
    nErrDescNoAttributeStr,
    nErrDescInvMessageStr,
    nErrDescMultihopStr,
    nErrDescNoLinkStr,
    nErrDescProtocolStr,
    nErrDescFDIncapableStr,
    nErrDescCapabilityModeStr,
    nErrDescNotRecoverableStr,
    nErrDescOwnerDiedStr,
    nErrDescIntegrityStr,

#elif (NIMBLE_OS == NIMBLE_LINUX) || (NIMBLE_OS == NIMBLE_UNIX)
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
    nErrDescWouldBlockStr,
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
    nErrDescDeadlockStr,
    nErrDescMaxFileNameStr,
    nErrDescNoFileLockStr,
    nErrDescFuncNotSupportedStr,
    nErrDescDirNotEmptyStr,
    nErrDescLinkLoopStr,
    nErrDescNoMessageStr,
    nErrDescNoIdentifierStr,
    nErrDescMaxChannelStr,
    nErrDescLvl2NoSyncStr,
    nErrDescLvl3HaultStr,
    nErrDescLvl3ResetStr,
    nErrDescLinkNumStr,
    nErrDescProtoUnattachedStr,
    nErrDescNoCSIStr,
    nErrDescLvl2HaultStr,
    nErrDescInvExchangeStr,
    nErrDescInvRequestDescStr,
    nErrDescExchangeFullStr,
    nErrDescNoAnodeStr,
    nErrDescInvRequestCodeStr,
    nErrDescInvSlotStr,
    nErrDescInvFontStr,
    nErrDescDeviceNotStreamStr,
    nErrDescNoDataStr,
    nErrDescTimerStr,
    nErrDescNoStreamResourcesStr,
    nErrDescNoNetworkStr,
    nErrDescNoPackageStr,
    nErrDescRemoteStr,
    nErrDescNoLinkStr,
    nErrDescAdvertiseStr,
    nErrDescSrmountStr,
    nErrDescCommunicationStr,
    nErrDescProtocolStr,
    nErrDescMultihopStr,
    nErrDescDotDotStr,
    nErrDescInvMessageStr,
    nErrDescOverflowStr,
    nErrDescNotUniqueStr,
    nErrDescInvFDStr,
    nErrDescRemoteChangeStr,
    nErrDescNoLibStr,
    nErrDescInvLibStr,
    nErrDescInvLibScanStr,
    nErrDescMaxLibStr,
    nErrDescExecLibStr,
    nErrDescInvMultibyteStr,
    nErrDescRestartCallStr,
    nErrDescStrPipeStr,
    nErrDescMaxUsersStr,
    nErrDescNotSocketStr,
    nErrDescNoAddrStr,
    nErrDescMaxMessageStr,
    nErrDescInvProtoTypeStr,
    nErrDescInvProtoOptStr,
    nErrDescInvProtocolStr,
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
    nErrDescSockShutdownStr,
    nErrDescMaxRefsStr,
    nErrDescConnTimeoutStr,
    nErrDescConnRefusedStr,
    nErrDescHostDownStr,
    nErrDescHostUnreachableStr,
    nErrDescAlreadyStr,
    nErrDescInProgressStr,
    nErrDescStaleStr,
    nErrDescCleanStructStr,
    nErrDescNotXenixStr,
    nErrDescNoXenixSemStr,
    nErrDescNamedStr,
    nErrDescRemoteIOStr,
    nErrDescMaxDiskQuotaStr,
    nErrDescNoMediumStr,
    nErrDescInvMediumStr,
#endif
    nErrDescErrnoEndStr,
    
    nErrDescMaxStr
};

const size_t nErrorDescLengths[] = {
    NCONST_STR_LEN(nErrDescMinStr),
    
    NCONST_STR_LEN(nErrDescUnknownStr),
    NCONST_STR_LEN(nErrDescInternalFailureStr),
    NCONST_STR_LEN(nErrDescNullStr),
    NCONST_STR_LEN(nErrDescInvErrorStr),
    
    NCONST_STR_LEN(nErrDescSignalStartStr),
    NCONST_STR_LEN(nErrDescSigAbrtStr),
    NCONST_STR_LEN(nErrDescSigFpeStr),
    NCONST_STR_LEN(nErrDescSigIllStr),
    NCONST_STR_LEN(nErrDescSigIntStr),
    NCONST_STR_LEN(nErrDescSigSegvStr),
    NCONST_STR_LEN(nErrDescSigTermStr),
    NCONST_STR_LEN(nErrDescSignalEndStr),
    
    NCONST_STR_LEN(nErrDescErrnoStartStr),
#if 0
    NCONST_STR_LEN(nErrDescNoPermStr),
    NCONST_STR_LEN(nErrDescNoFileStr),
    NCONST_STR_LEN(nErrDescNoProcessStr),
    NCONST_STR_LEN(nErrDescInterruptStr),
    NCONST_STR_LEN(nErrDescIOStr),
    NCONST_STR_LEN(nErrDescMaxArgsStr),
    NCONST_STR_LEN(nErrDescInvExecFormatStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescNoChildStr),
    NCONST_STR_LEN(nErrDescDeadlockStr),
    NCONST_STR_LEN(nErrDescNoMemoryStr),
    NCONST_STR_LEN(nErrDescNoFilePermStr),
    NCONST_STR_LEN(nErrDescFaultStr),
    NCONST_STR_LEN(nErrDescNotBlockStr),
    NCONST_STR_LEN(nErrDescDeviceBusyStr),
    NCONST_STR_LEN(nErrDescFileExistsStr),
    NCONST_STR_LEN(nErrDescInvCrosslinkStr),
    NCONST_STR_LEN(nErrDescInvDeviceStr),
    NCONST_STR_LEN(nErrDescNotDirStr),
    NCONST_STR_LEN(nErrDescIsDirStr),
    NCONST_STR_LEN(nErrDescInvArgStr),
    NCONST_STR_LEN(nErrDescMaxFileStr),
    NCONST_STR_LEN(nErrDescMaxFileSysStr),
    NCONST_STR_LEN(nErrDescInvIOCtlStr),
    NCONST_STR_LEN(nErrDescTextBusyStr),
    NCONST_STR_LEN(nErrDescFileTooBigStr),
    NCONST_STR_LEN(nErrDescNoSpaceStr),
    NCONST_STR_LEN(nErrDescInvSeekStr),
    NCONST_STR_LEN(nErrDescReadOnlyStr),
    NCONST_STR_LEN(nErrDescMaxLinksStr),
    NCONST_STR_LEN(nErrDescInvPipeStr),
    NCONST_STR_LEN(nErrDescDomainStr),
    NCONST_STR_LEN(nErrDescResultTooBigStr),
    NCONST_STR_LEN(nErrDescWouldBlockStr),
    NCONST_STR_LEN(nErrDescInProgressStr),
    NCONST_STR_LEN(nErrDescAlreadyStr),
    NCONST_STR_LEN(nErrDescNotSocketStr),
    NCONST_STR_LEN(nErrDescMaxMessageStr),
    NCONST_STR_LEN(nErrDescInvProtoTypeStr),
    NCONST_STR_LEN(nErrDescInvProtoOptStr),
    NCONST_STR_LEN(nErrDescInvProtocolStr),
    NCONST_STR_LEN(nErrDescInvSockTypeStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescInvProtoFamStr),
    NCONST_STR_LEN(nErrDescInvAddrFamStr),
    NCONST_STR_LEN(nErrDescAddrInUseStr),
    NCONST_STR_LEN(nErrDescAddrNotAvailableStr),
    NCONST_STR_LEN(nErrDescNetDownStr),
    NCONST_STR_LEN(nErrDescNetUnreachableStr),
    NCONST_STR_LEN(nErrDescNetResetStr),
    NCONST_STR_LEN(nErrDescConnAbortedStr),
    NCONST_STR_LEN(nErrDescConnResetStr),
    NCONST_STR_LEN(nErrDescNoBufferSpaceStr),
    NCONST_STR_LEN(nErrDescAlreadyConnStr),
    NCONST_STR_LEN(nErrDescNotConnStr),
    NCONST_STR_LEN(nErrDescNoAddrStr),
    NCONST_STR_LEN(nErrDescSockShutdownStr),
    NCONST_STR_LEN(nErrDescMaxRefsStr),
    NCONST_STR_LEN(nErrDescConnTimeoutStr),
    NCONST_STR_LEN(nErrDescConnRefusedStr),
    NCONST_STR_LEN(nErrDescLinkLoopStr),
    NCONST_STR_LEN(nErrDescMaxFileNameStr),
    NCONST_STR_LEN(nErrDescHostDownStr),
    NCONST_STR_LEN(nErrDescHostUnreachableStr),
    NCONST_STR_LEN(nErrDescDirNotEmptyStr),
    NCONST_STR_LEN(nErrDescMaxProcessStr),
    NCONST_STR_LEN(nErrDescMaxUsersStr),
    NCONST_STR_LEN(nErrDescMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrDescStaleStr),
    NCONST_STR_LEN(nErrDescRemoteStr),
    NCONST_STR_LEN(nErrDescInvRPCStr),
    NCONST_STR_LEN(nErrDescInvRPCVersionStr),
    NCONST_STR_LEN(nErrDescInvRPCProgStr),
    NCONST_STR_LEN(nErrDescInvRPCProgVersionStr),
    NCONST_STR_LEN(nErrDescInvRPCProcStr),
    NCONST_STR_LEN(nErrDescNoFileLockStr),
    NCONST_STR_LEN(nErrDescInvFileTypeStr),
    NCONST_STR_LEN(nErrDescAuthStr),
    NCONST_STR_LEN(nErrDescNoAuthStr),
    NCONST_STR_LEN(nErrDescFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDescNotSupportedStr),
    NCONST_STR_LEN(nErrDescInvMultibyteStr),
    NCONST_STR_LEN(nErrDescInvBackgroundStr),
    NCONST_STR_LEN(nErrDescTranslatorDiedStr),
    NCONST_STR_LEN(nErrDescJokeStr),
    NCONST_STR_LEN(nErrDescInvMessageStr),
    NCONST_STR_LEN(nErrDescNoIdentifierStr),
    NCONST_STR_LEN(nErrDescMultihopStr),
    NCONST_STR_LEN(nErrDescNoDataStr),
    NCONST_STR_LEN(nErrDescNoLinkStr),
    NCONST_STR_LEN(nErrDescNoMessageStr),
    NCONST_STR_LEN(nErrDescNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDescDeviceNotStreamStr),
    NCONST_STR_LEN(nErrDescOverflowStr),
    NCONST_STR_LEN(nErrDescProtocolStr),
    NCONST_STR_LEN(nErrDescTimerStr),
    NCONST_STR_LEN(nErrDescAsyncCancelStr),
    NCONST_STR_LEN(nErrDescOwnerDiedStr),
    NCONST_STR_LEN(nErrDescNotRecoverableStr),
    NCONST_STR_LEN(nErrDescDeviceOffStr),
    NCONST_STR_LEN(nErrDescDeviceErrorStr),
    NCONST_STR_LEN(nErrDescBadExecutableStr),
    NCONST_STR_LEN(nErrDescInvArchitectureStr),
    NCONST_STR_LEN(nErrDescInvLibVersionStr),
    NCONST_STR_LEN(nErrDescInvMachoStr),
    NCONST_STR_LEN(nErrDescNoAttributeStr),
    NCONST_STR_LEN(nErrDescNoPolicyStr),
    NCONST_STR_LEN(nErrDescMaxQueueStr),
    NCONST_STR_LEN(nErrDescMaxChannelStr),
    NCONST_STR_LEN(nErrDescLvl2NoSyncStr),
    NCONST_STR_LEN(nErrDescLvl3HaultStr),
    NCONST_STR_LEN(nErrDescLvl3ResetStr),
    NCONST_STR_LEN(nErrDescLinkNumStr),
    NCONST_STR_LEN(nErrDescProtoUnattachedStr),
    NCONST_STR_LEN(nErrDescNoCSIStr),
    NCONST_STR_LEN(nErrDescLvl2HaultStr),
    NCONST_STR_LEN(nErrDescInvExchangeStr),
    NCONST_STR_LEN(nErrDescInvRequestDescStr),
    NCONST_STR_LEN(nErrDescExchangeFullStr),
    NCONST_STR_LEN(nErrDescNoAnodeStr),
    NCONST_STR_LEN(nErrDescInvRequestCodeStr),
    NCONST_STR_LEN(nErrDescInvSlotStr),
    NCONST_STR_LEN(nErrDescInvFontStr),
    NCONST_STR_LEN(nErrDescNoNetworkStr),
    NCONST_STR_LEN(nErrDescNoPackageStr),
    NCONST_STR_LEN(nErrDescAdvertiseStr),
    NCONST_STR_LEN(nErrDescSrmountStr),
    NCONST_STR_LEN(nErrDescCommunicationStr),
    NCONST_STR_LEN(nErrDescDotDotStr),
    NCONST_STR_LEN(nErrDescNotUniqueStr),
    NCONST_STR_LEN(nErrDescInvFDStr),
    NCONST_STR_LEN(nErrDescRemoteChangeStr),
    NCONST_STR_LEN(nErrDescNoLibStr),
    NCONST_STR_LEN(nErrDescInvLibStr),
    NCONST_STR_LEN(nErrDescInvLibScanStr),
    NCONST_STR_LEN(nErrDescMaxLibStr),
    NCONST_STR_LEN(nErrDescExecLibStr),
    NCONST_STR_LEN(nErrDescRestartCallStr),
    NCONST_STR_LEN(nErrDescStrPipeStr),
    NCONST_STR_LEN(nErrDescCleanStructStr),
    NCONST_STR_LEN(nErrDescNotXenixStr),
    NCONST_STR_LEN(nErrDescNoXenixSemStr),
    NCONST_STR_LEN(nErrDescNamedStr),
    NCONST_STR_LEN(nErrDescRemoteIOStr),
    NCONST_STR_LEN(nErrDescNoMediumStr),
    NCONST_STR_LEN(nErrDescInvMediumStr),
    NCONST_STR_LEN(nErrDescProgrammerStr),
    NCONST_STR_LEN(nErrDescFDIncapableStr),
    NCONST_STR_LEN(nErrDescCapabilityModeStr),
    NCONST_STR_LEN(nErrDescIntegrityStr),
    NCONST_STR_LEN(nErrDescInodeRemoteStr),
    NCONST_STR_LEN(nErrDescNoMoreFilesStr),
    NCONST_STR_LEN(nErrDescNoNetPathStr),
    NCONST_STR_LEN(nErrDescFileCaseStr),
#endif

#if NIMBLE_OS == NIMBLE_WINDOWS
    NCONST_STR_LEN(nErrDescNoPermStr),
    NCONST_STR_LEN(nErrDescNoFileStr),
    NCONST_STR_LEN(nErrDescNoProcessStr),
    NCONST_STR_LEN(nErrDescInterruptStr),
    NCONST_STR_LEN(nErrDescIOStr),
    NCONST_STR_LEN(nErrDescMaxArgsStr),
    NCONST_STR_LEN(nErrDescInvExecFormatStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescNoChildStr),
    NCONST_STR_LEN(nErrDescWouldBlockStr),
    NCONST_STR_LEN(nErrDescNoMemoryStr),
    NCONST_STR_LEN(nErrDescNoFilePermStr),
    NCONST_STR_LEN(nErrDescFaultStr),
    NCONST_STR_LEN(nErrDescDeviceBusyStr),
    NCONST_STR_LEN(nErrDescFileExistsStr),
    NCONST_STR_LEN(nErrDescInvCrosslinkStr),
    NCONST_STR_LEN(nErrDescInvDeviceStr),
    NCONST_STR_LEN(nErrDescNotDirStr),
    NCONST_STR_LEN(nErrDescIsDirStr),
    NCONST_STR_LEN(nErrDescInvArgStr),
    NCONST_STR_LEN(nErrDescMaxFileSysStr),
    NCONST_STR_LEN(nErrDescMaxFileStr),
    NCONST_STR_LEN(nErrDescInvIOCtlStr),
    NCONST_STR_LEN(nErrDescFileTooBigStr),
    NCONST_STR_LEN(nErrDescNoSpaceStr),
    NCONST_STR_LEN(nErrDescInvSeekStr),
    NCONST_STR_LEN(nErrDescReadOnlyStr),
    NCONST_STR_LEN(nErrDescMaxLinksStr),
    NCONST_STR_LEN(nErrDescInvPipeStr),
    NCONST_STR_LEN(nErrDescDomainStr),
    NCONST_STR_LEN(nErrDescResultTooBigStr),
    NCONST_STR_LEN(nErrDescDeadlockStr),
    NCONST_STR_LEN(nErrDescMaxFileNameStr),
    NCONST_STR_LEN(nErrDescNoFileLockStr),
    NCONST_STR_LEN(nErrDescFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDescDirNotEmptyStr),
    NCONST_STR_LEN(nErrDescInvMultibyteStr),
    NCONST_STR_LEN(nErrDescAddrInUseStr),
    NCONST_STR_LEN(nErrDescAddrNotAvailableStr),
    NCONST_STR_LEN(nErrDescInvAddrFamStr),
    NCONST_STR_LEN(nErrDescAlreadyStr),
    NCONST_STR_LEN(nErrDescInvMessageStr),
    NCONST_STR_LEN(nErrDescAsyncCancelStr),
    NCONST_STR_LEN(nErrDescConnAbortedStr),
    NCONST_STR_LEN(nErrDescConnRefusedStr),
    NCONST_STR_LEN(nErrDescConnResetStr),
    NCONST_STR_LEN(nErrDescNoAddrStr),
    NCONST_STR_LEN(nErrDescHostUnreachableStr),
    NCONST_STR_LEN(nErrDescNoIdentifierStr),
    NCONST_STR_LEN(nErrDescInProgressStr),
    NCONST_STR_LEN(nErrDescAlreadyConnStr),
    NCONST_STR_LEN(nErrDescLinkLoopStr),
    NCONST_STR_LEN(nErrDescMaxMessageStr),
    NCONST_STR_LEN(nErrDescNetDownStr),
    NCONST_STR_LEN(nErrDescNetResetStr),
    NCONST_STR_LEN(nErrDescNetUnreachableStr),
    NCONST_STR_LEN(nErrDescNoBufferSpaceStr),
    NCONST_STR_LEN(nErrDescNoDataStr),
    NCONST_STR_LEN(nErrDescNoLinkStr),
    NCONST_STR_LEN(nErrDescNoMessageStr),
    NCONST_STR_LEN(nErrDescInvProtoOptStr),
    NCONST_STR_LEN(nErrDescNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDescDeviceNotStreamStr),
    NCONST_STR_LEN(nErrDescNotConnStr),
    NCONST_STR_LEN(nErrDescNotRecoverableStr),
    NCONST_STR_LEN(nErrDescNotSocketStr),
    NCONST_STR_LEN(nErrDescNotSupportedStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescOverflowStr),
    NCONST_STR_LEN(nErrDescOwnerDiedStr),
    NCONST_STR_LEN(nErrDescProtocolStr),
    NCONST_STR_LEN(nErrDescInvProtocolStr),
    NCONST_STR_LEN(nErrDescInvProtoTypeStr),
    NCONST_STR_LEN(nErrDescTimerStr),
    NCONST_STR_LEN(nErrDescConnTimeoutStr),
    NCONST_STR_LEN(nErrDescTextBusyStr),

#elif NIMBLE_OS == NIMBLE_MACOS
    NCONST_STR_LEN(nErrDescNoPermStr),
    NCONST_STR_LEN(nErrDescNoFileStr),
    NCONST_STR_LEN(nErrDescNoProcessStr),
    NCONST_STR_LEN(nErrDescInterruptStr),
    NCONST_STR_LEN(nErrDescIOStr),
    NCONST_STR_LEN(nErrDescNoDeviceStr),
    NCONST_STR_LEN(nErrDescMaxArgsStr),
    NCONST_STR_LEN(nErrDescInvExecFormatStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescNoChildStr),
    NCONST_STR_LEN(nErrDescDeadlockStr),
    NCONST_STR_LEN(nErrDescNoMemoryStr),
    NCONST_STR_LEN(nErrDescNoFilePermStr),
    NCONST_STR_LEN(nErrDescFaultStr),
    NCONST_STR_LEN(nErrDescNotBlockStr),
    NCONST_STR_LEN(nErrDescDeviceBusyStr),
    NCONST_STR_LEN(nErrDescFileExistsStr),
    NCONST_STR_LEN(nErrDescInvCrosslinkStr),
    NCONST_STR_LEN(nErrDescInvDeviceStr),
    NCONST_STR_LEN(nErrDescNotDirStr),
    NCONST_STR_LEN(nErrDescIsDirStr),
    NCONST_STR_LEN(nErrDescInvArgStr),
    NCONST_STR_LEN(nErrDescMaxFileStr),
    NCONST_STR_LEN(nErrDescMaxFileSysStr),
    NCONST_STR_LEN(nErrDescInvIOCtlStr),
    NCONST_STR_LEN(nErrDescTextBusyStr),
    NCONST_STR_LEN(nErrDescFileTooBigStr),
    NCONST_STR_LEN(nErrDescNoSpaceStr),
    NCONST_STR_LEN(nErrDescInvSeekStr),
    NCONST_STR_LEN(nErrDescReadOnlyStr),
    NCONST_STR_LEN(nErrDescMaxLinksStr),
    NCONST_STR_LEN(nErrDescInvPipeStr),
    NCONST_STR_LEN(nErrDescDomainStr),
    NCONST_STR_LEN(nErrDescResultTooBigStr),
    NCONST_STR_LEN(nErrDescWouldBlockStr),
    NCONST_STR_LEN(nErrDescInProgressStr),
    NCONST_STR_LEN(nErrDescAlreadyStr),
    NCONST_STR_LEN(nErrDescNotSocketStr),
    NCONST_STR_LEN(nErrDescNoAddrStr),
    NCONST_STR_LEN(nErrDescMaxMessageStr),
    NCONST_STR_LEN(nErrDescInvProtoTypeStr),
    NCONST_STR_LEN(nErrDescInvProtoOptStr),
    NCONST_STR_LEN(nErrDescInvProtocolStr),
    NCONST_STR_LEN(nErrDescInvSockTypeStr),
    NCONST_STR_LEN(nErrDescNotSupportedStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescInvProtoFamStr),
    NCONST_STR_LEN(nErrDescInvAddrFamStr),
    NCONST_STR_LEN(nErrDescAddrInUseStr),
    NCONST_STR_LEN(nErrDescAddrNotAvailableStr),
    NCONST_STR_LEN(nErrDescNetDownStr),
    NCONST_STR_LEN(nErrDescNetUnreachableStr),
    NCONST_STR_LEN(nErrDescNetResetStr),
    NCONST_STR_LEN(nErrDescConnAbortedStr),
    NCONST_STR_LEN(nErrDescConnResetStr),
    NCONST_STR_LEN(nErrDescNoBufferSpaceStr),
    NCONST_STR_LEN(nErrDescAlreadyConnStr),
    NCONST_STR_LEN(nErrDescNotConnStr),
    NCONST_STR_LEN(nErrDescSockShutdownStr),
    NCONST_STR_LEN(nErrDescMaxRefsStr),
    NCONST_STR_LEN(nErrDescConnTimeoutStr),
    NCONST_STR_LEN(nErrDescConnRefusedStr),
    NCONST_STR_LEN(nErrDescLinkLoopStr),
    NCONST_STR_LEN(nErrDescMaxFileNameStr),
    NCONST_STR_LEN(nErrDescHostDownStr),
    NCONST_STR_LEN(nErrDescHostUnreachableStr),
    NCONST_STR_LEN(nErrDescDirNotEmptyStr),
    NCONST_STR_LEN(nErrDescMaxProcessStr),
    NCONST_STR_LEN(nErrDescMaxUsersStr),
    NCONST_STR_LEN(nErrDescMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrDescStaleStr),
    NCONST_STR_LEN(nErrDescRemoteStr),
    NCONST_STR_LEN(nErrDescInvRPCStr),
    NCONST_STR_LEN(nErrDescInvRPCVersionStr),
    NCONST_STR_LEN(nErrDescInvRPCProgStr),
    NCONST_STR_LEN(nErrDescInvRPCProgVersionStr),
    NCONST_STR_LEN(nErrDescInvRPCProcStr),
    NCONST_STR_LEN(nErrDescNoFileLockStr),
    NCONST_STR_LEN(nErrDescFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDescInvFileTypeStr),
    NCONST_STR_LEN(nErrDescAuthStr),
    NCONST_STR_LEN(nErrDescNoAuthStr),
    NCONST_STR_LEN(nErrDescDeviceOffStr),
    NCONST_STR_LEN(nErrDescDeviceErrorStr),
    NCONST_STR_LEN(nErrDescOverflowStr),
    NCONST_STR_LEN(nErrDescBadExecutableStr),
    NCONST_STR_LEN(nErrDescInvArchitectureStr),
    NCONST_STR_LEN(nErrDescInvLibVersionStr),
    NCONST_STR_LEN(nErrDescInvMachoStr),
    NCONST_STR_LEN(nErrDescAsyncCancelStr),
    NCONST_STR_LEN(nErrDescNoIdentifierStr),
    NCONST_STR_LEN(nErrDescNoMessageStr),
    NCONST_STR_LEN(nErrDescInvMultibyteStr),
    NCONST_STR_LEN(nErrDescNoAttributeStr),
    NCONST_STR_LEN(nErrDescInvMessageStr),
    NCONST_STR_LEN(nErrDescMultihopStr),
    NCONST_STR_LEN(nErrDescNoDataStr),
    NCONST_STR_LEN(nErrDescNoLinkStr),
    NCONST_STR_LEN(nErrDescNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDescDeviceNotStreamStr),
    NCONST_STR_LEN(nErrDescProtocolStr),
    NCONST_STR_LEN(nErrDescTimerStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescNoPolicyStr),
    NCONST_STR_LEN(nErrDescNotRecoverableStr),
    NCONST_STR_LEN(nErrDescOwnerDiedStr),
    NCONST_STR_LEN(nErrDescMaxQueueStr),
    
#elif NIMBLE_OS == NIMBLE_ANDROID
    NCONST_STR_LEN(nErrDescNoPermStr),
    NCONST_STR_LEN(nErrDescNoFileStr),
    NCONST_STR_LEN(nErrDescNoProcessStr),
    NCONST_STR_LEN(nErrDescInterruptStr),
    NCONST_STR_LEN(nErrDescIOStr),
    NCONST_STR_LEN(nErrDescNoDeviceStr),
    NCONST_STR_LEN(nErrDescMaxArgsStr),
    NCONST_STR_LEN(nErrDescInvExecFormatStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescNoChildStr),
    NCONST_STR_LEN(nErrDescWouldBlockStr),
    NCONST_STR_LEN(nErrDescNoMemoryStr),
    NCONST_STR_LEN(nErrDescNoFilePermStr),
    NCONST_STR_LEN(nErrDescFaultStr),
    NCONST_STR_LEN(nErrDescNotBlockStr),
    NCONST_STR_LEN(nErrDescDeviceBusyStr),
    NCONST_STR_LEN(nErrDescFileExistsStr),
    NCONST_STR_LEN(nErrDescInvCrosslinkStr),
    NCONST_STR_LEN(nErrDescInvDeviceStr),
    NCONST_STR_LEN(nErrDescNotDirStr),
    NCONST_STR_LEN(nErrDescIsDirStr),
    NCONST_STR_LEN(nErrDescInvArgStr),
    NCONST_STR_LEN(nErrDescMaxFileStr),
    NCONST_STR_LEN(nErrDescMaxFileSysStr),
    NCONST_STR_LEN(nErrDescInvIOCtlStr),
    NCONST_STR_LEN(nErrDescTextBusyStr),
    NCONST_STR_LEN(nErrDescFileTooBigStr),
    NCONST_STR_LEN(nErrDescNoSpaceStr),
    NCONST_STR_LEN(nErrDescInvSeekStr),
    NCONST_STR_LEN(nErrDescReadOnlyStr),
    NCONST_STR_LEN(nErrDescMaxLinksStr),
    NCONST_STR_LEN(nErrDescInvPipeStr),
    NCONST_STR_LEN(nErrDescDomainStr),
    NCONST_STR_LEN(nErrDescResultTooBigStr),
    NCONST_STR_LEN(nErrDescNoMessageStr),
    NCONST_STR_LEN(nErrDescNoIdentifierStr),
    NCONST_STR_LEN(nErrDescMaxChannelStr),
    NCONST_STR_LEN(nErrDescLvl2NoSyncStr),
    NCONST_STR_LEN(nErrDescLvl3HaultStr),
    NCONST_STR_LEN(nErrDescLvl3ResetStr),
    NCONST_STR_LEN(nErrDescLinkNumStr),
    NCONST_STR_LEN(nErrDescProtoUnattachedStr),
    NCONST_STR_LEN(nErrDescNoCSIStr),
    NCONST_STR_LEN(nErrDescLvl2HaultStr),
    NCONST_STR_LEN(nErrDescDeadlockStr),
    NCONST_STR_LEN(nErrDescNoFileLockStr),
    NCONST_STR_LEN(nErrDescInvExchangeStr),
    NCONST_STR_LEN(nErrDescInvRequestDescStr),
    NCONST_STR_LEN(nErrDescExchangeFullStr),
    NCONST_STR_LEN(nErrDescNoAnodeStr),
    NCONST_STR_LEN(nErrDescInvRequestCodeStr),
    NCONST_STR_LEN(nErrDescInvSlotStr),
    NCONST_STR_LEN(nErrDescInvFontStr),
    NCONST_STR_LEN(nErrDescDeviceNotStreamStr),
    NCONST_STR_LEN(nErrDescNoDataStr),
    NCONST_STR_LEN(nErrDescTimerStr),
    NCONST_STR_LEN(nErrDescNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDescNoNetworkStr),
    NCONST_STR_LEN(nErrDescNoPackageStr),
    NCONST_STR_LEN(nErrDescRemoteStr),
    NCONST_STR_LEN(nErrDescNoLinkStr),
    NCONST_STR_LEN(nErrDescAdvertiseStr),
    NCONST_STR_LEN(nErrDescSrmountStr),
    NCONST_STR_LEN(nErrDescCommunicationStr),
    NCONST_STR_LEN(nErrDescProtocolStr),
    NCONST_STR_LEN(nErrDescMultihopStr),
    NCONST_STR_LEN(nErrDescInodeRemoteStr),
    NCONST_STR_LEN(nErrDescDotDotStr),
    NCONST_STR_LEN(nErrDescInvMessageStr),
    NCONST_STR_LEN(nErrDescInvFileTypeStr),
    NCONST_STR_LEN(nErrDescNotUniqueStr),
    NCONST_STR_LEN(nErrDescInvFDStr),
    NCONST_STR_LEN(nErrDescRemoteChangeStr),
    NCONST_STR_LEN(nErrDescNoLibStr),
    NCONST_STR_LEN(nErrDescInvLibStr),
    NCONST_STR_LEN(nErrDescInvLibScanStr),
    NCONST_STR_LEN(nErrDescMaxLibStr),
    NCONST_STR_LEN(nErrDescExecLibStr),
    NCONST_STR_LEN(nErrDescFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDescNoMoreFilesStr),
    NCONST_STR_LEN(nErrDescDirNotEmptyStr),
    NCONST_STR_LEN(nErrDescMaxFileNameStr),
    NCONST_STR_LEN(nErrDescLinkLoopStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescInvProtoFamStr),
    NCONST_STR_LEN(nErrDescConnResetStr),
    NCONST_STR_LEN(nErrDescNoBufferSpaceStr),
    NCONST_STR_LEN(nErrDescInvAddrFamStr),
    NCONST_STR_LEN(nErrDescInvProtoTypeStr),
    NCONST_STR_LEN(nErrDescNotSocketStr),
    NCONST_STR_LEN(nErrDescInvProtoOptStr),
    NCONST_STR_LEN(nErrDescSockShutdownStr),
    NCONST_STR_LEN(nErrDescConnRefusedStr),
    NCONST_STR_LEN(nErrDescAddrInUseStr),
    NCONST_STR_LEN(nErrDescConnAbortedStr),
    NCONST_STR_LEN(nErrDescNetUnreachableStr),
    NCONST_STR_LEN(nErrDescNetDownStr),
    NCONST_STR_LEN(nErrDescConnTimeoutStr),
    NCONST_STR_LEN(nErrDescHostDownStr),
    NCONST_STR_LEN(nErrDescHostUnreachableStr),
    NCONST_STR_LEN(nErrDescInProgressStr),
    NCONST_STR_LEN(nErrDescAlreadyStr),
    NCONST_STR_LEN(nErrDescNoAddrStr),
    NCONST_STR_LEN(nErrDescMaxMessageStr),
    NCONST_STR_LEN(nErrDescInvProtocolStr),
    NCONST_STR_LEN(nErrDescInvSockTypeStr),
    NCONST_STR_LEN(nErrDescAddrNotAvailableStr),
    NCONST_STR_LEN(nErrDescNetResetStr),
    NCONST_STR_LEN(nErrDescAlreadyConnStr),
    NCONST_STR_LEN(nErrDescNotConnStr),
    NCONST_STR_LEN(nErrDescMaxRefsStr),
    NCONST_STR_LEN(nErrDescMaxProcessStr),
    NCONST_STR_LEN(nErrDescMaxUsersStr),
    NCONST_STR_LEN(nErrDescMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrDescStaleStr),
    NCONST_STR_LEN(nErrDescNotSupportedStr),
    NCONST_STR_LEN(nErrDescNoMediumStr),
    NCONST_STR_LEN(nErrDescNoNetPathStr),
    NCONST_STR_LEN(nErrDescFileCaseStr),
    NCONST_STR_LEN(nErrDescInvMultibyteStr),
    NCONST_STR_LEN(nErrDescOverflowStr),

#elif NIMBLE_OS == NIMBLE_BSDnErrDescNoPermStr,
    NCONST_STR_LEN(nErrDescNoFileStr),
    NCONST_STR_LEN(nErrDescNoProcessStr),
    NCONST_STR_LEN(nErrDescInterruptStr),
    NCONST_STR_LEN(nErrDescIOStr),
    NCONST_STR_LEN(nErrDescNoDeviceStr),
    NCONST_STR_LEN(nErrDescMaxArgsStr),
    NCONST_STR_LEN(nErrDescInvExecFormatStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescNoChildStr),
    NCONST_STR_LEN(nErrDescDeadlockStr),
    NCONST_STR_LEN(nErrDescNoMemoryStr),
    NCONST_STR_LEN(nErrDescNoFilePermStr),
    NCONST_STR_LEN(nErrDescFaultStr),
    NCONST_STR_LEN(nErrDescNotBlockStr),
    NCONST_STR_LEN(nErrDescDeviceBusyStr),
    NCONST_STR_LEN(nErrDescFileExistsStr),
    NCONST_STR_LEN(nErrDescInvCrosslinkStr),
    NCONST_STR_LEN(nErrDescInvDeviceStr),
    NCONST_STR_LEN(nErrDescNotDirStr),
    NCONST_STR_LEN(nErrDescIsDirStr),
    NCONST_STR_LEN(nErrDescInvArgStr),
    NCONST_STR_LEN(nErrDescMaxFileStr),
    NCONST_STR_LEN(nErrDescMaxFileSysStr),
    NCONST_STR_LEN(nErrDescInvIOCtlStr),
    NCONST_STR_LEN(nErrDescTextBusyStr),
    NCONST_STR_LEN(nErrDescFileTooBigStr),
    NCONST_STR_LEN(nErrDescNoSpaceStr),
    NCONST_STR_LEN(nErrDescInvSeekStr),
    NCONST_STR_LEN(nErrDescReadOnlyStr),
    NCONST_STR_LEN(nErrDescMaxLinksStr),
    NCONST_STR_LEN(nErrDescInvPipeStr),
    NCONST_STR_LEN(nErrDescDomainStr),
    NCONST_STR_LEN(nErrDescResultTooBigStr),
    NCONST_STR_LEN(nErrDescWouldBlockStr),
    NCONST_STR_LEN(nErrDescInProgressStr),
    NCONST_STR_LEN(nErrDescAlreadyStr),
    NCONST_STR_LEN(nErrDescNotSocketStr),
    NCONST_STR_LEN(nErrDescNoAddrStr),
    NCONST_STR_LEN(nErrDescMaxMessageStr),
    NCONST_STR_LEN(nErrDescInvProtoTypeStr),
    NCONST_STR_LEN(nErrDescInvProtoOptStr),
    NCONST_STR_LEN(nErrDescInvProtocolStr),
    NCONST_STR_LEN(nErrDescInvSockTypeStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescInvProtoFamStr),
    NCONST_STR_LEN(nErrDescInvAddrFamStr),
    NCONST_STR_LEN(nErrDescAddrInUseStr),
    NCONST_STR_LEN(nErrDescAddrNotAvailableStr),
    NCONST_STR_LEN(nErrDescNetDownStr),
    NCONST_STR_LEN(nErrDescNetUnreachableStr),
    NCONST_STR_LEN(nErrDescNetResetStr),
    NCONST_STR_LEN(nErrDescConnAbortedStr),
    NCONST_STR_LEN(nErrDescConnResetStr),
    NCONST_STR_LEN(nErrDescNoBufferSpaceStr),
    NCONST_STR_LEN(nErrDescAlreadyConnStr),
    NCONST_STR_LEN(nErrDescNotConnStr),
    NCONST_STR_LEN(nErrDescSockShutdownStr),
    NCONST_STR_LEN(nErrDescConnTimeoutStr),
    NCONST_STR_LEN(nErrDescConnRefusedStr),
    NCONST_STR_LEN(nErrDescLinkLoopStr),
    NCONST_STR_LEN(nErrDescMaxFileNameStr),
    NCONST_STR_LEN(nErrDescHostDownStr),
    NCONST_STR_LEN(nErrDescHostUnreachableStr),
    NCONST_STR_LEN(nErrDescDirNotEmptyStr),
    NCONST_STR_LEN(nErrDescMaxProcessStr),
    NCONST_STR_LEN(nErrDescMaxUsersStr),
    NCONST_STR_LEN(nErrDescMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrDescStaleStr),
    NCONST_STR_LEN(nErrDescInvRPCStr),
    NCONST_STR_LEN(nErrDescInvRPCVersionStr),
    NCONST_STR_LEN(nErrDescInvRPCProgStr),
    NCONST_STR_LEN(nErrDescInvRPCProgVersionStr),
    NCONST_STR_LEN(nErrDescInvRPCProcStr),
    NCONST_STR_LEN(nErrDescNoFileLockStr),
    NCONST_STR_LEN(nErrDescFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDescInvFileTypeStr),
    NCONST_STR_LEN(nErrDescAuthStr),
    NCONST_STR_LEN(nErrDescNoAuthStr),
    NCONST_STR_LEN(nErrDescNoIdentifierStr),
    NCONST_STR_LEN(nErrDescNoMessageStr),
    NCONST_STR_LEN(nErrDescOverflowStr),
    NCONST_STR_LEN(nErrDescAsyncCancelStr),
    NCONST_STR_LEN(nErrDescInvMultibyteStr),
    NCONST_STR_LEN(nErrDescNoAttributeStr),
    NCONST_STR_LEN(nErrDescInvMessageStr),
    NCONST_STR_LEN(nErrDescMultihopStr),
    NCONST_STR_LEN(nErrDescNoLinkStr),
    NCONST_STR_LEN(nErrDescProtocolStr),
    NCONST_STR_LEN(nErrDescFDIncapableStr),
    NCONST_STR_LEN(nErrDescCapabilityModeStr),
    NCONST_STR_LEN(nErrDescNotRecoverableStr),
    NCONST_STR_LEN(nErrDescOwnerDiedStr),
    NCONST_STR_LEN(nErrDescIntegrityStr),

#elif (NIMBLE_OS == NIMBLE_LINUX) || (NIMBLE_OS == NIMBLE_UNIX)
    NCONST_STR_LEN(nErrDescNoPermStr),
    NCONST_STR_LEN(nErrDescNoFileStr),
    NCONST_STR_LEN(nErrDescNoProcessStr),
    NCONST_STR_LEN(nErrDescInterruptStr),
    NCONST_STR_LEN(nErrDescIOStr),
    NCONST_STR_LEN(nErrDescNoDeviceStr),
    NCONST_STR_LEN(nErrDescMaxArgsStr),
    NCONST_STR_LEN(nErrDescInvExecFormatStr),
    NCONST_STR_LEN(nErrDescInvFPStr),
    NCONST_STR_LEN(nErrDescNoChildStr),
    NCONST_STR_LEN(nErrDescWouldBlockStr),
    NCONST_STR_LEN(nErrDescNoMemoryStr),
    NCONST_STR_LEN(nErrDescNoFilePermStr),
    NCONST_STR_LEN(nErrDescFaultStr),
    NCONST_STR_LEN(nErrDescNotBlockStr),
    NCONST_STR_LEN(nErrDescDeviceBusyStr),
    NCONST_STR_LEN(nErrDescFileExistsStr),
    NCONST_STR_LEN(nErrDescInvCrosslinkStr),
    NCONST_STR_LEN(nErrDescInvDeviceStr),
    NCONST_STR_LEN(nErrDescNotDirStr),
    NCONST_STR_LEN(nErrDescIsDirStr),
    NCONST_STR_LEN(nErrDescInvArgStr),
    NCONST_STR_LEN(nErrDescMaxFileStr),
    NCONST_STR_LEN(nErrDescMaxFileSysStr),
    NCONST_STR_LEN(nErrDescInvIOCtlStr),
    NCONST_STR_LEN(nErrDescTextBusyStr),
    NCONST_STR_LEN(nErrDescFileTooBigStr),
    NCONST_STR_LEN(nErrDescNoSpaceStr),
    NCONST_STR_LEN(nErrDescInvSeekStr),
    NCONST_STR_LEN(nErrDescReadOnlyStr),
    NCONST_STR_LEN(nErrDescMaxLinksStr),
    NCONST_STR_LEN(nErrDescInvPipeStr),
    NCONST_STR_LEN(nErrDescDomainStr),
    NCONST_STR_LEN(nErrDescResultTooBigStr),
    NCONST_STR_LEN(nErrDescDeadlockStr),
    NCONST_STR_LEN(nErrDescMaxFileNameStr),
    NCONST_STR_LEN(nErrDescNoFileLockStr),
    NCONST_STR_LEN(nErrDescFuncNotSupportedStr),
    NCONST_STR_LEN(nErrDescDirNotEmptyStr),
    NCONST_STR_LEN(nErrDescLinkLoopStr),
    NCONST_STR_LEN(nErrDescNoMessageStr),
    NCONST_STR_LEN(nErrDescNoIdentifierStr),
    NCONST_STR_LEN(nErrDescMaxChannelStr),
    NCONST_STR_LEN(nErrDescLvl2NoSyncStr),
    NCONST_STR_LEN(nErrDescLvl3HaultStr),
    NCONST_STR_LEN(nErrDescLvl3ResetStr),
    NCONST_STR_LEN(nErrDescLinkNumStr),
    NCONST_STR_LEN(nErrDescProtoUnattachedStr),
    NCONST_STR_LEN(nErrDescNoCSIStr),
    NCONST_STR_LEN(nErrDescLvl2HaultStr),
    NCONST_STR_LEN(nErrDescInvExchangeStr),
    NCONST_STR_LEN(nErrDescInvRequestDescStr),
    NCONST_STR_LEN(nErrDescExchangeFullStr),
    NCONST_STR_LEN(nErrDescNoAnodeStr),
    NCONST_STR_LEN(nErrDescInvRequestCodeStr),
    NCONST_STR_LEN(nErrDescInvSlotStr),
    NCONST_STR_LEN(nErrDescInvFontStr),
    NCONST_STR_LEN(nErrDescDeviceNotStreamStr),
    NCONST_STR_LEN(nErrDescNoDataStr),
    NCONST_STR_LEN(nErrDescTimerStr),
    NCONST_STR_LEN(nErrDescNoStreamResourcesStr),
    NCONST_STR_LEN(nErrDescNoNetworkStr),
    NCONST_STR_LEN(nErrDescNoPackageStr),
    NCONST_STR_LEN(nErrDescRemoteStr),
    NCONST_STR_LEN(nErrDescNoLinkStr),
    NCONST_STR_LEN(nErrDescAdvertiseStr),
    NCONST_STR_LEN(nErrDescSrmountStr),
    NCONST_STR_LEN(nErrDescCommunicationStr),
    NCONST_STR_LEN(nErrDescProtocolStr),
    NCONST_STR_LEN(nErrDescMultihopStr),
    NCONST_STR_LEN(nErrDescDotDotStr),
    NCONST_STR_LEN(nErrDescInvMessageStr),
    NCONST_STR_LEN(nErrDescOverflowStr),
    NCONST_STR_LEN(nErrDescNotUniqueStr),
    NCONST_STR_LEN(nErrDescInvFDStr),
    NCONST_STR_LEN(nErrDescRemoteChangeStr),
    NCONST_STR_LEN(nErrDescNoLibStr),
    NCONST_STR_LEN(nErrDescInvLibStr),
    NCONST_STR_LEN(nErrDescInvLibScanStr),
    NCONST_STR_LEN(nErrDescMaxLibStr),
    NCONST_STR_LEN(nErrDescExecLibStr),
    NCONST_STR_LEN(nErrDescInvMultibyteStr),
    NCONST_STR_LEN(nErrDescRestartCallStr),
    NCONST_STR_LEN(nErrDescStrPipeStr),
    NCONST_STR_LEN(nErrDescMaxUsersStr),
    NCONST_STR_LEN(nErrDescNotSocketStr),
    NCONST_STR_LEN(nErrDescNoAddrStr),
    NCONST_STR_LEN(nErrDescMaxMessageStr),
    NCONST_STR_LEN(nErrDescInvProtoTypeStr),
    NCONST_STR_LEN(nErrDescInvProtoOptStr),
    NCONST_STR_LEN(nErrDescInvProtocolStr),
    NCONST_STR_LEN(nErrDescInvSockTypeStr),
    NCONST_STR_LEN(nErrDescInvSockOptStr),
    NCONST_STR_LEN(nErrDescInvProtoFamStr),
    NCONST_STR_LEN(nErrDescInvAddrFamStr),
    NCONST_STR_LEN(nErrDescAddrInUseStr),
    NCONST_STR_LEN(nErrDescAddrNotAvailableStr),
    NCONST_STR_LEN(nErrDescNetDownStr),
    NCONST_STR_LEN(nErrDescNetUnreachableStr),
    NCONST_STR_LEN(nErrDescNetResetStr),
    NCONST_STR_LEN(nErrDescConnAbortedStr),
    NCONST_STR_LEN(nErrDescConnResetStr),
    NCONST_STR_LEN(nErrDescNoBufferSpaceStr),
    NCONST_STR_LEN(nErrDescAlreadyConnStr),
    NCONST_STR_LEN(nErrDescNotConnStr),
    NCONST_STR_LEN(nErrDescSockShutdownStr),
    NCONST_STR_LEN(nErrDescMaxRefsStr),
    NCONST_STR_LEN(nErrDescConnTimeoutStr),
    NCONST_STR_LEN(nErrDescConnRefusedStr),
    NCONST_STR_LEN(nErrDescHostDownStr),
    NCONST_STR_LEN(nErrDescHostUnreachableStr),
    NCONST_STR_LEN(nErrDescAlreadyStr),
    NCONST_STR_LEN(nErrDescInProgressStr),
    NCONST_STR_LEN(nErrDescStaleStr),
    NCONST_STR_LEN(nErrDescCleanStructStr),
    NCONST_STR_LEN(nErrDescNotXenixStr),
    NCONST_STR_LEN(nErrDescNoXenixSemStr),
    NCONST_STR_LEN(nErrDescNamedStr),
    NCONST_STR_LEN(nErrDescRemoteIOStr),
    NCONST_STR_LEN(nErrDescMaxDiskQuotaStr),
    NCONST_STR_LEN(nErrDescNoMediumStr),
    NCONST_STR_LEN(nErrDescInvMediumStr),
#endif
    NCONST_STR_LEN(nErrDescErrnoEndStr),
    
    NCONST_STR_LEN(nErrDescMaxStr)
};


NCONST_STR noInfoStr[] = "No info.";

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
void (*volatile errorCallback) (const nint_t error, const time_t errorTime,
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
    if ((err > 0) && (err < 15))
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
    else if (err == 36)
    {
        return NERROR_DEADLOCK;
    }
    else if ((err > 37) && (err < 43))
    {
        return NERROR_ERRNO_START + err - 4;
    }
    else if ((err > 99) && (err < 131))
    {
        return NERROR_ERRNO_START + err - 61;
    }
    else if ((err > 131) && (err < 140))
    {
        return NERROR_ERRNO_START + err - 62;
    }
    else if (err == 140)
    {
        return NERROR_WOULD_BLOCK;
    }
    return NERROR_UNKNOWN;

#elif (NIMBLE_OS == NIMBLE_MACOS) || (NIMBLE_OS == BSD)
    if ((err > 0) && (err < (NERROR_ERRNO_END - NERROR_ERRNO_START - 1)))
    {
        return NERROR_ERRNO_START + err;
    }
    return NERROR_UNKNOWN;

#elif NIMBLE_OS == NIMBLE_ANDROID
    if ((err > 0) && (err < 56))
    {
        return NERROR_ERRNO_START + err;
    }
    else if (err == 56)
    {
        return NERROR_DEADLOCK;
    }
    else if ((err > 56) && (err < 140))
    {
        return NERROR_ERRNO_START + err - 2;
    }
    else if (err == 140)
    {
        return NERROR_WOULD_BLOCK;
    }
    return NERROR_UNKNOWN;

#elif (NIMBLE_OS == NIMBLE_LINUX) || (NIMBLE_OS == NIMBLE_UNIX)
    if ((err > 0) && (err < 41))
    {
        return NERROR_ERRNO_START + err;
    }
    else if (err == 41)
    {
        return NERROR_WOULD_BLOCK;
    }
    else if ((err > 41) && (err < 58))
    {
        return NERROR_ERRNO_START + err - 1;
    }
    else if (err == 57)
    {
        return NERROR_DEADLOCK;
    }
    else if ((err > 58) && (err <= 124))
    {
        return NERROR_ERRNO_START + err - 2;
    }
    return NERROR_UNKNOWN;

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
        NCONST_STR einfoCallbackStr[] = "Callback argument NULL in nErrorThrow().";
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
        NCONST_STR einfoParseStr[] = "Error not found in nErrorThrow().";
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
        NCONST_STR einfoCallbackStr[] = "Callback argument NULL in "\
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
