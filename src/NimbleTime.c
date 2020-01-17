/*
 *  NimbleTime.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include "NimbleTime.h"

// Returns 1 if the current time is > time.
const uint8_t nimbleTimeHasPast(const struct timeval time)
{
    struct timeval currentTime = {};
    gettimeofday(&currentTime, NULL);
    return ((currentTime.tv_sec * MICROS_PER_SEC) + currentTime.tv_usec) > ((time.tv_sec * MICROS_PER_SEC) + time.tv_usec);
}

// Returns the current time + milliseconds.
struct timeval nimbleTimeSetTimerMillis(const clock_t milliseconds)
{
    struct timeval currentTime = {};
    gettimeofday(&currentTime, NULL);
    currentTime.tv_sec += milliseconds / MILLIS_PER_SEC;
    currentTime.tv_usec += milliseconds % MILLIS_PER_SEC;
    return currentTime;
}


// NimbleTime.c
