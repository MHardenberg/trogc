cmake_minimum_required(VERSION 3.10)
project(forge C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()




set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/forgeAssert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arena.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scratchpad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.c
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
)

add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Debug-specific options
# ------------------------------------------------------------------------------
add_compile_definitions(_BLAS)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #add_compile_definitions(_DEBUG)
    #add_compile_options(-fsanitize=address -O0 -g)
    #add_link_options(-fsanitize=address)
    add_compile_options( -O3 -s)

else()
    add_compile_options(-O3 -s)
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

target_link_libraries(forge PRIVATE backtrace openblas)
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
target_link_libraries(forgetest PUBLIC forge backtrace openblas m)
