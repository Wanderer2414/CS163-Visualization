#ifndef ZOOMIN_TRANSITION_H
#define ZOOMIN_TRANSITION_H
#include "Clock.h"
#include "Controller.h"
class ZoomInTransition:public Controller {
public:
    Controller* host;
    ZoomInTransition();
    float           getProgress() const;
    virtual void    handle() override,
                    draw() override,
                    start();
    Color color;
private:
    float percent = 1;
    Vector2 delta, start_pos, start_size, delta_size;
    Clock   clock;
};
#endif