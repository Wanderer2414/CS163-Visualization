#include "../include/TabBox.h"
#include "../include/General.h"
#include <iostream>

TabBox::TabBox(FormSetting* f_setting) {
    pos_changed = false;
    form_setting = f_setting;
    tab_hover = -1;
    tab_index = -1;
    margin = 5;
    max_size = {0, margin};
    is_visible = true;
    m_is_hovered = m_is_pressed = false;
    m_size = {300, 400};
    m_position = {0, 0};
}
bool TabBox::isVisible() const {
    return is_visible;
}
bool TabBox::isHovered() const {
    return m_is_hovered;
}
bool TabBox::isPressed() const {
    return m_is_pressed;
}
void TabBox::push_back(const int& index, Controller* controller) {
    if (index>=tabs.size()) 
        for (int i = tabs.size(); i<=index; i++) {
            tabs.push_back({});
            m_name.push_back("");
            name_widths.push_back(0);
        }
    tabs[index].push_back(controller);
    Vector2 pos = controller->getPosition() + m_position;
    controller->setPosition(pos.x, pos.y);
}

void TabBox::setText(const int& index, const string& name) {
    if (index>=m_name.size()) 
        for (int i = m_name.size(); i<=index; i++) {
            tabs.push_back({});
            m_name.push_back("");
            name_widths.push_back(0);
        }
    m_name[index] = name;
    if (form_setting) {
        Vector2 tmp = MeasureTextEx(form_setting->font, name.c_str(), form_setting->font_size, form_setting->spacing);
        max_size.x = max(max_size.x, tmp.x + 2*margin);
        max_size.y += tmp.y + margin*3;
        name_widths[index] = tmp.x;
    } 
    else cerr << "[SETTING PACKAGE DOES NOT EXIST IN TABBOX!]" << endl;
}
void TabBox::draw() {
    if (is_visible && form_setting) {
        DrawRectangleRounded({m_position.x, m_position.y, max_size.x+2*margin, max_size.y}, form_setting->roundness, form_setting->segment, form_setting->middle_color);
        Rectangle rec;
        rec.y = m_position.y + margin;
        rec.x = m_position.x + margin;
        rec.width = max_size.x;
        rec.height = form_setting->font_size + 2*margin; 
        for (int i = 0; i<m_name.size(); i++) {
            if (tab_index == i) {
                DrawRectangleRounded(rec, form_setting->roundness, form_setting->segment, form_setting->click_color);
                for (auto& k:tabs[i]) {
                    k->draw();
                }
            }
            else if (tab_hover == i) 
                DrawRectangleRounded(rec, form_setting->roundness, form_setting->segment, form_setting->hover_color);
            else DrawRectangleRounded(rec, form_setting->roundness, form_setting->segment, form_setting->normal_color);
            DrawTextEx(form_setting->font, m_name[i].c_str(), {rec.x+rec.width/2-name_widths[i]/2, rec.y + margin}, form_setting->font_size, form_setting->spacing, form_setting->color);
            rec.y += form_setting->font_size + 3*margin;
        }
    } else if (!form_setting) cerr << "[SETTING PACKAGE DOES NOT EXIST IN TABBOX!]";
}
void TabBox::setVisible(const bool& visible) {
    is_visible = visible;
}
void TabBox::clear() {
    tabs.clear();
    m_name.clear();
}
void TabBox::setPosition(const float& x, const float& y) {
    Move::setPosition(x, y);
    for (auto& tab:tabs) {
        for (auto& control:tab) {
            Vector2 tmp = control->getPosition()-getPosition();
            control->setPosition(tmp.x, tmp.y);
        }
    }
    Controller::setPosition(x, y);
    for (auto& tab:tabs) {
        for (auto& control:tab) {
            Vector2 tmp = control->getPosition()+getPosition();
            control->setPosition(tmp.x, tmp.y);
        }
    }
}
Vector2 TabBox::getAutoSize() const {
    return max_size;
}
void TabBox::select(const int& index) {
    tab_index = index;
}
void TabBox::handle() {
    if (is_visible) {
        Move::handle();
        Vector2 pos = GetMousePosition();
        m_is_hovered = CheckCollisionPointRec(pos, {m_position.x, m_position.y, m_size.x, m_size.y});
        m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        if (m_is_hovered) {
            Rectangle rec;
            rec.x = m_position.x + margin;
            rec.y = m_position.y + margin;
            rec.width = max_size.x;
            rec.height = form_setting->font_size + 3*margin;
            if (pos.x >= m_position.x + margin && pos.x <= m_position.x+max_size.x) 
                tab_hover = (pos.y-rec.y)/rec.height;
            else tab_hover = -1;
            if (m_is_pressed && tab_hover>=0 && tab_hover <= m_name.size()) tab_index = tab_hover;
        }
        if (tab_index >= 0 && tab_index < tabs.size())
            for (auto& i:tabs[tab_index]) {
                i->handle();
                m_is_hovered = m_is_hovered || i->isHovered();
            }
    } else m_is_hovered = m_is_pressed = false;
}
Vector2 TabBox::getPosition() const {
    return m_position;
}