cmake_minimum_required(VERSION 3.18)
project(GrossPitaevskiiGpuC15 LANGUAGES CXX CUDA)

file(GLOB SOURCES
    *.hpp
    *.cpp
	*.cu
	*.h
)

set(CMAKE_CUDA_ARCHITECTURES 52)

add_executable(GrossPitaevskiiGpuC15 ${SOURCES})

target_include_directories(GrossPitaevskiiGpuC15 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_link_libraries(GrossPitaevskiiGpuC15 Mesh)
target_link_libraries(GrossPitaevskiiGpuC15 Output)
target_link_libraries(GrossPitaevskiiGpuC15 Types)