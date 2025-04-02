#ifndef COLORBOX_H
#define COLORBOX_H
#include "Controller.h"
class ColorBox: public Controller {
public:
    ColorBox(const Color& a, const Color& b);
    float               getPercent() const;
    virtual void        draw() override,
                        handle() override;

    virtual void        setSize(const float& width, const float& height) override,
                        setPosition(const float& x, const float& y) override,
                        setPercent(const float& percent);
    Color               getColor() const;
private:
    bool                m_is_hovered, m_is_focus;
    float               percent;
    Color               m_start, m_end;
    Rectangle           m_pointer;
};
#endif