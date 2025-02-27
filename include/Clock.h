#pragma once
#include "raylib.h"
#include <cstddef>
class Clock {
public:
    Clock();
    static size_t getTime();
    bool    isStarted(),
            isEnd();
    void    start(),
            setRange(const Vector2& start, const Vector2& end),
            setDuration(const float& duration);
    Vector2 get();
    ~Clock();
private:
    bool    m_is_started    = false,
            m_is_end        = false;
    float   m_duration      = 0;
    Vector2 m_start_point,
            m_delta;
};