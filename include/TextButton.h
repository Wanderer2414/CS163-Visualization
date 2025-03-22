#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "Button.h"
#include "../raylib/raylib.h"
#include "SettingPackage.h"
#include <string>
class TextButton: public Button {
public:
    TextButton();
    TextSetting     *text_setting;
    virtual void    init()                                              override,
                    handle()                                            override,
                    draw()                                              override,
                    setText(const std::string& text);
    std::string     getText() const;
    ~TextButton();
protected:
    bool            is_new_setting;
    std::string     m_text;
    virtual void    update_text();
    Vector2         m_text_position;
};

#endif