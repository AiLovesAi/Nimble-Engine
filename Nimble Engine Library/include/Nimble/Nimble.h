#include "NimbleLicense.h"
/*
 * Nimble.h
 * Nimble Engine
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
 * @mainpage Nimble Engine Library
 *
 * @section sec_intro Introduction
 *
 * @par
 * The <em>Nimble Engine Library</em> (or <em>Nimble Library</em>) is the
 * "engine" in <em>Nimble Engine</em>. Developers can use the library to
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

/* Compatability checks */
#if !defined(__GNUC__) || (__GNUC__ < 4)
#  error GCC 4.0+ required.
#endif

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
#  error C99+ standard required.
#endif

/* URL definitions */
#define NIMBLE_REPO_URL  "https://github.com/a3ology/Nimble-Game-Engine" /**< The url for the Nimble Engine repository. */
#define NIMBLE_ISSUE_URL "https://github.com/a3ology/Nimble-Game-Engine/issues/new/choose" /**< The url for the Nimble Engine repository new issue. */


/* OS/Standard definitions */
#define NIMBLE_WINDOWS 1
#define NIMBLE_MACOS   2
#define NIMBLE_UNIX    3
#define NIMBLE_LINUX   4
#define NIMBLE_BSD     5
#define NIMBLE_SOLARIS 6
#define NIMBLE_ANDROID 7

#if defined(_POSIX_SOURCE)
#  define NIMBLE_STD_POSIX
#endif
#if defined(__unix__) || defined(__unix)
#  define NIMBLE_STD_UNIX
#endif

#ifdef _WIN32
#  define NIMBLE_OS NIMBLE_WINDOWS
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(macintosh)
#  define NIMBLE_OS NIMBLE_MACOSX
#elif defined(__ANDROID__)
#  define NIMBLE_OS NIMBLE_ANDROID
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#  define NIMBLE_OS NIMBLE_BSD
#elif defined(__linux__) || defined(__linux) || defined(linux)
#  define NIMBLE_OS NIMBLE_LINUX
#elif defined(sun)
#  define NIMBLE_OS NIMBLE_SOLARIS
#elif defined(__unix__) || defined(__unix)
#  define NIMBLE_OS NIMBLE_UNIX
#else
#  error OS not supported.
#endif


/* Processor definitions */
#define NIMBLE_INTEL 1
#define NIMBLE_AMD   2
#define NIMBLE_ARM   3

#if defined(__i386__) || defined(__ia64__)
#  define NIMBLE_ARCH NIMBLE_INTEL
#elif defined(__amd64__)
#  define NIMBLE_ARCH NIMBLE_AMD
#elif defined(__arm__) || defined(__aarch64__) || defined(__thumb__)
#  define NIMBLE_ARCH NIMBLE_ARM
#else
#  error CPU architecture not supported.
#endif


/* Bit-width definitions */
#if UINTPTR_MAX == 0xffffffff
#  define NIMBLE_32BIT
#elif UINTPTR_MAX == 0xffffffffffffffff
#  define NIMBLE_64BIT
#elif UINTPTR_MAX == 0xffffffffffffffffffffffffffffffff
#  define NIMBLE_128BIT
#else
#  error Only 32-bit, 64-bit, and 128-bit hardware is supported.
#endif


/* Attribute definitions */
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

#define NIMBLE_FREEME /**< Denotes that a function may allocate memory that should later be freed. */


/* Macro definitions */
#ifndef NULL
#  define NULL ((void *) 0) /**< Null pointer. */
#endif
#define NFUNCTION_NAME_MAX 63

/* Basic function definitions */
#define NCONST_STR_LEN(str) sizeof(str) - 1 /**< Gets the length of a const char * as strlen() would, but at compile time. */
#define NCONST_STR_FORMAT_LEN(str, spec1, spec2, spec3, spec4) \
NCONST_STR_LEN(str) - (2 * spec1) - (3 * spec2) - (4 * spec3) - (5 * spec4) /**< Gets the length of a formatted string without the format characters. */

#define NSTR(str) #str /**< Stringifies the argument. */
#define NSTR_VAL(str) NSTR(str) /**< Stringifies the argument's defined value (for macros only). */

/* Nimble integer types */
typedef int_fast8_t   nbyte_t;
typedef uint_fast8_t  nubyte_t;
typedef int_fast16_t  nshort_t;
typedef uint_fast16_t nushort_t;
typedef int_fast32_t  nint_t;
typedef uint_fast32_t nuint_t;
#ifdef NIMBLE_64BIT
typedef int_fast64_t  nlong_t;
typedef uint_fast64_t nulong_t;
#else
typedef intmax_t      nlong_t;
typedef uintmax_t     nulong_t;
#endif

#endif // NIMBLE_H

#ifdef __cplusplus
}
#endif

// Nimble.h
