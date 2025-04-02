#include "../include/ColorPointer.h"

ColorPointer::ColorPointer(ButtonSetting* b_setting): red(WHITE, RED), blue(WHITE, BLUE), green(WHITE, GREEN), alpha(WHITE, BLACK) {
    red.setPosition(5, 5);
    green.setPosition(5, 30);
    blue.setPosition(5, 55);
    alpha.setPosition(5, 80);
    alpha.setPercent(1);
    button_setting = b_setting;
    m_is_visible = true;
    m_is_hovered = false;
}
bool ColorPointer::isVisible() const {
    return m_is_visible;
}
bool ColorPointer::isHovered() const {
    return m_is_hovered;
}
void ColorPointer::draw() {
    if (m_is_visible) {
        DrawRectangleRounded({m_position.x, m_position.y, m_size.x, m_size.y}, 0.05f, 30, button_setting->normal_color);
        red.draw();
        green.draw();
        blue.draw();
        alpha.draw();
        Color color;
        color.r = red.getPercent()*255;
        color.g = green.getPercent()*255;
        color.b = blue.getPercent()*255;
        color.a = alpha.getPercent()*255;
        DrawRectangle(m_position.x + m_size.x - 25, m_position.y + 5, 20, 95, color);
    }
}
void ColorPointer::handle() {
    if (m_is_visible) {
        m_is_hovered = CheckCollisionPointRec(GetMousePosition(), {m_position.x, m_position.y, m_size.x, m_size.y});
        red.handle();
        green.handle();
        blue.handle();
        alpha.handle();
    }
}

void ColorPointer::setPosition(const float& x, const float& y) {
    green.setPosition(green.getPosition().x - m_position.x + x, green.getPosition().y - m_position.y + y);
    red.setPosition(red.getPosition().x - m_position.x + x, red.getPosition().y - m_position.y + y);
    blue.setPosition(blue.getPosition().x - m_position.x + x, blue.getPosition().y - m_position.y + y);
    alpha.setPosition(alpha.getPosition().x - m_position.x + x, alpha.getPosition().y - m_position.y + y);
    Controller::setPosition(x, y);
}
void ColorPointer::setVisible(const bool& visible) {
    m_is_visible = visible;
}
void ColorPointer::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    red.setSize(width - 35, 20);
    green.setSize(width - 35, 20);
    blue.setSize(width - 35, 20);
    alpha.setSize(width - 35, 20);
}
void ColorPointer::setColor(const Color& color) {
    red.setPercent(1.*color.r/255);
    green.setPercent(1.*color.g/255);
    blue.setPercent(1.*color.b/255);
    alpha.setPercent(1.*color.a/255);
}
Color ColorPointer::getColor() const {
    Color color;
    color.r = red.getPercent()*255;
    color.g = green.getPercent()*255;
    color.b = blue.getPercent()*255;
    color.a = alpha.getPercent()*255;
    return color;
}