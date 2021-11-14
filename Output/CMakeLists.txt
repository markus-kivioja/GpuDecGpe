cmake_minimum_required(VERSION 3.18)
project(Output)

file(GLOB SOURCES
    *.hpp
    *.cpp
)

add_library(Output ${SOURCES})
set_target_properties(Output PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/"
)

target_include_directories(Output PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})