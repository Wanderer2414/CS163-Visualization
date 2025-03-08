#pragma once
#include "../raylib/raylib.h"
class Controller {
public:
    Controller();
    void            setRoundness(const float& roundness),
                    setSegment(const int& segment);
    virtual void    init()      = 0,
                    handle()    = 0,
                    draw()      = 0,
                    setPosition(const float& x, const float& y),
                    setSize(const float& width, const float& height);
    Vector2         getSize() const,
                    getPosition() const;
    ~Controller();
protected:
    float           m_roundness = 0.1;
    int             m_segment   = 30;
    Vector2         m_position,
                    m_size;
};