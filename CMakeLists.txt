cmake_minimum_required(VERSION 2.8.7)
project(Brainy)
enable_testing()
include(ExternalProject)
include_directories(include)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MACOSX_RPATH 1)

add_subdirectory (src)
add_subdirectory (examples)
add_subdirectory (tests)
