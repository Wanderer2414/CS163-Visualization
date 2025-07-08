#ifndef AVLNODE_H
#define AVLNODE_H

#include "Controller.h"
#include "Global.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include "TextButton.h"

class AVLNode : public Controller, public SlowMotion {
public:
    AVLNode(ButtonSetting* b_setting, TextSetting* t_setting, const int& index, const int& val);
    ButtonSetting       *button_setting;
    TextSetting         *text_setting;
    bool                isFocus() const;
    virtual int         getIndex() const,
                        getValue() const;

    int                 height = 1;
                        
    virtual void        draw() override,
                        handle(const Camera2D& camera),

                        setPosition(const float& x, const float& y) override,
                        
                        start(const float& duration, const Color& color),
                        end_color(const float& duration);

    AVLNode             *left = nullptr,
                        *right = nullptr,
                        *parent = nullptr;
    virtual Vector2     getPosition() const override;
    void                setValue(int x);
    ~AVLNode();
private:
    bool                is_reverse,
                        m_is_hovered,
                        m_is_focus,
                        m_is_pressed;
    int                 m_index = 0,
                        m_value = 0;
    float               m_start_time, m_duration, percent;
    Vector2             m_text_position, m_point;
    Color               color;
};

#endif