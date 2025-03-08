#ifndef GUI_H
#define GUI_H
#include "../raylib/raylib.h"
#include "TextButton.h"
class Node: public TextButton {
public:
    Node(const int& index, Vector2* origin, const int& val);
    bool                isVisible = false;
    int                 getIndex() const,
                        getValue() const;
    virtual void        draw() override,
                        handle() override,
                        setSlowPosition(const float& x, const float& y, const float& duration),
                        setPosition(const float& x, const float& y);
    Node                *left   = 0,
                        *right  = 0,
                        *next   = 0;
    Vector2             getCenter() const;
    ~Node();
private:
    int                 m_index = 0,
                        m_value = 0;
    float               m_duration = 0,
                        m_start_time = 0;
    Vector2             m_delta,
                        m_start_point,
                        m_center;
};
#endif