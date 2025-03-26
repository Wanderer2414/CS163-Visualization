#ifndef GUI_H
#define GUI_H

#include "Global.h"
#include "SlowMotion.h"
#include "TextButton.h"
namespace BST {
    class Node : public TextButton, public SlowMotion {
    public:

        Node(const int& index, const int& val);
        virtual int         getIndex() const,
                            getValue() const;
        virtual void        draw() override,
                            handle() override,
                            setPosition(const float& x, const float& y)     override;
        Node                *left = 0,
                            *right = 0;
        virtual Vector2     getCenter() const,
                            getPosition() const override;
        ~Node();
    private:
        int                 m_index = 0,
                            m_value = 0;
        Vector2             m_center;
    };
}

#endif