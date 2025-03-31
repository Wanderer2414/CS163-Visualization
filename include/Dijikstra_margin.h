#ifndef DIJIKSTRA_MARGIN_H
#define DIJIKSTRA_MARGIN_H
#include "Vertex.h"
class Dijikstra_Margin {
public:
    Dijikstra_Margin(Vertex* vertex);
    int             getValue() const;
    virtual void    setValue(const int& value),
                    draw();
private:
    int             m_value;
    Vertex*         host;
};
#endif