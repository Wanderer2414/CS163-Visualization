#include "../include/Bubble.h"

Bubble::Bubble() {
    m_color_a = m_color_b = WHITE;
    m_color_a.a /= 10;
    m_radius = 50;
}
float Bubble::getRadius() const {
    return m_radius;
}
void Bubble::handle() {

}
void Bubble::draw() {
    DrawCircleGradient(m_position.x, m_position.y, m_radius, m_color_a, m_color_b);
}
    
void Bubble::setRadius(const float& radius) {
    m_radius = radius;
}
void Bubble::setColor(const Color& color) {
    m_color_a = m_color_b = color;
    m_color_a.a/=10;
}
Bubble::~Bubble() {

}