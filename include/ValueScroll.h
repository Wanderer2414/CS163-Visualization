#ifndef VALUESCROLL_H
#define VALUESCROLL_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"

class ValueScroll: public Controller {
public:
    ValueScroll(TextSetting* text_setting);
    TextSetting             *text_setting                                                   ;
    bool                    empty() const                                                   ,
                            isChanged() const                                               ,
                            isHovered() const override                                      ;

    int                     getChoiceIndex() const                                          ;
    float                   getValue() const;
    virtual void            draw()          override                                        ,
                            handle()        override                                        , 

                            setSize(const float& width, const float& height) override       ,
                            setPosition(const float& x, const float& y) override            ,

                            push_back(const float& value, const std::string& str)           ,
                            select(const int& pointer)                                      ,
                            clear()                                                         ,
                            add_velocity(const float& velocity)                             ;

    std::string             getText()                                                       ,
                            getChoice()                                                     ;
    ~ValueScroll();
protected:
    bool                    m_is_hover                      ,
                            m_is_changed                    ;
    int                     m_index                         ;
    float                   pointer                         ,
                            velocity                        ;
    virtual void            update_text()                   ,
                            update_line(const int& line)    ;
    vector<float>           font_size                       ;
    vector<string>          m_text                          ;
    vector<float>           m_values;
    vector<Vector2>         m_text_position                 ;
};

#endif