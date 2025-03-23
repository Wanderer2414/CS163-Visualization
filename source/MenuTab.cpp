#include "../include/MenuTab.h"
#include "../include/raylib.h"
ButtonTab::ButtonTab() {
    button_setting = 0;
    before_press = 6;
    m_is_pressed = m_is_hovered = m_is_showed = 0;
    m_hover_selection = -1;
    m_selection = 0;
}
bool ButtonTab::isHovered() const {
    return m_is_hovered;
}
bool ButtonTab::isPressed() const {
    return m_is_pressed;
}
void ButtonTab::handle() {
    m_isChanged = false;
    if (Length.empty()) return;

    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    if (m_is_pressed) {
        m_is_showed = !m_is_showed; // Toggle menu
        return;
    }
    if (m_is_showed) {
        Vector2 mousePos = GetMousePosition();
        if (mousePos.x >= m_position.x && mousePos.x <= m_position.x + m_size.x) {
            int index = (mousePos.y - m_position.y - m_size.y) / m_size.y;
            if (index >= 0 && index < Items.size()) {
                m_hover_selection = index;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (m_selection != index) m_isChanged = true;
                    m_selection = index; // Update selection
                }
            }
        }
        else {
            m_hover_selection = -1;
        }
    }
}
void ButtonTab::push_back(const std::string& name)
{
    Items.push_back(name);
    Vector2 length = MeasureTextEx(text_setting->font, name.c_str(), text_setting->font_size, text_setting->spacing);
    Length.push_back(length.x);
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

    DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, button_setting->roundness, button_setting->segment, button_setting->normal_color);

    if (m_selection >= 0 && m_selection < Items.size())
        DrawTextEx(text_setting->font, Items[m_selection].c_str(),
                  { m_position.x + m_size.x / 2 - Length[m_selection] / 2, m_position.y + m_size.y / 2 - 15},
                   text_setting->font_size, 
                   text_setting->spacing, 
                   text_setting->color);

    if (m_is_showed) {
        for (int i = 0; i < Items.size(); i++) {
            Color rectColor = (m_hover_selection == i) ? button_setting->hover_color : ((m_selection == i) ? button_setting->click_color : button_setting->normal_color);
            DrawRectangleRounded({ m_position.x, m_position.y + m_size.y * (i + 1), m_size.x, m_size.y }, button_setting->roundness, button_setting->segment, rectColor);
            DrawTextEx(text_setting->font, Items[i].c_str(),
                { m_position.x + m_size.x / 2 - Length[i] / 2,
                m_position.y + m_size.y * (i + 1) + m_size.y / 2 - 15}, text_setting->font_size, text_setting->spacing, text_setting->color);
        }
    }
}
ButtonTab::~ButtonTab()
{
}
