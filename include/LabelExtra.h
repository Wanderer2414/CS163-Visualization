#ifndef LabelEx_H
#define LabelEx_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"

class LabelEx: public Controller {
public:
    LabelEx(TextSetting* text_setting);
    enum Align {
        Left    = 1,
        Right   = 2,
        Middle  = 0,
        Top     = 4,
        Bottom  = 8,
        Center  = 0
    };
    TextSetting             *text_setting;
    bool                    empty() const;
    virtual void            draw()          override,
                            handle()        override,
                            setSize(const float& width, const float& height) override,
                            setPosition(const float& x, const float& y) override,
                            setText(const std::string& str),

                            setAlignText(const int& line, const int& align),
                            insert(const int& row, const int& col, const char& c),
                            insert(int& row, int& col, const string& c),
                            erase(const int& row, const int& col),
                            erase(const Vector2& start, const Vector2& end),
                            clear();
    float                   margin;
    float                   getAutoHeight() const;
    virtual void            update() override;
    ~LabelEx();
protected:
    vector<string>          m_text;
    virtual void            update_text(),
                            update_line(const int& line);
    vector<Rectangle>         m_text_position;
    vector<char>            align;
};

#endif