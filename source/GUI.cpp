#include "GUI.h"
#include "SettingPackage.h"
#include "RaylibExtra.h"
#include "raylib.h"

Node::Node(ButtonSetting* button_setting, TextSetting* text_setting): TextButton(button_setting, text_setting) {
    setSize(50, 50);
}
void Node::handle() {
    TextButton::handle();
    SlowMotion::handle();
}
void Node::draw() {
    if (button_setting) {
        Color color = button_setting->normal_color;
        if (m_is_pressed) color = button_setting->click_color;
        else if (m_is_hovered) color = button_setting->hover_color;
        DrawCircleV(m_position, m_size.x, color);
        DrawText(text_setting, m_text_position, m_text);
    }
}
Vector2 Node::getPosition() const {
    return TextButton::getPosition();
}
Node::~Node() {

}