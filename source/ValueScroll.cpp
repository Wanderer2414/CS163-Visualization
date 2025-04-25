#include "../include/ValueScroll.h"
#include "../include/General.h"

ValueScroll::ValueScroll(TextSetting* t_setting) {
    text_setting = t_setting;
    m_text.clear();
    m_text_position.clear();
    m_is_hover = m_is_changed = false;
    m_index = 0;
    pointer = 0;
    velocity = 0;
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
float ValueScroll::getValue() const {
    return m_values[m_index];
}
void ValueScroll::clear() {
    m_text.clear();
    m_text_position.clear();
}

void ValueScroll::draw() {
    if (text_setting) {
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        int range = text_setting->font_size/5;
        int start = m_index - range;
        int end = m_index+range;
        for (int i = start; i<end; i++) {
            int index = (i+m_text.size())%m_text.size();
            DrawTextEx(text_setting->font, m_text[index].c_str(), m_text_position[index], font_size[index], text_setting->spacing,text_setting->color);
        }
        EndScissorMode();
    }
}
void ValueScroll::select(const int& p) {
    m_index = pointer = p;
    update_text();
}
void ValueScroll::add_velocity(const float& v) {
    velocity = v;
}
void ValueScroll::handle() {
    m_is_hover = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});   
    if (!text_setting) return ;
    if (m_is_hover && GetMouseWheelMove()) {
        velocity = GetMouseWheelMove();
    } 
    if (m_is_hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        velocity = -GetMouseDelta().y/2;
    }
    m_is_changed = false;
    if (velocity != 0) {
        pointer += velocity;
        if (abs(velocity) > 0.1) velocity /= 1.05;
        else velocity = 0;
        if (pointer>=m_text_position.size()) 
            pointer -= m_text_position.size();
        if (pointer<0) 
            pointer += m_text_position.size();
        m_index= round(pointer);
        if (m_index >= m_text_position.size()) m_index = m_text_position.size() - 1;
        m_is_changed = true;
        update_text();
    }
}
void ValueScroll::push_back(const float& value, const std::string& str) {
    m_text.push_back(str);
    m_text_position.push_back({0, 0});
    font_size.push_back(0);
    m_values.push_back(value);
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
    if (!text_setting || m_text.empty()) return;
    int range = text_setting->font_size/5;
    int start = m_index - range;
    int end = m_index+range;
    int n = text_setting->font_size/5;
    n = n*(n-1)/2;
    //Align middle
    int prev = (start-1+m_text.size())%m_text.size();
    m_text_position[prev].y = m_position.y + m_size.y/2 - text_setting->font_size/5 - int(text_setting->font_size)%5 - n*5;

    for (int i = start; i<end; i++) {
        int index = (i+m_text.size())%m_text.size();
        prev = (i-1+m_text.size())%m_text.size();
        float size = text_setting->font_size - abs(i-pointer)*5;
        font_size[index] = size;
        m_text_position[index].y = m_text_position[prev].y + font_size[prev];
        update_line(index);
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
    return m_text[m_index];
}
ValueScroll::~ValueScroll() {

}