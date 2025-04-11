#include "../include/MenuBox.h"
#include "../include/General.h"

MenuBox::MenuBox(FormSetting& f_setting): 
form_setting(f_setting), sun(&LightTheme, &DarkTheme), window_size(&form_setting, &form_setting) {
    m_position = {0, 0};
    children.push_back(&sun);
    children.push_back(&window_size);

    sun.setPosition(270, 20);
    sun.setSize(200, 50);

    window_size.setPosition(10, 75);
    window_size.setSize(200, 40);
    window_size.push_back("1366x768");
    window_size.push_back("1820x980");
    window_size.push_back("1024x768");
    window_size.setSelection(0);
}
bool MenuBox::isHovered() const {
    return m_is_hovered && m_is_visible;
}
int MenuBox::getMode() const {
    return round(sun.getPercent());
}
void MenuBox::setMode(const int& mode) {
    sun.setMode(mode);
}
void MenuBox::handle() {
    if (!m_is_visible) return;
    VerticalOpen::handle();
    for (auto& i:children) i->handle();
    m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
    if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || submit_button.isPressed()) VerticalOpen::close();
}
void MenuBox::draw() {
    if (m_is_visible) {
        Color color = LightTheme.background_color*sun.getPercent() + DarkTheme.background_color*(1-sun.getPercent());
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, form_setting.roundness, form_setting.segment, color);
        BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
        for (auto& i:children) i->draw();
        EndScissorMode();
    }
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
Vector2 MenuBox::getWindowSize() {
    return window_sizes[window_size.GetSelection()];
}
Vector2 MenuBox::getSize() const {
    return Controller::getSize();
}
Vector2 MenuBox::getPosition() const {
    return Controller::getPosition();
}
MenuBox::~MenuBox() {

}