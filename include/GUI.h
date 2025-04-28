#ifndef GUI_H
#define GUI_H

#include "Global.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include "TextButton.h"

class Node : public TextButton, public SlowMotion {
public:
    Node(ButtonSetting* button_setting, TextSetting* text_setting);
    virtual void        draw() override,
                        handle() override;
    virtual Vector2     getPosition() const override;
    ~Node();
private:
};

#endif