#include "../include/GUI.h"
#include "../include/General.h"

Node::Node(const int& index, const int& val): TextButton(0, 0), m_index(index), m_value(val) {
    setSize(50, 50);
    setText(std::to_string(val));
    left = right = 0;
    m_height = 1; // M
}
int Node::getIndex() const {
    return m_index;
}
int Node::getValue() const {
    return m_value;
}
void Node::setPosition(const float& x, const float& y) {
    TextButton::setPosition(x, y);
    m_center = m_position + m_size / 2;
}
void Node::handle() {
    TextButton::handle();
    SlowMotion::handle();
}
void Node::draw() {
    if (button_setting) {
        Color cur;
        if (m_is_hovered) cur = button_setting->hover_color;
        else cur = button_setting->normal_color;
        DrawEllipse(m_center.x, m_center.y, m_size.x / 2, m_size.y / 2, cur); // M
        DrawTextEx(text_setting->font, m_text.c_str(), m_text_position, text_setting->font_size, text_setting->spacing, text_setting->color); // M
    }
}
void Node::updateHeight()
{
    int leftHeight = left ? left->getHeight() : 0;
    int rightHeight = right ? right->getHeight() : 0;
    m_height = 1 + std::max(leftHeight, rightHeight);
}
;
Vector2 Node::getCenter() const {
    return m_center;
}
Vector2 Node::getPosition() const {
    return TextButton::getPosition();
}
void Node::setValue(int x) 
{
    m_value = x;
}
int Node::getHeight() const {
    return m_height;
}
Node::~Node() {

}