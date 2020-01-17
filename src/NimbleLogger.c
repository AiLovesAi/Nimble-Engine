/*
 *  Logger.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include "Logger.h"


uint8_t nimbleLoggerLog(FILE * logFile, const char * entry, const size_t entryLength, const uint8_t entryType, const uint8_t logToConsole)
{
    if (!entry)
    {
        return LOG_ERROR_NOENTRY;
    }
    
    if (!entryLength)
    {
        return LOG_ERROR_NOLENGTH;
    }
    
    struct timeval tv = {};
    
    gettimeofday(&tv, NULL);
    
    time_t t = time(0);
    const struct tm * localNow = localtime(&t);
    
    char * output;
    const char entryTime[]         = "[%02d-%02d-%04d %02d:%02d:%02d +%06d] "; // Time format: [MM-DD-YYYY HH:MM:SS +mmmmmm]
    const char entrySuffix[]       = "\n";
    size_t     currentOutputLength = 1;
    size_t     outputLength        = 1;
    
    const size_t entryTimeFormattedLength = ((sizeof(entryTime) - 1) - (FORMAT_LENGTH_4 * 7) +
                                             TM_DIGITS_MONTH + TM_DIGITS_DAY + TM_DIGITS_YEAR + TM_DIGITS_HOUR +
                                             TM_DIGITS_MINUTE + TM_DIGITS_SECOND + TM_DIGITS_MICROSECOND);
    // NOTE: FORMAT_LENGTH_4 * 7 for the 7 inputs to properly allocate memory.
    
    switch (entryType)
    {
            
        case ENTRY_TYPE_INFO: // Prints with "info" suffix.
        {
            const char infoSuffix[] = "INFO: ";
            outputLength = (entryTimeFormattedLength + (sizeof(infoSuffix) - 1) +
                            entryLength + (sizeof(entrySuffix) - 1) + 1);
            output = malloc(ptrSize + outputLength);
            
            snprintf(output, outputLength, entryTime,
                     (localNow->tm_mon + TM_DIF_MONTH), localNow->tm_mday, (localNow->tm_year + TM_DIF_EPOCH),
                     localNow->tm_hour, localNow->tm_min, localNow->tm_sec, tv.tv_usec);
            currentOutputLength += entryTimeFormattedLength;
            strncat(output, infoSuffix, (outputLength - currentOutputLength));
            currentOutputLength += (sizeof(infoSuffix) - 1);
            strncat(output, entry, (outputLength - currentOutputLength));
            currentOutputLength += entryLength;
            strncat(output, entrySuffix, (outputLength - currentOutputLength));
        }
        break;
            
        case ENTRY_TYPE_WARNING: // Prints with "warning" suffix.
        {
            const char warningSuffix[] = "WARNING: ";
            outputLength = (entryTimeFormattedLength + (sizeof(warningSuffix) - 1) +
                            entryLength + (sizeof(entrySuffix) - 1) + 1);
            output = malloc(ptrSize + outputLength);
            
            snprintf(output, outputLength, entryTime,
                     (localNow->tm_mon + TM_DIF_MONTH), localNow->tm_mday, (localNow->tm_year + TM_DIF_EPOCH),
                     localNow->tm_hour, localNow->tm_min, localNow->tm_sec, tv.tv_usec);
            currentOutputLength += entryTimeFormattedLength;
            strncat(output, warningSuffix, (outputLength - currentOutputLength));
            currentOutputLength += (sizeof(warningSuffix) - 1);
            strncat(output, entry, (outputLength - currentOutputLength));
            currentOutputLength += entryLength;
            strncat(output, entrySuffix, (outputLength - currentOutputLength));
        }
        break;
            
        default: // Prints normally.
        {
            outputLength = (entryTimeFormattedLength + entryLength +
                            (sizeof(entrySuffix) - 1) + 1);
            output = malloc(ptrSize + outputLength);
            
            snprintf(output, outputLength, entryTime,
                     (localNow->tm_mon + TM_DIF_MONTH), localNow->tm_mday, (localNow->tm_year + TM_DIF_EPOCH),
                     localNow->tm_hour, localNow->tm_min, localNow->tm_sec, tv.tv_usec);
            currentOutputLength += entryTimeFormattedLength;
            strncat(output, entry, (outputLength - currentOutputLength));
            currentOutputLength += entryLength;
            strncat(output, entrySuffix, (outputLength - currentOutputLength));
        }
        break;
            
    }
    
    outputLength = strlen(output);
    
    if (logToConsole)
    {
        fwrite(output, 1, outputLength, ((entryType == ENTRY_TYPE_WARNING) ? stderr : stdout));
    }
    
    fwrite(output, 1, outputLength, logFile);
    
    if(ferror(logFile))
    {
        return LOG_ERROR_FWRITE;
    }
    
    return 0;
}


// Logger.c