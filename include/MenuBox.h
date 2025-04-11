#ifndef MENUBOX_H
#define MENUBOX_H

#include "Controller.h"
#include "Label.h"
#include "SettingPackage.h"
#include "SunMode.h"
#include "TextButton.h"
#include "TextureButton.h"
#include "VerticalOpen.h"
#include "MenuTab.h"
#include "Global.h"

class MenuBox: public Controller, public VerticalOpen {
public:
    MenuBox(FormSetting& f_setting);
    int             getMode() const,
                    getWindowSizeIndex();
    FormSetting     &form_setting;
    bool            isHovered() const override,
                    isSizeChanged() const;
    virtual void    handle()    override,
                    draw()      override;

    virtual void    setSize(const float& width, const float& heigth) override,
                    setPosition(const float &width, const float &height) override;

    virtual void    setVisible(const bool& visible) override,
                    setMode(const int& mode),
                    setWindowSize(const int& index);
    
                
    Vector2         getPosition()   const override,
                    getSize()       const override;

    ~MenuBox();
protected:
    bool            m_is_hovered,
                    m_is_pressed,
                    is_size_changed,
                    m_is_visible;
    int             window_size_index;
    SunMode         sun;
    ButtonTab       window_size;
    
    Label           window_size_label, 
                    font_size_label, 
                    small_font_size_label, 
                    medium_font_size_label;
    TextButton      submit_button;
    vector<Controller*> children;
};

#endif