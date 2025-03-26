#ifndef EDGE_H
#define EDGE_H
#include "Controller.h"
#include "Vertex.h"

void DrawArc(const Vector2& start, const Vector2& end, const float& angular, const Color& color);

class Edge:public Controller {
public:
    Edge(Vertex* start, Vertex* end, TextSetting* text_setting);
    TextSetting*    text_setting;
    bool            IsColorChange() const,
                    IsReverse() const;
    virtual void    draw()      override,
                    handle()    override,
                    setType(const bool& is_direct),
                    setWeight(const int& weight),
                    setMode(const bool& is_weight),
                    setColor(const Color& color),
                    start(const bool& reverse, const bool& transparent = true);
    Vertex          *m_start, *m_end;
    Color           start_color, end_color;
private:
    bool            m_is_color_changed,
                    m_is_direct,
                    m_is_weight,
                    is_reverse;
    float           percent;
    int             weight;
    Vector2         m_point;
};
#endif