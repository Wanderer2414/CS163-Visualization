#include "../include/GUI.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
Node::Node(const int& index, Vector2* origin, const int& val):m_index(index), m_value(val), TextButton(origin) {
    init();
    setSize(50, 50);
    setText(std::to_string(val));
    m_hover_color = {200, 200, 200, 255};
    left = right = 0;
}
int Node::getIndex() const {
    return m_index;
}
int Node::getValue() const {
    return m_value;
}
void Node::setPosition(const float& x, const float& y) {
    TextButton::setPosition(x,y);
    m_center = m_position+m_size/2;
}
void Node::handle() {
    TextButton::handle();
    SlowMotion::handle();
}
void Node::draw() {
    Color cur;
    if (m_is_hovered) cur = m_hover_color;
    else cur = m_normal_color;
    if (left && left->isVisible) DrawLineEx(m_center+*m_origin, left->getCenter()+*m_origin, 1.5f, cur);
    if (right && right->isVisible) DrawLineEx(m_center+*m_origin, right->getCenter()+*m_origin, 1.5f, cur);
    DrawEllipse(m_center.x+m_origin->x, m_center.y+m_origin->y, m_size.x/2, m_size.y/2, cur);
    DrawTextEx(m_font, m_text.c_str(), m_text_position + *m_origin, m_font_size, m_spacing, m_text_color);
};
Vector2 Node::getCenter() const {
    return m_center;
}
Vector2 Node::getPosition() const {
    return TextButton::getPosition();
}
Node::~Node() {

}