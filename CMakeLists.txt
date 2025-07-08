cmake_minimum_required(VERSION 3.8)

project(DSAVisualization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(${CMAKE_SOURCE_DIR}/raylib)
# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/UI
    ${CMAKE_SOURCE_DIR}/include/Visualization
)

# Add the list of source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/source/*.cpp
    ${CMAKE_SOURCE_DIR}/source/UI/*.cpp
    ${CMAKE_SOURCE_DIR}/source/Visualization/*.cpp
)
add_executable(DSAVisualization ${SOURCES})

set(LIB raylib)
if (UNIX) 
    set(LIB X11 raylib)
endif()

target_link_libraries(DSAVisualization PRIVATE ${LIB})