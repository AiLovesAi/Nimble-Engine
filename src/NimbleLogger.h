/*
 *  NimbleLogger.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
