#include "Controller.h"
#include "raylib.h"
#include <vector>
#pragma once
class Form {
public:
    Form(Texture2D& background);
    virtual void    init()          = 0,
                    loadAsset()     = 0,
                    run()           = 0,
                    handle()        = 0,
                    draw()          = 0,
                    unloadAsset()   = 0,
                    close()         = 0;
    virtual void    add(const int& x)           = 0,
                    add(std::vector<int>& x)    = 0,
                    remove()                    = 0,
                    update(const int& x)        = 0,
                    search(const int& x)        = 0;
    void            setButtonRoundness(const float& roundness),
                    setBackgroundImage(Texture2D&),
                    setBackgroundColor(const Color&),
                    setFont(const Font& font),
                    setFontSize(const int& size);
    ~Form();
protected:
    float           m_roundness = 0,
                    m_font_size = 30;
    int             m_segment   = 30;
    std::vector<Controller*> children;
    Texture2D       &m_background_image;
    Color           m_background_color,
                    m_text_color;
    Font            m_font;

};