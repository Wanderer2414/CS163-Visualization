cmake_minimum_required(VERSION 3.8)

project(DSAVisualization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/raylib)
# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Add the list of source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)
add_executable(DSAVisualization ${SOURCES})

target_link_libraries(DSAVisualization PRIVATE raylib)