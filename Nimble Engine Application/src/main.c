/*
*  main.c
*  Nimble Engine
*
*  Created by Avery Aaron on 2020-08-09.
*  Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
*
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <Nimble/NimbleEngine.h>
#include <Nimble/Output/Errors/Errors.h>
#include <Nimble/System/Memory.h>

#include <Nimble/Graphics/NimbleOpenGL.h>


void crashCallback(const nErrorInfo_t errorInfo)
{
    struct tm *timeInfo = localtime((time_t *) &errorInfo.time.secs);
    const char format[] = "%02d/%02d/%04d %02d:%02d:%02d";
    const char example[] = "01/01/1970 00:00:00";
    char *timeStr = nAlloc(sizeof(example));

    snprintf(timeStr, sizeof(example), format, timeInfo->tm_mon + 1,
     timeInfo->tm_mday, timeInfo->tm_year + 1900, timeInfo->tm_hour,
     timeInfo->tm_min, timeInfo->tm_sec);

    fprintf(stderr, "\nCrash occurred at %s:\nError description of %s: "\
     "%s\nError info: %s\nSystem error description: %s\nStack trace: %s\n\n",
     timeStr, errorInfo.errorStr ? errorInfo.errorStr : "No error",
     errorInfo.descStr ? errorInfo.descStr : "No desc",
     errorInfo.infoStr ? errorInfo.infoStr : "No info",
     errorInfo.sysDescStr ? errorInfo.sysDescStr : "No sys desc",
     errorInfo.stackStr ? errorInfo.stackStr : "No stack");
    nFree((void **) &timeStr);
}

void errorCallback(const nErrorInfo_t errorInfo)
{
    struct tm *timeInfo = localtime((time_t *) &errorInfo.time.secs);
    const char format[] = "%02d/%02d/%02d %02d:%02d:%02d";
    const char example[] = "01/01/1970 00:00:00";
    char *timeStr = nAlloc(sizeof(example));

    snprintf(timeStr, sizeof(example), format, timeInfo->tm_mon + 1,
     timeInfo->tm_mday, timeInfo->tm_year + 1900, timeInfo->tm_hour,
     timeInfo->tm_min, timeInfo->tm_sec);

    fprintf(stderr, "\nAn error occurred at %s:\nError description of %s: "\
     "%s\nError info: %s\nSystem error description: %s\nStack trace: %s\n\n",
     timeStr, errorInfo.errorStr ? errorInfo.errorStr : "No error",
     errorInfo.descStr ? errorInfo.descStr : "No desc",
     errorInfo.infoStr ? errorInfo.infoStr : "No info",
     errorInfo.sysDescStr ? errorInfo.sysDescStr : "No sys desc",
     errorInfo.stackStr ? errorInfo.stackStr : "No stack");
    nFree((void **) &timeStr);
}


int main(int argc, char **argv)
{
    printf("Initializing engine...\n");
    nEngineInit(argv, argc, errorCallback, crashCallback);
    printf("Initialized engine.\n");

    char *stackStr = nErrorStacktrace(NULL, NULL);

    printf("%s\n", stackStr);

    nFree((void **) &stackStr);
    
    puts("EXITING\n");

    return EXIT_SUCCESS;
}

// main.c
