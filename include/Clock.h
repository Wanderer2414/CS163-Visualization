#pragma once
#include "../raylib/raylib.h"
#include <cstddef>
class Clock {
public:
    Clock();
    bool        get();
    void        setDuration(const float& duration);
    ~Clock();
private:
    int         old_time        = 0;
    float       m_duration      = 0;
};