#include "../include/TextBox.h"
#include "../include/General.h"
#include <cmath>
#include <cstdio>
#include "../raylib/raylib.h"

TextBox::TextBox() {
    m_size = { 100, 50 };
    m_position = {10, 10};
    text_setting = 0;
    button_setting = 0;
}
bool TextBox::isFocus() {
    return m_is_focus;
}
bool TextBox::isEnter() {
    return m_is_enter;
}
void TextBox::init() {
    Label::init();
    m_is_enter = m_is_focus = false;
    m_is_chosen = false;
    clear();
}
void TextBox::setFocus(const bool& focus) {
    m_is_focus = focus;
}
void TextBox::update_cursor() {
    if (!m_is_chosen) {
        m_fill_col = m_cursor_col;
        m_fill_row = m_cursor_row;
    }
    auto vec = getCharPosition(m_cursor_row,m_cursor_col);
    m_cursor_pos = {vec.x, vec.y, 2, text_setting->font_size};
    m_choice.clear();
    Vector2 start, end;
    if (m_fill_row > m_cursor_row || (m_fill_row == m_cursor_row && m_cursor_col < m_fill_col)) {
        start = {(float)m_cursor_col, (float)m_cursor_row};
        end = {(float)m_fill_col, (float)m_fill_row};
    } else {
        end = {(float)m_cursor_col, (float)m_cursor_row};
        start = {(float)m_fill_col, (float)m_fill_row};
    }

    Vector2 pos = getCharPosition(start.y, start.x),
            size = getCharPosition(start.y, (start.y==end.y)?end.x:getLineSize(start.y));
    m_choice.push_back({pos.x, pos.y, size.x-pos.x, text_setting->font_size});
    for (int i = start.y+1; i<end.y; i++) {
        pos = getCharPosition(i, 0);
        size = getCharPosition(i, getLineSize(i));
        m_choice.push_back({pos.x, pos.y, size.x-pos.x, text_setting->font_size});
    }

    if (start.y != end.y) {
        pos = getCharPosition(end.y, 0);
        size = getCharPosition(end.y, end.x);
        m_choice.push_back({pos.x, pos.y, size.x-pos.x, text_setting->font_size});
    }

    if (m_cursor_pos.x > m_position.x + m_size.x - 10) {
        float delta = m_cursor_pos.x - m_position.x - m_size.x + 10;
        for (int i = 0; i<m_text_position.size(); i++) {
            m_text_position[i].x -= delta;
        }
        m_cursor_pos.x-=delta;
    } else  if (m_cursor_pos.x<m_position.x) {
        for (int i = 0; i<m_text_position.size(); i++) {
            m_text_position[i].x -= m_cursor_pos.x-m_position.x;
        }
        m_cursor_pos.x = m_position.x;
    }

    if (m_cursor_pos.y + text_setting->font_size > m_position.y + m_size.y - 10) {
        float delta = m_cursor_pos.y + text_setting->font_size - m_position.y - m_size.y + 10;
        for (int i = 0; i<m_text_position.size(); i++) {
            m_text_position[i].y -= delta;
        }
        m_cursor_pos.y-=delta;
    } else if (m_cursor_pos.y < m_position.y) {
        for (int i = 0; i<m_text_position.size(); i++) {
            m_text_position[i].y -= m_position.y-m_cursor_pos.y;
        }
        m_cursor_pos.y = m_position.y;
    }
}
void TextBox::clear() {
    Label::clear();
    m_cursor_col = m_cursor_row = 0;
}
void TextBox::handle() {
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        m_is_focus = m_is_hovered;
        m_is_enter = false;
        if (m_is_focus) {
            m_cursor_row = 0;
            m_cursor_col = 0;
            update_text();
            while (m_cursor_row+1<m_text_position.size() && m_text_position[m_cursor_row+1].y<GetMousePosition().y) 
                m_cursor_row++;
            Vector2 tmp = getCharPosition(m_cursor_row, m_cursor_col);;
            float old_dis = abs(GetMousePosition() - tmp);
            while (m_cursor_col < m_text[m_cursor_row].size() && tmp.x < GetMousePosition().x) {
                m_cursor_col++;
                old_dis = abs(GetMousePosition() - tmp);
                tmp = getCharPosition(m_cursor_row, m_cursor_col);
            }
            if (old_dis<abs(tmp-GetMousePosition())) m_cursor_col--;

            update_cursor();
        }
    }
    if (m_is_focus) {
        int c = GetCharPressed();
        if (c) {
            if (m_cursor_col>getLineSize(m_cursor_row)) m_cursor_col = getLineSize(m_cursor_row);
            if (m_is_chosen) {
                Vector2 start, end;
                if (m_fill_row > m_cursor_row || (m_fill_row == m_cursor_row && m_cursor_col < m_fill_col)) {
                    start = {(float)m_cursor_col, (float)m_cursor_row};
                    end = {(float)m_fill_col, (float)m_fill_row};
                } else {
                    end = {(float)m_cursor_col, (float)m_cursor_row};
                    start = {(float)m_fill_col, (float)m_fill_row};
                }
                m_fill_col = m_cursor_col = start.x;
                m_fill_row = m_cursor_row = start.y;
                erase(start,end);
                m_is_chosen = false;
            }
            insert(m_cursor_row, m_cursor_col, c);
            m_cursor_col++;
            update_cursor();
        }
        else if (IsKeyPressed(KEY_A) && IsKeyDown(KEY_LEFT_CONTROL)) {
            m_is_chosen = true;
            m_fill_col = m_fill_row = 0;
            m_cursor_row = getLineCount()-1;
            m_cursor_col = getLineSize(m_cursor_row);
            update_cursor();
        }
        else if (IsKeyPressed(KEY_C) && IsKeyDown(KEY_LEFT_CONTROL)) {
            Vector2 start, end;
            if (m_fill_row > m_cursor_row || (m_fill_row == m_cursor_row && m_cursor_col < m_fill_col)) {
                start = {(float)m_cursor_col, (float)m_cursor_row};
                end = {(float)m_fill_col, (float)m_fill_row};
            } else {
                end = {(float)m_cursor_col, (float)m_cursor_row};
                start = {(float)m_fill_col, (float)m_fill_row};
            }
            SetClipboardText(getText(start, end).c_str());
        }
        else if (IsKeyPressed(KEY_V) && IsKeyDown(KEY_LEFT_CONTROL)) {
            insert(m_cursor_row, m_cursor_col, GetClipboardText());
            update_cursor();
        }
        else if (IsKeyPressed(KEY_HOME)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            m_cursor_col = 0;
            update_cursor();
        }
        else if (IsKeyPressed(KEY_END)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            m_cursor_col = getLineSize(m_cursor_row);
            update_cursor();
        }
        else if (IsKeyPressed(KEY_PAGE_UP)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            m_cursor_row = 0;
            update_cursor();
        }
        else if (IsKeyPressed(KEY_PAGE_DOWN)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            m_cursor_row = getLineCount()-1;
            update_cursor();
        }
        else if (IsKeyPressed(KEY_LEFT)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                if (m_cursor_col && m_text[m_cursor_row][m_cursor_col-1]!=' ')
                    while (m_cursor_col && m_text[m_cursor_row][m_cursor_col-1]!=' ') m_cursor_col--;
                else while (m_cursor_col && m_text[m_cursor_row][m_cursor_col-1]==' ') m_cursor_col--;
            } else if (m_cursor_col) {
                if (m_cursor_col<getLineSize(m_cursor_row)) m_cursor_col--;
                else m_cursor_col = getLineSize(m_cursor_row)-1;
            }
            else if (m_cursor_row) {
                m_cursor_row--;
                m_cursor_col=getLineSize(m_cursor_row);
            }
            update_cursor();
        }
        else if (IsKeyPressed(KEY_RIGHT)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                if (m_cursor_col<getLineSize(m_cursor_row) && m_text[m_cursor_row][m_cursor_col]!=' ')
                    while (m_cursor_col<getLineSize(m_cursor_row) && m_text[m_cursor_row][m_cursor_col]!=' ') m_cursor_col++;
                else while (m_cursor_col<getLineSize(m_cursor_row) && m_text[m_cursor_row][m_cursor_col]==' ') m_cursor_col++;
            }
            else if (m_cursor_col < getLineSize(m_cursor_row)) {
                m_cursor_col++;
            }
            else if (m_cursor_row<getLineCount()-1) {
                m_cursor_row++;
                m_cursor_col = 0;
            }
            update_cursor();
        }
        else if (IsKeyPressed(KEY_UP) && (m_cursor_row)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            m_cursor_row--;
            update_cursor();
        }
        else if (IsKeyPressed(KEY_DOWN) && (m_cursor_row < getLineCount()-1)) {
            m_is_chosen = IsKeyDown(KEY_LEFT_SHIFT);
            m_cursor_row++;
            update_cursor();
        }
        else if (IsKeyPressed(KEY_BACKSPACE)) {
            if (m_cursor_col>getLineSize(m_cursor_row)) m_cursor_col = getLineSize(m_cursor_row);
            if (!m_is_chosen) {
                if (m_cursor_col) {
                    if (m_cursor_col) {
                        m_cursor_col--;
                    }
                    erase(m_cursor_row, m_cursor_col);
                }
                else if (m_cursor_row) {
                    m_cursor_row--;
                    m_cursor_col = getLineSize(m_cursor_row);
                    erase(m_cursor_row, m_cursor_col);
                }
                update_cursor();
            } else {
                Vector2 start, end;
                if (m_fill_row > m_cursor_row || (m_fill_row == m_cursor_row && m_cursor_col < m_fill_col)) {
                    start = {(float)m_cursor_col, (float)m_cursor_row};
                    end = {(float)m_fill_col, (float)m_fill_row};
                } else {
                    end = {(float)m_cursor_col, (float)m_cursor_row};
                    start = {(float)m_fill_col, (float)m_fill_row};
                }
                m_fill_col = m_cursor_col = start.x;
                m_fill_row = m_cursor_row = start.y;
                erase(start,end);
                m_is_chosen = false;
                update_cursor();
            }
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            if (m_cursor_col>getLineSize(m_cursor_row)) m_cursor_col = getLineSize(m_cursor_row);
            if (!m_is_chosen) {
                erase(m_cursor_row, m_cursor_col);
                update_cursor();
            } else {
                Vector2 start, end;
                if (m_fill_row > m_cursor_row || (m_fill_row == m_cursor_row && m_cursor_col < m_fill_col)) {
                    start = {(float)m_cursor_col, (float)m_cursor_row};
                    end = {(float)m_fill_col, (float)m_fill_row};
                } else {
                    end = {(float)m_cursor_col, (float)m_cursor_row};
                    start = {(float)m_fill_col, (float)m_fill_row};
                }
                m_fill_col = m_cursor_col = start.x;
                m_fill_row = m_cursor_row = start.y;
                erase(start,end);
                m_is_chosen = false;
                update_cursor();
            }
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            if (IsKeyDown(KEY_LEFT_ALT)) {
                insert(m_cursor_row, m_cursor_col, '\n');
                m_cursor_row++;
                m_cursor_col = 0;
                update_cursor();
            } else {
                m_is_enter = true;
                m_is_focus = false;
            }
        }
    }
}

void TextBox::draw() {
    DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, button_setting->roundness, button_setting->segment, button_setting->normal_color);
    if (text_setting) {
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        Label::draw();
        if (m_is_focus && (int)(GetTime() * 5) % 2)
            DrawRectangle(m_cursor_pos.x, m_cursor_pos.y, m_cursor_pos.width, m_cursor_pos.height, BLACK);
        if (m_choice.size())
            for (auto& i:m_choice) DrawRectangleLinesEx(i, 1.0f, BLACK);
        EndScissorMode();
    }
}
TextBox::~TextBox() {

}