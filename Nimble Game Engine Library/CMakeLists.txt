#
# CmakeLists.txt
# Nimble Game Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.18)
set(ver 0.1.0)

project(NimbleGameEngineLibrary VERSION ${ver})

include_directories("include/Nimble/"
                    "include/Nimble/Graphics/NimbleVulkan/"
                    "include/Nimble/Graphics/NimbleOpenGL/"
                    "include/Nimble/Graphics/DirectX11/"
                    "include/Nimble/Graphics/DirectX12/"
                    "include/Nimble/"
                    "include/Nimble/Game/"
                    "include/Nimble/Game/AI/"
                    "include/Nimble/Game/Objects/"
                    "include/Nimble/Game/Physics/"
                    "include/Nimble/Math/"
                    "include/Nimble/Network/"
                    "include/Nimble/Output/"
                    "include/Nimble/System/"
                    )

# Graphics libraries
file(GLOB ogl
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NimbleOpenGL.c"
     "include/Nimble/Graphics/NimbleOpenGL.h"
     "src/Graphics/OpenGL/*.c"
     "include/Nimble/Graphics/OpenGL/*.h"
     )

file(GLOB vulkan
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/Graphics/NimbleVulkan.c"
     "include/Nimble/Graphics/NimbleVulkan.h"
     "src/Graphics/vulkan/*.c"
     "include/Nimble/Graphics/vulkan/*.h"
     )

file(GLOB dx11
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/Graphics/NimbleDirectX11.c"
     "include/Nimble/Graphics/NimbleDirectX11.h"
     "src/Graphics/DirectX11/*.c"
     "include/Nimble/Graphics/DirectX11/*.h"
     )

file(GLOB dx12
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NGraphics/imbleDirectX12.c"
     "include/Nimble/Graphics/NimbleDirectX12.h"
     "src/Graphics/DirectX12/*.c"
     "include/Nimble/Graphics/DirectX12/*.h"
     )

add_library(NimbleOGL_${ver} SHARED ${ogl})
add_library(NimbleVulkan_${ver} SHARED ${vulkan})
add_library(NimbleDX11_${ver} SHARED ${dx11})
add_library(NimbleDX12_${ver} SHARED ${dx12})

# Engine libraries
file(GLOB engine
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NimbleEngine.c"
     "include/Nimble/NimbleEngine.h"
     "src/*.c"
     "include/Nimble/*.h"
     "src/Game/*.c"
     "include/Nimble/Game/*.h"
     "src/Game/AI/*.c"
     "include/Nimble/Game/AI/*.h"
     "src/Game/Objects/*.c"
     "include/Nimble/Game/Objects/*.h"
     "src/Game/Physics/*.c"
     "include/Nimble/Game/Physics/*.h"
     "src/Math/*.c"
     "include/Nimble/Math/*.h"
     "src/Network/*.c"
     "include/Nimble/Network/*.h"
     "src/Output/*.c"
     "include/Nimble/Output/*.h"
     "src/System/*.c"
     "include/Nimble/System/*.h"
     )

add_library(NimbleEngine_${ver} SHARED ${engine})
