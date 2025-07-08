#ifndef MENU_H
#define MENU_H

#include "Console.h"
#include "MoveButton.h"
#include "MoveTexture.h"
#include "SettingPackage.h"
#include "TextButton.h"
#include "TextureButton.h"
#include "Global.h"
#include "ZoomInTransition.h"
extern const vector<string> form_name;
class Menu {
public:
    Menu(FormSetting form_setting, const Vector2& windowSize) ;
    virtual int     run()           ;
    
    virtual void    handle()        ,
                    draw()          ;
    FormSetting     form_setting;
private:
    int             return_value;
    vector<MoveButton> form_button;      
    MoveTexture     Back,
                    MenuDSA;
    ZoomInTransition zoom;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};

#endif