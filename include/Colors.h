#ifndef COLORS_H
#define COLORS_H
#include "../raylib/raylib.h"

struct ColorScheme {
    Color background;
    Color text;
    Color button;
    Color buttonHover;
    Color buttonPressed;
};

// Predefined color themes
extern ColorScheme LightTheme;
extern ColorScheme DarkTheme;
extern ColorScheme NeonTheme;

#endif 