/*
 *  NimbleWorldObjects.c
 *  Nimble Game Engine
 *
 *  Created by Avery Aaron on 1/11/20.
 *  Copyright © 2020 Avery Aaron. All rights reserved.
 *
 */

#include "NimbleMath.h"
#include "NimbleMemory.h"
#include "NimbleWorldObjects.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"


nimbleWorldObject * worldObjects = NULL;
volatile uint32_t          objectCount  = 0;
volatile uint32_t          nextID       = 0;
nimbleTexture *     textures     = NULL;
volatile uint32_t          textureCount = 0;


// Creates a texture and returns its ID.
const uint32_t nimbleTextureLoad(const char * png)
{
    int32_t width    = 0;
    int32_t height   = 0;
    int32_t colorChannels = 0;
    uint8_t * image = stbi_load(png, &width, &height, &colorChannels, 0);
    
    if (!image)
    {
        return 0;
    }
    
    textures = nimbleMemoryReallocate(textures, (sizeof(nimbleTexture) * textureCount), (sizeof(nimbleTexture) * (textureCount + 1)));
    textureCount++;
    
    uint32_t textureID = 0;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    const uint16_t dataType = (colorChannels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, dataType, width, height, 0, dataType, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    free(image);
    
    const uint32_t textureIndex = textureCount - 1;
    textures[textureIndex].textureID = textureID;
    textures[textureIndex].textureIndex = textureIndex;
    textures[textureIndex].colorChannels = colorChannels;
    textures[textureIndex].width = width;
    textures[textureIndex].height = height;
    
    return textureID;
}

// Unloads a texture.
void nimbleTextureUnload(const uint32_t textureIndex)
{
    // Destroy texture
    glDeleteTextures(1, &textures[textureIndex].textureID);
    textures[textureIndex].textureID = 0;
    
    // Reallocate textures
    if (textureIndex < (textureCount - 1))
    {
        
        for (uint32_t i = (textureIndex + 1); i < textureCount; i++)
        {
            textures[i].textureIndex--;
        }
        
        memcpy(textures + (textureIndex * sizeof(nimbleTexture)), textures + (textureIndex * sizeof(nimbleTexture)) + 1,
               (sizeof(nimbleTexture) * (textureCount - textureIndex - 1)));
    }
    
    textures = nimbleMemoryReallocate(textures, (sizeof(nimbleTexture) * textureCount), (sizeof(nimbleTexture) * (textureCount - 1)));
    textureCount--;
}

// Creates a world object and returns its ID.
const uint32_t nimbleObjectCreate(const vec3 position, const vec4 orientation, const uint32_t parentObjectID, const float * meshVertices, const uint32_t vertexCount, const uint32_t * meshIndices, const uint32_t indexCount, const uint32_t faces, const uint32_t * textureIDs)
{
    worldObjects = nimbleMemoryReallocate(worldObjects, (sizeof(nimbleWorldObject) * objectCount), (sizeof(nimbleWorldObject) * (objectCount + 1)));
    objectCount++;
    const uint32_t objectID = nextID;
    nextID++;
    const uint32_t objectIndex = objectCount - 1;
    worldObjects[objectIndex].objectID = objectID;
    worldObjects[objectIndex].objectIndex = objectIndex;
    
    // Create mesh
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * vertexCount), meshVertices, GL_STATIC_DRAW);
    
    GLuint IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(float) * indexCount), meshIndices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 5), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (sizeof(float) * 5), (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    worldObjects[objectIndex].mesh.VAO = VAO;
    worldObjects[objectIndex].mesh.IBO = IBO;
    worldObjects[objectIndex].mesh.VBO = VBO;
    worldObjects[objectIndex].mesh.indexCount = indexCount;
    worldObjects[objectIndex].mesh.vertexCount = vertexCount;
    
    for (uint32_t i = 0; i < (faces & 0xff); i++)
    {
        worldObjects[objectIndex].textureIDs[i] = textureIDs[i];
    }
    
    nimbleMathVec4InitFrom(worldObjects[objectIndex].orientation, orientation);
    nimbleMathVec3InitFrom(worldObjects[objectIndex].position, position);
    worldObjects[objectIndex].parentObject = parentObjectID;
    
    return objectID;
}

// Destroys a world object.
void nimbleObjectDestroy(const uint32_t objectIndex)
{
    worldObjects[objectIndex].objectID = 0;
    
    // Destroy mesh
    if (worldObjects[objectIndex].mesh.IBO)
    {
        glDeleteBuffers(1, &worldObjects[objectIndex].mesh.IBO);
        worldObjects[objectIndex].mesh.IBO = 0;
    }
    
    if (worldObjects[objectIndex].mesh.VBO)
    {
        glDeleteBuffers(1, &worldObjects[objectIndex].mesh.VBO);
        worldObjects[objectIndex].mesh.VBO = 0;
    }
    
    if (worldObjects[objectIndex].mesh.VAO)
    {
        glDeleteVertexArrays(1, &worldObjects[objectIndex].mesh.VAO);
        worldObjects[objectIndex].mesh.VAO = 0;
    }
    
    worldObjects[objectIndex].mesh.indexCount = 0;
    
    // Reallocate objects
    if (objectIndex < (objectCount - 1))
    {
        
        for (uint32_t i = (objectIndex + 1); i < objectCount; i++)
        {
            worldObjects[i].objectIndex--;
        }
        
        memcpy((worldObjects + (sizeof(nimbleWorldObject) * objectIndex)), (worldObjects + (sizeof(nimbleWorldObject) * objectIndex) + 1), (sizeof(nimbleWorldObject) * (objectCount - objectIndex - 1)));
    }
    
    worldObjects = nimbleMemoryReallocate(worldObjects, (sizeof(nimbleWorldObject) * objectCount), (sizeof(nimbleWorldObject) * (objectCount - 1)));
    objectCount--;
}


// NimbleWorldObjects.c
