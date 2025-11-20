cmake_minimum_required(VERSION 3.25)

project(dot)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)

add_compile_options(
    -Wall
    -Wextra
)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/raylib)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)