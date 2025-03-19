#include "../include/HomeButton.h"
HomeButton::HomeButton() {
    m_is_hovered = m_is_pressed = 0;
}
void HomeButton::handle() {
    float roofHeight = m_size.y*0.3f;
    roofPoints[0] = {m_position.x, m_position.y + roofHeight};
    roofPoints[1] = {m_position.x + m_size.x, m_position.y + roofHeight};
    roofPoints[2] = {m_position.x + m_size.x / 2, m_position.y};
    house = {m_position.x+0.15f*m_size.x, m_position.y + roofHeight, m_size.x*0.7f,m_size.y-roofHeight};

    Vector2 mousePos = GetMousePosition();
    m_is_hovered = CheckCollisionPointRec(mousePos, house);
    m_is_hovered = m_is_hovered || CheckCollisionPointTriangle(mousePos, roofPoints[0], roofPoints[1], roofPoints[2]);
    m_is_pressed = m_is_hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
void HomeButton::draw() {
    if (button_setting) {
        Color homeColor = m_is_hovered ? button_setting->hover_color : button_setting->normal_color;

        DrawTriangle(roofPoints[0], roofPoints[1], roofPoints[2], homeColor);
        DrawRectangle(house.x, house.y, house.width, house.height, homeColor);
        DrawRectangle(m_position.x + m_size.x*0.4, m_position.y + m_size.y*0.6f, m_size.x*0.2, m_size.y*0.4f, WHITE);
    }
}
HomeButton::~HomeButton() {

}