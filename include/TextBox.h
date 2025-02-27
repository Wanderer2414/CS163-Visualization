#pragma once
#include "Controller.h"
#include <string>
#include "raylib.h"
class TextBox: public Controller {
public:
    TextBox();
    std::string         *getString();
    virtual void        handle()                        override,
                        draw()                          override,
                        setFont(const Font&),
                        setFontSize(const float& size);
    ~TextBox();
private:
    float               m_font_size;
    std::string         m_text;
    Font                m_font;
};