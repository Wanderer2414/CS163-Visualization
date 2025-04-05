#ifndef FORM_H
#define FORM_H

#include "CommandLists.h"
#include "Console.h"
#include "Container.h"
#include "Controller.h"
#include "FileDropBox.h"
#include "Label.h"
#include "TabBox.h"
#include "TextureButton.h"
#include "ProgressBar.h"
#include "SettingPackage.h"
#include "TextBox.h"
#include "TextButton.h"
#include "MenuTab.h"
#include "Global.h"
#include "ValueScroll.h"

class Form : public CommandList {
public:
    Form(const int& index, FormSetting form_setting, const Vector2& window_size);
    FormSetting     form_setting;
    virtual int     run();
    virtual void    handle(),
                    draw();

    virtual void    add(const vector<string>& str),
                    remove(const std::string& str),
                    update(const std::string& old_value, const std::string& new_value),
                    search(const std::string& x);

    virtual string  RandomCreate() const,
                    RandomInsert() const,
                    RandomRemove() const,
                    RandomSearch() const,
                    RandomOldValue() const,
                    RandomNewValue() const;
    ~Form();
protected:
    bool            m_workspace_focus;
    std::vector<Controller*> children;
    Vector2         m_window_size;

    Label           create_label,
                    update_old_value_label,
                    update_new_value_label;
    
    TextBox         create_textbox,
                    insert_textbox,
                    remove_textbox,
                    update_textbox_choice,
                    update_textbox_value,
                    search_textbox;

    TextButton      track_hover;

    TextureButton   play_button,
                    back_button,
                    skip_button,
                    restart_button,
                    home_button,
                    small_skip_next_button,
                    small_skip_back_button;

    TextureButton   random_create,
                    random_insert,
                    random_remove,
                    random_search,
                    random_update_choice,
                    random_update_value;

    ValueScroll     speed_scroll;
    TabBox          option_box;

    TextButton      insert_button,
                    remove_button,
                    search_button,
                    update_button,
                    create_button;
    
    DropBox         m_drop_box;
    ButtonTab       buttonTab;

    Container       create_box,
                    insert_box,
                    remove_box,
                    search_box,
                    update_box;

    Console         console;
    Rectangle       m_workspace;
    ProgressBar     m_progress;
    Camera2D        m_camera;
    void main_box_show(), main_box_hide();
};

#endif //FORM_H