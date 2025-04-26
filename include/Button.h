#ifndef BUTTON_H
#define BUTTON_H

#include "Controller.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include "Global.h"

class Button : public Controller {
public:
    Button();
    bool                isHovered() const override,
                        isPressed() const;
    virtual void        handle()        override,
                        draw()          override;
    ~Button();
protected:
    char                before_press;
    bool                m_is_hovered = false,
                        m_is_pressed = false;
};

#endif