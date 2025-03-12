#include "../include/TextButton.h"
#include "../include/General.h"
#include "../raylib/raylib.h"

TextButton::TextButton(Vector2* origin): Button(origin) {
    
}
void TextButton::init() {
    m_font = GetFontDefault();
    m_text = "Button";
    update_text();
}
void TextButton::draw() {
    Vector2 pos = m_position;
    if (m_origin) pos = pos + *m_origin;
    if (m_is_hovered)
        DrawRectangleRounded({pos.x, pos.y, m_size.x, m_size.y}, m_roundness, m_segment, m_hover_color);
    else 
        DrawRectangleRounded({pos.x, pos.y, m_size.x, m_size.y}, m_roundness, m_segment, m_normal_color);
    DrawTextEx(m_font, m_text.c_str(), (m_origin)?m_text_position+*m_origin:m_text_position, m_font_size, m_spacing, m_text_color);
}
void TextButton::setPosition(const float& x, const float& y) {
    Button::setPosition(x, y);
    update_text();
}
void TextButton::setSize(const float& width, const float& height) {
    Button::setSize(width, height);
    update_text();
}
void TextButton::setText(const std::string& str) {
    m_text = str;
    update_text();
}
void TextButton::setFont(const Font& font) {
    m_font = font;
    update_text();
}
void TextButton::setFontSize(const float& size) {
    m_font_size = size;
    update_text();
}
void TextButton::setTextColor(const Color& color) {
    m_text_color = color;
}
void TextButton::setSpacing(const float& spacing) {
    m_spacing = spacing;
    update_text();
}
void TextButton::update_text() {
    m_text_position = m_position + m_size/2;
    Vector2 text_size = MeasureTextEx(m_font, m_text.c_str(), m_font_size, m_spacing);
    m_text_position.x -= text_size.x/2;
    m_text_position.y -= text_size.y/2;
}
std::string* TextButton::getText() {
    return &m_text;
}
TextButton::~TextButton(){

}