#include "../include/TabBox.h"
#include "../include/General.h"
TabBox::TabBox() {
    pos_changed = false;
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
void TabBox::draw() {
    if (is_visible) {
        //Draw small box
        DrawRectangleRounded({m_position.x, m_position.y, 30, m_size.y}, form_setting->roundness, form_setting->segment, form_setting->middle_color);
        //Draw big box
        DrawRectangleRounded({m_position.x+30, m_position.y, m_size.x-30, m_size.y}, form_setting->roundness, form_setting->segment, form_setting->middle_color);
        //Draw option
        for (int i = 0; i<name.size(); i++) {
            Vector2 pos = m_position;
            pos.y += i*102;
            if (tab_index == i) {
                DrawRectangleRounded({pos.x, pos.y, 30, 100}, form_setting->roundness, form_setting->segment, form_setting->hover_color);
                if (i<tabs.size()) {
                    BeginScissorMode(m_position.x+30, m_position.y, m_size.x-30, m_size.y);
                    for (int j = 0; j<tabs[i].size(); j++) tabs[i][j]->draw();
                    EndScissorMode();
                }
            } else if (tab_hover != i) DrawRectangleRounded({pos.x, pos.y, 30, 100}, form_setting->roundness, form_setting->segment, form_setting->normal_color);
            else DrawRectangleRounded({pos.x, pos.y, 30, 100}, form_setting->roundness, form_setting->segment, form_setting->hover_color);
            Vector2 sz = MeasureTextEx(form_setting->font, name[i].c_str(), form_setting->font_size, form_setting->spacing);
            DrawTextPro(form_setting->font, name[i].c_str(),pos+Vector2({0, 50+sz.x/2}), {0,0}, -90, form_setting->font_size, form_setting->spacing, form_setting->color);
        }
        DrawLineEx(m_position + Vector2({31, 0}), m_position + Vector2({31, m_size.y}), 1.5f,GRAY);
    }
}
void TabBox::setVisible(const bool& visible) {
    is_visible = visible;
}
void TabBox::clear() {
    tabs.clear();
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
                tab_hover = (pos.y-m_position.y)/105;
                if (GetMouseWheelMove()<0 && tab_index < tabs.size()-1) tab_index++;
                else if (GetMouseWheelMove()>0 && tab_index) tab_index--;
            }
            else tab_hover = -1;
            if (m_is_pressed && tab_hover<tabs.size()) tab_index = tab_hover;
        }
        for (auto& i:tabs[tab_index]) i->handle();
    } else m_is_hovered = m_is_pressed = false;
}
Vector2 TabBox::getPosition() const {
    return m_position;
}