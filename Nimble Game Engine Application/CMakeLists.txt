#
# NimbleInstaller.nsi
# Nimble Game Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.18)

project(NimbleGameEngineApplication VERSION 0.1.0)

file(GLOB src
  "../License/NimbleLicense.c"
  "../License/NimbleLicense.h"
  "src/*.c"
  "src/*.h"
)

IF (WIN32)
  set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
  set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
  add_executable(NimbleGameEngineW ${src})
ELSEIF(APPLE)
  set(CMAKE_C_COMPILER "gcc")
  set(CMAKE_CXX_COMPILER "g++")
  add_executable(NimbleGameEngineM ${src})
ELSE()
  set(CMAKE_C_COMPILER "gcc")
  set(CMAKE_CXX_COMPILER "g++")
  add_executable(NimbleGameEngineL ${src})
ENDIF()
