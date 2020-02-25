/*
 *  NimblePhysics.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
 *
 */
#include "NimbleLicense.h"


#ifndef NimblePhysics_h
#define NimblePhysics_h

#include <cglm/cglm.h>
#include <stdint.h>

#include "NimbleWorldObjects.h"

#define M_G 6.673889E-11

struct nimblePhysicsObject {
    struct nimbleWorldObject object;
    double mass; // Kilograms
    vec3 movementVector; // Stores movement axis with magnitude of velocity
    float velocity; // Meters per second
    float acceleration; // Meters per second per second
    vec3 rotationalVector; // Stores rotational axis with magnitude of angular velocity
    float angularVelocity; // Radians per second
    float angularAcceleration; // Randians per second per seconds
};

// TODO

#endif /* NimblePhysics_h */

// NimblePhysics.h
