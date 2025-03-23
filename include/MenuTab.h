#ifndef MENUTAB_H
#define MENUTAB_H

#include "Controller.h"
#include "../raylib/raylib.h"
#include "SettingPackage.h"
#include <vector>
#include <string>
class ButtonTab : public Controller {
public:
    ButtonTab();
    ButtonSetting* button_setting;
    bool                isHovered() const,
                        isPressed() const;
    virtual void        handle()        override;
    ~ButtonTab();
protected:
    char                before_press;
    bool                m_is_hovered = false,
                        m_is_pressed = false,
                        m_is_clicked = false;
    int                 Choose_val;
    std::vector<std::string>      store;
};

#endif // MENUTAB_H