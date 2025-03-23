#ifndef MENUTAB_H
#define MENUTAB_H

#include "Controller.h"
#include "../include/raylib.h"
#include "SettingPackage.h"
#include <vector>
#include <string>
class ButtonTab : public Controller {
public:
    ButtonTab(ButtonSetting* button_setting, TextSetting* text_setting);
    ButtonSetting*      button_setting;
    TextSetting*        text_setting;
    bool                isHovered() const,
                        isPressed() const;
    bool                isChanged();
    int                 GetSelection();
    virtual void        handle()        override,
                        draw()          override,
                        push_back(const std::string& name),
                        setSelection(const int& index);
    ~ButtonTab();
protected:
    bool                m_isChanged = false;
    char                before_press;
    bool                m_is_hovered = false,
                        m_is_pressed = false,
                        m_is_showed = false;
    int                 m_hover_selection, 
                        m_selection;
    std::vector<std::string>      Items;
    std::vector<float>            Length;
};

#endif // MENUTAB_H
