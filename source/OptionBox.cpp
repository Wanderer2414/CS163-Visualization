#include "../include/OptionBox.h"
#include "../include/General.h"
OptionBox::OptionBox(TextSetting* t_setting, const int& index, int& option_choice):
        option(option_choice) {
    text_setting = t_setting;
    m_index = index;
    m_is_hovered = m_is_pressed = m_is_changed = false;
}
bool OptionBox::isHovered() const {
    return m_is_hovered;
}
bool OptionBox::isPressed() const {
    return m_is_pressed;
}
bool OptionBox::isChanged() const {
    return m_is_changed;
}
void OptionBox::draw() {
    Vector2 pos = m_position + Vector2({text_setting->font_size/2, m_size.y})/2;
    DrawCircleLines(pos.x,pos.y, text_setting->font_size/2 - 5, text_setting->color);
    if (m_index == option) 
        DrawCircle(pos.x, pos.y, text_setting->font_size/2 - 7, text_setting->color);
    DrawTextEx(text_setting->font, m_text.c_str(), m_position + Vector2({text_setting->font_size, 0}), text_setting->font_size, text_setting->spacing, text_setting->color);
}
void OptionBox::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    m_is_changed = false;
    if (m_is_pressed && option != m_index) {
        option = m_index;
        m_is_changed = true;
    }
}
void OptionBox::select(const int& index) {
    option = m_index;
}
void OptionBox::setText(const std::string& text) {
    m_text = text;
}