cmake_minimum_required(VERSION 3.18)
project(GrossPitaevskiiGpuBcc LANGUAGES CXX CUDA)

file(GLOB SOURCES
    *.hpp
    *.cpp
	*.cu
	*.h
)

set(CMAKE_CUDA_ARCHITECTURES 52)

add_executable(GrossPitaevskiiGpuBcc ${SOURCES})

target_include_directories(GrossPitaevskiiGpuBcc PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_link_libraries(GrossPitaevskiiGpuBcc Mesh)
target_link_libraries(GrossPitaevskiiGpuBcc Output)
target_link_libraries(GrossPitaevskiiGpuBcc Types)