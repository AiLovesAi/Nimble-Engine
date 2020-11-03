#include "NimbleLicense.h"
/*
 * Nimble.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-14.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Nimble.h
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
 * @date 2020-08-14
 *
 * @brief Defines the macros that are used by other files.
 *
 * This header defines the macros that are used by other files.
 */

/**
 * @mainpage Nimble Game Engine Library
 *
 * @section sec_intro Introduction
 *
 * @par
 * The <em>Nimble Game Engine Library</em> (or <em>Nimble Library</em>) is the
 * "engine" in <em>Nimble Game Engine</em>. Developers can use the library to
 * make their own games, and it is recommended they use the <em>Nimble Game
 * Engine Application</em> to do so.
 * 
 * @par
 * As well as having useful tools to make low-level game development easier, the
 * library comes with its own error and crash handler that runs by default in
 * the background of each game, should the developer choose to call the engine
 * initialization function.
 *
 * @section sec_setup Setting Up the Library
 *
 * @todo Explain how to link the library or use the app to write code
 * @subsection sub_windows Windows
 *
 * @subsection sub_macosx Mac OS X
 *
 * @subsection sub_linux Linux
 *
 * @section sec_starting Getting Started
 *
 * @todo Explain how to get started, setting up a window and doing basic 2D/3D stuff
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_H
#define NIMBLE_H /**< Header definition */

#include <inttypes.h>
#include <stdlib.h>

#if UINTPTR_MAX == 0xffffffff
#define NIMBLE_32BIT
#elif UINTPTR_MAX == 0xffffffffffffffff
#define NIMBLE_64BIT
#else
#error Only 32-bit and 64-bit hardware is supported.
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define NIMBLE_EXPORT __attribute__((dllexport)) /**< Export alias. */
#      define NIMBLE_INLINE static inline __attribute__((always_inline)) /**< Inline alias. */
#    else
#      define NIMBLE_EXPORT __declspec(dllexport) /**< Export alias. */
#      define NIMBLE_INLINE __forceinline /**< Inline alias. */
#    endif
#  else
#    ifdef __GNUC__
#      define NIMBLE_EXPORT __attribute__((dllimport)) /**< Export alias. */
#      define NIMBLE_INLINE static inline __attribute__((always_inline)) /**< Inline alias. */
#    else
#      define NIMBLE_EXPORT __declspec(dllimport) /**< Export alias. */
#      define NIMBLE_INLINE __forceinline /**< Inline alias. */
#    endif
#  endif
#  define NIMBLE_LOCAL /**< Local alias. */
#else
#  if __GNUC__ >= 4
#    define NIMBLE_EXPORT __attribute__((visibility("default"))) /**< Export alias. */
#    define NIMBLE_LOCAL __attribute__((visibility("hidden"))) /**< Local alias. */
#  else
#    define NIMBLE_EXPORT /**< Export alias. */
#    define NIMBLE_LOCAL /**< Local alias. */
#  endif
#  define NIMBLE_INLINE static inline __attribute__((always_inline)) /**< Inline alias. */
#endif

#define NIMBLE_EXTERN extern /**< Extern alias. */

#ifndef NULL
#define NULL ((void *) 0) /**< Null pointer */
#endif

NIMBLE_INLINE
void nFree (void * ptr) {
    free(ptr);
    ptr = NULL;
};

#endif // NIMBLE_H

#ifdef __cplusplus
}
#endif

// Nimble.h
