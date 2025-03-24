#ifndef SLOWMOTION_H
#define SLOWMOTION_H
#include "../raylib/raylib.h"

class SlowMotion {
public:
    SlowMotion();
    bool            isComplete() const;
    float           getDuration() const;
    virtual void    setSlowPosition(const float& x, const float& y),
                    setDuration(const float& duration),
                    setPosition(const float& x, const float& y),
                    handle();
    virtual Vector2 getPosition() const,
                    getEndPoint() const;
private:
    bool                is_end;
    float               m_duration = 0,
                        m_start_time = 0,
                        m_speed = 0;
    Vector2             m_delta,
                        m_start_point;
};

#endif