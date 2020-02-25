/*
 *  NimbleEndianness.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#ifndef NimbleEndianness_h
#define NimbleEndianness_h

#include <stdint.h>


// Swaps the endianness of input.
extern uint64_t * nimbleByteSwap(uint64_t * input, const uint64_t length);

#endif /* NimbleEndianness_h */

// NimbleEndianness.h
