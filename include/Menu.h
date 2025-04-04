#ifndef MENU_H
#define MENU_H

#include "Console.h"
#include "SettingPackage.h"
#include "TextButton.h"
#include "TextureButton.h"
#include "Global.h"

#define main_button_width 350
#define main_button_height 100
#define button_count 3

class Menu {
public:
    Menu(FormSetting form_setting, const Vector2& windowSize) ;
    virtual int     run()           ;
    
    virtual void    handle()        ,
                    draw()          ;
    FormSetting     form_setting;
private:
    TextButton      BSTForm,
                    GraphForm,
                    HashTableForm,
                    SLLForm;
    TextureButton   Back,
                    MenuDSA;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};

#endif //MENU_H