#ifndef CLOCK_H
#define CLOCK_H

#include "Global.h"

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

#endif //CLOCK_H