#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../raylib/raylib.h"
class Controller {
public:
    Controller();
    void            setRoundness(const float& roundness),
                    setSegment(const int& segment);
    virtual void    init()      ,
                    handle()    ,
                    draw()      ,
                    setPosition(const float& x, const float& y),
                    setSize(const float& width, const float& height);
    virtual Vector2 getSize() const,
                    getPosition() const;
    ~Controller();
protected:
    float           m_roundness = 0.1;
    int             m_segment   = 30;
    Vector2         m_position,
                    m_size;
};

#endif //CONTROLLER_H