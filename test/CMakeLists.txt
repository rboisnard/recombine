cmake_minimum_required(VERSION 3.22)

project(
  recombine
  VERSION 1.0
)

# out of source builds
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" in_source)
get_filename_component(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PARENTDIR}" in_source_subdir)
if(in_source OR in_source_subdir)
  message(FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source build.")
endif(in_source OR in_source_subdir)

find_package(GTest)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(original)
add_subdirectory(recombined)