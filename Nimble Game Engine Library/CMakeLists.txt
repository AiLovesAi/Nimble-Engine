#
# NimbleInstaller.nsi
# Nimble Game Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.18)
set(ver 0.1.0)

project(NimbleGameEngineLibrary VERSION ${ver})

# Graphics libraries
file(GLOB ogl
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/Graphics/OpenGL/*.c"
  "src/Graphics/OpenGL/*.h"
)

file(GLOB vulkan
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/Graphics/vulkan/*.c"
  "src/Graphics/vulkan/*.h"
)

file(GLOB dx11
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/Graphics/DirectX11/*.c"
  "src/Graphics/DirectX11/*.h"
)

file(GLOB dx12
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/Graphics/DirectX12/*.c"
  "src/Graphics/DirectX12/*.h"
)

add_library(NimbleOGL_${ver} SHARED ${ogl})
add_library(NimbleVulkan_${ver} SHARED ${vulkan})
add_library(NimbleDX11_${ver} SHARED ${dx11})
add_library(NimbleDX12_${ver} SHARED ${dx12})

# Engine libraries
file(GLOB engine
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/Engine/*.c"
  "src/Engine/*.h"
)

add_library(NimbleEngine_${ver} SHARED ${engine})
