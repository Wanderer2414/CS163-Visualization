#include "../include/Label.h"
#include "../include/General.h"
#include "../include/include.h"
Label::Label() {
}
int Label::getFontSize() const {
    return m_font_size;
}

void Label::init() {
    m_font = LoadFont(font_link);
    m_font_size = 30;
    m_align = Center | Middle;
    update_text();
}
void Label::draw() {
    DrawTextEx(m_font, m_text.c_str(), m_text_position, m_font_size, m_spacing, m_text_color);
}
void Label::handle() {

}
void Label::setText(const std::string& str) {
    m_text = str;
    update_text();
}
void Label::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    update_text();
}
void Label::setFont(const Font& font) {
    m_font = font;
    update_text();
}
void Label::setFontSize(const float& size) {
    m_font_size = size;
    update_text();
}
void Label::setTextColor(const Color& color) {
    m_text_color = color;
}
void Label::setSpacing(const float& spacing) {
    m_spacing = spacing;
    update_text();
}
void Label::update_text() {
    m_text_position = m_position + m_size/2;
    Vector2 text_size = MeasureTextEx(m_font, m_text.c_str(), m_font_size, m_spacing);
    if ((m_align & Left)  == Left) m_text_position.x = m_position.x;
    else if ((m_align & Right)   == Right) m_text_position.x = m_position.x + m_size.x - text_size.x;
    else m_text_position.x -= text_size.x/2;

    if ((m_align & Top) == Top) m_text_position.y = m_text_position.y;
    else if ((m_align & Bottom) == Bottom) m_text_position.y = m_text_position.y + m_size.y - text_size.y;
    else m_text_position.y -= text_size.y/2;
}
void Label::setAlignText(const int& align) {
    m_align = align;
    update_text();
}
std::string* Label::getText() {
    return &m_text;
}
Label::~Label() {

}