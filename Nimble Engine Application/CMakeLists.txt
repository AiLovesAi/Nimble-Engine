#
# CmakeLists.txt
# Nimble Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.19)
set(ver 0.1.0)
project(NimbleEngineApp VERSION ${ver})

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for Windows 64-bit")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Os -fno-omit-frame-pointer -m64 -Wall -Wextra")
  else()
    message(STATUS "Compiling for Windows 32-bit")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Os -fno-omit-frame-pointer -m32 -Wall -Wextra")
  endif()
elseif(UNIX)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for Unix 64-bit")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Os -fno-omit-frame-pointer -rdynamic -m64 -Wall -Wextra")
  else()
    message(STATUS "Compiling for Unix 32-bit")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Os -fno-omit-frame-pointer -rdynamic -m32 -Wall -Wextra")
  endif()
else()
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Compiling for 64-bit OS")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Os -fno-omit-frame-pointer -rdynamic -m64 -Wall -Wextra")
  else()
    message(STATUS "Compiling for 32-bit OS")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Os -fno-omit-frame-pointer -rdynamic -m32 -Wall -Wextra")
  endif()
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


file(GLOB src
     "../License/NimbleLicense.c"
     "../License/NimbleLicense.h"
     "src/*.c"
     "src/*.h"
     )


add_executable(NimbleEngineApp ${src})
set_target_properties(NimbleEngineApp PROPERTIES OUTPUT_NAME "NimbleEngine")

find_library(NIMBLE_ENGINE NimbleEngine HINTS "../lib/Nimble/")
find_library(NIMBLE_OGL NimbleOGL HINTS "../lib/Nimble/")
target_include_directories(NimbleEngineApp PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lib/Nimble/include/>)
target_link_libraries(NimbleEngineApp ${NIMBLE_ENGINE} ${NIMBLE_OGL})
