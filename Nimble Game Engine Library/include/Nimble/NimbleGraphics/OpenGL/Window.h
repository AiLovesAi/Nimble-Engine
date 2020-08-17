#include "../../NimbleLicense.h"
/*
 * Window.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-08-10.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */


/**
 * @file Window.h
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
 * @brief Creates and controls application windows.
 *
 * This class is used to and controls application windows. Window input and
 * events are not handled by this class.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_GRAPHICS_WINDOW_H
#define NIMBLE_GRAPHICS_WINDOW_H /**< Header definition */

#include "../../NimbleOpenGL.h"

#include <limits.h>
#include <stdint.h>

/**
 * @brief The flags used for creating or changing a window.
 */
typedef enum nWindowFlags {
    NWINDOW_FULLSCREEN = 1 << 0, /**< Sets the window to fullscreen. */
    NWINDOW_CURSOR_SHOWN = 1 << 1, /**< Sets the cursor to be visible. */
    NWINDOW_CURSOR_HIDDEN = 1 << 2 /**< Sets the cursor to be hidden. */
} nWindowFlags_t;

/**
 * @brief The type of monitor to be selected instead of a monitor ID.
 *
 * @note The elements of this enumerator are negative so they can be used as a
 * @p monitor argument in functions that can also take a positive monitor ID.
 */
typedef enum nWindowMonitor {
    NWINDOW_MONITOR_DEFAULT = INT_MIN, /**< The default monitor. */
    NWINDOW_MONITOR_FIRST, /**< The first monitor found. */
    NWINDOW_MONITOR_LAST /**< The last monitor found. */
} nWindowMonitor_t;

/**
 * @brief Creates a window.
 *
 * Creates a window with dimensions @p dimensions, title @p title, icon
 * @p iconData, and flags @p flags.
 *
 * @par Example:
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <Nimble/NimbleOpenGL.h>
 * int main(int argc, char ** argv)
 * {
 *     uint8_t * iconData = nWindowLoadIcon("icon.ico");
 *     if (iconData == NULL)
 *     {
 *         fprintf(stderr, "Failed to load window icon.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     uint32_t * dimensions = nWindowDimensions(NWINDOW_MONITOR_DEFAULT,
 *                              windowPosX, windowPosY, windowWidth,
 *                              windowHeight);
 *     if (dimensions == NULL)
 *     {
 *         fprintf(stderr, "Failed to load window dimensions.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     int32_t window = nWindowCreate("Hello World", iconData, dimensions,
 *                       NWINDOW_FULLSCREEN | NWINDOW_CURSOR_HIDDEN);
 *     if (window == NERROR)
 *     {
 *         fprintf(stderr, "Failed to create window.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("Successfully created window.\n");
 *     exit(EXIT_SUCCESS);
 * }
 * @endcode
 *
 * @param[in] title The title that is displayed at the top of the window.
 * @param[in] iconData The image data of the icon for the window.
 * @param[in] dimensions The position and size of the window, generated by
 * @c nWindowDimensions().
 * @param[in] flags The flags set when creating the window, defined by
 * @c #nWindowFlags_t.
 * @return The window ID generated by the new window is returned if successful;
 * otherwise @c #NERROR is returned and a corresponding error is sent to the
 * error callback set by nErrorHandlerSetErrorCallback().
 */
NIMBLE_EXPORT
int32_t
nWindowCreate(const char * title,
              const uint8_t * iconData,
              const uint32_t * dimensions,
              const int32_t flags
              );

/**
 * @brief Loads a window icon file.
 *
 * Loads the icon file at @p iconPath and returns the pixel data as a
 * <tt>uint8_t *</tt>.
 *
 * @par Example:
 * @code
 * uint8_t *iconData = nWindowLoadIcon("path/to/icon.ico");
 * if (iconData == NULL)
 * {
 *     fprintf(stderr, "Failed to load window icon.\n");
 * }
 * @endcode
 *
 * @param[in] iconPath The file path (local or absolute; local is preferred) to
 * the icon to be loaded.
 * @return The pixel data of the icon @p iconPath is returned if successful;
 * otherwise @c #NULL is returned and a corresponding error is sent to the error
 * callback set by nErrorHandlerSetErrorCallback().
 *
 * @note This function is the same as nFileLoadImage(), but ensures RGBA format
 * is used. The supported file types are the same.
 */
NIMBLE_EXPORT
uint8_t *
nWindowLoadIcon(const char * iconPath
                );

#endif // NIMBLE_GRAPHICS_WINDOW_H

#ifdef __cplusplus
}
#endif

// Window.h
