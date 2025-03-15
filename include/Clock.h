#pragma once
#include "../raylib/raylib.h"
#include <cstddef>
class Clock {
public:
    Clock();
    bool        get();
    float       getDuration() const;
    void        setDuration(const float& duration);
    ~Clock();
private:
    int         old_time        = 0;
    float       m_duration      = 0;
};