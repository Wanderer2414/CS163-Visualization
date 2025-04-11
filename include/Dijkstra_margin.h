#ifndef DIJIKSTRA_MARGIN_H
#define DIJIKSTRA_MARGIN_H

#include "Vertex.h"

class Dijkstra_Margin {
public:
    Dijkstra_Margin(Vertex* vertex);
    float           getValue() const;
    virtual void    setValue(const float& value),
                    draw();
private:
    float           m_value;
    Vertex*         host;
};

#endif