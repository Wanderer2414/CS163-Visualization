#include "../include/Mode.h"

// Default theme is LightTheme
Mode::Mode() {
    currentTheme = LightTheme;
}

// Set a new theme
void Mode::SetTheme(ColorScheme theme) {
    currentTheme = theme;
}

// Get the current theme
ColorScheme Mode::GetTheme() const {
    return currentTheme;
}
