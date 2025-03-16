#pragma once
#include "Clock.h"
#include "Controller.h"
#include "TextButton.h"
#include <string>
#include <vector>
class Console:public TextButton {
public:
    Console();
    int             getFillLine() const;
    virtual void    InsertNextSubCommand(const std::string& log),
                    InsertNextMainCommand(const std::string& log),
                    PushBackMainCommand(const std::string& log),
                    PushBackSubCommand(const std::string& log),
                    GotoCommandLine(const float& progress),
                    goUp(),
                    goDown(),
                    clear(),
                    handle()                                    override,
                    draw()                                      override,
                    setSize(const float& width, const float& y) override,
                    setText(const std::string& str)             override,
                    setTextOrigin(const Vector2& origin),
                    setEnable(const bool& enable);
    Color           m_color_line    = RED;
    ~Console();
private:
    bool            m_is_enable;
    float           min_x           = 0,
                    min_y           = 0,
                    max_width       = 0,
                    max_height      = 0;
    int             line_cursor     = 0,
                    main_line_cursor= 0,
                    current_add     = 0;
    void            BeforeGoUp(),
                    BeforeGoDown(),
                    update_tail();
    virtual void    update_text() override;
    std::vector<std::string>    m_list;
    std::vector<bool>           temporary;
    Vector2     m_origin    = {0, 0},
                m_delta     = {0 , 0},
                m_fixed     = {0, 0};
    Clock       clock;
};