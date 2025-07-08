#include "MoveButton.h"

MoveButton::MoveButton(ButtonSetting* button_setting, TextSetting* text_setting):
    TextButton(button_setting, text_setting) {
        
    }
void MoveButton::setPosition(const float& x, const float& y) {
    TextButton::setPosition(x, y);
}
void MoveButton::handle() {
    Move::handle();
    TextButton::handle();
}
Vector2 MoveButton::getPosition() const {
    return TextButton::getPosition();
}