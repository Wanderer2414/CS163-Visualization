#ifndef VERTEX_H
#define VERTEX_H

#include "Controller.h"
#include "Label.h"
#include "SettingPackage.h"
#include "DynamicColorCircle.h"

class Vertex: public Controller, public DynamicColorCircle {
    public:
        Vertex(FormSetting* form_setting, const int& index);
        FormSetting         *form_setting;
        bool                isPressed() const,
                            isHovered() const override,
                            isFocused() const;
        int                 getValue() const,
                            getIndex() const;
        float               getRadius() const;
        virtual void        draw()                                          override,
                            handle()                                        override,

                            add_acceleration(const Vector2& acceleration),
                            setVelocity(const Vector2& velocity),
                            setPosition(const float& x, const float& y)     override,
                            setSize(const float& width, const float& height) override,
    
                            setValue(const int& value),
                            setFixed(const bool& fixed),
                            setDragable(const bool& dragable);
                            
        virtual Vector2     getCenter() const override;
    
        Vector2             getVelocity() const;
        ~Vertex();
    private:
        bool                m_is_pressed,
                            m_is_focus,
                            m_is_hovered,
                            m_is_hold,
                            m_is_fixed,
                            m_dragable;
        int                 m_value,
                            m_index;
        Vector2             velocity,
                            m_acceleration,
                            m_text_position;
        string              m_text;


    };

#endif