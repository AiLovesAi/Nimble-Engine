#include "../NimbleLicense.h"
/*
 * Hardware.h
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-12-05.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

/**
 * @file Hardware.h
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
 * @date 2020-12-05
 *
 * @brief This class defines error handling functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NIMBLE_ENGINE_HARDWARE_H
#define NIMBLE_ENGINE_HARDWARE_H /**< Header definition */

#include "../NimbleEngine.h"

/**
 * @brief Gets the CPU info of the system.
 *
 * Example:
 * @code
 * #include <stdio.h>
 * #include <Nimble/NimbleEngine.h>
 *
 * int main(int argc, char **argv)
 * {
 *     char *cpuInfo = nSysGetCPUInfo();
 *     if (cpuInfo == NULL)
 *     {
 *         fprintf(stderr, "Failed to get error string.\n");
 *         exit(EXIT_FAILURE);
 *     }
 *     printf("CPU installed: %s\n", cpuInfo);
 *     return EXIT_SUCCESS;
 * }
 * @endcode
 *
 * @param[out] errorLen The length of the string returned. This can be @c #NULL.
 * @return A pointer to the string of the CPU info is returned if successful;
 * otherwise @c #NULL is returned.
 */
NIMBLE_EXTERN
NIMBLE_FREEME
char *
nSysGetCPUInfo(void)
__attribute__((warn_unused_result))
;

#endif // NIMBLE_ENGINE_HARDWARE_H

#ifdef __cplusplus
}
#endif

// Hardware.h
