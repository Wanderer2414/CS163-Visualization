#include "../include/Controller.h"
#include "../raylib/raylib.h"
Controller::Controller() {
    m_position = {0, 0};
    m_size = {100, 50};
}
void Controller::setRoundness(const float& roundness) {
    m_roundness = roundness;
}
void Controller::setSegment(const int& segment) {
    m_segment = segment;
}
void Controller::setPosition(const float& x, const float& y) {
    m_position = {x,y};
}
void Controller::setSize(const float& width, const float& height) {
    m_size = {width, height};
}
Vector2 Controller::getSize() const {
    return m_size;
}
Vector2 Controller::getPosition() const {
    return m_position;
}
Controller::~Controller() {

}