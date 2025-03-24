#ifndef MENU_BOX_H
#define MENU_BOX_H
#include "../include/Controller.h"
#include "SettingPackage.h"
#include "SunMode.h"
#include "TextureButton.h"
#include "VerticalOpen.h"
#include <vector>
using namespace std;
class MenuBox: public Controller, public VerticalOpen {
public:
    MenuBox();
    int             getMode() const;
    FormSetting     light_setting, dark_setting;
    bool            isHovered() const;
    virtual void    handle()    override,
                    draw()      override;

    virtual void    setSize(const float& width, const float& heigth) override,
                    setPosition(const float &width, const float &height) override;

    virtual void    setVisible(const bool& visible) override,
                    setMode(const int& mode);
    
                
    Vector2         getPosition()   const override,
                    getSize()       const override;

    ~MenuBox();
protected:
    bool            m_is_hovered,
                    m_is_pressed,
                    m_is_visible;
    SunMode         sun;
    vector<Controller*> children;
};
#endif