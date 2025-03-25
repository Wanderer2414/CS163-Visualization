#include "../include/DynamicColorCircle.h"
#include "../include/General.h"

DynamicColorCircle::DynamicColorCircle() {
    m_is_color_change = false;
    m_radius= 20,
    percent = 1,
    m_scale = 1,
    start_angle = 0,
    delta_angle = 3.14;
    start_color = end_color = WHITE;
}
bool DynamicColorCircle::IsColorChange() const {
    return m_is_color_change;
}
void DynamicColorCircle::setRadius(const float& radius) {
    m_radius = radius;
}
void DynamicColorCircle::handle() {
    if (percent < 1) {
        float delta = 1 - percent;
        if (delta > 0.1) percent += delta/m_scale;
        else {
            percent += delta;
            m_is_color_change = true;
        } 
        delta_angle = percent*3.14;
    } 
    else m_is_color_change = false;
}
void DynamicColorCircle::draw() {
    DrawCircleSector(getCenter(), m_radius, to_degree(start_angle-delta_angle), to_degree(start_angle+delta_angle), 30, start_color);
    DrawCircleSector(getCenter(), m_radius,to_degree(start_angle+delta_angle), to_degree(start_angle-delta_angle+2*3.14), 30, end_color);
}
void DynamicColorCircle::start(const float& angle, const Color& start, const Color& end, const float& speed) {
    start_angle = angle;
    delta_angle = 0;
    m_scale = speed*5;
    percent = 0;
    start_color = start;
    end_color = end;
}
Vector2 DynamicColorCircle::getCenter() const {
    return {0,0};
}