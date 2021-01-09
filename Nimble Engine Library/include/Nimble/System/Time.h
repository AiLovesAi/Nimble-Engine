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

#include "../NimbleEngine.h"

#include <time.h>

#if NIMBLE_OS == NIMBLE_WINDOWS
#include <Windows.h>
#endif

typedef struct nTimeSpec {
    time_t secs; /**< Time in seconds after epoch. */
    long nanos; /**< Nanoseconds after seconds. */
} nTime_t;

#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE 1
#  ifdef NIMBLE_32BIT
#  else
NIMBLE_INLINE
void clock_gettime(int val, struct nTimeSpec *spec)
{
    __int64 wintime;
    GetSystemTimeAsFileTime((FILETIME*) &wintime);
    wintime -= 116444736000000000; //1jan1601 to 1jan1970
    spec->secs  = wintime / 10000000; //seconds
    spec->nanos = (wintime % 10000000) * 100; //nano-seconds
}
#  endif
#endif

/**
 * @brief Gets the system time.
 * 
 * @return Returns the system time as a #nTime_t.
 */
NIMBLE_INLINE
nTime_t nTime(void)
{
    nTime_t time;
    clock_gettime(CLOCK_REALTIME_COARSE, &time); // @todo Make assembly version
    return time;
}

#endif // NIMBLE_ENGINE_TIME_H

#ifdef __cplusplus
}
#endif

// Time.h
