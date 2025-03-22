#include "../include/SettingPackage.h"


FormSetting LightTheme = {
    {
        0.2f, 30, 
        {150, 150, 150, 255},  // Button Pressed (Even Darker Gray)
        {180, 180, 180, 255}, // Button Hover (Darker Gray)
        {200, 200, 200, 255} // Button (Gray)
    },
    {
    {}, 30, 2, 
    {20, 20, 20, 255},    // Text (Dark Gray)
    },
    {245, 245, 245, 255}, // Background (Light Gray)
};
FormSetting DarkTheme = {
    {
        0.2f, 30, 
        {100, 100, 100, 255},  // Button Pressed (Even Lighter Dark Gray)
        {80, 80, 80, 255},    // Button Hover (Lighter Dark Gray)
        {60, 60, 60, 255}    // Button (Dark Gray)
    },
    {
    {}, 30, 2, 
    {220, 220, 220, 255}, // Text (Light Gray)
    },
    {30, 30, 30, 255},    // Background (Dark Gray)
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
