/*
 *  NimbleWorldObjects.h
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#ifndef NimbleWorldObjects_h
#define NimbleWorldObjects_h

#include <cglm/cglm.h>
#include <GL/glew.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE static inline __attribute((always_inline))
#endif
#ifndef NULL
#define NULL (void *) 0
#endif

extern struct nimbleWorldObject * worldObjects;
extern volatile uint32_t objectCount;
extern volatile uint32_t objectMemory;
extern struct nimbleTexture * textures;
extern volatile uint32_t textureCount;

struct nimbleTexture {
    uint32_t textureID;
    uint32_t textureIndex;
    uint16_t width;
    uint16_t height;
    uint8_t colorChannels;
};

struct nimbleMesh {
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    uint32_t indexCount;
    uint32_t vertexCount;
};

struct nimbleWorldObject {
    uint32_t objectID;
    uint32_t objectIndex;
    struct nimbleMesh mesh;
    uint32_t faces;
    uint32_t textureIDs[256];
    vec3 position; // World position
    versor orientation; // Rotational orientation quaternion
    uint32_t parentObject; // ID of the parent object (0 if none)
};


// Loads a texture and returns its ID.
extern const uint32_t nimbleTextureLoad(const char * png);

// Unloads a texture.
extern void nimbleTextureUnload(const uint32_t textureIndex);

// Creates a world object and returns its ID.
extern const uint32_t nimbleObjectCreate(const vec3 position, const vec4 orientation, const uint32_t parentObjectID, const float * meshVertices, const uint32_t vertexCount, const uint32_t * meshIndices, const uint32_t indexCount, const uint32_t faces, const uint32_t * textureIDs);

// Destroys a world object.
extern void nimbleObjectDestroy(const uint32_t objectIndex);

ALWAYS_INLINE void nimbleObjectsNormalize(void)
{
    
    for (uint32_t i = 0; i < objectCount; i++)
    {
        
        if (glm_quat_norm(worldObjects[i].orientation))
        {
            glm_quat_normalize(worldObjects[i].orientation);
        }
        
    }
    
}

#endif /* NimbleWorldObjects_h */

// NimbleWorldObjects.h
