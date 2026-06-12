cmake_minimum_required(VERSION 3.10)
project(trog)

if(NOT CMAKE_BUILD_TYPE)
    # set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()




set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/ SOURCES) 
set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/trogAssert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arena.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scratchpad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/euclidean.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hyperbolic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tensor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plot.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/alist.c
)

# Compiler settings
# ------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    #-fPIC
)

add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Debug-specific options
# ------------------------------------------------------------------------------
add_compile_definitions(_BLAS)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
    add_compile_options(-fsanitize=address -O0 -g)
    add_link_options(-fsanitize=address)
else()
    add_compile_options(-O3 -s -flto -ffast-math -march=native)
    add_link_options(-flto)
endif()

# Library
# ------------------------------------------------------------------------------
add_library(trog STATIC
    ${SOURCES}
)

target_include_directories(trog
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(trog PRIVATE backtrace openblas)

# Executable
# ------------------------------------------------------------------------------
add_executable(trogtest
    test/main.c
)
target_include_directories(trogtest
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)
target_link_libraries(trogtest PUBLIC trog backtrace openblas m)
