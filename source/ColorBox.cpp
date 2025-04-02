#include "../include/ColorBox.h"

ColorBox::ColorBox(const Color& a, const Color& b) {
    percent = 0.5;
    m_pointer.width = 3;
    m_is_hovered = false;
    m_is_focus = false;
    m_start = a;
    m_end = b;
    m_pointer.y = -2;
}
float ColorBox::getPercent() const {
    return percent;
}
void ColorBox::draw() {
    DrawRectangleGradientH(m_position.x, m_position.y, m_size.x, m_size.y, m_start,m_end);
    Color color = m_start;
    color.r += (1-percent)*(m_end.r - m_start.r);
    color.g += (1-percent)*(m_end.g - m_start.g);
    color.b += (1-percent)*(m_end.b - m_start.b);
    DrawRectangleRec(m_pointer,color);
}
void ColorBox::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    if (m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) m_is_focus = true;
    else if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) m_is_focus = false;
    if (m_is_focus && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        m_pointer.x = GetMousePosition().x;
        if (m_pointer.x < m_position.x) m_pointer.x = m_position.x;
        if (m_pointer.x > m_position.x + m_size.x) m_pointer.x = m_position.x + m_size.x;
        percent = (m_pointer.x - m_position.x)/m_size.x;
    }
}

void ColorBox::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    m_pointer.x = m_position.x + m_size.x*percent;
    m_pointer.height = height + 4;
}
void ColorBox::setPosition(const float& x, const float& y)  {
    m_pointer.x = m_pointer.x - m_position.x + x;
    m_pointer.y = m_pointer.y - m_position.y + y;
    Controller::setPosition(x,y);
}
void ColorBox::setPercent(const float& p) {
    percent = p;
    m_pointer.x = m_position.x + m_size.x*p;
}
Color ColorBox::getColor() const {
    Color color = m_start;
    color.r += percent*(m_end.r - m_start.r);
    color.g += percent*(m_end.g - m_start.g);
    color.b += percent*(m_end.b - m_start.b);
    return color;
}