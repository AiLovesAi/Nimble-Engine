/*
 *  NimbleRender.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleRender_h
#define NimbleRender_h

#include <GL/glew.h>
#include <stdint.h>


#define NIMBLE_RENDERMODE_PERSPECTIVE 0 // Perspective matrix, most common in 3D games, fastest
#define NIMBLE_RENDERMODE_RAYMARCH    1 // Shoot rays for each pixel and increment until it hits, slower
#define NIMBLE_RENDERMODE_RAYTRACE    2 // Shoot rays for each pixel and reflect, slowest, most realistic reflections

#ifndef NIMBLE_RENDERMODE
#define NIMBLE_RENDERMODE NIMBLE_RENDERMODE_PERSPECTIVE
#endif

#endif /* NimbleRender_h */

// NimbleRender.h
