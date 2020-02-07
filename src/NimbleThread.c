/*
 *  NimbleThread.c
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
