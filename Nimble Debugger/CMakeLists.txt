#
# CmakeLists.txt
# Nimble Game Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
#

cmake_minimum_required(VERSION 3.18)
set(ver 0.1.0)
set(GCC_COMPILE_FLAGS, "-Ofast -Os -fno-omit-frame-pointer -rdynamic -Wall")

project(NimbleDebugger VERSION ${ver})

add_definitions(${GCC_COMPILE_FLAGS})
add_executable(NimbleDebugger main.c)
