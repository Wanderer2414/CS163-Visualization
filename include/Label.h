#ifndef LABEL_H
#define LABEL_H

#include "Controller.h"
#include "SettingPackage.h"
#include "Global.h"

class Label : public Controller {
public:
    Label(TextSetting* text_setting);
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
    int                     getLineSize(const int& line) const,
                            getLineCount()              const;
    virtual void            draw()          override,
                            handle()        override,
                            setSize(const float& width, const float& height) override,
                            setPosition(const float& x, const float& y) override,
                            setText(const std::string& str),

                            setAlignText(const int& align),
                            insert(const int& row, const int& col, const char& c),
                            insert(int& row, int& col, const string& c),
                            erase(const int& row, const int& col),
                            erase(const Vector2& start, const Vector2& end),
                            clear();
    Vector2                 getLinePosition(const int& index) const,
                            getCharPosition(const int& row, const int& col) const;
    std::string             getText()                                           const,
                            getText(const Vector2& start, const Vector2& end)   const;
    float                   margin;
    virtual void            update() override;
    ~Label();
protected:
    vector<string>          m_text;
    virtual void            update_text(),
                            update_line(const int& line);
    vector<Vector2>         m_text_position;

    int                     m_align;
};

#endif