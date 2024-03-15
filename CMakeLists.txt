cmake_minimum_required(VERSION 3.27)

message(STATUS "CMake version = " + ${CMAKE_VERSION})


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER g++) # Requires g++ to be included in PATH
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()

project(sfraytracing)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(dependencies)
add_subdirectory(library)

add_executable(sfraytracing main.cpp
        library/source/Vector.cpp)
