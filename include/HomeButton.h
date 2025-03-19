#ifndef HOMEBUTTON_H
#define HOMEBUTTON_H

#include "Button.h"

class HomeButton: public Button  {
public:
    HomeButton();
    virtual void        handle()        override,
                        draw()          override;
    ~HomeButton();
protected:
    Vector2             roofPoints[3];
    Rectangle           house;
};

#endif