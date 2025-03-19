#ifndef BUTTON_H
#define BUTTON_H

#include "Controller.h"
#include "../raylib/raylib.h"
class Button: public Controller {
public:
    Button();
    bool                isHovered(),
                        isPressed();
    virtual void        handle()        override;
    Color               m_normal_color  = WHITE,
                        m_hover_color   = {200, 200, 200, 255};
    virtual ~Button() = default;
protected:
    bool                m_is_hovered = false,
                        m_is_pressed = false;
};

#endif //BUTTON_H