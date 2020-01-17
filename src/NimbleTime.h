/*
 *  NimbleTime.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleTime_h
#define NimbleTime_h

#include <stdint.h>
#include <sys/time.h>

#ifdef _WIN32
#include <Windows.h>
#elif defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#endif

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute((always_inline))
#endif


#define MICROS_PER_SEC   1000000
#define MICROS_PER_MILLI 1000
#define MILLIS_PER_SEC   1000

#define TM_DIF_MONTH          1 // Month accuracy shift (0-11 to 1-12)
#define TM_DIF_EPOCH          1900 // Year accuract shift (0+ to 1900+)
#define TM_DIGITS_YEAR        4 // YYYY
#define TM_DIGITS_MONTH       2 // MM
#define TM_DIGITS_DAY         2 // DD
#define TM_DIGITS_HOUR        2 // hh
#define TM_DIGITS_MINUTE      2 // mm
#define TM_DIGITS_SECOND      2 // ss
#define TM_DIGITS_MICROSECOND 6 // uuuuuu

// Returns time1 + time2.
ALWAYS_INLINE clock_t nimbleTimeAdd(const struct timeval time1, const struct timeval time2)
{
    return (((time1.tv_sec + time2.tv_sec) * MICROS_PER_SEC) + (time1.tv_usec + time2.tv_usec));
}

// Returns time1 - time2.
ALWAYS_INLINE clock_t nimbleTimeSub(const struct timeval time1, const struct timeval time2)
{
    return (((time1.tv_sec - time2.tv_sec) * MICROS_PER_SEC) + (time1.tv_usec - time2.tv_usec));
}

// Returns 1 if the current time is > time.
extern const uint8_t nimbleTimeHasPast(const struct timeval time);

// Returns the current time + milliseconds.
extern struct timeval nimbleTimeSetTimerMillis(const clock_t milliseconds);

// Suspends thread for milliseconds.
#ifdef _WIN32
#define nimbleTimeSleepMillis(milliseconds) Sleep(milliseconds)
#elif defined(__APPLE__) || defined(__linux__)
#define nimbleTimeSleepMillis(milliseconds) usleep(milliseconds * MILLIS_PER_SEC)
#endif


#endif /* NimbleTime_h */

// NimbleTime.h
