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
    virtual void    push_back(const std::string& log),
                    insert(const int& index, const std::string& log),
                    pop_back(),
                    handle() override,
                    draw() override,
                    setSize(const float& width, const float& y) override,
                    setText(const std::string& str) override,
                    setTextOrigin(const Vector2& origin),
                    setFillLine(const int& line);
    Color           m_color_line    = RED;
private:
    float           min_x           = 0,
                    min_y           = 0,
                    max_width       = 0,
                    max_height      = 0,
                    m_line_choice   = -1;
    virtual void    update_text() override;
    std::vector<std::string> m_list;
    Vector2     m_origin    = {0, 0},
                m_delta     = {0 , 0},
                m_fixed     = {0, 0};
    Clock       clock;
};