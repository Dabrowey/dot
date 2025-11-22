cmake_minimum_required(VERSION 3.25)

project(dot)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)

add_compile_options(
    -Wall
    -Wextra
)

add_executable(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/main.c
    ${CMAKE_SOURCE_DIR}/localization.generated.c
    ${CMAKE_SOURCE_DIR}/settings.c
    ${CMAKE_SOURCE_DIR}/utils/file.c
    ${CMAKE_SOURCE_DIR}/deps/cJSON/cJSON.c
)

include_directories(
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/deps/cJSON
    ${CMAKE_SOURCE_DIR}/deps/raylib/src
)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/raylib)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)