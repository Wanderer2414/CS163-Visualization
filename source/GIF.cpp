#include "../include/GIF.h"
GIF::GIF() {
    image_pointer = 0;
}
Vector2 GIF::getPosition() const {
    return Controller::getPosition();
};
void GIF::setSize(const float& x, const float& y) {
    Controller::setSize(x, y);
    for(int i = 0; i<image_list.size(); i++) {
        image_list[i].width = x;
        image_list[i].height = y;
    }
}
void GIF::setPosition(const float& x, const float& y) {
    Controller::setPosition(x, y);
}
void GIF::setDuration(const float& duration) {
    clock.setDuration(duration);
}
void GIF::handle() {
    Move::handle();
    if (clock.get()) image_pointer = (image_pointer + 1)%image_list.size();
}
void GIF::draw() {
    DrawTexture(image_list[image_pointer], m_position.x, m_position.y, WHITE);
}
void GIF::push(const string& str) {
    image_list.push_back(LoadTexture(str.c_str()));
    image_list.back().width = m_size.x;
    image_list.back().height = m_size.y;
}
GIF::~GIF() {
    for (int i = 0; i<image_list.size(); i++) UnloadTexture(image_list[i]);
    image_list.clear();
}