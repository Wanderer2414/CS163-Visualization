#ifndef MENUBOX_H
#define MENUBOX_H

#include "ColorPointer.h"
#include "Controller.h"
#include "EmptyButton.h"
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
    MenuBox(FormSetting*& f_setting);
    int             getMode() const,
                    getWindowSizeIndex();
    FormSetting     *&form_setting;
    TextSetting     text_setting;
    bool            isHovered() const override,
                    isSizeChanged() const,
                    isSubmit();
    virtual void    handle()    override,
                    draw()      override;

    virtual void    setSize(const float& width, const float& heigth) override,
                    setPosition(const float &width, const float &height) override;

    virtual void    setVisible(const bool& visible) override,
                    setMode(const int& mode),
                    setWindowSize(const int& index),
                    open() override;
    
                
    Vector2         getPosition()   const override,
                    getSize()       const override;
    virtual void    update() override;
    ~MenuBox();
protected:
    bool            m_is_hovered,
                    m_is_pressed,
                    is_size_changed,
                    m_is_visible,
                    m_is_submit;

    int             window_size_index, color_pointer_index;
    SunMode         sun;

    ButtonTab       window_size, font_size, medium_font_size, small_font_size;
    
    Label           window_size_label, 
                    font_size_label, 
                    small_font_size_label, 
                    medium_font_size_label,

                    highlight_color_label1,
                    highlight_color_label2,
                    highlight_color_label3,
                    
                    button_color_label,
                    text_color_label;

    EmptyButton     hightlight_color_button1,
                    hightlight_color_button2,
                    hightlight_color_button3,
                    
                    button_color_button,
                    text_color_button;

    ColorPointer    color_pointer;

    TextButton      submit_button;
    vector<Controller*> children;
};

#endif