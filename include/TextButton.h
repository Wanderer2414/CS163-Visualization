#pragma once
#include "Button.h"
#include "raylib.h"
#include <string>
class TextButton: public Button {
public:
    TextButton();
    virtual void    draw()                                              override,
                    handle()                                            override,
                    setPosition(const float& x, const float& y)         override,
                    setSize(const float& width, const float& height)    override,
                    setText(const std::string& str),
                    setFont(const Font&),
                    setFontSize(const float& size),
                    setTextColor(const Color& color);
    ~TextButton();
private:
    float           m_font_size;
    std::string     m_text;
    Rectangle       m_text_bound;
    Font            m_font;
    Color           m_text_color;
};