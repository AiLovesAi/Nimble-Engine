/*
 *  NimbleEndianness.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "NimbleEndianness.h"

// Forces input to be in little endian order.
uint64_t * nimbleByteSwap(uint64_t * input, const uint64_t length)
{
        
    for (int64_t i = (length - 1); i >= 0; i--)
    {
        input[i] =
        ((input[i] & 0xff00000000000000) >> 56) |
        ((input[i] & 0x00ff000000000000) >> 40) |
        ((input[i] & 0x0000ff0000000000) >> 24) |
        ((input[i] & 0x000000ff00000000) >> 8) |
        ((input[i] & 0x00000000ff000000) << 8) |
        ((input[i] & 0x0000000000ff0000) << 24) |
        ((input[i] & 0x000000000000ff00) << 40) |
        ((input[i] & 0x00000000000000ff) << 56);
    }
    
    return input;
}


// NimbleEndianness.c
