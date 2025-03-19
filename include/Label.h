#ifndef LABEL_H
#define LABEL_H
#include "Controller.h"
#include <string>
class Label: public Controller {
public:
    Label();
    enum Align {
        Left    = 1,
        Right   = 2,
        Middle  = 0,
        Top     = 4,
        Bottom  = 8,
        Center  = 0
    };
    int                     getFontSize() const;
    virtual void            init()          override,
                            draw()          override,
                            handle()        override,
                            setSize(const float& width, const float& height) override,
    
                            setText(const std::string& str),
                            setFont(const Font&),
                            setFontSize(const float& size),
                            setTextColor(const Color& color),
                            setSpacing(const float& spacing),

                            setAlignText(const int& align);
    std::string             *getText();
    ~Label();
private:
    float                   m_font_size         = 30,
                            m_spacing           = 2;
    std::string             m_text;
    virtual void            update_text();
    Vector2                 m_text_position;
    Font                    m_font              ;
    Color                   m_text_color        = BLACK;

    int                     m_align;
};
#endif