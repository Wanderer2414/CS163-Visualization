#include "../include/AVLNode.h"
#include "../include/General.h"

AVLNode::AVLNode(ButtonSetting* b_setting, TextSetting* t_setting ,const int& index, const int& val): m_index(index), m_value(val) {
    button_setting = b_setting;
    text_setting = t_setting;
    m_text_position = m_position = {0, 0};
    setSize(50, 50);
    setValue(val);
    left = right = parent = nullptr;
    height = 1;
}
int AVLNode::getIndex() const {
    return m_index;
}
int AVLNode::getValue() const {
    return m_value;
}
void AVLNode::setPosition(const float& x, const float& y) {
    m_text_position = m_text_position-m_position + Vector2({x,y});
    Controller::setPosition(x, y);
}
void AVLNode::handle() {
    Controller::handle();
    SlowMotion::handle();
}
void AVLNode::draw() {
    if (button_setting && text_setting) {
        DrawEllipse(m_position.x, m_position.y, m_size.x / 2, m_size.y / 2, button_setting->normal_color);
        DrawTextEx(text_setting->font, to_string(m_value).c_str(), m_text_position, text_setting->font_size, text_setting->spacing, text_setting->color);
    }
}

Vector2 AVLNode::getPosition() const {
    return Controller::getPosition();
}
void AVLNode::setValue(int x)
{
    Vector2 sz = MeasureTextEx(text_setting->font, to_string(x).c_str(), text_setting->font_size, text_setting->spacing);
    m_text_position = m_position-sz/2;
    m_value = x;
}
AVLNode::~AVLNode() {

}
