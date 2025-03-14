#include "../include/ProgressBar.h"

ProgressBar::ProgressBar() {
    m_progress = 0;
    m_thick = 1.0f,
    m_radius = 5;
    m_delta = 0.02;
    m_press = false;
    m_is_focus = false;
    setSize(200, 30);
    uncomplete_color = {100, 100, 100, 200};
    complete_color = {255, 255, 255, 255};
    cursor_color = BLUE;
}
float ProgressBar::getProgress() const {
    return m_progress;
}
void ProgressBar::draw() {
    Vector2 start = getPosition();
    start.y = m_point.y;
    DrawLineEx(start, m_point, m_thick, complete_color);
    start.x += getSize().x;
    DrawLineEx(m_point, start, m_thick, uncomplete_color);
    DrawCircleV(m_point, m_radius, cursor_color);
}
void ProgressBar::setSize(const float& x, const float& y) {
    Button::setSize(x, y);
    m_point.y = getPosition().y+y/2;
}
void ProgressBar::setDelta(const float& delta) {
    m_delta = delta;
}
void ProgressBar::setPosition(const float& x, const float& y) {
    Button::setPosition(x, y);
    m_point.y = getPosition().y + y/2;
}
void ProgressBar::handle() {
    Button::handle();
    if (m_is_hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) m_press = true;
    else if (m_press && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) m_press = false;
    if (m_press) setProgresss((GetMousePosition().x - getPosition().x)/getSize().x);
    
    if (m_is_pressed) m_is_focus = true;
    else if (m_is_focus && !m_is_hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) m_is_focus = false;

    if (m_is_focus) {
        if (IsKeyDown(KEY_LEFT)) setProgresss(m_progress - m_delta);
        else if (IsKeyDown(KEY_RIGHT)) setProgresss(m_progress + m_delta);
    }
}
void ProgressBar::setProgresss(const float& progress) {
    if (progress>1) setProgresss(1);
    else if (progress<0) setProgresss(0);
    else {
        m_progress = progress;
        m_point.x = getPosition().x + getSize().x*progress;
    }
}
void ProgressBar::setThick(const float& thick) {
    m_thick = thick;
}
void ProgressBar::setCursorSize(const float& radius) {
    m_radius = radius;
}

ProgressBar::~ProgressBar() {

}