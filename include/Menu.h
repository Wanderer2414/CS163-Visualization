#pragma once
#include "Console.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#define main_button_width 100
#define main_button_height 350
#define button_count 3
class Menu {
public:
    Menu(const Vector2& windowSize) ;
    virtual int     run()           ;
    
    virtual void    init()          ,
                    handle()        ,
                    draw()          ,
                    close()         ;
private:
    TextButton      BSTForm,
                    GraphForm,
                    StringTree,
                    AVLTreeForm,
                    SLLForm,
                    HashTableForm;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};