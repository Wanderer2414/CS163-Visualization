#include "Button.h"
#include "Controller.h"
#include "RaylibExtra.h"

Button::Button(ButtonSetting* button_setting, TextSetting *text_setting) {
    buttonSetting   = button_setting;
    textSetting     = text_setting;
}

Button::~Button() {

}
bool Button::setHover(const bool& hover) {
    bool ans = Controller::setHover(hover);
    if (ans) {
        pColor = buttonSetting->normal_color;
        if (hover) pColor = buttonSetting->hover_color;
    }
    return ans;
}
bool Button::contains(const Vector2& position) const {
    return CheckCollisionPointRec(position, REC(getPosition(), getSize()));
}
bool Button::afterHandle() {
    bool is_changed = Controller::afterHandle();
    
    return is_changed;
}
void Button::draw() const {
    DrawRectangleRounded(buttonSetting, getPosition(), getSize(), pColor);
}