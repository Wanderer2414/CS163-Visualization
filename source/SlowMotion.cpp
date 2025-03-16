#include "../include/SlowMotion.h"
#include "../include/General.h"

float SlowMotion::getDuration() const {
    return m_duration;
}
void SlowMotion::setSlowPosition(const float& x, const float& y) {
    if (!m_duration) {
        setPosition(x, y);
        return;
    }
    m_start_point = getPosition();
    m_delta = Vector2({x,y})-m_start_point;
    m_start_time = GetTime();
}
void SlowMotion::setDuration(const float& duration) {
    m_duration = duration;
}
void SlowMotion::handle() {
    if (m_duration && abs(m_delta)) {
        float cur = GetTime();
        if (cur<m_start_time+m_duration) {
            Vector2 pos = m_start_point+m_delta*(cur-m_start_time)/m_duration;
            setPosition(pos.x, pos.y);
        } else {
            m_duration = 0;
            Vector2 pos = m_start_point+m_delta;
            m_delta = {0, 0};
            setPosition(pos.x, pos.y);
        }
    }
}
void SlowMotion::setPosition(const float& x, const float& y) {
    
}
Vector2 SlowMotion::getPosition() const {
    return {0,0};
}
Vector2 SlowMotion::getEndPoint() const {
    return m_start_point+m_delta;
}