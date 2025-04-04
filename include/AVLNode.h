#ifndef AVLNODE_H
#define AVLNODE_H

#include "Global.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include "TextButton.h"

class AVLNode : public Controller, public SlowMotion {
public:
    AVLNode(ButtonSetting* b_setting, TextSetting* t_setting, const int& index, const int& val);
    ButtonSetting       *button_setting;
    TextSetting         *text_setting;
    virtual int         getIndex() const,
                        getValue() const;

    int                 height = 1;
                        
    virtual void        draw() override,
                        handle() override,

                        setPosition(const float& x, const float& y) override;

    AVLNode             *left = nullptr,
                        *right = nullptr,
                        *parent = nullptr;
    virtual Vector2     getPosition() const override;
    void                setValue(int x);
    ~AVLNode();
private:
    int                 m_index = 0,
                        m_value = 0;
    Vector2             m_text_position;
};

#endif