#ifndef FORMSTART_H
#define FORMSTART_H

#include "Console.h"
#include "Label.h"
#include "MenuBox.h"
#include "MoveButton.h"
#include "SettingPackage.h"
#include "TextButton.h"
#include "Global.h"

class MenuStart {
public:
    MenuStart(FormSetting form_setting, const Vector2& windowSize);
    int             getMode() const;
    virtual int     run();
    virtual void    handle(),
                    draw();
                    
    virtual void    setMode(const int& mode),
                    setSizeIndex(const int& index);
    FormSetting     form_setting;
    int             getWindowSizeIndex();
private:
    int             old_mode = -1;
    MoveButton      Start, Setting, Exit, AboutUs;
    MenuBox         setting_box;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};

#endif