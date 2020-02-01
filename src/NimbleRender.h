/*
 *  NimbleRender.h
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
#include "NimbleLicense.h"

#ifndef NimbleRender_h
#define NimbleRender_h

#include <GL/glew.h>
#include <vulkan/vulkan.h>
#include <stdint.h>


#define NIMBLE_RENDERMODE_PERSPECTIVE 0 // Perspective matrix, most common in 3D games, fastest
#define NIMBLE_RENDERMODE_RAYMARCH    1 // Shoot rays for each pixel and increment until it hits, slower
#define NIMBLE_RENDERMODE_RAYTRACE    2 // Shoot rays for each pixel and reflect, slowest, most realistic reflections

#ifndef NIMBLE_RENDERMODE
#define NIMBLE_RENDERMODE NIMBLE_RENDERMODE_PERSPECTIVE
#endif

// TODO

#endif /* NimbleRender_h */

// NimbleRender.h
