#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "Button.h"
#include "SettingPackage.h"
#include "Global.h"

class TextButton: public Button {
public:
    TextButton(ButtonSetting* b_setting, TextSetting* t_setting);
    ButtonSetting   *button_setting;
    TextSetting     *text_setting;
    virtual void    handle()                                            override,
                    draw()                                              override,
                    setPosition(const float& x, const float& y)         override,
                    setSize(const float& width, const float& height)    override,
                    setText(const std::string& text);
    std::string     getText() const;
    virtual void    update() override;
    ~TextButton();
protected:
    std::string     m_text;
    virtual void    update_text();
    Vector2         m_text_position;
};

#endif