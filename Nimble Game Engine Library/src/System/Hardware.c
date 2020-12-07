#include "../../include/Nimble/NimbleLicense.h"
/*
 * Hardware.c
 * Nimble Game Engine
 *
 * Created by Avery Aaron on 2020-12-05.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/Hardware.h"

/**
 * @file Hardware.c
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
 * SOFTWARE.t
 * @endparblock
 * @date 2020-12-05
 *
 * @brief This class defines error handling functions.
 */

#include <inttypes.h>
#include <stdlib.h>

#if NIMBLE_ARCH == NIMBLE_ARM
/* Processor part numbers: */
#  define CORTEX_A53 0xD03
#endif

char *nSysGetCPUInfo(void)
{
#if (NIMBLE_ARCH == NIMBLE_INTEL) || (NIMBLE_ARCH == NIMBLE_AMD)
    uint32_t brand[12] = {0};

    nint_t eax = 0x80000002;
    for (nint_t i = 0; i < 12; eax++)
    {
        asm(
            "mov %4,%%eax\n"
            "cpuid\n"
            "mov %%eax,%0\n"
            "mov %%ebx,%1\n"
            "mov %%ecx,%2\n"
            "mov %%edx,%3\n"
            : "=g" (brand[i++]), "=g" (brand[i++]),
              "=g" (brand[i++]), "=g" (brand[i++])
            : "r" (eax)
            : "%eax", "%ebx", "%ecx", "%edx"
        );
    }

    if (!brand[0])
    {
        const char einfoFailureStr[] = "nSysGetCPUInfo() failed to run the "\
 "'cpuid' instruction to get the CPU info (x86).";
        nErrorThrow(NERROR_INTERNAL_FAILURE, einfoFailureStr,
         NCONST_STR_LEN(einfoFailureStr));
        return NULL;
    }

    char *cpuInfoStr = nAlloc(sizeof(brand));
    memcpy(cpuInfoStr, brand, sizeof(brand));
    return cpuInfoStr;
#elif NIMBLE_ARCH == NIMBLE_ARM
    scruct cpuidBits {
        uint32_t minor : 4, /* Revision number */
                 part  : 12, /* Part number */
                 arch  : 4, /* Architecture */
                 major : 4, /* Variant number */
                 impl  : 8; /* Implementer ('A') */
    };
    union {
        struct cpuidBits bits;
        uint32_t val;
    } info = {0};

    asm(
        "mrs %%MIDR_EL1, %0\n"
        : "=r" (info.val)
        : /* No input. */
        : /* No clobber. */
    );

    if (!info.val)
    {
        const char einfoFailureStr[] = "nSysGetCPUInfo() failed to run the "\
 "'mrs' instruction to get the CPU info using the 'MIDR_EL1' register "\
 "(ARM).";
        nErrorThrow(NERROR_INTERNAL_FAILURE, einfoFailureStr,
         NCONST_STR_LEN(einfoFailureStr));
        return NULL;
    }

    switch (info.cpuidBits.part)
    {
        case CORTEX_A53:
            break;
        case 2:
    }

    char *cpuInfoStr;
    return cpuInfoStr;
#endif
}

// Hardware.c
