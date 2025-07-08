#include "MoveLabel.h"

MoveLabel::MoveLabel(TextSetting* text_setting):Label(text_setting) {

}
void MoveLabel::setPosition(const float& x, const float& y) {
    Label::setPosition(x, y);
}
void MoveLabel::handle() {
    Move::handle();
    Label::handle();
}
Vector2 MoveLabel::getPosition() const{
    return Label::getPosition();
}