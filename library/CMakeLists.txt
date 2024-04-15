cmake_minimum_required(VERSION 3.27)
project(Library)

message("Fetching SFML...")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

message("Loading library...")

set(SOURCE_FILES
        include/Vector3.h source/Vector3.cpp
        include/Ray.h source/Ray.cpp
        include/Geometry/Sphere.h source/Geometry/Sphere.cpp
        include/Geometry/Plane.h source/Geometry/Plane.cpp
        include/Geometry/Triangle.h source/Geometry/Triangle.cpp
        include/Matrix4x4.h source/Matrix4x4.cpp
        include/Quaternion.h source/Quaternion.cpp
        include/Geometry/Geometry.h
        include/HitInfo.h
        include/Color.h source/Color.cpp
        include/Cameras/PerspectiveCamera.h source/Cameras/PerspectiveCamera.cpp
        include/Cameras/Camera.h source/Cameras/Camera.cpp
        include/Cameras/OrthographicCamera.h
        source/Cameras/OrthographicCamera.cpp
        include/Samplers/Sampler.h
        include/Samplers/UniformDistributionSuperSampler.h
        source/Samplers/UniformDistributionSuperSampler.cpp
        source/Samplers/Sampler.cpp
        include/Scene.h
        source/Scene.cpp
        include/Samplers/AdaptiveSuperSampler.h
        source/Samplers/AdaptiveSuperSampler.cpp
        include/Helpers/MathHelper.h
        source/Helpers/MathHelper.cpp
        include/Materials/Material.h
        include/Materials/MaterialInfo.h
        include/Materials/DiffuseMaterial.h
        source/Materials/DiffuseMaterial.cpp
        source/Materials/MetalMaterial.cpp
        include/Materials/MetalMaterial.h
        include/Helpers/LoggerHelper.h
        source/Helpers/LoggerHelper.cpp
        include/Lights/Light.h
        include/Lights/PointLight.h
        source/Lights/PointLight.cpp
        source/Lights/Light.cpp
        include/Precision.h
        include/Materials/DielectricMaterial.h
        source/Materials/DielectricMaterial.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})