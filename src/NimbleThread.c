/*
 *  NimbleThread.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 2/1/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#include "NimbleError.h"
#include "NimbleThread.h"


uint8_t nimbleThreadCount = 0;

// TODO

// Creates a thread with start function function with arguments args
uint32_t nimbleThreadCreate(nimbleThread_t * thread, void * (*function) (void *), void * args)
{
#   ifdef _WIN32
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) function, 0, 0, (PDWORD) &thread);
    
    if (thread)
    {
        nimbleThreadCount++;
        return 0;
    }
#   else
    
    if (pthread_create(thread, NULL, function, args))
    {
        nimbleThreadCount++;
        return 0;
    }
    
#   endif
    return NIMBLE_ERROR_THREAD_CREATE;
}


// NimbleThread.c
