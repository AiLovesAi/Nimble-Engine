/*
 *  Logger.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef Logger_h
#define Logger_h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GameTime.h"

#ifndef NULL
#define NULL (void *) 0
#endif
#ifndef ptrSize
#define ptrSize sizeof(NULL)
#endif

#ifndef FORMAT_LENGTH_4
#define FORMAT_LENGTH_4 4
#endif

#define LOG_ERROR_NOENTRY 1
#define LOG_ERROR_NOLENGTH 2
#define LOG_ERROR_FWRITE 3

#define ENTRY_TYPE_PRINT   0
#define ENTRY_TYPE_INFO    1
#define ENTRY_TYPE_WARNING 2
// Logs entry to logPath with a prefix defined by entryType. Returns errno if an error occurs.
extern uint8_t nimbleLoggerLog(FILE * logFile, const char * entry, const size_t entryLength, const uint8_t entryType, const uint8_t logToConsole);

#endif /* Logger_h */

// Logger.h
