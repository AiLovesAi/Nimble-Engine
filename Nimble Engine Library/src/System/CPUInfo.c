#include "../../include/Nimble/NimbleLicense.h"
/*
 * CPUInfo.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-05.
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
 *
 */

#include "../../include/Nimble/System/CPUInfo.h"

/**
 * @file CPUInfo.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
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

#include "../../include/Nimble/Errors/Errors.h"

char NCPU_INFO[129] = {0};
size_t NCPU_INFO_LEN = 0;

#if NIMBLE_INST == NIMBLE_INST_ARM
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


#  define nSetRevNum(str, val, len) ({\
    if (val > 0x9)
    {
        str[len++] = '1';
        str[len++] = (val - 10) + '0';
    }
    else
    {
        str[len++] = val + '0';
    }
})
#endif

NIMBLE_INLINE
#if NIMBLE_INST == NIMBLE_INST_x86
void nGetInfoReg(const int operation, unsigned int *val1, unsigned int *val2,
 unsigned int *val3, unsigned int *val4)
#elif NIMBLE_INST == NIMBLE_INST_ARM
void nGetInfoReg(uint64_t *val1)
#endif
{
#if NIMBLE_INST == NIMBLE_INST_x86
    asm volatile(
        "movl %4,%%eax\n" /* Set operation in eax. */
        "cpuid\n"         /* Run the cpuid instruction. */
        "movl %%eax,%0\n" /* Copy string from eax-edx to value. */
        "movl %%ebx,%1\n"
        "movl %%ecx,%2\n"
        "movl %%edx,%3\n"
        : "=g" (*val2),  "=g" (*val1),
          "=g" (*val3), "=g" (*val4)
        : "r" (operation)
        : "%eax", "%ebx", "%ecx", "%edx"
    );
#else
    asm(
        "mrs %%MIDR_EL1, %0\n" /* Store the MIDR_EL1 register in val1. */
        : "=r" (*val1)
        : /* No input. */
        : /* No clobber.*/
    );
#endif
}

