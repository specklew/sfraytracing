project(Program)

set(SOURCE_FILES
        main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        Library
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
)

