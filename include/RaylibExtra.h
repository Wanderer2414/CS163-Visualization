#ifndef RAYLIB_EXTRA_H
#define RAYLIB_EXTRA_H
#include "Global.h"
#include "SettingPackage.h"

#define REC(a, b) {a.x, a.y, b.x, b.y}

void DrawText(TextSetting* setting, const Vector2& position, const string& text);
void DrawText(TextSetting* setting, const Vector2& position, const string& text, const float& size);
void DrawSmallText(TextSetting* setting, const Vector2& position, const string& str);

void DrawRectangleRounded(ButtonSetting* setting, const Vector2& position, const Vector2& size, const Color& tint);
void DrawRectangleRoundedNormal(ButtonSetting* setting, const Vector2& position, const Vector2& size);
void DrawRectangleRoundedHover(ButtonSetting* setting, const Vector2& position, const Vector2& size);
void DrawRectangleRoundedClick(ButtonSetting* setting, const Vector2& position, const Vector2& size);


Vector2 MeasureText(TextSetting* setting, const string& text);
Vector2 MeasureSmallText(TextSetting* setting, const string& text);

#endif