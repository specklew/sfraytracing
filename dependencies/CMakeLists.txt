include(FetchContent)

#SFML
set(SFML_VERSION "2.6.0")

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG        "${SFML_VERSION}"
)

message(STATUS "Declaring sfml to fetch...")
add_subdirectory(sfml)