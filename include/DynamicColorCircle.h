#ifndef DYNAMIC_COLOR_CICLE_H
#define DYNAMIC_COLOR_CICLE_H
#include "../raylib/raylib.h"
class DynamicColorCircle {
public:
    DynamicColorCircle();
    bool                IsColorChange()                     const;
    virtual void        setRadius(const float& radius),
                        handle(),
                        draw(),
                        start(const float& start_angle, const Color& start, const Color& end),
                        setColor(const Color& color);
    Color               getColor() const;
    virtual Vector2     getCenter() const;
private:
    bool                m_is_color_change;
    float               m_radius,
                        percent,
                        m_scale,
                        start_angle,
                        delta_angle;
    Color               start_color,
                        end_color;
};
#endif