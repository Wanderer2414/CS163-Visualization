#include "../include/Controller.h"
#include "raylib.h"

Controller::Controller() {
    pIsPress = pIsFocus = pIsHovered = pIsRelease = false;
    pPosition = { 0, 0 };
    pSize = {0, 0};
}

Controller::~Controller() {

}

bool Controller::isHovered() const {
    return pIsHovered;
}
bool Controller::isFocus() const {
    return pIsFocus;
}
bool Controller::beforeHandle() {
    pIsPress = pIsRelease = false;
    return false;
}
bool Controller::handle() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pIsPress = true;
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) pIsRelease = true;
    return false;
}
bool Controller::afterHandle() {
    return false;
}
bool Controller::contains(const Vector2& position) const {
    return false;
}
bool Controller::setHover(const Vector2& position) {
    bool isHover = contains(position);
    return setHover(isHover);
}
bool Controller::setHover(const bool& hover) {
    if (hover != pIsHovered) {
        pIsHovered = hover;
        return true;
    }
    return false;
}
void Controller::draw() const {
    
}
void Controller::setPosition(const float& x, const float& y) {
    pPosition = { x,y };
}
void Controller::setPosition(const Vector2& position) {
    pPosition = position;
}
void Controller::setSize(const Vector2& size) {
    pSize = size;
}
void Controller::update() {
    
}
void Controller::setFocus(const bool& focus) {
    pIsFocus = focus;
}
Vector2 Controller::getSize() const {
    return {0 ,0};
}
Vector2 Controller::getPosition() const {
    return pPosition;
}