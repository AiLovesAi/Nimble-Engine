/*
 *  NimbleThread.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 2/1/20.
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
