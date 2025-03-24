#include "../include/VerticalOpen.h"
#include <algorithm>
VerticalOpen::VerticalOpen() {
    m_start = 0;
    m_duration = 1;
    m_is_end = false;
}
Vector2 VerticalOpen::getSize() const {
    return {0, 0};
}
Vector2 VerticalOpen::getPosition() const {
    return {0, 0};
}
Vector2 VerticalOpen::getEndSize() const {
    return {getPosition().x, m_start_height+m_delta};
}
void VerticalOpen::setDuration(const float& duration) {
    m_duration = duration;
    m_start = GetTime();
}
void VerticalOpen::open() {
    m_start = GetTime();
    m_start_height = 0;
    m_delta = getSize().y-m_start_height;
    m_is_end = false;
    setVisible(true);
}
void VerticalOpen::close() {
    m_start = GetTime();
    m_start_height = getSize().y;
    m_delta = -m_start_height;
    m_is_end = false;
    setVisible(true);
}
void VerticalOpen::handle() {
    float cur = GetTime();
    if (!m_is_end && cur > m_start && cur < m_start + m_duration) {
        float cur_height = m_start_height + m_delta*(cur-m_start)/m_duration;
        setPosition(getPosition().x, getPosition().y + getSize().y/2 - cur_height/2);
        setSize(getSize().x, cur_height);
    } else {
        float end = std::max(m_start_height+m_delta, m_start_height);
        setPosition(getPosition().x, getPosition().y + getSize().y/2 - end/2);
        setSize(getSize().x, end);
        if (m_delta<0) setVisible(false);
        m_is_end = true;
    }
}
void VerticalOpen::setVisible(const bool& visible) {

}
void VerticalOpen::setSize(const float& x, const float& y) {

}
void VerticalOpen::setPosition(const float& width, const float& height) {

}
VerticalOpen::~VerticalOpen() {

}