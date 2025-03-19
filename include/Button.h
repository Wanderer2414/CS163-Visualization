#ifndef BUTTON_H
#define BUTTON_H

#include "Controller.h"
#include "../raylib/raylib.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
class Button: public Controller {
public:
    Button();
    ButtonSetting       *button_setting;
    bool                isHovered() const,
                        isPressed() const;
    virtual void        handle()        override;
    ~Button();
protected:
    bool                m_is_hovered = false,
                        m_is_pressed = false;
};

#endif //BUTTON_H