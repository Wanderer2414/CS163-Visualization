#ifndef TABBOX_H
#define TABBOX_H
#include "Controller.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include <string>
#include <vector>
using namespace std;

class TabBox: public Controller, public SlowMotion {
public:
    TabBox();
    ButtonSetting   button_setting;
    TextSetting     text_setting;
    bool            isVisible() const,
                    isHovered() const,
                    isPressed() const;
    virtual void    init()      override,    
                    draw()      override,
                    handle()    override;

    virtual void    setVisible(const bool& visible),
                    setPosition(const float& x, const float& y) override;
    
    Vector2         getPosition() const override;
    vector<vector<Controller*>> tabs;
    vector<std::string>         name;
private:
    bool            is_visible,
                    pos_changed,
                    m_is_hovered,
                    m_is_pressed;
    int             tab_index = 0,
                    tab_hover = 0;
};

#endif