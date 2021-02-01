#
# CmakeLists.txt
# Nimble Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>
#

cmake_minimum_required(VERSION 3.19)
set(ver 0.1.0)
project(NimbleGameEngineLibrary VERSION ${ver})

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for Windows 64-bit")
    set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -m64 -Wall -Wextra -export-dynamic -fvisibility=hidden")
  else()
    message(STATUS "Compiling for Windows 32-bit")
    set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -m32 -Wall -Wextra -export-dynamic -fvisibility=hidden")
  endif()
elseif(UNIX)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for Unix 64-bit")
    set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m64 -Wall -Wextra -export-dynamic -fvisibility=hidden")
  else()
    message(STATUS "Compiling for Unix 32-bit")
    set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m32 -Wall -Wextra -export-dynamic -fvisibility=hidden")
  endif()
else()
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for 64-bit OS")
    set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m64 -Wall -Wextra -export-dynamic -fvisibility=hidden")
  else()
    message(STATUS "Compiling for 32-bit OS")
    set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m32 -Wall -Wextra -export-dynamic -fvisibility=hidden")
  endif()
endif()
message(STATUS "Flags: ${GCC_COMPILE_FLAGS}")
string(REGEX REPLACE " " ";" GCC_COMPILE_FLAGS "${GCC_COMPILE_FLAGS}")

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
                    "include/Nimble/Output/Errors/"
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
     "src/Output/Errors/*.c"
     "include/Nimble/Output/Errors/*.h"
     "src/System/*.c"
     "include/Nimble/System/*.h"
     )


add_library(NimbleOGL SHARED ${ogl})
add_library(NimbleVulkan SHARED ${vulkan})
add_library(NimbleDX11 SHARED ${dx11})
add_library(NimbleDX12 SHARED ${dx12})
add_library(NimbleEngine SHARED ${engine})

if(WIN32)
  target_link_libraries(NimbleOGL dbghelp)
  target_link_libraries(NimbleVulkan dbghelp)
  target_link_libraries(NimbleDX11 dbghelp)
  target_link_libraries(NimbleDX12 dbghelp)
  target_link_libraries(NimbleEngine dbghelp)
endif()

set(GCC_COMPILE_FLAGS "-DNIMBLE_SHARED -Ofast")
target_compile_options(NimbleOGL PUBLIC ${GCC_COMPILE_FLAGS})
target_compile_options(NimbleVulkan PUBLIC ${GCC_COMPILE_FLAGS})
target_compile_options(NimbleDX11 PUBLIC ${GCC_COMPILE_FLAGS})
target_compile_options(NimbleDX12 PUBLIC ${GCC_COMPILE_FLAGS})
target_compile_options(NimbleEngine PUBLIC ${GCC_COMPILE_FLAGS})

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for Windows 64-bit")
    set(GCC_COMPILE_FLAGS_STATIC "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -m64 -Wall -Wextra -export-all-symbols -fvisibility=hidden")
  else()
    message(STATUS "Compiling for Windows 32-bit")
    set(GCC_COMPILE_FLAGS_STATIC "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -m32 -Wall -Wextra -export-all-symbols -fvisibility=hidden")
  endif()
elseif(UNIX)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for Unix 64-bit")
    set(GCC_COMPILE_FLAGS_STATIC "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m64 -Wall -Wextra -export-all-symbols -fvisibility=hidden")
  else()
    message(STATUS "Compiling for Unix 32-bit")
    set(GCC_COMPILE_FLAGS_STATIC "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m32 -Wall -Wextra -export-all-symbols -fvisibility=hidden")
  endif()
else()
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for 64-bit OS")
    set(GCC_COMPILE_FLAGS_STATIC "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m64 -Wall -Wextra -export-all-symbols -fvisibility=hidden")
  else()
    message(STATUS "Compiling for 32-bit OS")
    set(GCC_COMPILE_FLAGS_STATIC "-DNIMBLE_SHARED -Ofast -Os -fno-omit-frame-pointer -rdynamic -m32 -Wall -Wextra -export-all-symbols -fvisibility=hidden")
  endif()
endif()
message(STATUS "Flags: ${GCC_COMPILE_FLAGS_STATIC}")
string(REGEX REPLACE " " ";" GCC_COMPILE_FLAGS_STATIC "${GCC_COMPILE_FLAGS_STATIC}")

add_library(NimbleOGL_static STATIC ${ogl})
add_library(NimbleVulkan_static STATIC ${vulkan})
add_library(NimbleDX11_static STATIC ${dx11})
add_library(NimbleDX12_static STATIC ${dx12})
add_library(NimbleEngine_static STATIC ${engine})

if(WIN32)
  target_link_libraries(NimbleOGL_static dbghelp)
  target_link_libraries(NimbleVulkan_static dbghelp)
  target_link_libraries(NimbleDX11_static dbghelp)
  target_link_libraries(NimbleDX12_static dbghelp)
  target_link_libraries(NimbleEngine_static dbghelp)
endif()

target_compile_options(NimbleOGL_static PUBLIC ${GCC_COMPILE_FLAGS_STATIC})
target_compile_options(NimbleVulkan_static PUBLIC ${GCC_COMPILE_FLAGS_STATIC})
target_compile_options(NimbleDX11_static PUBLIC ${GCC_COMPILE_FLAGS_STATIC})
target_compile_options(NimbleDX12_static PUBLIC ${GCC_COMPILE_FLAGS_STATIC})
target_compile_options(NimbleEngine_static PUBLIC ${GCC_COMPILE_FLAGS_STATIC})

set_target_properties(NimbleOGL_static PROPERTIES OUTPUT_NAME "NimbleOGL")
set_target_properties(NimbleVulkan_static PROPERTIES OUTPUT_NAME "NimbleVulkan")
set_target_properties(NimbleDX11_static PROPERTIES OUTPUT_NAME "NimbleDX11")
set_target_properties(NimbleDX12_static PROPERTIES OUTPUT_NAME "NimbleDX12")
set_target_properties(NimbleEngine_static PROPERTIES OUTPUT_NAME "NimbleEngine")
