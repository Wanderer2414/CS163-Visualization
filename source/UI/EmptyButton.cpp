#include "EmptyButton.h"

EmptyButton::EmptyButton() {
    before_press = 6;
    m_is_pressed = m_is_hovered = 0;
    segment = 30;
    roundness = 0.1;
    normal_color = hover_color = click_color = WHITE;
}
bool EmptyButton::isHovered() const {
    return m_is_hovered;
}
bool EmptyButton::isPressed() const {
    return m_is_pressed;
}

void EmptyButton::draw() {
    if (before_press < 3)
        DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, roundness, segment, click_color);
    else if (m_is_hovered)    
        DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, roundness,segment, hover_color);
    else
        DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, roundness,segment, normal_color);
}
void EmptyButton::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    if (m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) before_press = 0;
    if (before_press < 3) before_press++;
    else if (before_press == 3) {
        m_is_pressed = true;
        before_press++;
    }
    else m_is_pressed = false;
}
EmptyButton::~EmptyButton() {

}