#ifndef VALUESCROL_H
#define VALUESCROL_H
#include "Controller.h"
#include "SettingPackage.h"
#include <new>
#include <string>
#include <vector>
using namespace std;
class ValueScroll: public Controller {
public:
    ValueScroll(TextSetting* text_setting);
    TextSetting             *text_setting                                                   ;
    bool                    empty() const                                                   ,
                            isChanged() const                                               ,
                            isHovered() const                                               ;

    int                     getChoiceIndex() const                                          ;
    virtual void            draw()          override                                        ,
                            handle()        override                                        , 

                            setSize(const float& width, const float& height) override       ,
                            setPosition(const float& x, const float& y) override            ,

                            setText(const std::string& str)                                 ,
                            select(const int& pointer)                                      ,
                            clear()                                                         ;

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
    vector<Vector2>         m_text_position                 ;
};
#endif