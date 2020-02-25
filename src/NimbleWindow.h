/*
 *  NimbleWindow.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/30/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"

#ifndef NimbleWindow_h
#define NimbleWindow_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "NimbleError.h"

#ifndef NULL
#define NULL (void *) 0
#endif


// Render modes
#define NIMBLE_RENDERMODE_PERSPECTIVE 0 // Perspective matrix, most common in 3D games, fastest
#define NIMBLE_RENDERMODE_RAYMARCH    1 // Shoot rays for each pixel and increment until it hits, slower
#define NIMBLE_RENDERMODE_RAYTRACE    2 // Shoot rays for each pixel and reflect, slowest, most realistic reflections

#ifndef NIMBLE_RENDERMODE
#define NIMBLE_RENDERMODE NIMBLE_RENDERMODE_PERSPECTIVE
#endif

extern volatile uint8_t nimbleGameRunning;

extern GLFWwindow * nimbleWindowMain;

// TODO

#endif /* NimbleWindow_h */

// NimbleWindow.h
