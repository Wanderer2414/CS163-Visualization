#include "../include/Edge.h"
#include "../include/General.h"
#include <algorithm>
#include <cmath>
#include <string>

void DrawArc(const Vector2& start, const Vector2& end, const float& angular, const Color& color) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    Vector2 u = Vector2({-delta.y, delta.x})/abs(delta);
    float dis = abs(delta);
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;
    Vector2 middle_arc = center - u*radius;
    Vector2 arrow_start = middle_arc - delta/dis*7;
    Vector2 arrow_end = middle_arc + delta/dis*7;

    DrawLineEx(arrow_start-u*10, arrow_end, 3.0f, color);
    DrawLineEx(arrow_start+u*10, arrow_end, 3.0f, color);

    float start_angular = arctan(start-center);
    float end_angular = arctan(end-center);
    if (start_angular>end_angular) {
        start_angular -= 2*M_PI;
    }
    float delta_angular = (end_angular-start_angular)/30;
    Vector2 start_point = center;
    start_point.x += radius*cos(start_angular);
    start_point.y +=  radius*sin(start_angular);
    for (float i = start_angular+delta_angular; i<=end_angular; i+=delta_angular) {
        Vector2 end_point = center;
        end_point.x += radius*cos(i);
        end_point.y +=  radius*sin(i);
        DrawLineEx(start_point, end_point, 3.0f, color);
        start_point = end_point;
    }
}
void DrawText(TextSetting* text_setting, const Vector2& start, const Vector2& end, const float& angular, const string& text, const Color& color) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    float dis = abs(delta);
    Vector2 u = Vector2({-delta.y, delta.x})/dis;
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;
    Vector2 sz = MeasureTextEx(text_setting->font, text.c_str(), text_setting->font_size, text_setting->spacing);
    Vector2 center_text = center - u*(radius+sz.y/2 + 15);
    float rotate = to_degree(arctan(delta));
    DrawTextPro(text_setting->font, text.c_str(), center_text, sz/2, rotate, text_setting->font_size/1.2, text_setting->spacing, color);
}
Vector2 PointOnArc(const Vector2& start, const Vector2& end, const float& angular, const float& current_angular) {
    Vector2 middle = (start+end)/2;
    Vector2 delta = end - start;
    Vector2 u = Vector2({-delta.y, delta.x})/abs(delta);
    float dis = abs(delta);
    float side = dis/2;
    float radius = side/sin(angular/2);

    side = sqrt(radius*radius - side*side);
    Vector2 center =  middle + u*side;

    float start_angular = arctan(start-center);
    float end_angular = arctan(end-center);
    if (start_angular>end_angular) {
        start_angular -= 2*M_PI;
    }
    Vector2 ans = center;
    ans.x += radius*cos(start_angular+current_angular);
    ans.y +=  radius*sin(start_angular+current_angular);
    return ans;
}
Edge::Edge(Vertex* start, Vertex* end, TextSetting* t_setting) {
    text_setting = t_setting;
    m_start = start;
    m_end = end;
    weight = 1;
    m_point = end->getCenter();
    percent = 1;
    start_color = start->getColor();
    end_color = end->getColor();
    m_is_color_changed = false;
    m_is_direct = false;
    m_is_weight = false;
    is_reverse = false;
    m_speed = 10;
}
bool Edge::IsColorChange() const {
    return m_is_color_changed;
}
bool Edge::IsReverse() const {
    return is_reverse;
}
void Edge::setType(const bool& direct) {
    m_is_direct = direct;
}
void Edge::setSpeed(const float& speed) {
    if (speed) m_speed = 10/speed;
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
void Edge::draw() {
    cout << m_is_direct << endl;
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
            Vector2 sz = MeasureTextEx(text_setting->font, to_string(weight).c_str(), text_setting->font_size, text_setting->spacing);
            Vector2 pos = middle + u/abs(u)*(sz.y/2 + 5);
            float angular = to_degree(arctan(delta));
            DrawTextPro(text_setting->font, to_string(weight).c_str(), pos, sz/2, angular, text_setting->font_size, text_setting->spacing, start_color);
        }
    }
}
void Edge::handle() {
    cout << m_is_direct << endl;
    m_is_color_changed = false;
    Vector2 delta = m_end->getCenter() - m_start->getCenter();
    float dis = abs(delta);
    if (percent == 1) {
        if (dis < 200) {
            delta = delta/dis*((200-dis)/max(100.f, 200-dis)*10);
            m_start->add_acceleration(-1*delta);
            m_end->add_acceleration(delta);
        } 
        else if (dis > 400) {
            delta = delta/dis*log(dis - 400);
            m_start->add_acceleration(delta);
            m_end->add_acceleration(-1*delta);
        }
    }
    if (percent < 1) {
        float p_delta = 1 - percent;
        if (abs(p_delta)>0.1 && m_speed>=1) percent += p_delta/m_speed;
        else {
            percent += p_delta;
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
    is_reverse = reverse;
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