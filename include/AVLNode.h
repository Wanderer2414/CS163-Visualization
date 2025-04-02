#ifndef AVLNODE_H
#define AVLNODE_H

#include "Global.h"
#include "SlowMotion.h"
#include "TextButton.h"
class AVLNode : public TextButton, public SlowMotion {
public:
    AVLNode(const int& index, const int& val);
    virtual int         getIndex() const,
                        getValue() const,
                        getHeight() const;
    virtual void        draw() override,
        handle() override,
        setPosition(const float& x, const float& y) override,
        updateHeight();
        AVLNode         * left = nullptr,
                        * right = nullptr,
                        * parent = nullptr;
    virtual Vector2     getCenter() const,
                        getPosition() const override;
    void                setValue(int x);
    Color               anim_color;
    bool                is_animating = false;
    ~AVLNode();
private:
    int                 m_index = 0,
                        m_value = 0,
                        m_height = 1;
    Vector2             m_center;
};

#endif