#ifndef LabelEx_H
#define LabelEx_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"
#include "Clock.h"

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
                            clear();
    float                   margin;
    float                   getAutoHeight() const;
    int                     getTextSize()       const,
                            getCurrentTextSize() const;
    virtual void            update() override,
                            skip(),
                            Push();
    Vector2                 getCursorPosition() const;
    ~LabelEx();
protected:
    Sound                   wave1, wave2, wave3;
    Clock                   clock;
    bool                    canReset, is_push;
    int                     size = 0, total_text_length;
    string                  dummy_string;
    vector<vector<string>>  m_text;
    virtual void            update_text(),
                            update_line(const int& line);
    vector<vector<Vector2>> m_text_position;
    vector<vector<float>>   text_size;
    vector<vector<float>>   spacing;
    vector<vector<int>>     number_word;
    vector<char>            align;
    Vector2                 cursor_position;
};

#endif