#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Label.h"
#include "SettingPackage.h"
#include "TextButton.h"
#include "Global.h"

class TextBox: public Label {
public:
    TextBox(ButtonSetting* button_setting, TextSetting* text_setting);
    ButtonSetting       *button_setting;
    bool                isFocus(),
                        isEnter();
    virtual void        handle()                        override,
                        draw()                          override,
                        setPosition(const float& x, const float& y) override,
                        clear()                         override,
                        setText(const string& str)      override,
                        setFocus(const bool& focus);
    
    ~TextBox();
private:
    int                 m_fill_row = 0, m_fill_col = 0,
                        m_cursor_row  = 0, m_cursor_col = 0;
    bool                m_is_focus  = false,
                        m_is_enter  = false,
                        m_is_hovered= false,
                        m_is_pressed = false,
                        m_is_chosen = false;
    void                update_cursor();
    Rectangle           m_cursor_pos;
    vector<Rectangle>   m_choice;
};

#endif