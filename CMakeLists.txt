cmake_minimum_required(VERSION 3.8)

project(DSAVisual)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the path to Raylib (change this to where you have Raylib installed)
set(RAYLIB_INCLUDE_DIR "C:/Users/Dell/Downloads/CS163-DSAVisual/raylib")

# Include directories (Raylib headers)
include_directories(${RAYLIB_INCLUDE_DIR})

# Add the list of source files
set(SOURCES
    source/Application.cpp
    AVLNode.cpp
    AVLTree.cpp
    Button.cpp
    Clock.cpp
    ColorBox.cpp
    ColorPointer.cpp
    CommandLists.cpp
    Console.cpp
    Container.cpp
    Controller.cpp
    Dijikstra_margin.cpp
    DSU.cpp
    DynamicColorCircle.cpp
    Edge.cpp
    FileDropBox.cpp
    Form.cpp
    FormStart.cpp
    General.cpp
    Graph.cpp
    Graph.design.cpp
    Graph.logic.cpp
    GUI.cpp
    HeapVisual.cpp
    Label.cpp
    LinearHashTable.cpp
    Menu.cpp
    MenuBox.cpp
    MenuTab.cpp
    MinHeap.cpp
    Move.cpp
    NotationBox.cpp
    OptionBox.cpp
    ProgressBar.cpp
    SettingPackage.cpp
    ShortestPath.cpp
    SinglyLinkedList.cpp
    SlowMotion.cpp
    SunMode.cpp
    TabBox.cpp
    TextBox.cpp
    TextButton.cpp
    TextureButton.cpp
    ValueScroll.cpp
    Vertex.cpp
    VerticalOpen.cpp
    main.cpp
)

#Add Executables

#Target Link Libraries
#-ID:\raylib\include -LD:\raylib\lib -lraylib -lopengl32 -lgdi32 –lwinmm

# Only have to rerun the cmake when we change this file (CMakeLists.txt)
# cmake -G "Visual Studio 17 2022" -A x64 ..

# Ctrl + Shift + B --> F5 or Ctrl F5