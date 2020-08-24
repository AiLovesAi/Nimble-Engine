#
# NimbleInstaller.nsi
# Nimble Game Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.18)

project(NimbleGameEngineApplication VERSION 0.1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-Ofast -Os")


file(GLOB src
     "../License/NimbleLicense.c"
     "../License/NimbleLicense.h"
     "src/*.c"
     "src/*.h"
     )

IF (WIN32)
  set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
  set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
ELSEIF(APPLE)
  set(CMAKE_C_COMPILER "gcc")
  set(CMAKE_CXX_COMPILER "g++")
ELSE()
  set(CMAKE_C_COMPILER "gcc")
  set(CMAKE_CXX_COMPILER "g++")
ENDIF()


add_executable(NimbleGameEngineApp ${src})

find_library(NIMBLE_ENGINE NimbleEngine HINTS "../lib/Nimble/")
find_library(NIMBLE_OGL NimbleOGL HINTS "../lib/Nimble/")
target_link_libraries(NimbleGameEngineApp ${NIMBLE_ENGINE} ${NIMBLE_OGL})
