#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/General.h"
#include "../include/RaylibExtra.h"

Edge::Edge(Vertex* start, Vertex* end, const int& globalIndex, const int& localIndex, TextSetting* t_setting) {
    text_setting = t_setting;
    m_start = start;
    m_end = end;
    weight = 1;
    m_point = end->getCenter();
    percent = 1;
    start_color = start->getColor();
    end_color = end->getColor();
    m_global_index = globalIndex;
    m_local_index = localIndex;
    reverse = 0;
    m_is_color_changed = false;
    m_is_direct = false;
    m_is_weight = false;
    is_reverse = false;
    m_duration = 0.5;
    m_start_time = 0;
}
bool Edge::IsColorChange() const {
    return m_is_color_changed;
}
bool Edge::IsReverse() const {
    return is_reverse;
}
bool Edge::isHovered() const {
    return m_is_hovered;
}
bool Edge::isPressed() const {
    return m_is_pressed;
}
int Edge::getWeight() const {
    return weight;
}
int Edge::getLocalIndex() const {
    return m_local_index;
}
int Edge::getGlobalIndex() const {
    return m_global_index;
}
void Edge::setType(const bool& direct) {
    m_is_direct = direct;
}
void Edge::setDuration(const float& duration) {
    m_duration = duration;
}
void Edge::setColor(const Color& color) {
    start_color = end_color = color;
}
void Edge::setMode(const bool& is_weight) {
    m_is_weight = is_weight;
}
void Edge::setWeight(const int& w) {
    weight = w;
}
void Edge::complete() {
    percent = 1;
    if (!is_reverse) end_color = start_color;
    else start_color = end_color;
}
void Edge::draw() {
    if (m_is_direct) {
        DrawArc(m_start->getCenter(), m_point, M_PI/6*percent, start_color);
        DrawArc(m_point, m_end->getCenter(),  M_PI/6*(1-percent), end_color);
        if (m_is_weight) 
            DrawText(text_setting, m_start->getCenter(), m_end->getCenter(), M_PI_2/6, to_string(weight), start_color);
    }
    else {
        DrawLineEx(m_start->getCenter(), m_point, 3, start_color);
        DrawLineEx(m_point, m_end->getCenter(), 3, end_color);
        if (m_is_weight) {
            Vector2 delta = m_end->getCenter() - m_start->getCenter();
            Vector2 middle = (m_end->getCenter() + m_start->getCenter())/2;
            Vector2 u = {delta.y, -delta.x};
            Vector2 sz = MeasureText(text_setting, to_string(weight));
            Vector2 pos = middle + u/abs(u)*(sz.y/2 + 5);
            float angular = to_degree(arctan(delta));
            DrawTextPro(text_setting->font, to_string(weight).c_str(), pos, sz/2, angular, text_setting->font_size, text_setting->spacing, start_color);
        }
    }
}
void Edge::handle() {
    if (!m_is_direct) {
        m_is_hovered = CheckCollisionPointLine(GetMousePosition(), m_start->getCenter(), m_end->getCenter(), 15);
    }
    else m_is_hovered = CheckCollisionArc(GetMousePosition(), m_start->getCenter(), m_end->getCenter(), M_PI/6, 15);
    m_is_pressed = m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    m_is_color_changed = false;
    Vector2 delta = m_end->getCenter() - m_start->getCenter();
    float dis = abs(delta);
    if (percent == 1) {
        if (dis < 200) {
            delta = delta/dis*sqrt(200-dis)/3;
            m_start->add_acceleration(-1*delta);
            m_end->add_acceleration(delta);
        } 
        else if (dis > 400) {
            delta = delta/dis*sqrt(dis - 400)/3;
            m_start->add_acceleration(delta);
            m_end->add_acceleration(-1*delta);
        }
    }
    if (percent < 1) {
        if (m_duration) percent = (GetTime()-m_start_time)/m_duration;
        else percent = 1;
        if (percent >= 1) {
            percent = 1;
            m_is_color_changed = true;
            if (!is_reverse) end_color = start_color;
            else start_color = end_color;
        }
        if (!m_is_direct) {
            if (!is_reverse)
                m_point = m_start->getCenter() + delta*percent;
            else m_point = m_end->getCenter() - delta*percent;
        } else {
            if (!is_reverse) {
                m_point = PointOnArc(m_start->getCenter(), m_end->getCenter(), M_PI/6, M_PI/6*percent);
            }
            else 
            m_point = PointOnArc(m_start->getCenter(), m_end->getCenter(), M_PI/6, M_PI/6*(1-percent));
        }
    }
    else m_point = m_end->getPosition();
}

void Edge::start(const bool& reverse, const bool& transparent) {
    if (!transparent && m_start->getColor() == m_end->getColor()) return;
    is_reverse = reverse;
    m_start_time = GetTime();
    if (!reverse) {
        m_point = m_start->getCenter();
        start_color = m_start->getColor();
        if (!transparent) end_color = m_end->getColor();
        else end_color = {0,0,0,0};
        percent = 0;
    } else {
        m_point = m_end->getCenter();
        end_color = m_end->getColor();
        if (!transparent) start_color = m_start->getColor();
        else start_color = {0,0,0,0};
        percent = 0;
    }
}