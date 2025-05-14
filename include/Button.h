#ifndef BUTTON_H
#define BUTTON_H

#include "Controller.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include "Global.h"
#include "raylib.h"

class Button: public Controller {
public:
    Button(ButtonSetting* button_setting = &ButtonSetting::Default, TextSetting* text_setting = &TextSetting::Default);
    ~Button();
    ButtonSetting*  buttonSetting;
    TextSetting*    textSetting;
    virtual bool    contains(const Vector2& position) const override,
                    setHover(const bool& hover) override,
                    afterHandle()               override;
    virtual void    draw() const override;
private:
    Color           pColor;
};

#endif