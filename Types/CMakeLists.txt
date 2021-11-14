cmake_minimum_required(VERSION 3.18)
project(Types)

file(GLOB SOURCES
    *.hpp
    *.cpp
)

add_library(Types ${SOURCES})
set_target_properties(Types PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/"
)

target_include_directories(Types PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})