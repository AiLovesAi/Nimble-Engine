#include "../../include/Nimble/NimbleLicense.h"
/*
 * CPUInfo.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-05.
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/CPUInfo.h"

/**
 * @file CPUInfo.c
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
 * @brief This class defines CPU info functions.
 */

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

char NCPU_INFO[129] = {0};
size_t NCPU_INFO_LEN = 0;

#if (NIMBLE_ARCH == NIMBLE_INTEL) || (NIMBLE_ARCH == NIMBLE_AMD)
#define nGetInfoReg(eax, ret1, ret2, ret3, ret4) ({\
    asm volatile(\
        "movl %4,%%eax\n" /* Set the eax register that cpuid checks. */\
        "cpuid\n"         /* Run the cpuid instruction. */\
        "movl %%eax,%0\n" /* Store the new eax-edx values in "brand". */\
        "movl %%ebx,%1\n"\
        "movl %%ecx,%2\n"\
        "movl %%edx,%3\n"\
        : "=g" (ret1), "=g" (ret2),\
          "=g" (ret3), "=g" (ret4)\
        : "r" (eax)\
        : "%eax", "%ebx", "%ecx", "%edx"\
    );\
})
#endif

#if NIMBLE_ARCH == NIMBLE_ARM
/* Architecture definitions */
#  define ARMv4        0x1
#  define ARMv4T       0x2
#  define ARMv5        0x3
#  define ARMv5T       0x4
#  define ARMv5TE      0x5
#  define ARMv5TEJ     0x6
#  define ARMv6        0x7
#  define ARMv7        0x8
#  define ARMv7f       0x9
#  define ARMv7s       0xa
#  define ARMv7k       0xb
#  define ARMv8        0xc
#  define ARM_EXTENDED 0xf

/* Processor part definitions */
#  define SWIFT              0x0
#  define CYCLONE            0x1
#  define TYPHOON            0x2
#  define TYPHOON_CAPRI      0x3
#  define TWISTER            0x4
#  define TWISTER_ELBA_MALTA 0x5
#  define HURRICANE          0x6
#  define HURRICANE_MYST     0x7
#  define ARM_920T           0x920
#  define ARM_926EJS         0x926
#  define ARM_1136JFS        0xB36
#  define ARM_1176JZFS       0xB76
#  define CORTEX_A5          0xC05
#  define CORTEX_A7          0xC07
#  define CORTEX_A8          0xC08
#  define CORTEX_A9          0xC09
#  define CORTEX_A53         0xD03
#  define CORTEX_A55         0xD05


