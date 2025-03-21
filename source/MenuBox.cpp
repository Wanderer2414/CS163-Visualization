#include "../include/MenuBox.h"

MenuBox::MenuBox() {
    button_setting = 0;
}
void MenuBox::init() {
    background_color = WHITE;
}
void MenuBox::handle() {
    if (!m_is_visible) return;
    VerticalOpen::handle();
    for (auto& i:children) i->handle();
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) close();
}
void MenuBox::draw() {
    if (m_is_visible && button_setting) {
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, button_setting->roundness, button_setting->segment, background_color);
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (auto& i:children) i->draw();
        EndScissorMode();
    }
}
void MenuBox::setVisible(const bool& visible) {
    m_is_visible = visible;
} 
void MenuBox::setPosition(const float& x, const float& y) {
    Controller::setPosition(x, y);
}
void MenuBox::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
}
void MenuBox::setBackgroundColor(const Color& color) {
    background_color = color;
}
void MenuBox::push_back(Controller* control) {
    children.push_back(control);
}
void MenuBox::remove(Controller* control) {
    for (int i = 0; i<children.size() ; i++) 
        if (children[i] == control) {
            children.erase(children.begin() + i);
            break;
        } 
}
Vector2 MenuBox::getSize() const {
    return Controller::getSize();
}
Vector2 MenuBox::getPosition() const {
    return Controller::getPosition();
}
MenuBox::~MenuBox() {

}