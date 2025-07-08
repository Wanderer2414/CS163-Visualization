#include "MenuTab.h"

ButtonTab::ButtonTab(ButtonSetting* b_setting, TextSetting *t_setting) {
    button_setting = b_setting;
    text_setting = t_setting;
    m_is_pressed = m_is_hovered = m_is_showed = 0;
    m_hover_selection = -1;
    m_selection = -1;
    m_is_focus = false;
    delta = 0;
}
bool ButtonTab:: isFocus() const {
    return m_is_focus;
}
bool ButtonTab::isHovered() const {
    return m_is_hovered;
}
bool ButtonTab::isPressed() const {
    return m_is_pressed;
}
void ButtonTab::setSelection(const int& index) {
    if (index>=0 && index<Items.size()) m_selection = index;
}
void ButtonTab::handle() {
    m_isChanged = false;
    if (Length.empty()) return;

    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_is_pressed = m_is_hovered;
        m_is_focus = m_is_hovered;
        if (m_is_pressed) {
            m_is_focus = true;
            m_is_showed = !m_is_showed; // Toggle menu
        }
    } else m_is_pressed = false;
    
    m_hover_selection = -1;
    if (m_is_showed) {
        Vector2 mousePos = GetMousePosition();
        delta += GetMouseWheelMove() * 20;
        delta = clamp(delta, 0.f, (m_size.y + 2)*(Items.size()-3));
        if (mousePos.x >= m_position.x && mousePos.x <= m_position.x + m_size.x) {
            int index = (mousePos.y - m_position.y - m_size.y + delta) / (m_size.y+2);
            if (mousePos.y - m_position.y - m_size.y>0 && index >= 0 && index < Items.size()) {
                m_hover_selection = index;
                m_is_hovered = true;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (m_selection != index) m_isChanged = true;
                    m_selection = index; // Update selection
                    m_is_showed = false;
                }
            }
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !m_is_hovered) m_is_showed = false;
}
void ButtonTab::push_back(const std::string& name)
{
    Items.push_back(name);
    Vector2 length = MeasureTextEx(text_setting->font, name.c_str(), text_setting->font_size, text_setting->spacing);
    Length.push_back(length.x);
}
void ButtonTab::update() {
    for (int i = 0; i<Length.size(); i++) {
        Vector2 length = MeasureTextEx(text_setting->font, Items[i].c_str(), text_setting->font_size, text_setting->spacing);
        Length[i] = length.x;
    }
}
int ButtonTab::GetSelection()
{
    return m_selection;
}
bool ButtonTab::isChanged()
{
    return m_isChanged;
}
void ButtonTab::draw() {
    if (Items.empty() || Length.empty()) return;

    DrawRectangleRounded({m_position.x, m_position.y-2, m_size.x, m_size.y+4}, button_setting->roundness, button_setting->segment, button_setting->click_color);
    DrawRectangleRounded({m_position.x+2, m_position.y, m_size.x-4, m_size.y}, button_setting->roundness, button_setting->segment, button_setting->normal_color);

    if (m_selection >= 0 && m_selection < Items.size())
        DrawTextEx(text_setting->font, Items[m_selection].c_str(),
                  { m_position.x + m_size.x / 2 - Length[m_selection] / 2, m_position.y + m_size.y / 2 - 15},
                   text_setting->font_size, 
                   text_setting->spacing, 
                   text_setting->color);

    if (m_is_showed) {
        BeginScissorMode(m_position.x, m_position.y+m_size.y+2, m_size.x, m_size.y*5);
        for (int i = 0; i < Items.size(); i++) {
            Color rectColor = (m_hover_selection == i) ? button_setting->hover_color : ((m_selection == i) ? button_setting->click_color : button_setting->normal_color);
            Vector2 pos = m_position;
            pos.y = m_position.y + (m_size.y+2) * (i + 1) - delta;
            DrawRectangleRounded({ m_position.x, pos.y-2, m_size.x, m_size.y+4 }, button_setting->roundness, button_setting->segment, button_setting->click_color);
            DrawRectangleRounded({ m_position.x+2, pos.y, m_size.x-4, m_size.y }, button_setting->roundness, button_setting->segment, rectColor);
            DrawTextEx(text_setting->font, Items[i].c_str(),
                { m_position.x + m_size.x / 2 - Length[i] / 2,
                pos.y + m_size.y / 2 - text_setting->font_size/2}, text_setting->font_size, text_setting->spacing, text_setting->color);
        }
        EndScissorMode();
    }
}
ButtonTab::~ButtonTab() {
    
}
