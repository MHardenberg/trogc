cmake_minimum_required(VERSION 3.10)
project(forge C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler settings
# ------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 17)
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
set(SOURCES ${CMAKE_SOURCE_DIR}/src/arena.c)
# ------------------------------------------------------------------------------
add_library(forge STATIC
    ${SOURCES}
)

target_include_directories(forge
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# Executable
# ------------------------------------------------------------------------------
add_executable(StaticTest
    main.c
)

target_link_libraries(StaticTest
    PRIVATE forge
)

