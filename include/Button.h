#pragma once
#include "Controller.h"
#include "raylib.h"
class Button: public Controller {
public:
    Button();
    bool                isHovered(),
                        isPressed();
    Color               m_normal_color,
                        m_hover_color;
    ~Button();
protected:
    bool                m_is_hovered = false,
                        m_is_pressed = false;
};