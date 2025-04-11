#ifndef SETTINGPACKAGE_H
#define SETTINGPACKAGE_H

#include "Global.h"

class ButtonSetting {
public:
    float   roundness;
    int     segment;
    Color   click_color ,     
            hover_color ,
            normal_color;
    
    Color   hightlight_color1,
            hightlight_color2,
            hightlight_color3;
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
    Color   background_color,
            reverse_color,
            middle_reverse_color;

    const char* back_normal;
    const char* back_hovered;
    const char* home_normal;
    const char* home_hovered;
    const char* menu_avltree_normal;
    const char* menu_avltree_hovered;
    const char* menu_sll_normal;
    const char* menu_sll_hovered;
    const char* menu_graph_normal;
    const char* menu_graph_hovered;
    const char* menu_hash_normal;
    const char* menu_hash_hoverd;
    const char* PlayButton;
    const char* PlayButtonHovered;
    const char* PauseButton;
    const char* PauseButtonHovered;
    const char* Replay;
    const char* Replayhovered;
    const char* SkipNormal;
    const char* SkipHovered;
    const char* SkipBackNormal;
    const char* SkipBackHovered;
    const char* DoubleArrowRight;
    const char* DoubleArrowRight_Hovered;
    const char* DoubleArrowLeft;
    const char* DoubleArrowLeft_Hovered;
    const char* sun;
    const char* Rand;
    const char* TitleMenu;
    const char* match_cursor_icon;
    const char* match_filled_icon;
    const char* match_icon;
    const char* fill_icon;
    const char* fill_cursor_icon;
    const char* fill_filled_icon;
    const char* scissor_icon;
    const char* scissor_cursor_icon;
    const char* scissor_filled_icon;
};

extern FormSetting LightTheme;
extern FormSetting DarkTheme;
extern FormSetting NeonTheme;

#endif