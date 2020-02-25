/*
 *  NimbleThread.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 2/1/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#ifndef NimbleThread_h
#define NimbleThread_h

#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

#ifdef _WIN32
typedef uint32_t nimbleThread_t;
#else
typedef pthread_t nimbleThread_t;
#endif

extern uint8_t nimbleThreadCount;

// TODO

// Creates a thread with start function function with arguments args
extern uint32_t nimbleThreadCreate(nimbleThread_t * thread, void * (*function) (void *), void * args);

#endif /* NimbleThread_h */

// NimbleThread.h
