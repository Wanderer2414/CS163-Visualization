#ifndef SUNMODE_H
#define SUNMODE_H

#include "Controller.h"
#include "SettingPackage.h"
class SunMode: public Controller {
public:
    #define color_start YELLOW
    #define color_end LIGHTGRAY
    ButtonSetting   *light_button_setting, *dark_button_setting;
    SunMode(ButtonSetting* light_setting, ButtonSetting* dark_setting);
    float           getPercent() const;
    virtual void    draw()      override,
                    handle()    override;
    
    virtual void    setPosition(const float& x, const float& y) override,
                    setSize(const float& x, const float& y)     override,
                    setMode(const int& mode);
    ~SunMode();
private:
    bool            m_is_light,
                    m_is_pressed,
                    m_is_hovered;
    float           percent;
    unsigned char   percent_alpha;
    Vector2         m_point;
    Texture2D       sun_light_texture, sun_dark_texture;
};

#endif