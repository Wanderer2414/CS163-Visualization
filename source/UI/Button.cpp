#include "Button.h"

Button::Button() {
    before_press = 6;
    m_is_pressed = m_is_hovered = 0;
}
bool Button::isHovered() const {
    return m_is_hovered;
}
bool Button::isPressed() const {
    return m_is_pressed;
}
void Button::draw() {
    
}
void Button::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    if (m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) before_press = 0;
    if (before_press < 3) before_press++;
    else if (before_press == 3) {
        m_is_pressed = true;
        before_press++;
    }
    else m_is_pressed = false;
}
Button::~Button() {

}