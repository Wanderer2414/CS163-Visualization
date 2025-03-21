#include "../include/TabBox.h"
#include "../include/General.h"
#include "../include/IncludePath.h"
TabBox::TabBox() {
    pos_changed = false;
}
bool TabBox::isVisible() const {
    return is_visible;
}
void TabBox::init() {
    Controller::init();
    text_setting.font = LoadFont(font_link);
    m_size = {300, 400};
    m_position = {0, 0};

    m_is_hovered = m_is_pressed = false;
    is_visible = true;

    button_setting.roundness = 0.05;
    button_setting.hover_color = DARKGRAY;

    for (auto& i:tabs)
        for (auto& j:i) j->init();
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
        DrawRectangleRounded({m_position.x, m_position.y, 30, m_size.y}, button_setting.roundness, button_setting.segment, WHITE);
        //Draw big box
        DrawRectangleRounded({m_position.x+30, m_position.y, m_size.x-30, m_size.y}, button_setting.roundness, button_setting.segment, button_setting.hover_color);
        //Draw option
        for (int i = 0; i<name.size(); i++) {
            Vector2 pos = m_position;
            pos.y += i*102;
            if (tab_index == i) {
                DrawRectangleRounded({pos.x, pos.y, 30, 100}, button_setting.roundness, button_setting.segment, button_setting.hover_color);
                if (i<tabs.size()) {
                    BeginScissorMode(m_position.x+30, m_position.y, m_size.x-30, m_size.y);
                    for (int j = 0; j<tabs[i].size(); j++) tabs[i][j]->draw();
                    EndScissorMode();
                }
            } else if (tab_hover != i) DrawRectangleRounded({pos.x, pos.y, 30, 100}, button_setting.roundness, button_setting.segment, button_setting.normal_color);
            else DrawRectangleRounded({pos.x, pos.y, 30, 100}, button_setting.roundness, button_setting.segment, button_setting.hover_color);
            Vector2 sz = MeasureTextEx(text_setting.font, name[i].c_str(), text_setting.font_size, text_setting.spacing);
            DrawTextPro(text_setting.font, name[i].c_str(),pos+Vector2({0, 50+sz.x/2}), {0,0}, -90, text_setting.font_size, text_setting.spacing, text_setting.color);
        }
        DrawLineEx(m_position + Vector2({31, 0}), m_position + Vector2({31, m_size.y}), 1.5f,GRAY);
    }
}
void TabBox::setVisible(const bool& visible) {
    is_visible = visible;
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
            if (pos.x<m_position.x + 30 && pos.x>=m_position.x) tab_hover = (pos.y-m_position.y)/105;
            else tab_hover = -1;
            if (m_is_pressed && tab_hover<tabs.size()) tab_index = tab_hover;
            if (GetMouseWheelMove()<0 && tab_index < tabs.size()-1) tab_index++;
            else if (GetMouseWheelMove()>0 && tab_index) tab_index--;
        }
        for (auto& i:tabs[tab_index]) i->handle();
    } else m_is_hovered = m_is_pressed = false;
}
Vector2 TabBox::getPosition() const {
    return m_position;
}