char *nSysGetCPUInfo(size_t *len)
{
    /** @todo Get more CPU info (logical/physical processors) and use function similar to lscpu. */
    if (!NCPU_INFO[0])
    {
#if NIMBLE_INST == NIMBLE_INST_x86
        uint32_t brand[12] = {0};

        /* Note: 0x80000002-0x80000004 are used to get the highest level CPU brand
        * string for Intel and AMD processors.*/
        uint32_t operation = 0x80000002;
        for (uint32_t i = 0; i < 12; operation++, i += 4)
        {
            nGetInfoReg(operation, &brand[i], &brand[i + 1], &brand[i + 2], &brand[i + 3]);
        }

#  define einfoStr "nSysGetCPUInfo() failed to run the 'cpuid' instruction to "\
 "get the CPU info (x86)."
        if (nErrorAssert(
         brand[0],
         NERROR_INTERNAL_FAILURE,
         einfoStr,
         NCONST_STR_LEN(einfoStr)
        )) return NULL;
#  undef einfoStr

        /* Copy value to "NCPU_INFO". */
        size_t l = strlen((char *) brand);
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
        if (nErrorAssert(
         l <= NCONST_STR_LEN(NCPU_INFO),
         NERROR_BUFFER_OVERFLOW,
         einfoStr,
         NCONST_STR_LEN(einfoStr)
        )) return NULL;
#  undef einfoStr

        NCPU_INFO_LEN = l;
        if (len) *len = l;
        l++;
        memcpy(NCPU_INFO, brand, l);
#elif NIMBLE_INST == NIMBLE_INST_ARM
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

#  define einfoStr "nSysGetCPUInfo() failed to run the "\
"'mrs' instruction to get the CPU info using the 'MIDR_EL1' register (ARM)."
        if (nErrorAssert(
         info.val,
         NERROR_INTERNAL_FAILURE,
         einfoStr,
         NCONST_STR_LEN(einfoStr)
        )) return NULL;
#  undef einfoStr

        /* CPU is not ARM, but somehow ARM is defined. */
        if (info.cpuidBits.impl != 'A')
        {
#  define unknownCPUStr "Unknown"
            nStringCopy(NCPU_INFO, unknownCPUStr,
            NCONST_STR_LEN(unknownCPUStr));
            NCPU_INFO_LEN = NCONST_STR_LEN(unknownCPUStr);
            if (len) *len = NCONST_STR_LEN(unknownCPUStr);
            return NCPU_INFO;
        }

#  define armStr "ARM "
        size_t l = NCONST_STR_LEN(armStr);
        nStringCopy(NCPU_INFO, armStr, NCONST_STR_LEN(armStr));
#  undef armStr

        /** @todo Find more part and architecture values for more support. */
        /* Identify CPU part. */
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
        switch (info.cpuidBits.part)
        {
            case SWIFT:
#  define partStr "SWIFT"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CYCLONE:
#  define partStr "CYCLONE"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case TYPHOON:
#  define partStr "TYPHOON"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case TYPHOON_CAPRI:
#  define partStr "TYPHOON-CAPRI"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case TWISTER:
#  define partStr "TWISTER"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case TWISTER_ELBA_MALTA:
#  define partStr "TWISTER-ELBA-MALTA"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case HURRICANE:
#  define partStr "HURRICANE"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case HURRICANE_MYST:
#  define partStr "HURRICANE-MYST"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case HURRICANE:
#  define partStr "HURRICANE"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case ARM_920T:
#  define partStr "920T"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case ARM_926EJS:
#  define partStr "926EJS"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case ARM_1136JFS:
#  define partStr "1136JFS"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case ARM_1176JZFS:
#  define partStr "1176JZFS"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CORTEX_A5:
#  define partStr "CORTEX-A5"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CORTEX_A7:
#  define partStr "CORTEX_A7"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CORTEX_A8:
#  define partStr "CORTEX_A8"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CORTEX_A9:
#  define partStr "CORTEX_A9"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CORTEX_A53:
#  define partStr "CORTEX-A53"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            case CORTEX_A55:
#  define partStr "CORTEX-A55"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
#  undef partStr
                break;
            default:
#  define formatStr "It appears you are using an ARM "\
 "processor, but a call to nSysGetCPUInfo() failed to identify the part code.\n"\
 "It would help all others using the same processor if you could go to \""
 NIMBLE_ISSUE_URL "\" and open a New Processor issue, then entering your "\
 "CPU's name and architecture and the following code detected to identify "\
 "your CPU:\n%08x (%d)\nThank you for taking the time to improve the Nimble "\
 "Game Engine!";
            char userRequestStr[NCONST_STR_FORMAT_LEN(formatStr, 1, 0, 1, 0)
                                + 19];
            snprintf(userRequestStr, sizeof(userRequestStr), formatStr,
             info.val, info.val);
#  undef formatStr

            nErrorThrow(NERROR_WARN, userRequestStr,
             NCONST_STR_LEN(userRequestStr), 1);

            if (nErrorAssert(
             l + NCONST_STR_LEN(unknownCPUStr) <= NCONST_STR_LEN(NCPU_INFO),
             NERROR_BUFFER_OVERFLOW,
             einfoStr,
             NCONST_STR_LEN(einfoStr)
            )) return NULL;
            NCPU_INFO = nRealloc(NCPU_INFO, l + sizeof(unknownCPUStr));
            nStringCopy(NCPU_INFO + l, unknownCPUStr,
             NCONST_STR_LEN(unknownCPUStr));
            
            l += NCONST_STR_LEN(unknownCPUStr);
            NCPU_INFO_LEN = l;
            if (len) *len = l;
            return NCPU_INFO;
        }
#  undef unknownCPUStr

#  define majorStr " r";
        nStringCopy(NCPU_INFO + l, majorStr, NCONST_STR_LEN(majorStr));
#  undef majorStr

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
#  define archStr "ARMv4"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv4T:
#  define archStr "ARMv4T"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv5:
#  define archStr "ARMv5"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv5T:
#  define archStr "ARMv5T"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv5TE:
#  define archStr "ARMv5TE"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv5TEJ:
#  define archStr "ARMv5TEJ"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv6:
#  define archStr "ARMv6"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv7:
#  define archStr "ARMv7"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv7f:
#  define archStr "ARMv7f"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv7s:
#  define archStr "ARMv7s"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv7k:
#  define archStr "ARMv7k"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;
            case ARMv8:
#  define archStr "ARMv8"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
#  undef archStr
                break;

            default:
#  define unknownArchStr "Unknown architecture"
                if (nErrorAssert(
                 l + NCONST_STR_LEN(unknownArchStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW,
                 einfoStr,
                 NCONST_STR_LEN(einfoStr)
                )) return NULL;
                nStringCopy(NCPU_INFO + l, unknownArchStr,
                NCONST_STR_LEN(unknownArchStr));
                l += NCONST_STR_LEN(unknownArchStr);
#  undef unknownArchStr
                break;
        }
#  undef einfoStr

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
