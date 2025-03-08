#include "../include/Button.h"

Button::Button(Vector2* origin):Controller(origin) {

}
bool Button::isHovered() {
    return m_is_hovered;
}
bool Button::isPressed() {
    return m_is_pressed;
}
void Button::handle() {
    if (!m_origin)
        m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    else m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x+m_origin->x, m_position.y+m_origin->y, m_size.x, m_size.y});
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
Button::~Button() {

}