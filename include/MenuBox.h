#ifndef MENU_BOX_H
#define MENU_BOX_H
#include "../include/Controller.h"
#include "Colors.h"
#include "SettingPackage.h"
#include "VerticalOpen.h"
#include <vector>
using namespace std;
class MenuBox: public Controller, public VerticalOpen {
public:
    MenuBox();
    ButtonSetting   *button_setting;
    virtual void    init()      override,
                    handle()    override,
                    draw()      override;

    virtual void    setSize(const float& width, const float& heigth) override,
                    setPosition(const float &width, const float &height) override;

    virtual void    push_back(Controller* control),
                    remove(Controller* control),
                    setBackgroundColor(const Color& color),
                    setVisible(const bool& visible) override;
    
                
    Vector2         getPosition()   const override,
                    getSize()       const override;

    ~MenuBox();
protected:
    bool            m_is_hovered,
                    m_is_pressed,
                    m_is_visible;
    Color           background_color;
    vector<Controller*> children;
};
#endif