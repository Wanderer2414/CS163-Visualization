#include "../include/MenuBox.h"
#include "../include/General.h"
#include <cmath>
MenuBox::MenuBox() {
    light_setting = LightTheme;
    dark_setting = DarkTheme;
    light_setting.roundness = dark_setting.roundness = 0.05f;
}
bool MenuBox::isHovered() const {
    return m_is_hovered && m_is_visible;
}
int MenuBox::getMode() const {
    return round(sun.getPercent());
}
void MenuBox::init() {
    m_position = {0, 0};

    children.push_back(&sun);
    for (auto& i:children) i->init();

    sun.light_button_setting = &light_setting;
    sun.dark_button_setting = &dark_setting;
    sun.setPosition(270, 20);
    sun.setSize(200, 50);
}
void MenuBox::setMode(const int& mode) {
    sun.setMode(mode);
}
void MenuBox::handle() {
    if (!m_is_visible) return;
    VerticalOpen::handle();
    for (auto& i:children) i->handle();
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) VerticalOpen::close();
}
void MenuBox::draw() {
    if (m_is_visible) {
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y},light_setting.roundness, light_setting.segment, dark_setting.background_color);
        Color color = light_setting.background_color;
        color.a *= sun.getPercent();
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y},dark_setting.roundness, dark_setting.segment, color);
        // BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (auto& i:children) i->draw();
        // EndScissorMode();
    }
}
void MenuBox::close() {
    for (auto& i:children) i->close();
    children.clear();
}
void MenuBox::setVisible(const bool& visible) {
    m_is_visible = visible;
} 
void MenuBox::setPosition(const float& x, const float& y) {
    for (auto& i:children) {
        Vector2 tmp = i->getPosition() - m_position + Vector2({x,y});
        i->setPosition(tmp.x, tmp.y);
    }
    Controller::setPosition(x, y);
}
void MenuBox::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
}
Vector2 MenuBox::getSize() const {
    return Controller::getSize();
}
Vector2 MenuBox::getPosition() const {
    return Controller::getPosition();
}
MenuBox::~MenuBox() {

}