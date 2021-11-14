cmake_minimum_required(VERSION 3.18)
project(GrossPitaevskiiGpuCube LANGUAGES CXX CUDA)

file(GLOB SOURCES
    *.hpp
    *.cpp
	*.cu
	*.h
)

set(CMAKE_CUDA_ARCHITECTURES 52)

add_executable(GrossPitaevskiiGpuCube ${SOURCES})

target_include_directories(GrossPitaevskiiGpuCube PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_link_libraries(GrossPitaevskiiGpuCube Mesh)
target_link_libraries(GrossPitaevskiiGpuCube Output)
target_link_libraries(GrossPitaevskiiGpuCube Types)