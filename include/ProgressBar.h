#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "Controller.h"
class ProgressBar : public Controller {
public:
    ProgressBar();
    bool            isFocus(),
                    isChanged();
    float           getProgress() const;
    virtual void    init()      override,
                    draw()      override,
                    handle()    override,
                    setProgresss(const float& progress),
                    setSize(const float& x, const float& y)     override,
                    setPosition(const float& x, const float& y) override,
                    setThick(const float& thick),
                    setCursorSize(const float& radius),
                    setSplitCount(const int& count),
                    setSplitSize(const float& size),
                    setSplitThick(const float& thick);
    Color           uncomplete_color,
                    complete_color,
                    cursor_color;
    ~ProgressBar();
private:
    bool            m_is_focus,
                    m_is_changed;
    int             m_split_count;
    float           m_progress,
                    m_thick,
                    m_radius,
                    m_split_size,
                    m_split_thick;
    Vector2         m_point;
};
#endif