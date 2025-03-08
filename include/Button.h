#pragma once
#include "Controller.h"
#include "../raylib/raylib.h"
class Button: public Controller {
public:
    Button(Vector2* origin = 0);
    bool                isHovered(),
                        isPressed();
    virtual void        handle()        override;
    Color               m_normal_color  = WHITE,
                        m_hover_color   = {200, 200, 200, 255};
    ~Button();
protected:
    bool                m_is_hovered = false,
                        m_is_pressed = false;
};