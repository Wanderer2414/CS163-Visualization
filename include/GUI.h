#ifndef GUI_H
#define GUI_H

#include "Global.h"
#include "SettingPackage.h"
#include "SlowMotion.h"
#include "TextButton.h"

class Node : public TextButton, public SlowMotion {
public:
    Node();
    virtual int         getValue() const;
    virtual void        draw() override,
                        handle() override;

    virtual void        setValue(const int& value);
    virtual Vector2     getPosition() const override;
    ~Node();
private:
};

#endif