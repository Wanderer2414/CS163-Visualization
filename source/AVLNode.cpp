#include "../include/AVLNode.h"
#include "../include/General.h"

AVLNode::AVLNode(const int& index, const int& val) : TextButton(0, 0), m_index(index), m_value(val) {
    setSize(50, 50);
    setText(std::to_string(val));
    left = right = parent = nullptr;
    m_height = 1; // M
    is_animating = false;
    anim_color = WHITE;
}
int AVLNode::getIndex() const {
    return m_index;
}
int AVLNode::getValue() const {
    return m_value;
}
void AVLNode::setPosition(const float& x, const float& y) {
    TextButton::setPosition(x, y);
    m_center = m_position + m_size / 2;
}
void AVLNode::handle() {
    TextButton::handle();
    SlowMotion::handle();
}
void AVLNode::draw() {
    if (button_setting) {
        Color cur;
        if (is_animating) {
            cur = anim_color;
        }
        else {
            if (m_is_hovered) cur = button_setting->hover_color;
            else cur = button_setting->normal_color;
        }
        DrawEllipse(m_center.x, m_center.y, m_size.x / 2, m_size.y / 2, cur); // M
        DrawTextEx(text_setting->font, m_text.c_str(), m_text_position, text_setting->font_size, text_setting->spacing, text_setting->color); // M
    }
}
void AVLNode::updateHeight()
{
    int leftHeight = left ? left->getHeight() : 0;
    int rightHeight = right ? right->getHeight() : 0;
    m_height = 1 + std::max(leftHeight, rightHeight);
}

Vector2 AVLNode::getCenter() const {
    return m_center;
}
Vector2 AVLNode::getPosition() const {
    return TextButton::getPosition();
}
void AVLNode::setValue(int x)
{
    m_value = x;
}
int AVLNode::getHeight() const {
    return m_height;
}
AVLNode::~AVLNode() {

}