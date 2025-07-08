#include "Controller.h"

Controller::Controller() {
    m_position = { 0, 0 };
    m_size = { 100, 50 };
}

bool Controller::isHovered() const {
    return false;
}
bool Controller::isFocus() const {
    return false;
}
void Controller::handle() {

}
void Controller::draw() {

}
void Controller::setPosition(const float& x, const float& y) {
    m_position = { x,y };
}
void Controller::setSize(const float& width, const float& height) {
    m_size = { width, height };
}
void Controller::update() {
    
}
Vector2 Controller::getSize() const {
    return m_size;
}
Vector2 Controller::getPosition() const {
    return m_position;
}
Controller::~Controller() {

}