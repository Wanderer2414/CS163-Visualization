#include "../include/AVLNode.h"
#include "../include/General.h"

AVLNode::AVLNode(ButtonSetting* b_setting, TextSetting* t_setting ,const int& index, const int& val): m_index(index), m_value(val) {
    button_setting = b_setting;
    text_setting = t_setting;
    m_text_position = m_position = m_point ={0, 0};
    setSize(60, 60);
    setValue(val);
    left = right = parent = nullptr;
    height = 1;

    color = button_setting->click_color;
    m_start_time = 0;
    m_duration = 0;
    percent = 1;
    is_reverse = 0;

    m_is_hovered = false;
    m_is_focus = false;
    m_is_pressed = false;
}
bool AVLNode::isFocus() const {
    return m_is_focus;
}
int AVLNode::getIndex() const {
    return m_index;
}
int AVLNode::getValue() const {
    return m_value;
}
void AVLNode::start(const float& duration, const Color& c) {
    m_duration = duration;
    percent = 0;
    color = c;
    m_start_time = GetTime();
    is_reverse = false;
}
void AVLNode::setPosition(const float& x, const float& y) {
    m_point = m_point - m_position + Vector2({x, y});
    m_text_position = m_text_position-m_position + Vector2({x,y});
    Controller::setPosition(x, y);
}
void AVLNode::handle(const Camera2D& camera) {
    m_is_hovered = CheckCollisionPointCircle(TransToGlobalPoint(camera, GetMousePosition()), m_position, m_size.x/2);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (m_is_hovered) m_is_focus = true;
        else m_is_focus = false;
    }
    Controller::handle();
    SlowMotion::handle();
    if (percent < 1) {
        if (m_duration) percent = (GetTime() - m_start_time)/m_duration;
        else percent = 1;
        if (percent > 1) percent = 1;
    }
}
void AVLNode::end_color(const float& duration) {
    is_reverse = true;
    m_duration = duration;
    m_start_time = GetTime();
    percent = 0;
}
void AVLNode::draw() {
    if (button_setting && text_setting) {
        Color bcolor = button_setting->normal_color;
        if (m_is_focus) bcolor = button_setting->click_color;
        else if (m_is_hovered) bcolor = button_setting->hover_color;
            
        DrawEllipse(m_position.x, m_position.y, m_size.x / 2, m_size.y / 2, bcolor);

        DrawTextEx(text_setting->font, to_string(m_value).c_str(), m_text_position, text_setting->font_size, text_setting->spacing, text_setting->color);
        Vector2 pos = m_position;
        pos.x += m_size.x/2;
        pos.y -= m_size.y/2 + text_setting->font_size/1.5;
        DrawTextEx(text_setting->font, to_string(height).c_str(), pos, text_setting->font_size/1.5, text_setting->spacing, text_setting->color);

        if (parent) {
            Vector2 pos = m_position, delta = pos-parent->getPosition();
            float length = abs(delta);
            if (length>m_size.x) {
                Vector2 u = delta/length, n = {u.y, -u.x};
                Vector2 radius = u*max(m_size.x, parent->getSize().x)/2;
                pos = pos - radius;
                Vector2 start_point = pos - u*10;
                Vector2 dis  = delta*percent;

                Color lcolor = button_setting->click_color;
                if (!is_reverse) {
                    if (length*(1-percent) > m_size.x) {
                        m_point = parent->getPosition()+radius+delta*percent;
                        lcolor = button_setting->click_color;
                    } else {
                        m_point = m_position-radius;
                        lcolor = color;
                        DrawRing(m_position, m_size.x / 2 - 4 , m_size.x/2, 0, 360, 30, color);
                    }
                } else {
                    if (length*percent > m_size.x) {
                        m_point = m_position+radius-delta*percent;
                    }
                    DrawRing(m_position, m_size.x / 2 - 4 , m_size.x/2, 0, 360, 30, button_setting->click_color);
                }

                DrawLineEx(parent->getPosition()+radius, m_point, 4, color);
                DrawLineEx(m_point, pos, 4, button_setting->click_color);

                DrawLineEx(start_point-5*n, pos, 2.5f, lcolor);
                DrawLineEx(start_point+5*n, pos, 2.5f, lcolor);

            } 
        }
        else {
            if (!is_reverse) {
                DrawRing(m_position, m_size.x / 2 - 4 , m_size.x/2, 0, 360, 30, color);
            } else {
                DrawRing(m_position, m_size.x / 2 - 4 , m_size.x/2, 0, 360, 30, button_setting->click_color);
            }
        }
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
