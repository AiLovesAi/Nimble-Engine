#include "../include/Nimble/NimbleLicense.h"
/*
 * NimbleEngine.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-10.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../include/Nimble/NimbleEngine.h"

/**
 * @file NimbleEngine.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
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
 * @date 2020-08-10
 *
 * @brief This class includes all the necessary game engine header files.
 *
 * This class includes all the necessary game engine header files that are
 * used in game development, and defines the functions used in initialization.
 */

#include <signal.h>
#include <stdlib.h>

#include "../include/Nimble/NimbleEngine/Output/CrashHandler.h"

void nEngineExit(void)
{
    /** @todo Make safe exit function */
    exit(EXIT_SUCCESS);
}

void nEngineExitSignal(int signum)
{
    nEngineExit();
}

int32_t nEngineInit(void)
{
    /** @todo Make init function */
    atexit(nEngineExit);
    signal(SIGTERM, nEngineExitSignal);
    
    signal(SIGABRT, nCrashSignal);
    signal(SIGFPE, nCrashSignal);
    signal(SIGILL, nCrashSignal);
    signal(SIGINT, nCrashSignal);
    signal(SIGSEGV, nCrashSignal);
    
    return NSUCCESS;
}

// NimbleEngine.c