/* Info register functions */
#  ifdef NIMBLE_32BIT
#    define nGetInfoReg(val) ({\
    asm(\
        "mrc %%p15, $0, %0, %%c0, %%c0, $0\n" /* Store the MIDR register in "info.val". */
        : "=r" (val)
        : /* No input. */
        : "%p15", "%c0"
    );\
})
#  else
#    define nGetInfoReg(val) ({\
    asm(\
        "mrs %%MIDR_EL1, %0\n" /* Store the MIDR_EL1 register in "info.val". */\
        : "=r" (val)\
        : /* No input. */\
        : /* No clobber.*/\
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
    if (!NCPU_INFO[0])
    {
#if (NIMBLE_ARCH == NIMBLE_INTEL) || (NIMBLE_ARCH == NIMBLE_AMD)
        uint32_t brand[12] = {0};

        /* Note: 0x80000002-0x80000004 are used to get the highest level CPU brand
        * string for Intel and AMD processors.*/
        uint32_t eax = 0x80000002;
        for (uint32_t i = 0; i < 12; eax++, i += 4)
        {
            nGetInfoReg(eax, brand[i], brand[i + 1], brand[i + 2], brand[i + 3]);
        }

        if (!brand[0])
        {
            const char einfoFailureStr[] = "nSysGetCPUInfo() failed to run "\
"the 'cpuid' instruction to get the CPU info (x86).";
            size_t errorDescLen;
            char *errorDescStr = nErrorToString(&errorDescLen,
            NERROR_INTERNAL_FAILURE, einfoFailureStr,
            NCONST_STR_LEN(einfoFailureStr));
            nErrorThrow(NERROR_INTERNAL_FAILURE, errorDescStr, errorDescLen);
            nFree(errorDescStr);
            return NULL;
        }

        /* Copy value to "NCPU_INFO". */
        size_t l = strlen((char *) brand);
        if (l > NCONST_STR_LEN(NCPU_INFO))
        {
            const char einfoTooBigStr[] = "CPU info was longer than max size "\
 "in nSysGetCPUInfo().";
            size_t errorDescLen;
            char *errorDescStr = nErrorToString(&errorDescLen,
            NERROR_INTERNAL_FAILURE, einfoTooBigStr,
            NCONST_STR_LEN(einfoTooBigStr));
            nErrorThrow(NERROR_INTERNAL_FAILURE, errorDescStr, errorDescLen);
            return NULL;
        }

        NCPU_INFO_LEN = l;
        if (len) *len = l;
        l++;
        memcpy(NCPU_INFO, brand, l);
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
#  ifdef NIMBLE_32BIT
 "'mrc' instruction to get the CPU info using the 'MIDR' register "\
#  else
 "'mrs' instruction to get the CPU info using the 'MIDR_EL1' register "\
#  endif
 "(ARM).";
            size_t errorDescLen;
            char *errorDescStr = nErrorToString(&errorDescLen,
            NERROR_BUFFER_OVERFLOW, einfoFailureStr,
            NCONST_STR_LEN(einfoFailureStr));
            nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
            nFree(errorDescStr);
            return NULL;
        }

        /* CPU is not ARM, but somehow ARM is defined. */
        if (info.cpuidBits.impl != 'A')
        {
            const char unknownCPUStr[] = "Unknown";
            nStringCopy(NCPU_INFO, unknownCPUStr,
            NCONST_STR_LEN(unknownCPUStr));
            NCPU_INFO_LEN = NCONST_STR_LEN(unknownCPUStr);
            if (len) *len = NCONST_STR_LEN(unknownCPUStr);
            return NCPU_INFO;
        }

        const char armStr[] = "ARM ";
        size_t l = NCONST_STR_LEN(armStr);
        nStringCopy(NCPU_INFO, armStr, NCONST_STR_LEN(armStr));

        /** @todo Find more part and architecture values for more support. */
        /* Identify CPU part. */
        switch (info.cpuidBits.part)
        {
            case SWIFT:
                const char partStr[] = "SWIFT";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CYCLONE:
                const char partStr[] = "CYCLONE";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TYPHOON:
                const char partStr[] = "TYPHOON";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TYPHOON_CAPRI:
                const char partStr[] = "TYPHOON-CAPRI";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TWISTER:
                const char partStr[] = "TWISTER";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TWISTER_ELBA_MALTA:
                const char partStr[] = "TWISTER-ELBA-MALTA";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case HURRICANE:
                const char partStr[] = "HURRICANE";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case HURRICANE_MYST:
                const char partStr[] = "HURRICANE-MYST";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case HURRICANE:
                const char partStr[] = "HURRICANE";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_920T:
                const char partStr[] = "920T";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_926EJS:
                const char partStr[] = "926EJS";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_1136JFS:
                const char partStr[] = "1136JFS";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_1176JZFS:
                const char partStr[] = "1176JZFS";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A5:
                const char partStr[] = "CORTEX-A5";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A7:
                const char partStr[] = "CORTEX_A7";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A8:
                const char partStr[] = "CORTEX_A8";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A9:
                const char partStr[] = "CORTEX_A9";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A53:
                const char partStr[] = "CORTEX-A53";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A55:
                const char partStr[] = "CORTEX-A55";
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            default:
            const char formatStr[] = "It appears you are using an ARM "\
 "processor, but a nSysGetCPUInfo() call failed to identify the part code.\n"\
 "It would help all others using the same processor if you could go to \""
 NIMBLE_ISSUE_URL "\" and open a New Processor issue, then entering your "\
 "CPU's name and architecture and the following code detected to identify "\
 "your CPU:\n%08x (%d)\nThank you for taking the time to improve the Nimble "\
 "Game Engine!";
            char userRequestStr[NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 1, 0)
                                + 19];
            snprintf(userRequestStr, sizeof(userRequestStr), formatStr,
             info.val, info.val);

            size_t errorDescLen;
            char *errorDescStr = nErrorToString(&errorDescLen, NERROR_WARN,
             userRequestStr, NCONST_STR_LEN(userRequestStr));
            nErrorThrow(NERROR_WARN, errorDescStr, errorDescLen);
            nFree(errorDescStr);

            const char unknownCPUStr[] = "Unknown";
            if (l + NCONST_STR_LEN(unknownCPUStr) > NCONST_STR_LEN(NCPU_INFO))
            {
                const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                size_t errorDescLen;
                char *errorDescStr = nErrorToString(&errorDescLen,
                NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                NCONST_STR_LEN(einfoTooBigStr));
                nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                return NULL;
            }
            NCPU_INFO = nRealloc(NCPU_INFO, l + sizeof(unknownCPUStr));
            nStringCopy(NCPU_INFO + l, unknownCPUStr,
             NCONST_STR_LEN(unknownCPUStr));
            
            l += NCONST_STR_LEN(unknownCPUStr);
            NCPU_INFO_LEN = l;
            if (len) *len = l;
            return NCPU_INFO;
        }

        const char majorStr[] = " r";
        nStringCopy(NCPU_INFO + l, majorStr, NCONST_STR_LEN(majorStr));

        /* Get part revision number. */
        nSetRevNum(NCPU_INFO, info.cpuidBits.major, l);
        NCPU_INFO[len] = 'p';
        l++;
        nSetRevNum(NCPU_INFO, info.cpuidBits.minor, l);
        NCPU_INFO[len] = ' ';
        l++;

        /* Identify CPU architecture. */
        switch (info.cpuidBits.arch)
        {
            case ARMv4:
                const char archStr[] = "ARMv4";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv4T:
                const char archStr[] = "ARMv4T";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5:
                const char archStr[] = "ARMv5";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5T:
                const char archStr[] = "ARMv5T";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5TE:
                const char archStr[] = "ARMv5TE";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5TEJ:
                const char archStr[] = "ARMv5TEJ";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv6:
                const char archStr[] = "ARMv6";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7:
                const char archStr[] = "ARMv7";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7f:
                const char archStr[] = "ARMv7f";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7s:
                const char archStr[] = "ARMv7s";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7k:
                const char archStr[] = "ARMv7k";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv8:
                const char archStr[] = "ARMv8";
                if (l + NCONST_STR_LEN(archStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;

            default:
                const char unknownArchStr[] = "Unknown architecture";
                if (l + NCONST_STR_LEN(unknownArchStr) > NCONST_STR_LEN(NCPU_INFO))
                {
                    const char einfoTooBigStr[] = "CPU info was longer than max "\
 "size in nSysGetCPUInfo().";
                    size_t errorDescLen;
                    char *errorDescStr = nErrorToString(&errorDescLen,
                    NERROR_BUFFER_OVERFLOW, einfoTooBigStr,
                    NCONST_STR_LEN(einfoTooBigStr));
                    nErrorThrow(NERROR_BUFFER_OVERFLOW, errorDescStr, errorDescLen);
                    return NULL;
                }
                nStringCopy(NCPU_INFO + l, unknownArchStr,
                NCONST_STR_LEN(unknownArchStr));
                l += NCONST_STR_LEN(unknownArchStr);
                break;
        }

        NCPU_INFO_LEN = l;
        if (len) *len = l;
#endif
    }
    else if (len)
    {
        *len = NCPU_INFO_LEN;
    }
    
    return NCPU_INFO;
}

// CPUInfo.c
