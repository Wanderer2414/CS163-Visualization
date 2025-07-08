#include "Clock.h"
#include "General.h"

Clock::Clock() {

}
bool Clock::get() {
    if (!m_duration) return true;
    int tmp = (int)(GetTime() / m_duration);
    if (tmp != old_time) {
        old_time = tmp;
        return true;
    }
    return false;
}
float Clock::getDuration() const {
    return m_duration;
}
void Clock::setDuration(const float& duration) {
    m_duration = duration;
    if (m_duration) {
        old_time = (int)(GetTime()/m_duration);
    }
}
Clock::~Clock() {

}