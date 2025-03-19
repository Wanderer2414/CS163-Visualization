#include "../include/TextButton.h"
#include "../include/General.h"
#include "../raylib/raylib.h"
#include <iostream>
TextButton::TextButton() {

}
void TextButton::init() {
    m_font = GetFontDefault(); 
    m_text = "";
    update_text();
}
void TextButton::setTexture(const std::string& normalPath, const std::string& hoverPath) {
    m_textureNormal = LoadTexture(normalPath.c_str());
    m_textureHovered = LoadTexture(hoverPath.c_str());
    m_useTexture = true;
}
void TextButton::draw() {
    if (m_useTexture) {
        // Use the hover texture if the button is hovered
        if (m_is_hovered) {
            DrawTexture(m_textureHovered, m_position.x, m_position.y, WHITE);
        }
        else {
            DrawTexture(m_textureNormal, m_position.x, m_position.y, WHITE);
        }
    }
    else {
        if (m_is_hovered)
            DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, m_roundness, m_segment, m_hover_color);
        else
            DrawRectangleRounded({ m_position.x, m_position.y, m_size.x, m_size.y }, m_roundness, m_segment, m_normal_color);
    }

    DrawTextEx(m_font, m_text.c_str(), m_text_position, m_font_size, m_spacing, m_text_color);
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
    m_text_position = m_position + m_size / 2;
    Vector2 text_size = MeasureTextEx(m_font, m_text.c_str(), m_font_size, m_spacing);
    m_text_position.x -= text_size.x / 2;
    m_text_position.y -= text_size.y / 2;
}
std::string* TextButton::getText() {
    return &m_text;
}
TextButton::~TextButton() {

}