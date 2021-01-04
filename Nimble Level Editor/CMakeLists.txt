#
# CmakeLists.txt
# Nimble Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020-2021 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.19)
set(ver 0.1.0)
project(NimbleLevelEditor VERSION ${ver})

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

add_executable(NimbleLevelEditor main.c)
