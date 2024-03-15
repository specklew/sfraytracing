cmake_minimum_required(VERSION 3.27)
project(Library)

message("Loading library...")

set(SOURCE_FILES
        include/Vector.h source/Vector.cpp)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)