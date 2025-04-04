cmake_minimum_required(VERSION 3.8)

project(DSAVisual)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the path to Raylib (change this to where you have Raylib installed)
set(RAYLIB_INCLUDE_DIR "C:/Users/Dell/Downloads/CS163-DSAVisual/raylib")

# Include directories (Raylib headers)
include_directories(${RAYLIB_INCLUDE_DIR})

# Link to raylib library (static or dynamic)
link_directories(${RAYLIB_LIB_DIR})

# Add the list of source files
set(Run
    source/Application.cpp
    source/AVLNode.cpp
    source/AVLTree.cpp
    source/Button.cpp
    source/Clock.cpp
    source/ColorBox.cpp
    source/ColorPointer.cpp
    source/CommandLists.cpp
    source/Console.cpp
    source/Container.cpp
    source/Controller.cpp
    source/Dijikstra_margin.cpp
    source/DSU.cpp
    source/DynamicColorCircle.cpp
    source/Edge.cpp
    source/FileDropBox.cpp
    source/Form.cpp
    source/FormStart.cpp
    source/General.cpp
    source/Graph.cpp
    source/Graph.design.cpp
    source/Graph.logic.cpp
    source/GUI.cpp
    source/HeapVisual.cpp
    source/Label.cpp
    source/LinearHashTable.cpp
    source/Menu.cpp
    source/MenuBox.cpp
    source/MenuTab.cpp
    source/MinHeap.cpp
    source/Move.cpp
    source/NotationBox.cpp
    source/OptionBox.cpp
    source/ProgressBar.cpp
    source/SettingPackage.cpp
    source/ShortestPath.cpp
    source/SinglyLinkedList.cpp
    source/SlowMotion.cpp
    source/SunMode.cpp
    source/TabBox.cpp
    source/TextBox.cpp
    source/TextButton.cpp
    source/TextureButton.cpp
    source/ValueScroll.cpp
    source/Vertex.cpp
    source/VerticalOpen.cpp
    source/main.cpp
)

#Add Executables
add_executable(DSAVisual ${Run})

# Link the executable target with raylib and other system libraries
target_link_libraries(DSAVisual ${RAYLIB_LIB_DIR}/libraylib.a opengl32 gdi32 kernel32 winmm)
add_custom_command(TARGET DSAVisual POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   -E copy_if_different "${RAYLIB_LIB_DIR}/raylib.dll"
                   $<TARGET_FILE_DIR:DSAVisual>)

# Only have to rerun the cmake when we change this file (CMakeLists.txt)
# cmake -G "Visual Studio 17 2022" -A x64 ..

# Ctrl + Shift + B --> F5 or Ctrl F5