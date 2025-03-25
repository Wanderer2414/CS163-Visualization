#ifndef SETTING_PACKAGE_H
#define SETTING_PACKAGE_H
#include "Global.h"
class ButtonSetting {
public:
    float   roundness;
    int     segment;
    Color   click_color ,     
            hover_color ,
            normal_color;
};
class TextSetting {
public:
    Font    font;
    float   font_size,
            spacing;
    Color   color;
};
class FormSetting: public ButtonSetting, public TextSetting {
public:
    Color   middle_color;
    Color   background_color;
};

extern FormSetting LightTheme;
extern FormSetting DarkTheme;
extern FormSetting NeonTheme;
#endif