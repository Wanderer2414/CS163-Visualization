#include "../include/Clock.h"
#include "../include/General.h"

Clock::Clock() {

}
bool Clock::get() {
    int tmp = (int)(GetTime() / m_duration);
    if (tmp != old_time) {
        old_time = tmp;
        return true;
    }
    return false;
}

void Clock::setDuration(const float& duration) {
    m_duration = duration;
}
Clock::~Clock() {

}