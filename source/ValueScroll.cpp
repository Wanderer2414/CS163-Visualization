#include "../include/ValueScroll.h"
#include "../include/General.h"
#include <algorithm>
#include <cmath>

ValueScroll::ValueScroll() {
    text_setting = 0;
    m_text = {""};
    m_text_position = {{0, 0}};
    pointer = 0;
    m_is_changed = m_is_hover = false;
}
bool ValueScroll::empty() const {
    return (m_text.size()<=1) && (m_text[0].empty());
}
bool ValueScroll::isChanged() const {
    return m_is_changed;
}
bool ValueScroll::isHovered() const {
    return m_is_hover;
}
int ValueScroll::getChoiceIndex() const {
    return pointer;
}
void ValueScroll::init() {
    update_text();
}
void ValueScroll::clear() {
    m_text.clear();
    m_text_position.clear();
    m_text = {""};
    m_text_position = {{0, 0}};
}
void ValueScroll::draw() {
    if (text_setting) {
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (int i = 0; i<m_text_position.size(); i++) {
            DrawTextEx(text_setting->font, m_text[i].c_str(), m_text_position[i], font_size[i], text_setting->spacing,text_setting->color);
        }
        EndScissorMode();
    }
}
void ValueScroll::handle() {
    m_is_hover = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});   
    if (!text_setting) return ;
    if (m_is_hover && GetMouseWheelMove()) {
        pointer += GetMouseWheelMove()/5;
        if (pointer>=m_text_position.size()) pointer = m_text_position.size()-1;
        if (pointer<0) pointer = 0;
        m_is_changed = true;
        update_text();
    } else if (!m_is_hover && pointer!=round(pointer)) {
        float delta = pointer - round(pointer);
        if (abs(delta)>0.1) pointer -= delta/10;
        else pointer = round(pointer);
        update_text();
        m_is_changed = false;
    } else m_is_changed = false;
}
void ValueScroll::setText(const std::string& str) {
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
void ValueScroll::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    update_text();
}
void ValueScroll::setPosition(const float& x, const float& y) {
    for (auto& i:m_text_position) {
        i = i - getPosition() + Vector2({x,y});
    }
    Controller::setPosition(x, y);
}
void ValueScroll::update_text() {
    if (!text_setting) return;
    font_size.clear();
    for (int i = 0; i<m_text.size(); i++) {
        font_size.push_back(std::max(text_setting->font_size - abs(i-pointer)*10, 0.f));
        update_line(i);
    }
    m_text_position[0].y = m_position.y + text_setting->font_size/2;
    for (int i =1; i<m_text_position.size(); i++) {
        m_text_position[i].y = m_text_position[i-1].y + font_size[i-1];
    }
}
void ValueScroll::update_line(const int& line) {
    if (!text_setting) return ;
    if (line>=m_text.size()) return ;
    m_text_position[line].x = m_position.x + m_size.x/2;
    Vector2 text_size = MeasureTextEx(text_setting->font, m_text[line].c_str(),font_size[line],text_setting->spacing);
    m_text_position[line].x -= text_size.x/2;

}
std::string ValueScroll::getText() {
    string ans;
    for (auto& i:m_text) ans+=i;
    return ans;
}
std::string ValueScroll::getChoice() {
    return m_text[pointer];
}
ValueScroll::~ValueScroll() {

}