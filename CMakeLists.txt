cmake_minimum_required(VERSION 3.8)

project(DSAVisual)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)


# Set the path to Raylib (change this to where you have Raylib installed)
set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/raylib/include")
set(RAYLIB_LIB_DIR "${CMAKE_SOURCE_DIR}/raylib")


# Include directories
include_directories(
    ${RAYLIB_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# Add the list of source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)

# Create executable
add_executable(DSAVisualization ${SOURCES})

# Link libraries
target_link_libraries(DSAVisualization
    ${RAYLIB_LIB_DIR}/raylib.lib
    opengl32
    gdi32
    winmm
)