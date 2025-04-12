#include "../include/SlowMotion.h"
#include "../include/General.h"

SlowMotion::SlowMotion() {
    is_end = true;
    m_duration = 0.5;
}
float SlowMotion::getDuration() const {
    return m_duration;
}

bool SlowMotion::isComplete() const {
    return is_end;
}
void SlowMotion::setSlowPosition(const float& x, const float& y) {
    if (!m_duration) {
        setPosition(x, y);
        return;
    }
    m_start_point = getPosition();
    is_end = false;
    m_delta = Vector2({ x,y }) - m_start_point;
    m_start_time = GetTime();
    
}
void SlowMotion::setDuration(const float& duration) {
    m_duration = duration;
}
void SlowMotion::handle() {
	cout << "HaIn" << m_duration<< endl;
    if (!is_end) {
        float cur = GetTime();
        if (cur < m_start_time + m_duration) {
            Vector2 pos = m_start_point + m_delta * (cur - m_start_time) / m_duration;
            setPosition(pos.x, pos.y);
        }
        else {
            is_end = true;
            Vector2 pos = m_start_point + m_delta;
            setPosition(pos.x, pos.y);
        }
    }
	cout << "HaOut" << endl;
}
void SlowMotion::setPosition(const float& x, const float& y) {

}
Vector2 SlowMotion::getPosition() const {
    return { 0,0 };
}
Vector2 SlowMotion::getEndPoint() const {
    if (!is_end) return m_start_point + m_delta;
    else return getPosition();
}