#include "../include/Form.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/IncludePath.h"

Form::Form(const Vector2& window_size) :m_window_size(window_size) {
    m_workspace_focus = false;
}
void Form::init() {
    form_setting.font = LoadFont(font_link);
    CommandList::init();
    children.push_back(&console);
    // children.push_back(&add_button);
    // children.push_back(&input_textbox);
    // children.push_back(&m_drop_box);
    children.push_back(&m_progress);
    // children.push_back(&remove_textbox);
    // children.push_back(&remove_button);
    children.push_back(&track_hover);
    children.push_back(&option_box);
    children.push_back(&back_button);
    children.push_back(&home_button);

    option_box.tabs.push_back({&play_button, &skip_button});
    option_box.tabs.push_back({&add_button, &input_textbox, &m_drop_box});
    option_box.tabs.push_back({&remove_button, &remove_textbox});
    option_box.name = {"Replay", "Add","Remove"};
    option_box.setVisible(false);
    option_box.setDuration(0.25);

    for (auto i : children) i->init();
    Vector2 center = 0.5f * m_window_size;

    console.button_setting = &form_setting;
    console.text_setting = &form_setting;
    console.setPosition(m_window_size.x - Console_width-10, m_window_size.y - Console_height - 20);
    console.setSize(Console_width, Console_height);
    console.setTextOrigin({ 10,10 });

    add_button.text_setting = &form_setting;
    add_button.button_setting = &form_setting;
    add_button.setPosition(40, 260);
    add_button.setSize(145,50);
    add_button.setText("Add");

    input_textbox.text_setting = &form_setting;
    input_textbox.button_setting = &form_setting;
    input_textbox.setPosition(40, 50);
    input_textbox.setSize(145,200);
    input_textbox.setAlignText(TextBox::Left | TextBox::Top);

    play_button.button_setting = &form_setting;
    play_button.setPosition(100, 260);
    play_button.setSize(30, 30);
    play_button.setButtonStage(0, PlayButton, PlayButtonHovered);
    play_button.setButtonStage(1, PauseButton,PauseButtonHovered);
    play_button.setButtonStage(2, Replay, Replayhovered);

    skip_button.button_setting = &form_setting;
    skip_button.setPosition(150, 260);
    skip_button.setSize(30, 30);
    skip_button.setButtonStage(0, SkipNormal, SkipHovered);

    back_button.button_setting = &form_setting;
    back_button.setPosition(30, 30);
    back_button.setSize(40, 40);
    back_button.setButtonStage(0, back_normal, back_hovered);

    remove_button.button_setting = &form_setting;
    remove_button.text_setting = &form_setting;
    remove_button.setPosition(50,400 + Console_height + Control_height + 20);
    remove_button.setSize(Control_width, Control_height);
    remove_button.setText("Remove");

    remove_textbox.button_setting = &form_setting;
    remove_textbox.text_setting = &form_setting;
    remove_textbox.setPosition(100 + Control_width + 10, remove_button.getPosition().y);
    remove_textbox.setSize(TextInput_Width, Control_height);

    m_workspace.x = Console_width + 10 + 10;
    m_workspace.y = 10;
    m_workspace.width = m_window_size.x - m_workspace.x;
    m_workspace.height = m_window_size.y - m_workspace.y - 50;

    m_drop_box.text_setting = &form_setting;
    m_drop_box.button_setting = &form_setting;
    m_drop_box.setVisible(false);
    m_drop_box.setPosition(input_textbox.getPosition().x,input_textbox.getPosition().y);
    m_drop_box.setSize(input_textbox.getSize().x, input_textbox.getSize().y);

    m_camera.offset = { m_window_size.x / 2, 100 };
    m_camera.zoom = 1;
    m_camera.rotation = 0;
    m_camera.target = { 0, 0 };

    m_progress.setPosition(10, m_window_size.y - 20);
    m_progress.setSize(m_window_size.x - 20, 20);
    m_progress.setThick(3);

    home_button.button_setting = &form_setting;
    home_button.setPosition(m_window_size.x / 2, 20);
    home_button.setSize(40, 40);
    home_button.setButtonStage(0, home_normal, home_hovered);

    option_box.button_setting = form_setting;
    option_box.text_setting = form_setting;
    option_box.setPosition(-option_box.getSize().x, m_window_size.y/2);
    option_box.setSize(200, m_window_size.y/2-30);
    option_box.setVisible(false);

    track_hover.button_setting = &form_setting;
    track_hover.text_setting = &form_setting;
    track_hover.setText("");
    track_hover.setPosition(0, option_box.getPosition().y);
    track_hover.setSize(10, option_box.getSize().y);


    setSpeed(0.5);
}
int Form::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();

        ClearBackground(form_setting.background_color);
        draw();
        EndDrawing();
        if (add_button.isPressed() || input_textbox.isEnter()) {
            string str = input_textbox.getText();
            add(split(str));
            input_textbox.clear();
        }
        if (remove_button.isPressed() || remove_textbox.isEnter()) {
            remove(remove_textbox.getText());
            remove_textbox.clear();
        }
        if (back_button.isPressed()) return 1;
        //Home button handle
        if (home_button.isPressed()) {
            return 0;
        }
    }
    return 0;
}
void Form::handle() {
    //Base handle + children handle
    CommandList::handle();
    for (auto i : children) i->handle();
    //Zoom in/out + zoom move setting
    bool workspace_hover = CheckCollisionPointRec(GetMousePosition(), m_workspace);
    if (!m_workspace_focus && workspace_hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) m_workspace_focus = true;
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_workspace_focus = false;
    if (workspace_hover && m_workspace_focus && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_camera.offset = m_camera.offset + GetMouseDelta();
    if (workspace_hover) m_camera.zoom += GetMouseWheelMove() / 10;

    //Progresss setting
    float progress = 0;
    m_progress.setSplitCount(getCommandCount());
    if (m_progress.isChanged()) {
        //PProgress drag and drop
        progress = m_progress.getProgress();
        GotoCommandLine(progress);
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_progress.setProgresss(getProgress());
    }
    else {
        //Progress go next and go back
        if (IsKeyReleased(KEY_RIGHT)) goNext();
        else if (IsKeyReleased(KEY_LEFT)) goBack();
        //Reshow progress
        progress = getProgress();
        m_progress.setProgresss(progress);
    }
    //Main box show
    if (track_hover.isHovered() && !option_box.isVisible()) {
        option_box.setVisible(true);
        option_box.setSlowPosition(10, option_box.getPosition().y);
    } else if (!track_hover.isHovered() && !option_box.isHovered()) {
        if (option_box.getPosition().x == 10) {
            option_box.setSlowPosition(-option_box.getSize().x, option_box.getPosition().y);
            input_textbox.setFocus(false);
            remove_textbox.setFocus(false);
        }
        else if (option_box.getPosition().x == -option_box.getSize().x && option_box.isVisible()) 
            option_box.setVisible(false);
    }
    //Is file add
    if (m_drop_box.IsFileAdd()) {
        input_textbox.setText(readFromFile(m_drop_box.getFiles()[0]));
    }
    //Play button;
    if (!isPause() && progress < 1) play_button.go(0);
    else if (isPause()) play_button.go(1);
    else play_button.go(2);
    if (play_button.isPressed()) {
        if (play_button.getStage() == 0) {
            setPause(true);
            play_button.next();
        } else if (play_button.getStage() == 1) {
            if (progress == 1) {
                play_button.next();
            } else {
                play_button.back();
                setPause(false);
            }
        } else if (play_button.getStage() == 2) {
            GotoCommandLine(0);
        }
    }
    //Skip button
    if (skip_button.isPressed()) {
        GotoCommandLine(1);
    }
}
void Form::draw() {
    for (auto i : children) i->draw();
}
void Form::add(const vector<string>& x) {

}
void Form::remove(const std::string& str) {

}
void Form::update(const int& x) {

}
void Form::search(const int& x) {

}
void Form::close() {
    children.clear();
    clear();
    console.clear();
}
Form::~Form() {

}