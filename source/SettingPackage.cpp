#include "../include/SettingPackage.h"


FormSetting LightTheme = {
    {
        0.2f, 30,
        {100, 160, 220, 255},  // Button Pressed 
        {130, 180, 230, 255},  // Button Hover 
        {160, 200, 250, 255}   // Button 
    },
    {
        {}, 30, 2,
        {20, 40, 80, 255},     // Text 
    },
    {120, 170, 220, 255},     // Border or other UI elements
    {240, 250, 255, 255},     // Background 
};

FormSetting DarkTheme = {
    {
        0.2f, 30,
        {4, 13, 18, 255},    // Button Pressed (Deepest Green-Blue)
        {24, 61, 61, 255},   // Button Hover (Muted Dark Teal)
        {92, 131, 116, 255}  // Button (Soft Desaturated Green)
    },
    {
        {}, 30, 2,
        {220, 230, 225, 255}, // Text (Light Grayish Green for readability)
    },
    {147, 177, 166, 255},    // Border or other UI elements (Muted Greenish-Gray)
    {4, 13, 18, 255}         // Background (Deep Dark Green-Blue)
};


FormSetting NeonTheme = {
    {
        0.2f, 30, 
        {255, 255, 0, 255},    // Button Pressed (Neon Yellow)
        {0, 255, 255, 255},   // Button Hover (Neon Cyan)
        {255, 0, 255, 255}   // Button (Neon Pink)
    },
    {
    {}, 30, 2, 
    {0, 255, 0, 255},     // Text (Neon Green)
    },
    {10, 10, 50, 255},    // Background (Dark Blue)
};
