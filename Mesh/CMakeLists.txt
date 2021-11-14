cmake_minimum_required(VERSION 3.18)
project(Mesh)

file(GLOB SOURCES
    *.hpp
    *.cpp
)

add_library(Mesh ${SOURCES})
set_target_properties(Mesh PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/"
)

target_include_directories(Mesh PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})