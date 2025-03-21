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
    ValueScroll();
    TextSetting             *text_setting;
    bool                    empty() const,
                            isChanged() const,
                            isHovered() const;
    int                     getChoiceIndex() const;
    virtual void            init()          override,
                            draw()          override,
                            handle()        override,
                            setSize(const float& width, const float& height) override,
                            setPosition(const float& x, const float& height) override,
                            setText(const std::string& str),
                            clear();
    std::string             getText(),
                            getChoice();
    ~ValueScroll();
protected:
    bool                    m_is_hover,
                            m_is_changed;
    vector<string>          m_text;
    float                   pointer;
    virtual void            update_text(),
                            update_line(const int& line);
    vector<Vector2>         m_text_position;
    vector<float>           font_size;
};
#endif