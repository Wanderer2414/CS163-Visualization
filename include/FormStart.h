#ifndef FORMSTART_H
#define FORMSTART_H

#include "Console.h"
#include "MenuBox.h"
#include "SettingPackage.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#define main_button_width 400
#define main_button_height 60
#define button_count 3
class MenuStart {
public:
    MenuStart(const Vector2& windowSize);
    int             getMode() const;
    virtual int     run();
    virtual void    init(),
                    handle(),
                    draw(),
                    close();
                    
    virtual void    setMode(const int& mode);
    FormSetting     form_setting;
private:
    int             old_mode = -1;
    TextButton      Start, Setting, Exit, AboutUs;
    MenuBox         setting_box;
    std::vector<Controller*> children;
    Vector2         m_windowSize;
};

#endif //FORMSTART_H