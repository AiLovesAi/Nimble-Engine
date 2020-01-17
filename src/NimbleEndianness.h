/*
 *  NimbleEndianness.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleEndianness_h
#define NimbleEndianness_h

#include <stdint.h>


// Forces input to be in little endian order.
extern uint32_t * nimbleForceLittleEndian(uint32_t * input, const uint32_t length);

#endif /* NimbleEndianness_h */

// NimbleEndianness.h
