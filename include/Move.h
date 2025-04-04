#ifndef MOVE_H
#define MOVE_H

#include "Global.h"

class Move {
public:
    Move();
    int             getVertexDone() const,
                    size()          const;
    virtual void    handle();
    virtual void    setPosition(const float& x, const float& y),
                    add_vertex(const Vector2& point),
                    next(),
                    back();
    virtual Vector2 getPosition() const;
private:
    float           progress;
    int             pointer;
    std::vector<Vector2> m_vertices;
};

#endif