#ifndef TABBOX_H
#define TABBOX_H
#include "Controller.h"
#include "SettingPackage.h"
#include "Move.h"
#include <string>
#include <vector>
using namespace std;

class TabBox: public Controller, public Move {
public:
    TabBox();
    FormSetting     *form_setting;
    bool            isVisible() const,
                    isHovered() const,
                    isPressed() const;
    virtual void    init()      override,    
                    draw()      override,
                    handle()    override,
                    close()     override;

    virtual void    setVisible(const bool& visible),
                    setPosition(const float& x, const float& y) override,
                    push_back(const int& index, Controller* controller),
                    setText(const int& index, const string& name),
                    clear();

    Vector2         getPosition() const override;
private:
    bool            is_visible,
                    pos_changed,
                    m_is_hovered,
                    m_is_pressed;
    int             tab_index = 0,
                    tab_hover = 0;
    float           margin = 5;
    Vector2         max_size;
    
    vector<vector<Controller*>> tabs;
    vector<string>  m_name;
    vector<float> name_widths;
};

#endif