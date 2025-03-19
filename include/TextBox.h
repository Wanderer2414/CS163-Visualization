#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <cstddef>
#include <string>
#include "TextButton.h"
#include "../raylib/raylib.h"
class TextBox: public TextButton {
public:
    TextBox();
    bool                isFocus(),
                        isEnter();
    virtual void        init()                          override,
                        handle()                        override,
                        draw()                          override,
                        clear();
    ~TextBox();
private:
    unsigned int        m_cursor_index  = 0;
    bool                m_is_focus  = false,
                        m_is_enter  = false;
    virtual void        update_text() override;
    Rectangle           m_cursor_pos;
};

#endif //TEXTBOX_H