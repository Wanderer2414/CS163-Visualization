#pragma once
#include "Button.h"
#include "../raylib/raylib.h"
#include <string>
class TextButton: public Button {
public:
    TextButton();
    virtual void    init()                                              override,
                    draw()                                              override,
                    setPosition(const float& x, const float& y)         override,
                    setSize(const float& width, const float& height)    override,
                    setText(const std::string& str),
                    setFont(const Font&),
                    setFontSize(const float& size),
                    setTextColor(const Color& color),
                    setSpacing(const float& spacing);
    std::string     *getText();
    ~TextButton();
protected:
    float           m_font_size         = 30,
                    m_spacing           = 2;
    std::string     m_text;
    virtual void    update_text();
    Vector2         m_text_position;
    Font            m_font              ;
    Color           m_text_color        = BLACK;
};