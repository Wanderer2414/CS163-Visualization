#ifndef ARROW_H
#define ARROW_H
#include "Clock.h"
#include "Controller.h"
#include "GraphNode.h"

class Arrow: public Controller {
public:
    Arrow(GraphForm::Node* start, GraphForm::Node* end);
    bool                isComplete() const;
    virtual void        draw()      override,
                        handle()    override;

    virtual void        setStartPoint(GraphForm::Node* m_start),
                        setEndPoint(GraphForm::Node* m_end),
                        setDuration(const float& duration),
                        start();
private:
    bool                m_is_completed;
    float               m_duration,
                        m_start_time;
    Vector2             m_point,
                        m_delta;
    GraphForm::Node    *m_start,
                        *m_end;
    Color               old_color;
};
#endif