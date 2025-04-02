#include "../include/Vertex.h"
#include "../include/General.h"
#include <cstdlib>
#include <ctime>
Vertex::Vertex(FormSetting* f_setting, const int& index) {
    m_index = index;
    form_setting = f_setting;
    velocity = {0, 0};
    m_acceleration = {0, 0};
    m_is_hold = false;
    m_is_pressed = false;
    m_is_hovered = false;
    m_is_fixed = false;
    m_is_focus = false;
    m_dragable = false;
}
bool Vertex::isPressed() const {
    return m_is_pressed;
}
bool Vertex::isHovered() const {
    return m_is_hovered;
}
bool Vertex::isFocused() const {
    return m_is_focus;
}
int Vertex::getIndex() const {
    return m_index;
}
int Vertex::getValue() const {
    return m_value;
}
float Vertex::getRadius() const {
    return max(m_size.x, m_size.y)/2;
}
void Vertex::draw() {
    DynamicColorCircle::draw();
    if (!m_is_focus) {
        DrawEllipse(m_position.x, m_position.y, m_size.x/2, m_size.y/2, form_setting->normal_color);
    } else DrawEllipse(m_position.x, m_position.y, m_size.x/2, m_size.y/2, form_setting->click_color);
    DrawTextEx(form_setting->font, m_text.c_str(), m_text_position, form_setting->font_size, form_setting->spacing, form_setting->color);
}
void Vertex::setFixed(const bool& fixed) {
    m_is_fixed = fixed;
}

void Vertex::handle() {
    DynamicColorCircle::handle();
    m_is_hovered = CheckCollisionPointCircle(GetMousePosition(), m_position, getRadius());
    m_is_pressed = m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (m_is_pressed) {
        m_is_hold = true;
        m_is_focus = !m_is_focus;
    }
    if (!m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) m_is_focus = false;
    else if (m_is_hold && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_is_hold = false;

    if (m_dragable) velocity = {0, 0};
    else {
        velocity = velocity + m_acceleration;
        m_acceleration = {0, 0};
    }
    if (m_is_hold) {
        velocity = GetMouseDelta();
    } else if (!m_dragable && !m_is_fixed) {
        if (abs(velocity)>0.3) velocity=velocity/1.05;
        else if (abs(velocity)<0.3 && abs(velocity)>0) {
            velocity = velocity/abs(velocity)*0.3;
        } else {
            srand(clock());
            velocity.x = rand()-RAND_MAX/2;
            velocity.y = rand()-RAND_MAX/2;
            if (abs(velocity))
                velocity = velocity/abs(velocity)*0.3;
        }
    }

    if (!m_is_fixed) {
        setPosition(m_position.x + velocity.x, m_position.y + velocity.y);
    }
}
void Vertex::setDragable(const bool& dragable) {
    m_dragable = dragable;
}
void Vertex::add_acceleration(const Vector2& acceleration) {
    m_acceleration = m_acceleration + acceleration;
}
void Vertex::setVelocity(const Vector2& v) {
    velocity = v;
}
void Vertex::setSize(const float& width, const float& height) {
    Controller::setSize(width, height);
    DynamicColorCircle::setRadius(getRadius()+5);
}
void Vertex::setPosition(const float& x, const float& y) {
    m_text_position = m_text_position - m_position + Vector2({x,y});
    Controller::setPosition(x, y);
}
void Vertex::setValue(const int& value) {
    m_value = value;
    m_text = to_string(value);
    Vector2 size = MeasureTextEx(form_setting->font, m_text.c_str(), form_setting->font_size, form_setting->spacing);
    m_text_position = m_position - size/2;
}
                            
Vector2 Vertex::getCenter() const {
    return m_position;
}
    
Vector2 Vertex::getVelocity() const {
    return velocity;
}
Vertex::~Vertex() {

}