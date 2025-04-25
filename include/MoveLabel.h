#ifndef MOVELABEL_H
#define MOVELABEL_H

#include "Label.h"
#include "Move.h"
#include "SettingPackage.h"

class MoveLabel: public Label, public Move {
public:
    MoveLabel(TextSetting* text_setting);
    virtual void    setPosition(const float& x, const float& y),
                    handle();
    Vector2         getPosition() const;
};

#endif