#include "../include/MoveContainer.h"

MoveContainer::MoveContainer(FormSetting* form_setting): Container(form_setting) {

}
void MoveContainer::setPosition(const float& x, const float& y) {
    Container::setPosition(x, y);
}
void MoveContainer::handle() {
    Container::handle();
    Move::handle();
}
Vector2 MoveContainer::getPosition() const {
    return Container::getPosition();
}