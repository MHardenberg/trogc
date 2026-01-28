cmake_minimum_required(VERSION 3.10)
project(forge C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arena.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/linalg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ode.c
)

# Compiler settings
# ------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

# Debug-specific options
# ------------------------------------------------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    add_compile_options(-fsanitize=address -O0 -g)
    add_link_options(-fsanitize=address)
endif()

# Library
# ------------------------------------------------------------------------------
add_library(forge STATIC
    ${SOURCES}
)

target_include_directories(forge
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(forge PUBLIC openblas)

# Executable
# ------------------------------------------------------------------------------
add_executable(forgetest
    test/main.c
)
target_include_directories(forgetest
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)
target_link_libraries(forgetest PUBLIC forge openblas)
