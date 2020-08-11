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
  "src/NimbleOpenGL.c"
  "src/NimbleOpenGL.h"
  "src/NimbleGraphics/OpenGL/*.c"
  "src/NimbleGraphics/OpenGL/*.h"
)

file(GLOB vulkan
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/NimbleVulkan.c"
  "src/NimbleVulkan.h"
  "src/NimbleGraphics/vulkan/*.c"
  "src/NimbleGraphics/vulkan/*.h"
)

file(GLOB dx11
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/NimbleDirectX11.c"
  "src/NimbleDirectX11.h"
  "src/NimbleGraphics/DirectX11/*.c"
  "src/NimbleGraphics/DirectX11/*.h"
)

file(GLOB dx12
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/NimbleDirectX12.c"
  "src/NimbleDirectX12.h"
  "src/NimbleGraphics/DirectX12/*.c"
  "src/NimbleGraphics/DirectX12/*.h"
)

add_library(NimbleOGL_${ver} SHARED ${ogl})
add_library(NimbleVulkan_${ver} SHARED ${vulkan})
add_library(NimbleDX11_${ver} SHARED ${dx11})
add_library(NimbleDX12_${ver} SHARED ${dx12})

# Engine libraries
file(GLOB engine
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/NimbleEngine.c"
  "src/NimbleEngine.h"
  "src/NimbleEngine/*.c"
  "src/NimbleEngine/*.h"
)

add_library(NimbleEngine_${ver} SHARED ${engine})
