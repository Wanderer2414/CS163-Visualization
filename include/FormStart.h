#ifndef FORMSTART_H
#define FORMSTART_H

#include "Console.h"
#include "GIF.h"
#include "ImageTab.h"
#include "Label.h"
#include "MenuBox.h"
#include "MoveButton.h"
#include "MoveLabel.h"
#include "SettingPackage.h"
#include "TextButton.h"
#include "Global.h"

class MenuStart {
public:
    MenuStart(FormSetting* form_setting, const Vector2& windowSize, const std::vector<Vector2>& windowSizes);
    int             getMode() const;
    virtual int     run();
    virtual void    handle(),
                    draw();
                    
    virtual void    setMode(const int& mode),
                    setSizeIndex(const int& index);
    FormSetting     *form_setting;
    int             getWindowSizeIndex();
private:
    int             old_mode = -1, return_value;
    TextSetting     title_setting;
    MoveLabel       Title;
    MoveButton      Start, Setting, Exit, AboutUs;
    MenuBox         setting_box;
    ImageTab        image_list;
    GIF             LightAVL, LightHashTable, LightSLL, LightGraph;
    GIF             DarkAVL, DarkHashTable, DarkSLL, DarkGraph;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
    void            update(), update_gif();
};

#endif