/*
 *  NimbleLogger.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#ifndef NimbleLogger_h
#define NimbleLogger_h

#include <stdint.h>

#ifndef NULL
#define NULL (void *) 0
#endif



#define LOG_ERROR_NOENTRY 1
#define LOG_ERROR_NOLENGTH 2
#define LOG_ERROR_FWRITE 3

#define ENTRY_TYPE_PRINT   0
#define ENTRY_TYPE_INFO    1
#define ENTRY_TYPE_WARNING 2
// Logs entry to logPath with a prefix defined by entryType. Returns errno if an error occurs.
extern uint8_t nimbleLoggerLog(FILE * logFile, const char * entry, const size_t entryLength, const uint8_t entryType, const uint8_t logToConsole);

#endif /* NimbleLogger_h */

// NimbleLogger.h
