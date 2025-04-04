#ifndef EDGE_H
#define EDGE_H

#define _USE_MATH_DEFINES
#include <cmath>

#include "Controller.h"
#include "Vertex.h"

void DrawArc(const Vector2& start, const Vector2& end, const float& angular, const Color& color);

class Edge:public Controller {
public:
    Edge(Vertex* start, Vertex* end, TextSetting* text_setting);
    TextSetting*    text_setting;
    bool            IsColorChange() const,
                    IsReverse() const,
                    isHovered() const override,
                    isPressed() const;
    int             getWeight() const;
    virtual void    draw()      override,
                    handle()    override,
                    setType(const bool& is_direct),
                    setWeight(const int& weight),
                    setMode(const bool& is_weight),
                    setColor(const Color& color),
                    setDuration(const float& duration),
                    complete(),
                    start(const bool& reverse, const bool& transparent = true);

    Vertex          *m_start, *m_end;
    Color           start_color, end_color;
private:
    bool            m_is_color_changed,
                    m_is_direct,
                    m_is_weight,
                    is_reverse,
                    m_is_hovered,
                    m_is_pressed;
    float           percent,
                    m_duration,
                    m_start_time;
    int             weight;
    Vector2         m_point;
};
#endif