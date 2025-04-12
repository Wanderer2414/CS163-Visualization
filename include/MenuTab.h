#ifndef MENUTAB_H
#define MENUTAB_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"

class ButtonTab : public Controller {
public:
    ButtonTab(ButtonSetting* button_setting, TextSetting* text_setting);
    ButtonSetting*      button_setting;
    TextSetting*        text_setting;
    bool                isHovered() const override,
                        isFocus()   const override,
                        isPressed() const;
    bool                isChanged();
    int                 GetSelection();
    virtual void        handle()        override,
                        draw()          override,
                        push_back(const std::string& name),
                        setSelection(const int& index),
                        update() override;
    ~ButtonTab();
protected:
    bool                m_isChanged = false,
                        m_is_focus;
    char                before_press;
    bool                m_is_hovered = false,
                        m_is_pressed = false,
                        m_is_showed = false;
    int                 m_hover_selection, 
                        m_selection;
    float               delta;
    std::vector<std::string>      Items;
    std::vector<float>            Length;
};

#endif