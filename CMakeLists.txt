cmake_minimum_required(VERSION 3.8)

project(DSAVisualization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the path to Raylib (change this to where you have Raylib installed)
set(RAYLIB_INCLUDE_DIR "C:/Users/MY\ PC/ProjectDSA/CS163-DSAVisualization/raylib")


# Include directories (Raylib headers)
include_directories(${RAYLIB_INCLUDE_DIR})

# Add the list of source files
set(SOURCES
    source/Application.cpp
    source/Button.cpp
    source/Clock.cpp
    source/Console.cpp
    source/Controller.cpp
    source/Form.cpp
    source/General.cpp
    source/main.cpp
    source/Menu.cpp
    source/TextBox.cpp
    source/TextButton.cpp
    source/TextureButton.cpp
)

# Create executable
add_executable(DSAVisualization ${SOURCES} "include/Colors.h" "source/Colors.cpp" "include/Mode.h" "source/Mode.cpp")

# Link libraries
target_link_libraries(DSAVisualization
    -lraylib
    -lopengl32                      
    -lgdi32                         
    -lwinmm                         
)
# Only have to rerun the cmake when we change this file (CMakeLists.txt)
# cmake -G "Visual Studio 17 2022" -A x64 ..

# Ctrl + Shift + B --> F5 or Ctrl F5