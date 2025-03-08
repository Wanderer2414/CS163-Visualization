#include "Console.h"
#include "Controller.h"
#include "TextBox.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#include <string>
#include <vector>
#pragma once
class Form {
public:
    Form(const Vector2& window_size);
    virtual int     run()           ;
    virtual void    init()          ,
                    loadAsset()     ,
                    handle()        ,
                    draw()          ,
                    unloadAsset()   ,
                    close()         ;
    virtual void    add(const int& x)           ,
                    add(std::vector<int>& x)    ,
                    remove()                    ,
                    update(const int& x)        ,
                    search(const int& x)        ;
    void            setButtonRoundness(const float& roundness),
                    setBackgroundImage(const std::string& str),
                    setBackgroundColor(const Color&),
                    setFont(const Font& font),
                    setFontSize(const int& size),
                    PrintConsole(const std::string& log);
    ~Form();
protected:
    float           m_roundness = 0,
                    m_font_size = 30;
    int             m_segment   = 30;
    std::vector<Controller*> children;
    Texture2D       m_background_image;
    Color           m_background_color,
                    m_text_color;
    Font            m_font;
    Vector2         m_window_size;
    TextBox         input;
    TextButton      add_button;
    Console         console;
};