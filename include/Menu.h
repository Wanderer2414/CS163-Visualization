#ifndef MENU_H
#define MENU_H

#include "Console.h"
#include "TextButton.h"
#include "TextureButton.h"
#include "../raylib/raylib.h"
#define main_button_width 350
#define main_button_height 100
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
                    HashTableForm,
                    SLLForm,
                    Back;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};

#endif //MENU_H