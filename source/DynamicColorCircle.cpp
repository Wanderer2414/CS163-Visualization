#include "../include/DynamicColorCircle.h"
#include "../include/General.h"
#include <cmath>

DynamicColorCircle::DynamicColorCircle() {
    m_is_color_change = false;
    m_radius= 20,
    percent = 1,
    m_scale = 1,
    start_angle = 0,
    delta_angle = M_PI;
    start_color = end_color = WHITE;
    m_speed = 10;
}
bool DynamicColorCircle::IsColorChange() const {
    return m_is_color_change;
}
void DynamicColorCircle::setRadius(const float& radius) {
    m_radius = radius;
}
void DynamicColorCircle::setSpeed(const float& speed) {
    if (speed) m_speed = 10/speed;
}
void DynamicColorCircle::handle() {
    if (percent < 1 || end_color != start_color) {
        float delta = 1 - percent;
        if (delta > 0.1 && m_speed>1) percent += delta/m_scale;
        else {
            percent = 1;
            end_color = start_color;
            m_is_color_change = true;
        } 
        delta_angle = percent*M_PI;
    } 
    else m_is_color_change = false;
}
void DynamicColorCircle::setColor(const Color& color) {
    end_color = start_color = color;
}
void DynamicColorCircle::draw() {
    DrawCircleSector(getCenter(), m_radius, to_degree(start_angle-delta_angle), to_degree(start_angle+delta_angle), 30, start_color);
    DrawCircleSector(getCenter(), m_radius,to_degree(start_angle+delta_angle), to_degree(start_angle-delta_angle+2*M_PI), 30, end_color);
}
void DynamicColorCircle::start(const float& angle, const Color& start, const Color& end) {
    start_angle = angle;
    delta_angle = 0;
    m_scale = 10;
    percent = 0;
    start_color = start;
    end_color = end;
}
Color DynamicColorCircle::getColor() const {
    return start_color;
}
Vector2 DynamicColorCircle::getCenter() const {
    return {0,0};
}