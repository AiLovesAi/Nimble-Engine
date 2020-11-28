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
                    "include/Nimble/NimbleVulkan/"
                    "include/Nimble/NimbleOpenGL/"
                    "include/Nimble/DirectX11/"
                    "include/Nimble/DirectX12/"
                    "include/Nimble/NimbleEngine/"
                    "include/Nimble/NimbleEngine/Game/"
                    "include/Nimble/NimbleEngine/Game/AI/"
                    "include/Nimble/NimbleEngine/Game/Objects/"
                    "include/Nimble/NimbleEngine/Game/Physics/"
                    "include/Nimble/NimbleEngine/Math/"
                    "include/Nimble/NimbleEngine/Network/"
                    "include/Nimble/NimbleEngine/Output/"
                    "include/Nimble/NimbleEngine/System/"
                    )

# Graphics libraries
file(GLOB ogl
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NimbleOpenGL.c"
     "include/Nimble/NimbleOpenGL.h"
     "src/NimbleGraphics/OpenGL/*.c"
     "include/Nimble/NimbleGraphics/OpenGL/*.h"
     )

file(GLOB vulkan
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NimbleVulkan.c"
     "include/Nimble/NimbleVulkan.h"
     "src/NimbleGraphics/vulkan/*.c"
     "include/Nimble/NimbleGraphics/vulkan/*.h"
     )

file(GLOB dx11
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NimbleDirectX11.c"
     "include/Nimble/NimbleDirectX11.h"
     "src/NimbleGraphics/DirectX11/*.c"
     "include/Nimble/NimbleGraphics/DirectX11/*.h"
     )

file(GLOB dx12
     "src/NimbleLicense.c"
     "include/Nimble/NimbleLicense.h"
     "src/NimbleDirectX12.c"
     "include/Nimble/NimbleDirectX12.h"
     "src/NimbleGraphics/DirectX12/*.c"
     "include/Nimble/NimbleGraphics/DirectX12/*.h"
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
     "src/NimbleEngine/*.c"
     "include/Nimble/NimbleEngine/*.h"
     "src/NimbleEngine/Game/*.c"
     "include/Nimble/NimbleEngine/Game/*.h"
     "src/NimbleEngine/Game/AI/*.c"
     "include/Nimble/NimbleEngine/Game/AI/*.h"
     "src/NimbleEngine/Game/Objects/*.c"
     "include/Nimble/NimbleEngine/Game/Objects/*.h"
     "src/NimbleEngine/Game/Physics/*.c"
     "include/Nimble/NimbleEngine/Game/Physics/*.h"
     "src/NimbleEngine/Math/*.c"
     "include/Nimble/NimbleEngine/Math/*.h"
     "src/NimbleEngine/Network/*.c"
     "include/Nimble/NimbleEngine/Network/*.h"
     "src/NimbleEngine/Output/*.c"
     "include/Nimble/NimbleEngine/Output/*.h"
     "src/NimbleEngine/System/*.c"
     "include/Nimble/NimbleEngine/System/*.h"
     )

add_library(NimbleEngine_${ver} SHARED ${engine})
