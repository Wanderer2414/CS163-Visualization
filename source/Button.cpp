#include "../include/Button.h"

Button::Button() {
    button_setting = 0;
}
bool Button::isHovered() const {
    return m_is_hovered;
}
bool Button::isPressed() const {
    return m_is_pressed;
}
void Button::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
Button::~Button() {
}