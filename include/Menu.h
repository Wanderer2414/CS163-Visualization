#pragma once
#include "../include/Form.h"
#include "Console.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#define main_button_width 150
#define main_button_height 50
#define button_count 2
class Menu: public Form {
public:
    Menu(const Vector2& windowSize);
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
private:
    TextButton      start;
    Vector2         m_windowSize;
};