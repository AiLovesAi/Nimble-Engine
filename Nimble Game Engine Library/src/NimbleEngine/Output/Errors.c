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

#include <stdlib.h>
#include <string.h>

const char noInfoStr[]          = "No info";
const char unknownErrStr[]      = "NERROR_UNKNOWN: An unknown error occurred: ";
const char nullErrStr[]         = "NERROR_NULL: A null pointer was passed "\
                                  "when a nonnull pointer was expected.";
const char fileNotFoundErrStr[] = "NERROR_FILE_NOT_FOUND: The specified file "\
                                  "was not found: ";

char * nErrorToString(char * dst, const int32_t error, const char * info)
{
    int32_t infoLen = 0;
    
    if (info != NULL)
    {
        infoLen = strlen(info);
    }
    
    switch (error)
    {
        case NERROR_UNKNOWN:
        {
            if (info != NULL)
            {
                dst = malloc(sizeof(void *) + sizeof(unknownErrStr) + infoLen);
                strncpy(dst, unknownErrStr, sizeof(unknownErrStr));
                strncat(dst, info, infoLen + 1);
            }
            else
            {
                dst = malloc(sizeof(void *) + sizeof(unknownErrStr) +
                       sizeof(noInfoStr));
                strncpy(dst, unknownErrStr, sizeof(unknownErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
        }
        break;
        case NERROR_NULL:
        {
            dst = malloc(sizeof(void *) + sizeof(nullErrStr));
            strncpy(dst, nullErrStr, sizeof(nullErrStr));
        }
        break;
        case NERROR_FILE_NOT_FOUND:
        {
            if (info != NULL)
            {
                dst = malloc(sizeof(void *) + sizeof(fileNotFoundErrStr) +
                       infoLen);
                strncpy(dst, fileNotFoundErrStr, sizeof(fileNotFoundErrStr));
                strncat(dst, info, infoLen + 1);
            }
            else
            {
                dst = malloc(sizeof(void *) + sizeof(fileNotFoundErrStr) +
                       sizeof(noInfoStr));
                strncpy(dst, fileNotFoundErrStr, sizeof(fileNotFoundErrStr));
                strncat(dst, noInfoStr, sizeof(noInfoStr));
            }
        }
        break;
        default:
        {
            /** TODO Throw error */
            dst = NULL;
        }
        break;
    }
    return dst;
}

// Errors.c
