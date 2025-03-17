#ifndef FORM_H
#define FORM_H
#include "CommandLists.h"
#include "Console.h"
#include "Controller.h"
#include "FileDropBox.h"
#include "ProgressBar.h"
#include "TextBox.h"
#include "TextButton.h"
#include "../raylib/raylib.h"
#include <string>
#include <vector>
#include <deque>
#include <initializer_list>

#define Home_width  300
#define Home_height 30
#define Console_x 10
#define Console_y 50
#define TextInput_Width 150
#define Console_width 250
#define Console_height 300
#define Control_width 80
#define Control_height 30

class Form : public CommandList {
public:
    Form(const Vector2& window_size);
    virtual int     run();
    virtual void    init(),
        handle(),
        draw(),
        close();

    virtual void    add(const std::string& str),
        add_from_file(const std::string& source),
        remove(const std::string& str),
        update(const int& x),
        search(const int& x);

    void            setButtonRoundness(const float& roundness),
        setBackgroundImage(const std::string& str),
        setBackgroundColor(const Color&),
        setFont(const Font& font),
        setFontSize(const int& size);
    ~Form();
protected:
    bool            m_workspace_focus;
    float           m_roundness = 0,
        m_font_size = 30;
    int             m_segment = 30;
    std::vector<Controller*> children;
    Texture2D       m_background_image;
    Color           m_background_color,
        m_text_color;
    Font            m_font;
    Vector2         m_window_size;
    TextBox         input_textbox,
        remove_textbox;

    TextButton      add_button,
        home_button,
        remove_button,
        back_button;

    DropBox         m_drop_box;

    Console         console;
    Rectangle       m_workspace;
    ProgressBar     m_progress;
    Camera2D        m_camera;
};
#endif