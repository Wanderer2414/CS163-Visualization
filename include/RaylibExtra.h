#ifndef RAYLIB_EXTRA_H
#define RAYLIB_EXTRA_H

#include "Global.h"
#include "General.h"
#include "SettingPackage.h"

#define REC(a, b) {a.x, a.y, b.x, b.y}

bool CheckCollisionArc(const Vector2& point, const Vector2& start, const Vector2& end, const float& angular, const float& width);

void DrawText(TextSetting* setting, const Vector2& position, const string& text);
void DrawText(TextSetting* setting, const Vector2& position, const string& text, const float& size);
void DrawSmallText(TextSetting* setting, const Vector2& position, const string& str);

void DrawRectangleRounded(ButtonSetting* setting, const Vector2& position, const Vector2& size, const Color& tint);
void DrawRectangleRoundedNormal(ButtonSetting* setting, const Vector2& position, const Vector2& size);
void DrawRectangleRoundedHover(ButtonSetting* setting, const Vector2& position, const Vector2& size);
void DrawRectangleRoundedClick(ButtonSetting* setting, const Vector2& position, const Vector2& size);


void DrawArc(const Vector2& start, const Vector2& end, const float& angular, const Color& color);
void DrawText(TextSetting* text_setting, const Vector2& start, const Vector2& end, const float& angular, const string& text, const Color& color);

Vector2 PointOnArc(const Vector2& start, const Vector2& end, const float& angular, const float& current_angular);

Vector2 MeasureText(TextSetting* setting, const string& text);
Vector2 MeasureSmallText(TextSetting* setting, const string& text);

#endif