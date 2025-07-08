#include "GUI.h"
#include "Controller.h"
#include "General.h"
#include "SettingPackage.h"
#include "RaylibExtra.h"
#include "raylib.h"

extern FormSetting* setting;
extern Camera2D m_camera;

Node::Node(): TextButton(setting, setting) {
    setSize(50, 50);
}
int Node::getValue() const {
    return 0;
}
void Node::setValue(const int& value) {
}
void Node::setPosition(const float& x, const float& y) {
    Controller::setPosition(x, y);
}
void Node::handle() {
    setText(to_string(getValue()));
    m_is_hovered = CheckCollisionPointRec(TransToGlobalPoint(m_camera,GetMousePosition()), { m_position.x, m_position.y, m_size.x, m_size.y });
    m_is_pressed = (m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
    SlowMotion::handle();
}
void Node::draw() {
    if (button_setting) {
        Color color = button_setting->normal_color;
        if (m_is_pressed) color = button_setting->click_color;
        else if (m_is_hovered) color = button_setting->hover_color;
        DrawCircleV(m_position + m_size/2, m_size.x/2, color);
        DrawText(text_setting, m_text_position, m_text);
    }
}
Vector2 Node::getPosition() const {
    return TextButton::getPosition();
}
Vector2 Node::getCenter() const {
    return getPosition() + getSize()/2;
}
Node::~Node() {

}