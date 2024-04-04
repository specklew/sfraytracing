cmake_minimum_required(VERSION 3.27)
message(STATUS "CMake version = " + ${CMAKE_VERSION})

project(sf-raytracing)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(library)
add_subdirectory(program)
