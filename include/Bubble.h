#ifndef BUBBLE_H
#define BUBBLE_H

#include "Controller.h"

class Bubble: public Controller {
public:
    Bubble();
    float               getRadius() const;
    virtual void        handle() override,
                        draw()   override;
    
    virtual void        setRadius(const float& radius),
                        setColor(const Color& color);
    ~Bubble();
private:
    float               m_radius;
    Color               m_color_a, m_color_b;
};

#endif