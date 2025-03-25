#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"

class OptionBox: public Controller {
public:
    OptionBox(TextSetting* text_setting, const int& index, int& option_choice);
    TextSetting *text_setting;
    bool        isHovered() const override,
                isPressed() const,
                isChanged() const;
    virtual void    draw()      override,
                    handle()    override,
                    setText(const std::string& text);
protected:
    bool        m_is_hovered,
                m_is_pressed,
                m_is_changed;
    int&        option;
    int         m_index;
    std::string m_text;
};
#endif