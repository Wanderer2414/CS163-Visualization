#include "../include/TabBox.h"
#include "../include/General.h"
#include <iostream>
TabBox::TabBox() {
    pos_changed = false;
    form_setting = 0;
    delta = 0;
}
bool TabBox::isVisible() const {
    return is_visible;
}
void TabBox::init() {
    Controller::init();
    for (auto& i:tabs)
        for (auto& j:i) j->init();
    m_size = {300, 400};
    m_position = {0, 0};

    m_is_hovered = m_is_pressed = false;
    is_visible = true;
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
            m_height.push_back(100);
        }
    tabs[index].push_back(controller);
}

void TabBox::setText(const int& index, const string& name) {
    if (index>=m_name.size()) 
        for (int i = m_name.size(); i<=index; i++) {
            tabs.push_back({});
            m_name.push_back("");
            m_height.push_back(100+m_height.back());
        }
    m_name[index] = name;
    if (form_setting) {
        Vector2 tmp = MeasureTextEx(form_setting->font, name.c_str(), form_setting->font_size, form_setting->spacing);
        m_height[index] = tmp.x+20;
    } 
    else cerr << "[SETTING PACKAGE DOES NOT EXIST IN TABBOX!]";
}
void TabBox::draw() {
    if (is_visible && form_setting) {
        //Draw small box
        DrawRectangleRounded({m_position.x, m_position.y, 30, m_size.y}, form_setting->roundness, form_setting->segment, form_setting->middle_color);
        //Draw big box
        DrawRectangleRounded({m_position.x+30, m_position.y, m_size.x-30, m_size.y}, form_setting->roundness, form_setting->segment, form_setting->middle_color);
        //Draw option
    Vector2 pos = m_position;
    pos.y -= delta;
    cout << delta << endl;
    for (int i = 0; i<m_name.size(); i++) {
            BeginScissorMode(m_position.x, m_position.y, 30, m_size.y);
                Rectangle rec = {pos.x, pos.y, 30, m_height[i]};

                if (i==tab_index)
                    DrawRectangleRounded(rec, form_setting->roundness, form_setting->segment, form_setting->hover_color);
                else if (tab_hover != i) 
                    DrawRectangleRounded(rec, form_setting->roundness, form_setting->segment, form_setting->normal_color);
                else DrawRectangleRounded(rec, form_setting->roundness, form_setting->segment, form_setting->hover_color);
                
                DrawTextPro(form_setting->font, m_name[i].c_str(),{rec.x, rec.y+rec.height - 10}, {0,0}, -90, form_setting->font_size, form_setting->spacing, form_setting->color);
            EndScissorMode();

            if (i==tab_index && i<tabs.size()) {
                BeginScissorMode(m_position.x+30, m_position.y, m_size.x-30, m_size.y);
                    for (int j = 0; j<tabs[i].size(); j++) tabs[i][j]->draw();
                EndScissorMode();
            }
            pos.y += m_height[i];
        }
        DrawLineEx(m_position + Vector2({31, 0}), m_position + Vector2({31, m_size.y}), 1.5f,GRAY);
    } else if (!form_setting) cerr << "[SETTING PACKAGE DOES NOT EXIST IN TABBOX!]";
}
void TabBox::setVisible(const bool& visible) {
    is_visible = visible;
}
void TabBox::clear() {
    tabs.clear();
    m_height.clear();
    m_name.clear();
}
void TabBox::setPosition(const float& x, const float& y) {
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
void TabBox::handle() {
    if (is_visible) {
        SlowMotion::handle();
        Vector2 pos = GetMousePosition();
        m_is_hovered = CheckCollisionPointRec(pos, {m_position.x, m_position.y, m_size.x, m_size.y});
        m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        if (m_is_hovered) {
            if (pos.x<m_position.x + 30 && pos.x>=m_position.x) {
                tab_hover = 0;
                pos.y -= delta;
                while (tab_hover < m_height.size() && pos.y > m_height[tab_hover]+m_position.y) {
                    pos.y -= m_height[tab_hover];
                    tab_hover++;
                }
                if (GetMouseWheelMove()<0 && tab_index < tabs.size()-1) {
                    delta+=m_height[tab_index];
                    tab_index++;
                }
                else if (GetMouseWheelMove()>0 && tab_index) {
                    tab_index--;
                    delta -= m_height[tab_index];
                }
                if (delta < 0) delta = 0;
                if (m_is_pressed && tab_hover<tabs.size()) tab_index = tab_hover;
            } else tab_hover = tab_index;
        }
        for (auto& i:tabs[tab_index]) i->handle();
    } else m_is_hovered = m_is_pressed = false;
}
void TabBox::close() {
    clear();
}
Vector2 TabBox::getPosition() const {
    return m_position;
}