/*
 *  NimbleEndianness.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include "NimbleEndianness.h"

#define ORDER_LITTLE_ENDIAN 0x03020100UL
#define ORDER_BIG_ENDIAN    0x00010203UL

uint32_t HOST_ENDIANNESS = 0;


// Checks the endianness of the host machine at runtime.
static void nimbleCheckHostEndianness(void)
{
    const union {
        uint8_t input[4];
        uint32_t value;
    } hostOrder = {{0x00, 0x01, 0x02, 0x03}};
    
    HOST_ENDIANNESS = hostOrder.value;
}

// Forces input to be in little endian order.
uint32_t * nimbleForceLittleEndian(uint32_t * input, const uint32_t length)
{
    
    if (!HOST_ENDIANNESS)
    {
        nimbleCheckHostEndianness();
    }
    
    if (HOST_ENDIANNESS == ORDER_BIG_ENDIAN)
    {
        
        for (int32_t i = (length - 1); i >= 0; i--)
        {
            input[i] = ((input[i] >> 24) & 0xff) | ((input[i] << 8) & 0xff0000) | ((input[i] >> 8) & 0xff00) | ((input[i] << 24) & 0xff000000);
        }
        
    }
    
    return input;
}


// NimbleEndianness.c
