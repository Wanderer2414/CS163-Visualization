#include "../include/MenuTab.h"

ButtonTab::ButtonTab() {
    button_setting = 0;
    before_press = 6;
    m_is_pressed = m_is_hovered = m_is_clicked = 0;
}
bool ButtonTab::isHovered() const {
    return m_is_hovered;
}
bool ButtonTab::isPressed() const {
    return m_is_pressed;
}
void ButtonTab::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    if (m_is_hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) before_press = 0;
    if (before_press < 3) before_press++;
    else if (before_press == 3) {
        m_is_pressed = true;
        before_press++;
    }
    else m_is_pressed = false;
}

ButtonTab::~ButtonTab()
{
}
