/*
*  main.c
*  Nimble Engine
*
*  Created by Avery Aaron on 2020-08-09.
*  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
*
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <Nimble/NimbleEngine.h>
#include <Nimble/Graphics/NimbleOpenGL.h>


void crashCallback(const nint_t error, const time_t errorTime,
 const char *errorDesc, const size_t errorDescLen, const char *stack,
 const size_t stackLen)
{
    struct tm *timeInfo = localtime(&errorTime);
    const char format[] = "%02d/%02d/%04d %02d:%02d:%02d";
    const char example[] = "01/01/1970 00:00:00";
    char *timeStr = nAlloc(sizeof(example));
    if (!timeStr)
    {
        fprintf(stderr, "Failed to allocate to timeStr.\n");
        return;
    }
    snprintf(timeStr, sizeof(example), format, timeInfo->tm_mon + 1,
     timeInfo->tm_mday, timeInfo->tm_year + 1900, timeInfo->tm_hour,
     timeInfo->tm_min, timeInfo->tm_sec);

    fprintf(stderr, "\nCrash occurred at %s:\nError description: "\
    "%s\nStack trace: %s\n\n", timeStr, errorDesc, stack);
    nFree(timeStr);
}

void errorCallback(const nint_t error, const time_t errorTime,
 const char * errorDesc, const size_t errorDescLen, const char * stack,
 const size_t stackLen)
{
    struct tm *timeInfo = localtime(&errorTime);
    const char format[] = "%02d/%02d/%02d %02d:%02d:%02d";
    const char example[] = "01/01/1970 00:00:00";
    char *timeStr = nAlloc(sizeof(example));
    if (!timeStr)
    {
        fprintf(stderr, "Failed to allocate to timeStr.\n");
        return;
    }
    snprintf(timeStr, sizeof(example), format, timeInfo->tm_mon + 1,
     timeInfo->tm_mday, timeInfo->tm_year + 1900, timeInfo->tm_hour,
     timeInfo->tm_min, timeInfo->tm_sec);

    fprintf(stderr, "\nAn error occurred at %s:\nError description: "\
    "%s\nStack trace: %s\n\n", timeStr, errorDesc, stack);
    nFree(timeStr);
}


int main(int argc, char **argv)
{
    printf("Initializing engine...\n");
    nEngineInit(argv, argc, errorCallback, crashCallback);
    printf("Initialized engine.\n");

    return EXIT_SUCCESS;
}

// main.c
