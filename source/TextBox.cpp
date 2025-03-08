#include "../include/TextBox.h"
#include <cmath>
#include <cstdio>
#include <string>
#include "../raylib/raylib.h"

TextBox::TextBox() {
    
}
std::string* TextBox::getString() {
    return &m_text;
}
bool TextBox::isFocus() {
    return m_is_focus;
}
bool TextBox::isEnter() {
    return m_is_enter;
}
void TextBox::init() {
    m_font = GetFontDefault();
    m_size = {100, 50};
    clear();
}
void TextBox::update_text() {
    m_text_position = m_position;
    Vector2 text_size = MeasureTextEx(m_font, m_text.substr(0, m_cursor_index).c_str(), m_font_size, m_spacing);
    if (!text_size.y) text_size.y = m_font_size;
    m_text_position.x += 5;
    m_text_position.y += m_size.y/2 - text_size.y/2;
    m_cursor_pos = {m_text_position.x + text_size.x, m_text_position.y, 2, text_size.y};
    if (m_cursor_pos.x>m_position.x+m_size.x-10 && m_text.size()) {
        float delta = m_cursor_pos.x - m_position.x - m_size.x + 10;
        m_text_position.x -= delta;
        m_cursor_pos.x -= delta;
    }
}
void TextBox::clear() {
    m_text.clear();
    m_cursor_index = 0;
    update_text();
}
void TextBox::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    m_is_enter = false;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        m_is_focus = m_is_hovered;
    }
    if (m_is_focus) {
        int c = GetCharPressed();
        if (c) {
            m_text.insert(m_text.begin() + m_cursor_index, c);
            m_cursor_index++;
            update_text();
        } 
        else if (IsKeyReleased(KEY_LEFT) && m_cursor_index) {
            m_cursor_index--;
            update_text();
        }
        else if (IsKeyReleased(KEY_RIGHT) && m_cursor_index<m_text.size()) {
            m_cursor_index++;
            update_text();
        }
        else if (IsKeyReleased(KEY_BACKSPACE) && m_cursor_index) {
            m_text.erase(m_text.begin() + m_cursor_index - 1);
            m_cursor_index--;
            update_text();
        }
        else if (IsKeyReleased(KEY_DELETE) && m_cursor_index<m_text.size()) {
            m_text.erase(m_text.begin() + m_cursor_index);
            update_text();
        }
        else if (IsKeyReleased(KEY_ENTER)) m_is_enter = true;
    }
}
void TextBox::draw() {
    BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        TextButton::draw();
        if (m_is_focus && (int)(GetTime()*5)%2)
            DrawRectangle(m_cursor_pos.x, m_cursor_pos.y, m_cursor_pos.width, m_cursor_pos.height, BLACK);
    EndScissorMode();
}
TextBox::~TextBox() {

}