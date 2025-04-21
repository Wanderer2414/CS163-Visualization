#include "../include/LabelExtra.h"
#include "../include/General.h"
#include <cmath>

LabelEx::LabelEx(TextSetting* t_setting) {
    text_setting = t_setting;
    m_text = {""};
    m_text_position = {{0, 0}};
    align = {Top | Middle};
    margin = 5;
    update_text();
}
bool LabelEx::empty() const {
    return (m_text.size()<=1) && (m_text[0].empty());
}
void LabelEx::clear() {
    m_text.clear();
    m_text_position.clear();
    m_text = {""};
    m_text_position = {{0, 0}};
    align = {Left | Top};
    update_line(0);
}
void LabelEx::draw() {
    if (text_setting) {
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (int i = 0; i<m_text_position.size(); i++) {
            Vector2 offset = {0, 0};
            while (m_text_position[i].width > offset.x) {
                DrawTextEx(text_setting->font, m_text[i].c_str(), {m_text_position[i].x - offset.x, m_text_position[i].y + offset.y}, text_setting->font_size, text_setting->spacing,text_setting->color);
                offset.x += m_size.x;
                offset.y += text_setting->font_size;
            }
        }
        EndScissorMode();
    }
}
void LabelEx::handle() {

}
void LabelEx::erase(const Vector2& start, const Vector2& end) {
    if (end.y < start.y || (end.y==start.y && end.x<=start.x)) return;
    if (start.x<0 || start.y<0 || end.x < 0 || start.x < 0) return ;
    if (start.y >= m_text.size() || end.y >= m_text.size()) return ;
    if (start.x > m_text[start.y].size() || end.x > m_text[end.y].size()) return ;
    if (start.y == end.y) m_text[start.y].erase(m_text[start.y].begin() + start.x, m_text[start.y].begin()+end.x);
    else {
        m_text[start.y].erase(m_text[start.y].begin() + start.x,m_text[start.y].end());
        m_text[start.y] += m_text[end.y].substr(end.x);
        m_text.erase(m_text.begin() + start.y + 1, m_text.begin() + end.y + 1);
        m_text_position.erase(m_text_position.begin() + start.y + 1, m_text_position.begin() + end.y + 1);
    }
    update_text();
}
void LabelEx::erase(const int& row, const int& col) {
    if (row>=m_text.size() || row<0) return ;
    if (col>m_text[row].size() || col<0) return;
    if (col<m_text[row].size()) {
        m_text[row].erase(m_text[row].begin()+col);
        update_line(row);
    }
    else if (row<m_text.size()-1) {
        m_text[row]+=m_text[row+1];
        m_text.erase(m_text.begin() + row + 1);
        m_text_position.erase(m_text_position.begin() + row + 1);
        update_text();
    }
}
void LabelEx::insert(int& row, int& col, const string& str) {
    if (row>=m_text.size() || row<0) return ;
    if (col>m_text[row].size() || col<0) return;
    for (char c:str) {
        if (c!='\n') {
            m_text[row].insert(m_text[row].begin() + col, c);
            col++;
        }
        else {
            m_text.insert(m_text.begin() + row+ 1, m_text[row].substr(col, m_text[row].size()-col));
            m_text[row].erase(m_text[row].begin() + col, m_text[row].end());
            m_text_position.insert(m_text_position.begin() + row+1,{0, 0});
            row++;
            col=0;
        }
    }
    update_text();
}
void LabelEx::insert(const int& row, const int& col, const char& c) {
    if (row>=m_text.size() || row<0) return ;
    if (col>m_text[row].size() || col<0) return;
    if (c!='\n') {
        m_text[row].insert(m_text[row].begin() + col, c);
        update_line(row);
    }
    else {
        m_text.insert(m_text.begin() + row+ 1, m_text[row].substr(col, m_text[row].size()-col));
        m_text[row].erase(m_text[row].begin() + col, m_text[row].end());
        m_text_position.insert(m_text_position.begin() + row+1,{0, 0});
        update_text();
    }
}
void LabelEx::setText(const std::string& str) {
    m_text.clear();
    m_text.push_back("");
    m_text_position.clear();
    m_text_position.push_back({0, 0});
    align = {Left | Top};
    int i = 0;
    while(i<str.size()) {
        if (str[i]=='\n') {
            m_text_position.push_back({0, 0});
            m_text.push_back("");
            align.push_back(Left | Top);
        }
        else {
            if (str[i]=='\\' && i+6<str.size() && str.substr(i, 6) == "\\right") {
                align.back() = Right | Top;
                i+=5;
            }
            else if (str[i]=='\\' && i+5<str.size() && str.substr(i, 5) == "\\left") {
                align.back() = Left | Top;
                i+=4;
            }
            else if (str[i]=='\\' && i+7<str.size() && str.substr(i, 7) == "\\center") {
                align.back() = Middle | Top;
                i+=6;
            }
            else m_text.back().push_back(str[i]);
        }
        i++;
    }
    update_text();
}
void LabelEx::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    update_text();
}
void LabelEx::setPosition(const float& x, const float& y) {
    for (auto& i:m_text_position) {
        i.x = i.x - getPosition().x + x;
        i.y = i.y - getPosition().y + y;
    }
    Controller::setPosition(x, y);
}
void LabelEx::update_text() {
    if (!text_setting) return;
    update_line(0);
    m_text_position[0].y = m_position.y + margin;
    for (int i = 1; i<m_text.size(); i++) {
        update_line(i);
        m_text_position[i].y = m_text_position[i-1].y + m_text_position[i-1].height + 5;
    }
}
void LabelEx::update_line(const int& line) {
    if (!text_setting) return ;
    if (line>=m_text.size()) return ;
    m_text_position[line].x = m_position.x + m_size.x/2;
    Vector2 text_size = MeasureTextEx(text_setting->font, m_text[line].c_str(),text_setting->font_size,text_setting->spacing);
    m_text_position[line].width = text_size.x;
    m_text_position[line].height = text_size.y*ceil(text_size.x/m_size.x);
    if ((align[line] & Left)  == Left) m_text_position[line].x = m_position.x + margin;
    else if ((align[line] & Right) == Right) m_text_position[line].x = m_position.x + m_size.x - text_size.x - margin;
    else m_text_position[line].x -= text_size.x/2;

}
void LabelEx::setAlignText(const int& line, const int& m_align) {
    align[line] = m_align;
    update_line(line);
}
void LabelEx::update() {
    update_text();
}
float LabelEx::getAutoHeight() const {
    return m_text_position.back().y + m_text_position.back().height;
}
LabelEx::~LabelEx() {

}