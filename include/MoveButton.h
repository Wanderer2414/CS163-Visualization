#ifndef MOVEBUTTON_H
#define MOVEBUTTON_H

#include "Move.h"
#include "SettingPackage.h"
#include "TextButton.h"

class MoveButton: public TextButton, public Move {
public:
    MoveButton(ButtonSetting*, TextSetting*);
    virtual void    setPosition(const float& x, const float& y) override,
                    handle()    override;
    virtual Vector2 getPosition() const override;
};

#endif