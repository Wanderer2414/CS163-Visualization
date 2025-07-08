#ifndef NOTATIONBOX_H
#define NOTATIONBOX_H

#include "Controller.h"
#include "Label.h"
#include "Global.h"
#include "SettingPackage.h"
#include "Vertex.h"

class NotationBox : public Controller {
public:
    NotationBox(FormSetting* form_setting);
    FormSetting         *form_setting;
    virtual void        handle()    override,
                        draw()      override,
                        setPosition(const float& x, const float& y)         override,
                        setSize(const float& widht, const float& height)    override;
    Vertex              *vertex;
    virtual void        show(),
                        hide();
    TextSetting         main_text_setting, other_text_setting;
private:
    bool                isVisible;
    Label               m_address, m_value, m_pos, m_index;
};

#endif