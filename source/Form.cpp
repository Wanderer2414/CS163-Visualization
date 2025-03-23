#include "../include/Form.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/IncludePath.h"
#include <sstream>

Form::Form(const Vector2& window_size) :m_window_size(window_size) {
    m_workspace_focus = false;
}
void Form::init() {
    CommandList::init();
    children.push_back(&console);
    children.push_back(&m_progress);
    children.push_back(&track_hover);
    children.push_back(&option_box);
    children.push_back(&skip_button);
    children.push_back(&speed_scroll);
    children.push_back(&restart_button);
    children.push_back(&play_button);
    children.push_back(&back_button);
    children.push_back(&home_button);

    console.button_setting              = &form_setting;
    console.text_setting                = &form_setting;

    create_box.form_setting             = &form_setting;
    remove_box.form_setting             = &form_setting;
    update_box.form_setting             = &form_setting;
    search_box.form_setting             = &form_setting;
    insert_box.form_setting             = &form_setting;

    create_label.text_setting           = &form_setting;
    add_button.text_setting             = &form_setting;
    add_button.button_setting           = &form_setting;
    input_textbox.text_setting          = &form_setting;
    input_textbox.button_setting        = &form_setting;

    speed_scroll.text_setting           = &form_setting;

    remove_button.button_setting        = &form_setting;
    remove_button.text_setting          = &form_setting;
    remove_textbox.button_setting       = &form_setting;
    remove_textbox.text_setting         = &form_setting;

    create_button.text_setting          = &form_setting;
    create_button.button_setting        = &form_setting;

    m_drop_box.text_setting             = &form_setting;
    m_drop_box.button_setting           = &form_setting;

    home_button.button_setting          = &form_setting;
    option_box.form_setting             = &form_setting;
    track_hover.button_setting          = &form_setting;
    track_hover.text_setting            = &form_setting;

    create_box.push_back(&create_label);
    create_box.push_back(&create_button);
    create_box.push_back(&m_drop_box);

    insert_box.push_back(&input_textbox);
    insert_box.push_back(&add_button);

    // update_box.push_back()

    remove_box.push_back(&remove_button);
    remove_box.push_back(&remove_textbox);

    option_box.push_back(0, &create_box);
    option_box.push_back(1, &insert_box);
    option_box.push_back(2, &update_box);
    option_box.push_back(3, &search_box);
    option_box.push_back(4, &remove_box);

    option_box.setText(0,"Create");
    option_box.setText(1,"Insert");
    option_box.setText(2,"Update");
    option_box.setText(3,"Search");
    option_box.setText(4,"Remove");
    option_box.setVisible(false);

    for (auto i : children) i->init();
    Vector2 center = 0.5f * m_window_size;

    console.setPosition(m_window_size.x - 240, m_window_size.y - 170);
    console.setSize(230, 150);
    console.setTextOrigin({ 10,10 });

    create_label.setText("Create");
    create_label.setPosition(0, 5);
    create_label.setSize(300, 30);

    create_button.setText("Create");
    create_button.setPosition(25, 50);
    create_button.setSize(200,40);

    create_box.setPosition(150, 0);
    create_box.setSize(300, 100);

    add_button.setPosition(10, 270);
    add_button.setSize(145,40);
    add_button.setText("Add");

    input_textbox.setPosition(10, 50);
    input_textbox.setSize(145,200);
    input_textbox.setAlignText(TextBox::Left | TextBox::Top);

    insert_box.setPosition(150, 0);
    insert_box.setSize(300, 100);

    play_button.setPosition(m_window_size.x/2-25, m_window_size.y - 65);
    play_button.setSize(50, 50);
    play_button.setButtonStage(0, PlayButton, PlayButtonHovered);
    play_button.setButtonStage(1, PauseButton,PauseButtonHovered);
    play_button.setButtonStage(2, Replay, Replayhovered);

    skip_button.setPosition(play_button.getPosition().x - 50, play_button.getPosition().y + 5);
    skip_button.setSize(40, 40);
    skip_button.setButtonStage(0, Skip, Skip_hover);

    restart_button.setPosition(play_button.getPosition().x + 60, play_button.getPosition().y + 5);
    restart_button.setSize(40, 40);
    restart_button.setButtonStage(0, Skip, Skip_hover);
    
    speed_scroll.setPosition(m_window_size.x - 100, 10);
    speed_scroll.setSize(70, m_window_size.y - 160);
    stringstream s;
    s << 0.2 << "x";
    for (float i = 0.4; i<=5; i+=0.2) s<<endl<< i<<"x";
    speed_scroll.select(4);
    speed_scroll.setText(s.str());

    back_button.setPosition(20, 20);
    back_button.setSize(30, 30);
    back_button.setButtonStage(0, back_normal, back_hovered);

    remove_button.setPosition(40, 250);
    remove_button.setSize(145,40);
    remove_button.setText("Remove");

    remove_textbox.setPosition(40, 50);
    remove_textbox.setSize(145, 200);

    remove_box.setPosition(150, 0);
    remove_box.setSize(300, 100);

    m_workspace.x = 10;
    m_workspace.y = 10;
    m_workspace.width = m_window_size.x - m_workspace.x;
    m_workspace.height = m_window_size.y - m_workspace.y - 50;

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

    home_button.setPosition(m_window_size.x / 2, 20);
    home_button.setSize(40, 40);
    home_button.setButtonStage(0, home_normal, home_hovered);

    option_box.setPosition(-option_box.getSize().x, m_window_size.y/2);
    option_box.add_vertex({-option_box.getSize().x, m_window_size.y/2});
    option_box.add_vertex({10, m_window_size.y/2});
    option_box.setSize(400, m_window_size.y/2-30);
    option_box.setVisible(false);

    track_hover.setText("");
    track_hover.setPosition(0, option_box.getPosition().y);
    track_hover.setSize(10, option_box.getSize().y);

    setSpeed(5);
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
#include <iostream>
using namespace std;

void Form::handle() {
    //Base handle + children handle
    CommandList::handle();
    for (auto i : children) i->handle();
    //Zoom in/out + zoom move setting
    bool workspace_hover = CheckCollisionPointRec(GetMousePosition(), m_workspace);
    if (!m_workspace_focus && workspace_hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) m_workspace_focus = true;
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) m_workspace_focus = false;
    if (workspace_hover && m_workspace_focus && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_camera.offset = m_camera.offset + GetMouseDelta();
    if (workspace_hover && !option_box.isHovered()) m_camera.zoom += GetMouseWheelMove() / 10;

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
    if (track_hover.isHovered() && option_box.getVertexDone()==0) {
        option_box.setVisible(true);
        option_box.next();
    } else if (!track_hover.isHovered() && !option_box.isHovered()) {
        if (option_box.getVertexDone() == 1) {
            option_box.next();
            input_textbox.setFocus(false);
            remove_textbox.setFocus(false);
        }
        else if (option_box.getVertexDone() == 0) {
            option_box.setVisible(false);
        }
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
    //Speed
    if (speed_scroll.isChanged()) setSpeed(5.0f/(speed_scroll.getChoiceIndex()+1));
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
    for (auto& i:children) i->close();
    children.clear();
    clear();
    console.clear();
    option_box.clear();
}
Form::~Form() {

}