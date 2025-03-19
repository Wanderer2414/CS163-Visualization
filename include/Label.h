#ifndef LABEL_H
#define LABEL_H
#include "Controller.h"
#include "SettingPackage.h"
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
    TextSetting             *text_setting;
    virtual void            init()          override,
                            draw()          override,
                            handle()        override,
                            setSize(const float& width, const float& height) override,
    
                            setText(const std::string& str),

                            setAlignText(const int& align);
    std::string             *getText();
    ~Label();
private:
    std::string             m_text;
    virtual void            update_text();
    Vector2                 m_text_position;

    int                     m_align;
};
#endif