#include "../include/Console.h"
#include "../include/General.h"
#include <algorithm>
Console::Console() {
    clock.setDuration(0.01);
    m_line_choice = -1;
    max_width = max_height = 0;
}
int Console::getFillLine() const {
    return m_line_choice;
}
void Console::setText(const std::string& str) {
    update_text();
}
void Console::push_back(const std::string& log) {
    m_list.push_back(log);
    Vector2 text_size = MeasureTextEx(m_font, log.c_str(), m_font_size, m_spacing);
    max_width = std::max(max_width, text_size.x);
    max_height += text_size.y;
    update_text();
}
void Console::insert(const int& index, const std::string& log) {
    m_list.insert(m_list.begin() + index, log);
    Vector2 text_size = MeasureTextEx(m_font, log.c_str(), m_font_size, m_spacing);
    max_width = std::max(max_width, text_size.x);
    max_height += text_size.y;
    update_text();
}
void Console::pop_back() {
    m_list.pop_back();
    update_text();
}
void Console::clear() {
    m_list.clear();
    m_line_choice = -1;
    m_origin = {0,0};
}
void Console::setTextOrigin(const Vector2& origin) {
    m_origin = origin;
}
void Console::setSize(const float& width, const float& height) {
    TextButton::setSize(width, height);
    update_text();
}
void Console::update_text() {
    min_x = m_size.x - max_width;
    if (min_x>0) min_x = 0;
    min_y = m_size.y - max_height;
    if (min_y>0) min_y = 0;
}
void Console::handle() {
    TextButton::handle();
    if ((m_fixed.x || m_fixed.y) && clock.get()) {
        if (m_delta!=m_fixed) {
            m_delta = m_delta + (m_fixed-m_delta)/10;
            if (abs(m_delta-m_fixed)<1) {
                m_delta = m_fixed;
            }
        }
        else m_fixed = {0, 0};
    }
    if (m_is_hovered) {
        m_delta = m_delta + GetMouseWheelMoveV()*20;
    }
    if (m_delta.x>0) m_delta.x = m_fixed.x = 0;
    if (m_delta.y>0) m_delta.y = m_fixed.y = 0;
    if (m_delta.x<min_x) m_delta.x = m_fixed.x = min_x;
    if (m_delta.y<min_y) m_delta.y = m_fixed.y = min_y;
}
void Console::setFillLine(const int& line) {
    if (line>=0 && line<m_list.size()) {
        m_line_choice = line;
    }
    m_fixed = {0, -m_line_choice*m_font_size+m_size.y/2};
}
void Console::draw() {
    if (m_is_hovered)
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, m_roundness, m_segment, m_hover_color);
    else 
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, m_roundness, m_segment, m_normal_color);
    BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        if (m_line_choice>=0) 
            DrawRectangle(m_position.x, m_origin.y + m_position.y+m_font_size*m_line_choice+m_delta.y, m_size.x, m_font_size, m_color_line);
        for (int i = 0; i<m_list.size(); i++) 
            DrawTextEx(m_font, m_list[i].c_str(), m_origin+m_delta+m_position+Vector2({0, m_font_size*i}), m_font_size, m_spacing, m_text_color);
    EndScissorMode();
}