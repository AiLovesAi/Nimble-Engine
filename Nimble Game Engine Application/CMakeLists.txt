set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
cmake_minimum_required(VERSION 3.18)

project(NimbleGameEngineApplication VERSION 0.1.0)

IF (WIN32)
add_executable(NimbleApplication.exe src/*.c ../License/*.c)
ELSE()
add_executable(NimbleApplication src/*.c ../License/*.c)
ENDIF()
