#include "../include/Clock.h"
#include "../include/General.h"

Clock::Clock() {

}
bool Clock::get() {
    if (int tmp = (int)(GetTime()/m_duration); tmp!=old_time) {
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