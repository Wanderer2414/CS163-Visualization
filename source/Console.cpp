#include "../include/Console.h"
#include "../include/General.h"
#include <algorithm>

Console::Console() {
    clock.setDuration(0.01);
    line_cursor = 0;
    current_add = 0;
    main_line_cursor = 0;
    max_width = max_height = 0;
    m_is_enable = true;
}
int Console::getFillLine() const {
    return line_cursor;
}
void Console::setText(const std::string& str) {
    update_text();
}
void Console::InsertNextMainCommand(const std::string& log) {
    if (m_is_enable) {
        if (line_cursor == m_list.size() || !temporary[line_cursor]) {
            m_list.insert(m_list.begin()+line_cursor, log);
            temporary.insert(temporary.begin() + line_cursor, false);
        } else {
            m_list.insert(m_list.begin() + current_add, log);
            temporary.insert(temporary.begin() + current_add, false);
        }
        update_tail();

        Vector2 text_size = MeasureTextEx(m_font, log.c_str(), m_font_size, m_spacing);
        max_width = std::max(max_width, text_size.x);
        max_height += text_size.y;

        update_text();
    }
}
void Console::InsertNextSubCommand(const std::string& log) {
    if (m_is_enable) {
        m_list.insert(m_list.begin() + current_add, log);
        temporary.insert(temporary.begin() + current_add, true);
        current_add++;

        Vector2 text_size = MeasureTextEx(m_font, log.c_str(), m_font_size, m_spacing);
        max_width = std::max(max_width, text_size.x);
        max_height += text_size.y;

        update_text();
    }
}
void Console::GotoCommandLine(const float& progress) {

}
void Console::PushBackMainCommand(const std::string& log) {
    if (m_is_enable) {
        m_list.push_back(log);
        temporary.push_back(false);

        Vector2 text_size = MeasureTextEx(m_font, log.c_str(), m_font_size, m_spacing);
        max_width = std::max(max_width, text_size.x);
        max_height += text_size.y;

        update_text();
    }
}
void Console::PushBackSubCommnad(const std::string& log) {
    if (m_is_enable) {
        m_list.push_back(log);
        temporary.push_back(true);

        Vector2 text_size = MeasureTextEx(m_font, log.c_str(), m_font_size, m_spacing);
        max_width = std::max(max_width, text_size.x);
        max_height += text_size.y;
        
        update_text();
    }
}
void Console::goUp() {
    if (!line_cursor) return;
    BeforeGoUp();
    update_tail();
}
void Console::goDown() {
    if (line_cursor==m_list.size()) return;
    BeforeGoDown();
    update_tail();
}
void Console::BeforeGoUp() {
    if (!line_cursor) return;
    line_cursor--;
    if (!temporary[line_cursor]) {
        while (line_cursor+1<m_list.size() && temporary[line_cursor+1]) {
            m_list.erase(m_list.begin()+line_cursor+1);
            temporary.erase(temporary.begin() + line_cursor+1);
        }
    }
}
void Console::BeforeGoDown() {
    if (line_cursor == m_list.size()) return;
    line_cursor++;
    if (line_cursor == temporary.size() || !temporary[line_cursor]) {
        while (line_cursor && temporary[line_cursor-1]) {
            m_list.erase(m_list.begin()+line_cursor-1);
            temporary.erase(temporary.begin() + line_cursor-1);
            line_cursor--;
        }
    }
}
void Console::update_tail() {
    if (line_cursor<temporary.size()) {
        current_add = line_cursor+1;
        while (current_add<temporary.size() && temporary[current_add]) current_add++;
    } else current_add = temporary.size();
}
void Console::clear() {
    if (m_is_enable) {
        m_list.clear();
        line_cursor = 0;
        m_origin = {0,0};
    }
}
void Console::setEnable(const bool& enbale) {
    m_is_enable = enbale;
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
void Console::draw() {
    if (m_is_hovered)
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, m_roundness, m_segment, m_hover_color);
    else 
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, m_roundness, m_segment, m_normal_color);
    BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        if (line_cursor>=0) 
            DrawRectangle(m_position.x, m_origin.y + m_position.y+m_font_size*line_cursor+m_delta.y, m_size.x, m_font_size, m_color_line);
        for (int i = 0; i<m_list.size(); i++) 
            DrawTextEx(m_font, m_list[i].c_str(), m_origin+m_delta+m_position+Vector2({0, m_font_size*i}), m_font_size, m_spacing, m_text_color);
    EndScissorMode();
}
Console::~Console() {

}