cmake_minimum_required(VERSION 3.27)
project(Library)

message("Loading library...")

set(SOURCE_FILES
        include/Vector3.h source/Vector3.cpp
        include/Ray.h source/Ray.cpp
        include/Sphere.h source/Sphere.cpp
        include/Plane.h source/Plane.cpp
        include/Triangle.h source/Triangle.cpp
        include/Matrix4x4.h source/Matrix4x4.cpp
        include/Quaternion.h source/Quaternion.cpp
        include/Geometry.h
        include/HitInfo.h
        include/Color.h
        source/Color.cpp
        include/Camera.h
        source/Camera.cpp
)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
