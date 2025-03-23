#ifndef FORM_H
#define FORM_H
#include "CommandLists.h"
#include "Console.h"
#include "Controller.h"
#include "FileDropBox.h"
#include "Label.h"
#include "TabBox.h"
#include "TextureButton.h"
#include "ProgressBar.h"
#include "SettingPackage.h"
#include "TextBox.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#include "ValueScroll.h"
#include <string>
#include <vector>
#include <deque>

class Form : public CommandList {
public:
    Form(const Vector2& window_size);
    FormSetting     form_setting;
    virtual int     run();
    virtual void    init(),
                    handle(),
                    draw(),
                    close();

    virtual void    add(const vector<string>& str),
                    remove(const std::string& str),
                    update(const int& x),
                    search(const int& x);
    ~Form();
protected:
    bool            m_workspace_focus;
    std::vector<Controller*> children;
    Vector2         m_window_size;

    Label           setting_label,
                    create_label,
                    insert_label,
                    search_label,
                    update_label,
                    remove_label;
    
    TextBox         input_textbox,
                    remove_textbox;

    TextButton      track_hover;

    TextureButton   play_button,
                    back_button,
                    skip_button,
                    restart_button,
                    home_button;
    ValueScroll     speed_scroll;
    TabBox          option_box;

    TextButton      add_button,
                    remove_button,
                    create_button;
    
    DropBox         m_drop_box;

    Console         console;
    Rectangle       m_workspace;
    ProgressBar     m_progress;
    Camera2D        m_camera;
};
#endif