#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "Button.h"
class ProgressBar: public Button {
public:
    ProgressBar();
    float           getProgress() const;
    virtual void    draw()      override,
                    handle()    override,
                    setProgresss(const float& progress),
                    setSize(const float& x, const float& y)     override,
                    setPosition(const float& x, const float& y) override,
                    setThick(const float& thick),
                    setCursorSize(const float& radius),
                    setDelta(const float& delta);
    Color           uncomplete_color,
                    complete_color,
                    cursor_color;
    ~ProgressBar();
private:
    bool            m_press,
                    m_is_focus;
    float           m_progress,
                    m_thick,
                    m_radius,
                    m_delta;
    Vector2         m_point;
};
#endif