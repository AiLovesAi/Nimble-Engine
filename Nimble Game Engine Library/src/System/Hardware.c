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
#include <string.h>

#define ARM_BUFFER_LEN 77

#if (NIMBLE_ARCH == NIMBLE_INTEL) || (NIMBLE_ARCH == NIMBLE_AMD)
#define nGetInfoReg(eax, ret1, ret2, ret3, ret4) ({\
    asm volatile(\
        "mov %4,%%eax\n" /* Set the eax register that cpuid checks. */\
        "cpuid\n"        /* Run the cpuid instruction. */\
        "mov %%eax,%0\n" /* Store the new eax-edx values in "brand". */\
        "mov %%ebx,%1\n"\
        "mov %%ecx,%2\n"\
        "mov %%edx,%3\n"\
        : "=g" (ret1), "=g" (ret2),\
            "=g" (ret3), "=g" (ret4)\
        : "r" (eax)\
        : "%eax", "%ebx", "%ecx", "%edx"\
    );\
})
#endif

#if NIMBLE_ARCH == NIMBLE_ARM

/* Processor part numbers */
#  define CORTEX_A53 0xD03


/* Info register functions. */
#  ifdef NIMBLE_64BIT
#    define nGetInfoReg(val) ({\
    asm(\
        "mrs %%MIDR_EL1, %0\n" /* Store the MIDR_EL1 register in "info.val". */\
        : "=r" (val)\
        : /* No input. */\
        : /* No clobber.*/\
    );\
})
#  else
#    define nGetInfoReg(val) ({\
    asm(\
        "mrc %%p15, $0, %0, %%c0, %%c0, $0\n" /* Store the MIDR register in "info.val". */
        : "=r" (val)
        : /* No input. */
        : "%p15", "%c0"
    );\
})
#  endif

#  define nSetRevNum(str, val, len) ({\
    if (val > 0x9)
    {
        str[len] = '1';
        len++;
        str[len] = (val - 10) + '0';
        len++;
    }
    else
    {
        str[len] = val + '0';
        len++;
    }
})
#endif

char *nSysGetCPUInfo(size_t *len)
{
#if (NIMBLE_ARCH == NIMBLE_INTEL) || (NIMBLE_ARCH == NIMBLE_AMD)
    uint32_t brand[12] = {0};

    /* Note: 0x80000002-0x80000004 are used to get the highest level CPU brand
     * string for Intel and AMD processors.*/
    uint32_t eax = 0x80000002;
    for (uint32_t i = 0; i < 12; eax++)
    {
        nGetInfoReg(eax, brand[i++], brand[i++], brand[i++], brand[i++]);
    }

    if (!brand[0])
    {
        const char einfoFailureStr[] = "nSysGetCPUInfo() failed to run the "\
 "'cpuid' instruction to get the CPU info (x86).";
        nErrorThrow(NERROR_INTERNAL_FAILURE, einfoFailureStr,
         NCONST_STR_LEN(einfoFailureStr));
        return NULL;
    }

    /* Copy value to "cpuInfoStr". */
    const size_t l = strlen((char *) brand);
    char *cpuInfoStr = nAlloc(l + 1);
    memcpy(cpuInfoStr, brand, l);
    cpuInfoStr[l] = '\0';
    
    *len = l;
    return cpuInfoStr;
#elif NIMBLE_ARCH == NIMBLE_ARM
    /* Use a union to share the data between a uint32_t and a structure defining
     * what the accessed bits are for. */
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

    nGetInfoReg(info.val);

    if (!info.val)
    {
        const char einfoFailureStr[] = "nSysGetCPUInfo() failed to run the "\
#  ifdef NIMBLE_64BIT
 "'mrs' instruction to get the CPU info using the 'MIDR_EL1' register "\
#  else
  "'mrc' instruction to get the CPU info using the 'MIDR' register "\
#  endif
 "(ARM).";
        nErrorThrow(NERROR_INTERNAL_FAILURE, einfoFailureStr,
         NCONST_STR_LEN(einfoFailureStr));
        return NULL;
    }

    /* "ARM %32s rXXpYY %32s" (77 bytes max) */
    char *cpuInfoStr;

    /* CPU is not ARM, but somehow ARM is defined. */
    if (info.cpuidBits.impl != 'A')
    {
        const char unknownCPUStr[] = "Unknown";
        cpuInfoStr = nAlloc(sizeof(unknownCPUStr));
        nStringCopy(cpuInfoStr, unknownCPUStr,
         NCONST_STR_LEN(unknownCPUStr));
        *len = NCONST_STR_LEN(unknownCPUStr);
        return cpuInfoStr;
    }

    const char armStr[] = "ARM ";
    cpuInfoStr = nAlloc(ARM_BUFFER_LEN);
    size_t l = NCONST_STR_LEN(armStr);
    nStringCopy(cpuInfoStr, armStr, NCONST_STR_LEN(armStr));

    /* Identify CPU part. */
    switch (info.cpuidBits.part)
    {
        /** @todo More cases here. */
        case CORTEX_A53:
            const char cortexA53Str[] = "CORTEX-A53";
            nStringCopy(cpuInfoStr + l, cortexA53Str,
             NCONST_STR_LEN(cortexA53Str));
            l += NCONST_STR_LEN(cortexA53Str);
            break;
        default:
            const char unknownCPUStr[] = "Unknown";
            cpuInfoStr = nRealloc(cpuInfoStr, l + sizeof(unknownCPUStr));
            nStringCopy(cpuInfoStr + l, unknownCPUStr,
             NCONST_STR_LEN(unknownCPUStr));
            *len = l + NCONST_STR_LEN(unknownCPUStr);
            return cpuInfoStr;
    }

    const char majorStr[] = " r";
    nStringCopy(cpuInfoStr + l, majorStr, NCONST_STR_LEN(majorStr));

    /* Get part revision number. */
    nSetRevNum(cpuInfoStr, info.cpuidBits.major, l);
    cpuInfoStr[len] = 'p';
    len++;
    nSetRevNum(cpuInfoStr, info.cpuidBits.minor, l);
    cpuInfoStr[len] = ' ';
    len++;

    /* Identify CPU architecture. */
    switch (info.cpuidBits.arch)
    {
        /** @todo More cases here. */
        case 0xf:
            /** @todo "Architectural features are individually identified in the ID_* registers, see 'ID registers'." */
            break;
        default:
            const char unknownArchStr[] = "Unknown architecture";
            nStringCopy(cpuInfoStr + l, unknownArchStr,
             NCONST_STR_LEN(unknownArchStr));
            l += NCONST_STR_LEN(unknownArchStr);
            break;
    }

    cpuInfoStr = nRealloc(cpuInfoStr, l + 1);
    *len = l;
    return cpuInfoStr;
#endif
}

// Hardware.c
