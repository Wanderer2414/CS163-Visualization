#include "DynamicColorCircle.h"
#include "General.h"

DynamicColorCircle::DynamicColorCircle() {
    m_is_color_change = false;
    m_radius= 20,
    percent = 1,
    m_scale = 1,
    start_angle = 0,
    delta_angle = 3.14;
    start_color = end_color = WHITE;
    m_duration = 0.5;
    m_start_time = 0;
}
bool DynamicColorCircle::IsColorChange() const {
    return m_is_color_change;
}
void DynamicColorCircle::setRadius(const float& radius) {
    m_radius = radius;
}
void DynamicColorCircle::setDuration(const float& duration) {
    m_duration = duration;
}
void DynamicColorCircle::handle() {
    if (percent < 1 || end_color != start_color) {
        if (m_duration) percent = (GetTime()-m_start_time)/m_duration;
        else percent = 1;
        if (percent >= 1) {
            percent = 1;
            end_color = start_color;
            m_is_color_change = true;
        } 
        delta_angle = percent*3.14;
    } 
    else m_is_color_change = false;
}
void DynamicColorCircle::setColor(const Color& color) {
    end_color = start_color = color;
}
void DynamicColorCircle::draw() {
    DrawCircleSector(getCenter(), m_radius, to_degree(start_angle-delta_angle), to_degree(start_angle+delta_angle), 30, start_color);
    DrawCircleSector(getCenter(), m_radius,to_degree(start_angle+delta_angle), to_degree(start_angle-delta_angle+2*3.14), 30, end_color);
}
void DynamicColorCircle::complete() {
    percent = 1;
    end_color = start_color;
}
void DynamicColorCircle::start(const float& angle, const Color& start, const Color& end) {
    start_angle = angle;
    delta_angle = 0;
    m_scale = 10;
    percent = 0;
    m_start_time = GetTime();
    start_color = start;
    end_color = end;
}
Color DynamicColorCircle::getColor() const {
    return start_color;
}
Vector2 DynamicColorCircle::getCenter() const {
    return {0,0};
}