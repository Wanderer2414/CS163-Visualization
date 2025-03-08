#include "../include/Button.h"

Button::Button() {

}
bool Button::isHovered() {
    return m_is_hovered;
}
bool Button::isPressed() {
    return m_is_pressed;
}
void Button::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
Button::~Button() {

}