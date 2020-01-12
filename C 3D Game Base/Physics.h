/*
 *  Physics.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */


#ifndef Physics_h
#define Physics_h

#include <cglm/cglm.h>
#include <stdint.h>

#include "WorldObjects.h"

#define M_G 6.673889E-11

struct physicsObject {
    struct worldObject object;
    double mass; // Kilograms
    vec3 movementAxis;
    double velocity; // Meters per second
    double acceleration; // Meters per second per second
    vec3 rotationalAxis;
    double angularVelocity; // Radians per second
    double angularAcceleration; // Randians per second per seconds
};

// TODO

#endif /* Physics_h */

// Physics.h
