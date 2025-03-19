#include "../include/TextButton.h"
#include "../include/General.h"
#include "../raylib/raylib.h"

TextButton::TextButton() {
    button_setting = 0;
    text_setting = 0;
}
void TextButton::handle() {
    Button::handle();
    update_text();
}
void TextButton::init() {
    m_text = "";
}
void TextButton::setTexture(const std::string& normalPath, const std::string& hoverPath) {
    m_textureNormal = LoadTexture(normalPath.c_str());
    m_textureHovered = LoadTexture(hoverPath.c_str());
    m_useTexture = true;
}
void TextButton::draw() {
    if (button_setting) {
        if (m_useTexture) {
        // Use the hover texture if the button is hovered
            if (m_is_hovered) {
                DrawTexture(m_textureHovered, m_position.x, m_position.y, WHITE);
            }
            else {
                DrawTexture(m_textureNormal, m_position.x, m_position.y, WHITE);
            }
        } else {
            if (m_is_hovered)
                DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, button_setting->roundness, button_setting->segment, button_setting->hover_color);
            else
                DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, button_setting->roundness,button_setting->segment, button_setting->normal_color);
        }
    }
    if (text_setting)
        DrawTextEx(text_setting->font, m_text.c_str(), m_text_position, text_setting->font_size, text_setting->spacing,text_setting->color);
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
}
std::string* TextButton::getText() {
    return &m_text;
}
TextButton::~TextButton() {

}