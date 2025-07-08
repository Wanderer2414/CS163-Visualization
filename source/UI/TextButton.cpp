#include "TextButton.h"
#include "General.h"

TextButton::TextButton(ButtonSetting* b_setting, TextSetting* t_setting) {
    button_setting = b_setting;
    text_setting = t_setting;
    m_text  = "";
    m_text_position = {0, 0};
}
void TextButton::handle() {
    Button::handle();
}
void TextButton::setSize(const float& width, const float& height) {
    Button::setSize(width, height);
    update_text();
}
void TextButton::setPosition(const float& x, const float& y) {
    Button::setPosition(x, y);
    update_text();
}
void TextButton::draw() {
    if (button_setting) {
        if (before_press < 3 || isFocus())
            DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, button_setting->roundness, button_setting->segment, button_setting->click_color);
        else if (m_is_hovered)    
            DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, button_setting->roundness, button_setting->segment, button_setting->hover_color);
        else
            DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, button_setting->roundness,button_setting->segment, button_setting->normal_color);
    }
    if (text_setting)
        DrawTextEx(text_setting->font, m_text.c_str(), m_text_position, text_setting->font_size, text_setting->spacing,text_setting->color);
    else cerr<<"[TEXT_SETTING DOES NOT EXIST IN TEXTBUTTON!]" << endl;
}
void TextButton::update() {
    update_text();
}
void TextButton::update_text() {
    if (text_setting) {
        m_text_position = m_position + m_size / 2;
        Vector2 text_size = MeasureTextEx(text_setting->font, m_text.c_str(),text_setting->font_size,text_setting->spacing);
        m_text_position.x -= text_size.x / 2;
        m_text_position.y -= text_size.y / 2;
    }
}
void TextButton::setText(const std::string& text) {
    m_text = text;
    update_text();
}
std::string TextButton::getText() const {
    return m_text;
}
TextButton::~TextButton() {

}