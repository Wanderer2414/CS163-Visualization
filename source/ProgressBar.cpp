#include "../include/ProgressBar.h"

ProgressBar::ProgressBar() {
    m_progress = 0;
    m_thick = 1.0f,
        m_radius = 5;
    m_is_focus = false;
    m_is_changed = false;
    m_split_count = 0;
    m_split_thick = 1.5f;
    m_split_size = 10;
    setSize(200, 30);
    uncomplete_color = { 100, 100, 100, 200 };
    complete_color = { 255, 255, 255, 255 };
    cursor_color = BLUE;
}
bool ProgressBar::isFocus() {
    return m_is_focus;
}
bool ProgressBar::isChanged() {
    return m_is_changed;
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
    if (m_split_count) {
        float range_width = m_size.x / m_split_count,
            start_y = m_position.y + m_size.y / 2 - m_split_size / 2,
            end_y = m_position.y + m_size.y / 2 + m_split_size / 2;
        for (int i = 0; i <= m_split_count; i++) {
            float x = m_position.x + range_width * i;
            if (x <= m_point.x)
                DrawLineEx({ x, start_y }, { x, end_y }, m_thick, complete_color);
            else DrawLineEx({ x, start_y }, { x, end_y }, m_thick, uncomplete_color);
        }
    }
}
void ProgressBar::setSize(const float& x, const float& y) {
    Controller::setSize(x, y);
    m_point.y = getPosition().y + y / 2;
}
void ProgressBar::setPosition(const float& x, const float& y) {
    Controller::setPosition(x, y);
    m_point.y = getPosition().y + y / 2;
}
void ProgressBar::setSplitCount(const int& count) {
    m_split_count = count;
}
void ProgressBar::setSplitThick(const float& thick) {
    m_thick = thick;
}
void ProgressBar::setSplitSize(const float& size) {
    m_split_size = size;
}
void ProgressBar::handle() {
    bool m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    if (m_is_hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) m_is_focus = true;
    else if (m_is_focus && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) m_is_focus = false;
    if (m_is_focus && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        m_is_changed = true;
        setProgresss((GetMousePosition().x - getPosition().x) / getSize().x);
    }
    else m_is_changed = false;
}
void ProgressBar::setProgresss(const float& progress) {
    if (progress > 1) setProgresss(1);
    else if (progress < 0) setProgresss(0);
    else {
        m_progress = progress;
        m_point.x = getPosition().x + getSize().x * progress;
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