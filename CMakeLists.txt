cmake_minimum_required(VERSION 2.8.7)
project(Brainy)
enable_testing()
include(ExternalProject)
include_directories(src)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MACOSX_RPATH 1)

# Google Test Framework
ExternalProject_Add(
  GTest
  URL https://github.com/google/googletest/archive/release-1.7.0.zip
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(GTest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/include)
include_directories("${GTEST_INCLUDE_DIR}")

ExternalProject_Get_Property(GTest binary_dir)

set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_PATH})
add_dependencies(${GTEST_LIBRARY} GTest)

set(GTEST_LIBRARY_MAIN_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a)
set(GTEST_LIBRARY_MAIN gtest_main)
add_library(${GTEST_LIBRARY_MAIN} UNKNOWN IMPORTED)
set_property(TARGET ${GTEST_LIBRARY_MAIN} PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_MAIN_PATH})
add_dependencies(${GTEST_LIBRARY_MAIN} GTest)

# JsonCpp library
ExternalProject_Add(
  JsonCpp
  URL https://github.com/open-source-parsers/jsoncpp/archive/1.6.5.zip
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(JsonCpp source_dir)
set(JSONCPP_INCLUDE_DIR ${source_dir}/include)
include_directories("${JSONCPP_INCLUDE_DIR}")

ExternalProject_Get_Property(JsonCpp binary_dir)

set(JSONCPP_LIBRARY_PATH ${binary_dir}/src/lib_json/libjsoncpp.a)
set(JSONCPP_LIBRARY libjsoncpp)
add_library(${JSONCPP_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${JSONCPP_LIBRARY} PROPERTY IMPORTED_LOCATION ${JSONCPP_LIBRARY_PATH})
add_dependencies(${JSONCPP_LIBRARY} JsonCpp)

add_subdirectory (src)
add_subdirectory (examples)
add_subdirectory (tests)
