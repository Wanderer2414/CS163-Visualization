#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include "Button.h"
#include "TextButton.h"
class CircleButton: public TextButton {
public:
    CircleButton();
    virtual void        handle()        override,
                        draw()          override,
                        setRadius(const float& radius),
                        setSegment(const int& segment);
    ~CircleButton();
private:
    float               m_radius;
    int                 m_segment;
};

#endif //CIRCLEBUTTON_H