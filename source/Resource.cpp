#include "../include/Resource.h"

void Theme::change() {
    if (!isDarkMode) {
        BACKGROUND = {245, 245, 245, 255};
        MENUBUTTON = {200, 200, 200, 255};
        HOVERBUTTON = {180, 180, 180, 255};
        BUTTON = {200, 200, 200, 255};
        HIGHLIGHTTEXT = {20, 20, 20, 255};
        HIGHLIGHTNODE = {55, 221, 149, 255};
        COLORNODE = {249, 208, 208, 255};
        COLORLINE = {182, 157, 157, 255};
        COLORPROGRESSBAR = {250, 254, 255, 255};
        WEIGHT = {6, 155, 91, 255};
    } else {
        BACKGROUND = {30, 30, 30, 255};
        MENUBUTTON = {60, 60, 60, 255};
        HOVERBUTTON = {80, 80, 80, 255};
        BUTTON = {204, 204, 204, 255};
        HIGHLIGHTTEXT = {220, 220, 220, 255};
        HIGHLIGHTNODE = {255, 245, 131, 255};
        COLORNODE = {182, 234, 255, 255};
        COLORLINE = {147, 177, 169, 255};
        COLORPROGRESSBAR = {96, 124, 135, 255};
        WEIGHT = {255, 255, 134, 255};
    }
    isDarkMode = !isDarkMode;
}

