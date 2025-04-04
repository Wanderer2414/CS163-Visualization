#include "../include/Label.h"
#include "../include/General.h"

Label::Label(TextSetting* t_setting) {
    text_setting = t_setting;
    m_text = {""};
    m_text_position = {{0, 0}};
    m_align = Center | Middle;
    margin = 5;
    update_text();
}
bool Label::empty() const {
    return (m_text.size()<=1) && (m_text[0].empty());
}
int Label::getLineSize(const int& line) const {
    if (line>=m_text.size()) return -1;
    return m_text[line].size();
}
int Label::getLineCount() const {
    return m_text.size();
}
void Label::clear() {
    m_text.clear();
    m_text_position.clear();
    m_text = {""};
    m_text_position = {{0, 0}};
    update_line(0);
}
void Label::draw() {
    if (text_setting) {
        for (int i = 0; i<m_text_position.size(); i++) {
            DrawTextEx(text_setting->font, m_text[i].c_str(), m_text_position[i], text_setting->font_size, text_setting->spacing,text_setting->color);
        }
    }
}
void Label::handle() {

}
void Label::erase(const Vector2& start, const Vector2& end) {
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
void Label::erase(const int& row, const int& col) {
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
void Label::insert(int& row, int& col, const string& str) {
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
void Label::insert(const int& row, const int& col, const char& c) {
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
void Label::setText(const std::string& str) {
    m_text.clear();
    m_text.push_back("");
    m_text_position.clear();
    m_text_position.push_back({0, 0});
    for (int i = 0; i<str.size(); i++) {
        if (str[i]=='\n') {
            m_text_position.push_back({0, 0});
            m_text.push_back("");
        }
        else m_text.back().push_back(str[i]);
    }
    update_text();
}
void Label::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    update_text();
}
void Label::setPosition(const float& x, const float& y) {
    for (auto& i:m_text_position) {
        i = i - getPosition() + Vector2({x,y});
    }
    Controller::setPosition(x, y);
}
void Label::update_text() {
    if (!text_setting) return;
    for (int i = 0; i<m_text.size(); i++) {
        update_line(i);
        m_text_position[i].y = m_position.y + m_size.y/2;
        Vector2 text_size = MeasureTextEx(text_setting->font, m_text[i].c_str(),text_setting->font_size,text_setting->spacing);
        if ((m_align & Top) == Top) m_text_position[i].y = m_position.y + margin + i*text_setting->font_size;
        else if ((m_align & Bottom) == Bottom) m_text_position[i].y = m_text_position[i].y + m_size.y - margin - (m_text.size()-i)*text_setting->font_size;
        else {
            m_text_position[i].y -= (0.5f*m_text_position.size() - i)*text_setting->font_size;
        }
    }
}
void Label::update_line(const int& line) {
    if (!text_setting) return ;
    if (line>=m_text.size()) return ;
    m_text_position[line].x = m_position.x + m_size.x/2;
    Vector2 text_size = MeasureTextEx(text_setting->font, m_text[line].c_str(),text_setting->font_size,text_setting->spacing);
    if ((m_align & Left)  == Left) m_text_position[line].x = m_position.x + margin;
    else if ((m_align & Right)   == Right) m_text_position[line].x = m_position.x + m_size.x - text_size.x - margin;
    else m_text_position[line].x -= text_size.x/2;

}
void Label::setAlignText(const int& align) {
    m_align = align;
    update_text();
}
std::string Label::getText() const {
    string ans;
    for (auto& i:m_text) ans+=i+'\n';
    return ans;
}
std::string Label::getText(const Vector2& start, const Vector2& end) const {
    if (end.y < start.y || (end.y==start.y && end.x<=start.x)) return "";
    if (start.x<0 || start.y<0 || end.x < 0 || start.x < 0) return "";
    if (start.y >= m_text.size() || end.y >= m_text.size()) return "";
    if (start.x > m_text[start.y].size() || end.x > m_text[end.y].size()) return "";
    if (start.y == end.y) return m_text[start.y].substr(start.x, end.x-start.x);
    else {
        string ans;    
        ans += m_text[start.y].substr(start.x) + '\n';
        for (int i = start.y+1; i<end.y;i++) ans += m_text[i] + '\n';
        ans += m_text[end.y].substr(0, end.x);
        return ans;
    }
}
Vector2 Label::getCharPosition(const int& row, const int& col) const {
    if (text_setting) {
        Vector2 pos = MeasureTextEx(text_setting->font, m_text[row].substr(0, col).c_str(), text_setting->font_size, text_setting->spacing);
        pos.x+= m_text_position[row].x;
        pos.y = m_text_position[row].y;
        return pos;
    } else return m_position+m_size/2;
}
Vector2 Label::getLinePosition(const int& line) const {
    if (line>=m_text_position.size()) return {0, 0};
    return m_text_position[line];
}
Label::~Label() {

}