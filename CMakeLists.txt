cmake_minimum_required(VERSION 3.8)

project(DSAVisualization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to Raylib (adjust this to your actual folder structure)
set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/raylib/include")
set(RAYLIB_LIB_DIR "${CMAKE_SOURCE_DIR}/raylib/lib")

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

# Link Raylib (MinGW-compatible .a or .dll.a file)
# Example: raylib.dll.a or libraylib.a
# Adjust the name to match the actual file you have in your lib folder
target_link_libraries(DSAVisualization
    ${RAYLIB_LIB_DIR}/libraylib.a
    opengl32
    gdi32
    winmm
)