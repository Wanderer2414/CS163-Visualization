#ifndef EDGE_H
#define EDGE_H
#include "Controller.h"
#include "Vertex.h"

class Edge:public Controller {
public:
    Edge(Vertex* start, Vertex* end);
    virtual void    draw()      override,
                    handle()    override;
private:
    Vertex* m_start, *m_end;
};
#endif