#include "SettingPackage.h"
#include "IncludePath.h"

FormSetting LightTheme = {
    {
        0.1f, 30,
        {100, 160, 220, 255},  // Button Pressed 
        {130, 180, 230, 255},  // Button Hover 
        {160, 200, 250, 255},   // Button 

        {255, 0, 0, 255},
        {89, 254, 89, 255},
        {255, 255, 51, 255},
    },
    {
        {}, 30, 25, 15, 2,
        {20, 40, 80, 255},     // Text 
    },
    {120, 170, 220, 255},     // Border or other UI elements
    {240, 240, 240, 255},     // Background 
    { 4, 13, 18, 255},
    { 100, 100, 100, 255},

    source"/asset/images/dark/back-normal.png",
    source"/asset/images/dark/back-selected.png",

    source"/asset/images/dark/home-normal.png",
    source"/asset/images/dark/home-selected.png",

    source"/asset/images/dark/menu-avl-normal.png",
    source"/asset/images/menu-avl-selected.png",
    
    source"/asset/images/dark/menu-maxheap-normal.png",
    source"/asset/images/dark/menu-maxheap-selected.png",
    source"/asset/images/dark/menu-graph-normal.png",
    source"/asset/images/dark/menu-graph-selected.png",
    source"/asset/images/dark/menu-hash-normal.png",
    source"/asset/images/dark/menu-hash-selected.png",
    source"/asset/images/dark/play-normal.png",
    source"/asset/images/dark/play-selected.png",
    source"/asset/images/dark/pause-normal.png",
    source"/asset/images/dark/pause-selected.png",
    source"/asset/images/dark/replay-normal.png",
    source"/asset/images/dark/replay-selected.png",
    source"/asset/images/dark/skip_normal.png",
    source"/asset/images/dark/skip_hovered.png",
    source"/asset/images/dark/skipback.png",
    source"/asset/images/dark/skipback-hoverd.png",
    source"/asset/images/dark/double-arrow-right-normal.png",
    source"/asset/images/dark/double-arrow-right-hovered.png",
    source"/asset/images/dark/double-arrow-left.png",
    source"/asset/images/dark/double-arrow-left-hoverd.png",
    source"/asset/Icon/Light-hovered.png",
    source"/asset/images/Rand.png",
    source"/asset/images/Rand_hovered.png",
    source"/asset/images/dark/TitleMenu.png",
    source"/asset/Icon/pepicons-pencil--pen.png",
    source"/asset/Icon/pepicons-pencil--pen-circle-filled.png",
    source"/asset/Icon/pepicons-pencil--pen-circle.png",
    source"/asset/Icon/paint-pallet-circle.png",
    source"/asset/Icon/paint-pallet.png",
    source"/asset/Icon/paint-pallet-circle-filled.png",
    source"/asset/Icon/scissors-circle.png",
    source"/asset/Icon/scissors.png",
    source"/asset/Icon/scissors-circle-filled.png",
    source"/asset/images/dark/Graph0.png",
    source"/asset/images/dark/Graph1.png",
    source"/asset/images/dark/Graph2.png",
    source"/asset/images/dark/Graph3.png",
    source"/asset/images/dark/Graph2_hovered.png",
    source"/asset/images/dark/AVL0.png",
    source"/asset/images/dark/AVL1.png",
    source"/asset/images/dark/AVL2.png",
    source"/asset/images/dark/AVL3.png",
    source"/asset/images/dark/AVL3_hovered.png",
    source"/asset/images/dark/HT0.png",
    source"/asset/images/dark/HT1.png",
    source"/asset/images/dark/HT2.png",
    source"/asset/images/dark/HT3.png",
    source"/asset/images/dark/HT3_hovered.png",
    source"/asset/images/dark/SLL0.png",
    source"/asset/images/dark/SLL1.png",
    source"/asset/images/dark/SLL2.png",
    source"/asset/images/dark/SLL3.png",
    source"/asset/images/dark/SLL2_hovered.png"
};

FormSetting DarkTheme = {
    {
        0.1f, 30,
        {54, 63, 68, 255},    // Button Pressed (Deepest Green-Blue)
        {24, 61, 61, 255},   // Button Hover (Muted Dark Teal)
        {92, 131, 116, 255},  // Button (Soft Desaturated Green)

        {255, 0, 0, 255},
        {89, 254, 89, 255},
        {255, 255, 51, 255},
    },
    {
        {}, 30, 25, 15, 2,
        {220, 230, 225, 255}, // Text (Light Grayish Green for readability)
    },
    {147, 177, 166, 255},    // Border or other UI elements (Muted Greenish-Gray)
    {4, 13, 18, 255},         // Background (Deep Dark Green-Blue)
    {240, 240, 240, 255},
    {100, 100, 100, 255},

    source"/asset/images/back-normal.png",
    source"/asset/images/back-selected.png",
    source"/asset/images/home-normal.png",
    source"/asset/images/home-selected.png",

    source"/asset/images/menu-avl-normal.png",
    source"/asset/images/menu-avl-selected.png",

    source"/asset/images/menu-maxheap-normal.png",
    source"/asset/images/menu-maxheap-selected.png",

    source"/asset/images/menu-graph-normal.png",
    source"/asset/images/menu-graph-selected.png",

    source"/asset/images/menu-hash-normal.png",
    source"/asset/images/menu-hash-selected.png",

    source"/asset/images/play-normal.png",
    source"/asset/images/play-selected.png",

    source"/asset/images/pause-normal.png",
    source"/asset/images/pause-selected.png",
    source"/asset/images/replay-normal.png",
    source"/asset/images/replay-selected.png",
    source"/asset/images/skip_normal.png",
    source"/asset/images/skip_hovered.png",
    source"/asset/images/skipback.png",
    source"/asset/images/skipback-hoverd.png",
    source"/asset/images/double-arrow-right-normal.png",
    source"/asset/images/double-arrow-right-hovered.png",
    source"/asset/images/double-arrow-left.png",
    source"/asset/images/double-arrow-left-hoverd.png",
    source"/asset/Icon/Dark-hovered.png",
    source"/asset/images/Rand.png",
    source"/asset/images/Rand_hovered.png",
    source"/asset/images/TitleMenu.png",
    source"/asset/Icon/pepicons-pencil--pen.png",
    source"/asset/Icon/pepicons-pencil--pen-circle-filled.png",
    source"/asset/Icon/pepicons-pencil--pen-circle.png",
    source"/asset/Icon/paint-pallet-circle.png",
    source"/asset/Icon/paint-pallet.png",
    source"/asset/Icon/paint-pallet-circle-filled.png",
    source"/asset/Icon/scissors-circle.png",
    source"/asset/Icon/scissors.png",
    source"/asset/Icon/scissors-circle-filled.png",
    source"/asset/images/Graph0.png",
    source"/asset/images/Graph1.png",
    source"/asset/images/Graph2.png",
    source"/asset/images/Graph3.png",
    source"/asset/images/Graph2_hovered.png",
    source"/asset/images/AVL0.png",
    source"/asset/images/AVL1.png",
    source"/asset/images/AVL2.png",
    source"/asset/images/AVL3.png",
    source"/asset/images/AVL3_hovered.png",
    source"/asset/images/HT0.png",
    source"/asset/images/HT1.png",
    source"/asset/images/HT2.png",
    source"/asset/images/HT3.png",
    source"/asset/images/HT3_hovered.png",
    source"/asset/images/SLL0.png",
    source"/asset/images/SLL1.png",
    source"/asset/images/SLL2.png",
    source"/asset/images/SLL3.png",
    source"/asset/images/SLL2_hovered.png",
};
