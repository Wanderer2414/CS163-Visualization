#ifndef MOVE_CONTAINTER_H
#define MOVE_CONTAINTER_H
#include "Container.h"
#include "Move.h"
#include "SettingPackage.h"
class MoveContainer: public Container, public Move {
public:
    MoveContainer(FormSetting* button_setting);
    virtual void    setPosition(const float& x, const float& y) override,
                    handle()                                    override;
    Vector2         getPosition() const                         override;
};
#endif