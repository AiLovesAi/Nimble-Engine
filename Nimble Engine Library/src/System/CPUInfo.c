#include "../../include/Nimble/NimbleLicense.h"
/*
 * CPUInfo.c
 * Nimble Engine
 *
 * Created by Avery Aaron on 2020-12-05.
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
 *
 */

#include "../../include/Nimble/System/CPUInfo.h"

/**
 * @file CPUInfo.c
 * @author Avery Aaron
 * @copyright
 * @parblock
 * The MIT License (MIT)
 * Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
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

#include "../../include/Nimble/Output/Errors/Errors.h"

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
        if (nErrorAssert(brand[0],
         NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr

        /* Copy value to "NCPU_INFO". */
        size_t l = strlen((char *) brand);
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
        if (nErrorAssert(l <= NCONST_STR_LEN(NCPU_INFO),
         NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
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
        if (nErrorAssert(info.val,
         NERROR_INTERNAL_FAILURE, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr

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
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CYCLONE:
                const char partStr[] = "CYCLONE";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TYPHOON:
                const char partStr[] = "TYPHOON";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TYPHOON_CAPRI:
                const char partStr[] = "TYPHOON-CAPRI";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TWISTER:
                const char partStr[] = "TWISTER";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case TWISTER_ELBA_MALTA:
                const char partStr[] = "TWISTER-ELBA-MALTA";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case HURRICANE:
                const char partStr[] = "HURRICANE";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case HURRICANE_MYST:
                const char partStr[] = "HURRICANE-MYST";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case HURRICANE:
                const char partStr[] = "HURRICANE";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_920T:
                const char partStr[] = "920T";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_926EJS:
                const char partStr[] = "926EJS";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_1136JFS:
                const char partStr[] = "1136JFS";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case ARM_1176JZFS:
                const char partStr[] = "1176JZFS";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A5:
                const char partStr[] = "CORTEX-A5";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A7:
                const char partStr[] = "CORTEX_A7";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A8:
                const char partStr[] = "CORTEX_A8";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A9:
                const char partStr[] = "CORTEX_A9";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A53:
                const char partStr[] = "CORTEX-A53";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, partStr, NCONST_STR_LEN(partStr));
                l += NCONST_STR_LEN(partStr);
                break;
            case CORTEX_A55:
                const char partStr[] = "CORTEX-A55";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(partStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
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

            nErrorThrow(NERROR_WARN, userRequestStr,
             NCONST_STR_LEN(userRequestStr), 1);

            const char unknownCPUStr[] = "Unknown";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
            if (nErrorAssert(
             l + NCONST_STR_LEN(unknownCPUStr) <= NCONST_STR_LEN(NCPU_INFO),
             NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
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
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv4T:
                const char archStr[] = "ARMv4T";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5:
                const char archStr[] = "ARMv5";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5T:
                const char archStr[] = "ARMv5T";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5TE:
                const char archStr[] = "ARMv5TE";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv5TEJ:
                const char archStr[] = "ARMv5TEJ";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv6:
                const char archStr[] = "ARMv6";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7:
                const char archStr[] = "ARMv7";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7f:
                const char archStr[] = "ARMv7f";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7s:
                const char archStr[] = "ARMv7s";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv7k:
                const char archStr[] = "ARMv7k";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;
            case ARMv8:
                const char archStr[] = "ARMv8";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(archStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
                nStringCopy(NCPU_INFO + l, archStr, NCONST_STR_LEN(archStr));
                l += NCONST_STR_LEN(archStr);
                break;

            default:
                const char unknownArchStr[] = "Unknown architecture";
#  define einfoStr "CPU info was longer than max size in nSysGetCPUInfo()."
                if (nErrorAssert(
                 l + NCONST_STR_LEN(unknownArchStr) <= NCONST_STR_LEN(NCPU_INFO),
                 NERROR_BUFFER_OVERFLOW, einfoStr, NCONST_STR_LEN(einfoStr))) return NULL;
#  undef einfoStr
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
