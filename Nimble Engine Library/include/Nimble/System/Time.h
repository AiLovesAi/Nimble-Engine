#include "../NimbleLicense.h"
/*
 * Time.h
 * Nimble Engine
 *
 * Created by Avery Aaron on 2021-01-06.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Time.h
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * @endparblock
 * @date 2021-01-06
 *
 * @brief This class defines time functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_TIME_H
#define NIMBLE_ENGINE_TIME_H /**< Header definition */

#include "../Nimble.h"

#include <time.h>

#if NIMBLE_OS == NIMBLE_WINDOWS
#include <Windows.h>
#endif

#define NTIME_NS_IN_US   1000L /**< Nanoseconds in a microsecond. */

#define NTIME_US_IN_MS   1000L /**< Microseconds in a millisecond. */
#define NTIME_NS_IN_MS   NTIME_US_IN_MS * NTIME_NS_IN_US /**< Nanoseconds in a millisecond. */

#define NTIME_MS_IN_SEC  1000L /**< Milliseconds in a second. */
#define NTIME_US_IN_SEC  NTIME_MS_IN_SEC * NTIME_US_IN_MS /**< Microseconds in a second. */
#define NTIME_NS_IN_SEC  NTIME_MS_IN_SEC * NTIME_NS_IN_MS /**< Nanoseconds in a second. */

#define NTIME_SEC_IN_MIN 60L /**< Seconds in a minute. */
#define NTIME_MS_IN_MIN  NTIME_SEC_IN_MIN * NTIME_MS_IN_SEC /**< Milliseconds in a minute. */
#define NTIME_US_IN_MIN  NTIME_SEC_IN_MIN * NTIME_US_IN_SEC /**< Microseconds in a minute. */
#define NTIME_NS_IN_MIN  NTIME_SEC_IN_MIN * NTIME_NS_IN_SEC /**< Nanoseconds in a minute. */

#define NTIME_MIN_IN_HR  60L /**< Minutes in an hour. */
#define NTIME_SEC_IN_HR  NTIME_MIN_IN_HR * NTIME_SEC_IN_MIN /**< Seconds in an hour. */
#define NTIME_MS_IN_HR   NTIME_MIN_IN_HR * NTIME_MS_IN_MIN /**< Milliseconds in an hour. */
#define NTIME_US_IN_HR   NTIME_MIN_IN_HR * NTIME_US_IN_MIN /**< Microseconds in an hour. */
#define NTIME_NS_IN_HR   NTIME_MIN_IN_HR * NTIME_NS_IN_MIN /**< Nanoseconds in an hour. */

#define NTIME_HR_IN_DAY  24L /**< Hours in a day. */
#define NTIME_MIN_IN_DAY NTIME_HR_IN_DAY * NTIME_MIN_IN_HR /**< Minutes in a day. */
#define NTIME_SEC_IN_DAY NTIME_HR_IN_DAY * NTIME_SEC_IN_HR /**< Seconds in a day. */
#define NTIME_MS_IN_DAY  NTIME_HR_IN_DAY * NTIME_MS_IN_HR /**< Milliseconds in a day. */
#define NTIME_US_IN_DAY  NTIME_HR_IN_DAY * NTIME_US_IN_HR /**< Microseconds in a day. */
#define NTIME_NS_IN_DAY  NTIME_HR_IN_DAY * NTIME_NS_IN_HR /**< Nanoseconds in a day. */

#define NTIME_DAY_IN_YR  365L /**< Days in a year. */
#define NTIME_HR_IN_YR   NTIME_DAY_IN_YR * NTIME_HR_IN_DAY /**< Hours in a year. */
#define NTIME_MIN_IN_YR  NTIME_DAY_IN_YR * NTIME_MIN_IN_DAY /**< Minutes in a year. */
#define NTIME_SEC_IN_YR  NTIME_DAY_IN_YR * NTIME_SEC_IN_DAY /**< Seconds in a year. */
#define NTIME_MS_IN_YR   NTIME_DAY_IN_YR * NTIME_MS_IN_DAY /**< Milliseconds in a year. */
#define NTIME_US_IN_YR  NTIME_DAY_IN_YR * NTIME_US_IN_DAY /**< Microseconds in a year. */
#define NTIME_NS_IN_YR  NTIME_DAY_IN_YR * NTIME_NS_IN_DAY /**< Nanoseconds in a year. */

#define NTIME_DAY_IN_LYR 366L /**< Days in a leap year. */
#define NTIME_HR_IN_LYR   NTIME_DAY_IN_LYR * NTIME_HR_IN_DAY /**< Hours in a leap year. */
#define NTIME_MIN_IN_LYR  NTIME_DAY_IN_LYR * NTIME_MIN_IN_DAY /**< Minutes in a leap year. */
#define NTIME_SEC_IN_LYR  NTIME_DAY_IN_LYR * NTIME_SEC_IN_DAY /**< Seconds in a leap year. */
#define NTIME_MS_IN_LYR   NTIME_DAY_IN_LYR * NTIME_MS_IN_DAY /**< Milliseconds in a leap year. */
#define NTIME_US_IN_LYR  NTIME_DAY_IN_LYR * NTIME_US_IN_DAY /**< Microseconds in a leap year. */
#define NTIME_NS_IN_LYR  NTIME_DAY_IN_LYR * NTIME_NS_IN_DAY /**< Nanoseconds in a leap year. */

#define NTIME_DAY_IN_JYR 365.25f /**< Days in a Julian year. */
#define NTIME_HR_IN_JYR  8766L /**< Hours in a Julian year. */
#define NTIME_MIN_IN_JYR NTIME_HR_IN_JYR * NTIME_MIN_IN_HR /**< Minutes in a Julian year. */
#define NTIME_SEC_IN_JYR NTIME_HR_IN_JYR * NTIME_SEC_IN_HR /**< Seconds in a Julian year. */
#define NTIME_MS_IN_JYR  NTIME_HR_IN_JYR * NTIME_MS_IN_HR /**< Milliseconds in a Julian year. */
#define NTIME_US_IN_JYR  NTIME_HR_IN_JYR * NTIME_US_IN_HR /**< Microseconds in a Julian year. */
#define NTIME_NS_IN_JYR  NTIME_HR_IN_JYR * NTIME_NS_IN_HR /**< Nanoseconds in a Julian year. */

typedef struct nTimeSpec {
    time_t secs; /**< Time in seconds after the Unix epoch (1 Jan, 1970). */
    long nanos; /**< Nanoseconds after seconds. */
} nTime_t;

/**
 * @brief Gets the system time.
 * 
 * @return Returns the system time as a #nTime_t.
 */
NIMBLE_INLINE
nTime_t nTime(void)
{
    nTime_t time;
#if NIMBLE_OS == NIMBLE_WINDOWS
    int64_t rawTime;
    GetSystemTimeAsFileTime((FILETIME*) &rawTime);
    /* Convert from 1601 to 1970 epoch. */
    /* Note: This is the result of the following, but with exact leap year time accounted for:
     * (1970 * (NTIME_NS_IN_JYR / 100)) - (1601 * (NTIME_NS_IN_JYR / 100))
     * = The amount of time between 1 Jan, 1601 and 1 Jan, 1970 in 100ns intervals.
     */
    rawTime -= 116444736000000000LL;
    time.secs = rawTime / 10000000L;
    time.nanos = (rawTime % 10000000L) * 100L;
#else
    clock_gettime(CLOCK_REALTIME_COARSE, &time);
#endif
    return time;
}

#endif // NIMBLE_ENGINE_TIME_H

#ifdef __cplusplus
}
#endif

// Time.h
