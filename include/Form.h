#ifndef FORM_H
#define FORM_H
#include "Console.h"
#include "Controller.h"
#include "TextBox.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#include <string>
#include <vector>
#include <deque>
#include <initializer_list>

#define Home_width  300
#define Home_height 30
#define Console_x 10
#define Console_y 50
#define TextInput_Width 150
#define Console_width 250
#define Console_height 300
#define Control_width 80
#define Control_height 30
class Form {
public:
    Form(const Vector2& window_size);
    virtual int     run()           ;
    float           PullCommand();
    virtual void    init()          ,
                    loadAsset()     ,
                    handle()        ,
                    draw()          ,
                    unloadAsset()   ,
                    close()         ,
                    add(const std::string& str) ,
                    add(std::vector<int>& x)    ,
                    remove()                    ,
                    update(const int& x)        ,
                    search(const int& x)        ,
                    FetchCommandQueue()         ;
    void            setButtonRoundness(const float& roundness),
                    setBackgroundImage(const std::string& str),
                    setBackgroundColor(const Color&),
                    setFont(const Font& font),
                    setFontSize(const int& size),
                    setSpeed(const float& duration),
                    PushCommand(const std::vector<float>& list);
    ~Form();
protected:
    float           m_roundness = 0,
                    m_font_size = 30,
                    m_speed;
    int             m_segment   = 30;
    std::vector<Controller*> children;
    Texture2D       m_background_image;
    Color           m_background_color,
                    m_text_color;
    Font            m_font;
    Vector2         m_window_size,
                    m_origin;
    TextBox         input_textbox;
    TextButton      add_button,
                    home_button;
    Console         console;
    Clock           m_clock;
    Rectangle       m_workspace;
    std::deque<float> CommandQueue;
};
#endif