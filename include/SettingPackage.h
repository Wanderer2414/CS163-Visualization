#ifndef SETTING_PACKAGE_H
#define SETTING_PACKAGE_H
#include "../raylib/raylib.h"
class ButtonSetting {
public:
    float   roundness   = 0.2;
    int     segment     = 30;
    Color   click_color     = WHITE,     
            hover_color     = WHITE,
            normal_color    = LIGHTGRAY;
};
class TextSetting {
public:
    Font    font;
    float   font_size   = 30,
            spacing     = 0.5;
    Color   color       = BLACK;
};
class FormSetting: public ButtonSetting, public TextSetting {
public:
    Color   background_color = {0, 0, 50, 255};
};

extern FormSetting LightTheme;
extern FormSetting DarkTheme;
extern FormSetting NeonTheme;
#endif