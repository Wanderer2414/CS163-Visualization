#include "../include/Arrow.h"
#include "../include/General.h"
using namespace GraphForm;
Arrow::Arrow(Node* start, Node *end) {
    m_start = start;
    m_end = end;
    m_duration = 0.5;
    old_color = {0,0,0,0};
    m_is_completed = true;
}
bool Arrow::isComplete() const {
    return m_is_completed;
}
void Arrow::draw() {
    DrawLineEx(m_start->getVertex(), m_point, 2.5f, m_start->getColor());
    DrawLineEx(m_point, m_end->getVertex(), 2.5f, old_color);    
}
void Arrow::handle() {
    float cur = GetTime();
    m_delta = m_end->getVertex() - m_start->getVertex();
    //Distance control
    float dis = abs(m_delta);
    if (dis>400 || dis < 200) {
        Vector2 pull;
        if (dis<200) {
            pull = (m_delta - m_delta/dis*200)*0.01;
        } else {
            pull = (m_delta-m_delta/dis*400)*0.01;
        }
        m_start->add_acceleration(pull);
        m_end->add_acceleration(-1*pull);
    } 
    //Color change
    if (m_start->getColor() != old_color) {
        if (m_is_completed) start();
    }
    if (m_is_completed && m_end->getColor() != old_color && m_end->isComplete()) {
        auto tmp = m_end;
        m_end = m_start;
        m_start = tmp;
    }
    //Fill color control
    if (!m_is_completed) {
        if (cur>m_start_time+m_duration) {
            m_end->setSlowColor(m_start->getColor(), m_start->getVertex());
            m_is_completed = true;
            old_color = m_start->getColor();
        } else m_point = m_start->getVertex() + m_delta*(cur-m_start_time)/m_duration;
    } else m_point = m_end->getVertex();
    
}
void Arrow::start() {
    m_start_time = GetTime();
    m_is_completed = false;
}
void Arrow::setStartPoint(Node* start) {
    m_start = start;
}
void Arrow::setEndPoint(Node* end) {
    m_end = end;
    m_point = end->getVertex();
}
void Arrow::setDuration(const float& duration) {
    m_duration = duration;
}
