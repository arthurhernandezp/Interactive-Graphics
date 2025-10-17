cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME InteractiveGraphicsCourse)
project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available configurations" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Werror -D_CRT_SECURE_NO_WARNINGS -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -D_NDEBUG -funroll-loops -fexceptions")

set(CMAKE_VERBOSE_MAKEFILE OFF)

add_subdirectory(src)
add_subdirectory(external)

message("Adding tests")
enable_testing()
add_subdirectory(tests)
