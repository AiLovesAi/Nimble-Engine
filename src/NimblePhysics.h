/*
 *  NimblePhysics.h
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
