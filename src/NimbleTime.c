/*
 *  NimbleTime.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
