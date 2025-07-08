#include "RaylibExtra.h"

bool CheckCollisionArc(const Vector2& point, const Vector2& start, const Vector2& end, const float& angular, const float& width) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    Vector2 u = Vector2({-delta.y, delta.x})/abs(delta);
    float dis = abs(delta);
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;
    float arc = arctan(point-center);
    return (abs(center-point)>=radius-width/2 && abs(center-point)<=radius+width/2) &&
            ((arc-arctan(start-center))*(arc-arctan(end-center)) < 0);
}

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


void DrawArc(const Vector2& start, const Vector2& end, const float& angular, const Color& color) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    Vector2 u = Vector2({-delta.y, delta.x})/abs(delta);
    float dis = abs(delta);
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;
    Vector2 middle_arc = center - u*radius;
    Vector2 arrow_start = middle_arc - delta/dis*7;
    Vector2 arrow_end = middle_arc + delta/dis*7;

    DrawLineEx(arrow_start-u*10, arrow_end, 3.0f, color);
    DrawLineEx(arrow_start+u*10, arrow_end, 3.0f, color);

    float start_angular = arctan(start-center);
    float end_angular = arctan(end-center);
    if (start_angular>end_angular) {
        start_angular -= 2*M_PI;
    }
    float delta_angular = (end_angular-start_angular)/30;
    Vector2 start_point = center;
    start_point.x += radius*cos(start_angular);
    start_point.y +=  radius*sin(start_angular);
    for (float i = start_angular+delta_angular; i<=end_angular; i+=delta_angular) {
        Vector2 end_point = center;
        end_point.x += radius*cos(i);
        end_point.y +=  radius*sin(i);
        DrawLineEx(start_point, end_point, 3.0f, color);
        start_point = end_point;
    }
}
void DrawText(TextSetting* text_setting, const Vector2& start, const Vector2& end, const float& angular, const string& text, const Color& color) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    float dis = abs(delta);
    Vector2 u = Vector2({-delta.y, delta.x})/dis;
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;
    Vector2 sz = MeasureTextEx(text_setting->font, text.c_str(), text_setting->font_size, text_setting->spacing);
    Vector2 center_text = center - u*(radius+sz.y/2 + 15);
    float rotate = to_degree(arctan(delta));
    DrawTextPro(text_setting->font, text.c_str(), center_text, sz/2, rotate, text_setting->font_size/1.2, text_setting->spacing, color);
}
Vector2 PointOnArc(const Vector2& start, const Vector2& end, const float& angular, const float& current_angular) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    Vector2 u = Vector2({-delta.y, delta.x})/abs(delta);
    float dis = abs(delta);
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;

    float start_angular = arctan(start-center);
    float end_angular = arctan(end-center);
    if (start_angular>end_angular) {
        start_angular -= 2*M_PI;
    }
    Vector2 ans = center;
    ans.x += radius*cos(start_angular+current_angular);
    ans.y +=  radius*sin(start_angular+current_angular);
    return ans;
}