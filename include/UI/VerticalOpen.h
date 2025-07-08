#ifndef VERTICALOPEN_H
#define VERTICALOPEN_H

#include "Global.h"

class VerticalOpen {
public:
    VerticalOpen();
    bool                isEnd() const;
    virtual Vector2     getSize() const,
                        getPosition() const,
                        getEndSize() const;
    
    virtual void        handle(),
                        open(),
                        close();

    virtual void        setVisible(const bool& visible),
                        setSize(const float& x, const float& y),
                        setPosition(const float& width, const float& height),
                        setDuration(const float& duration);
    ~VerticalOpen();
private:
    bool                m_is_end;
    float               m_start_height,
                        m_start,
                        m_delta,
                        m_duration;
};

#endif