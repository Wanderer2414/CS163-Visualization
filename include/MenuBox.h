#ifndef MENUBOX_H
#define MENUBOX_H

#include "Controller.h"
#include "SettingPackage.h"
#include "SunMode.h"
#include "TextureButton.h"
#include "VerticalOpen.h"
#include "MenuTab.h"
#include "Global.h"

class MenuBox: public Controller, public VerticalOpen {
public:
    MenuBox(FormSetting& f_setting);
    int             getMode() const;
    FormSetting     &form_setting;
    bool            isHovered() const;
    virtual void    handle()    override,
                    draw()      override;

    virtual void    setSize(const float& width, const float& heigth) override,
                    setPosition(const float &width, const float &height) override;

    virtual void    setVisible(const bool& visible) override,
                    setMode(const int& mode);
    
                
    Vector2         getPosition()   const override,
                    getSize()       const override,
                    getWindowSize();

    ~MenuBox();
protected:
    bool            m_is_hovered,
                    m_is_pressed,
                    m_is_visible;
    SunMode         sun;
    ButtonTab       window_size;
    TextButton      submit_button;
    vector<Controller*> children;
    const Vector2 window_sizes[3] = {Vector2({1366, 768}), Vector2({1820, 980}), Vector2({1024, 768})};
};

#endif