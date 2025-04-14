#ifndef EMPTY_BUTTON_H
#define EMPTY_BUTTON_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"

class EmptyButton: public Controller {
public:
    EmptyButton();
    bool                isHovered() const override,
                        isPressed() const;
    float               roundness;
    int                 segment;
    virtual void        handle()        override,
                        draw()          override;
    Color               normal_color, hover_color, click_color;

    ~EmptyButton();
protected:
    char                before_press;
    bool                m_is_hovered = false,
                        m_is_pressed = false;
};

#endif //BUTTON_H