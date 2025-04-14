#include "../include/RaylibExtra.h"
#include <raylib.h>

void DrawText(TextSetting* setting, const Vector2& position, const string& text) {
    DrawTextEx(setting->font, text.c_str(), position, setting->font_size, setting->spacing, setting->color);
}
void DrawText(TextSetting* setting, const Vector2& position, const string& text, const float& size) {
    DrawTextEx(setting->font, text.c_str(), position, size, setting->spacing, setting->color);
}
void DrawSmallText(TextSetting* setting, const Vector2& position, const string& str) {
    DrawTextEx(setting->font, str.c_str(), position, setting->small_font_size, setting->spacing, setting->color);
}

void DrawRectangleRounded(ButtonSetting* setting, const Vector2& position, const Vector2& size, const Color& tint) {
    DrawRectangleRounded(REC(position, size), setting->roundness, setting->segment, tint);
}
void DrawRectangleRoundedNormal(ButtonSetting* setting, const Vector2& position, const Vector2& size) {
    DrawRectangleRounded(REC(position, size), setting->roundness, setting->segment, setting->normal_color);
}

void DrawRectangleRoundedHover(ButtonSetting* setting, const Vector2& position, const Vector2& size) {
    DrawRectangleRounded(REC(position, size), setting->roundness, setting->segment, setting->hover_color);
}
void DrawRectangleRoundedClick(ButtonSetting* setting, const Vector2& position, const Vector2& size) {
    DrawRectangleRounded(REC(position, size), setting->roundness, setting->segment, setting->click_color);
}
Vector2 MeasureText(TextSetting* setting, const string& text) {
    return MeasureTextEx(setting->font, text.c_str(), setting->font_size, setting->spacing);
}
Vector2 MeasureSmallText(TextSetting* setting, const string& text) {
    return MeasureTextEx(setting->font, text.c_str(), setting->small_font_size, setting->spacing);
}