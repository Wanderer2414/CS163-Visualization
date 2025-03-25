#include "../include/Form.h"
#include "../include/General.h"
#include "../include/IncludePath.h"

Form::Form(const int& index, FormSetting f_setting, const Vector2& window_size) :
    m_window_size(window_size),
    form_setting(f_setting),
    console(&form_setting, &form_setting),
    buttonTab(&form_setting, &form_setting),

    create_box(&form_setting),
    remove_box(&form_setting),
    update_box(&form_setting),
    search_box(&form_setting),
    insert_box(&form_setting),

    create_label(&form_setting),

    add_button(&form_setting,&form_setting),
    search_button(&form_setting,&form_setting),
    update_button(&form_setting, &form_setting),
    remove_button(&form_setting, &form_setting),

    input_textbox(&form_setting, &form_setting),
    search_textbox(&form_setting, &form_setting),
    update_textbox(&form_setting, &form_setting),
    remove_textbox(&form_setting,&form_setting),

    speed_scroll(&form_setting),
    create_button(&form_setting, &form_setting),
    option_box(&form_setting),
    track_hover(&form_setting, &form_setting)
{
    m_workspace_focus = false;
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
    children.push_back(&buttonTab);


    create_box.push_back(&create_label);
    create_box.push_back(&create_button);
    create_box.push_back(&m_drop_box);

    insert_box.push_back(&input_textbox);
    insert_box.push_back(&add_button);

    update_box.push_back(&update_textbox);
    update_box.push_back(&update_button);

    search_box.push_back(&search_textbox);
    search_box.push_back(&search_button);

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

    console.setPosition(m_window_size.x - 240, m_window_size.y - 170);
    console.setSize(230, 150);
    console.setTextOrigin({ 10,10 });

    buttonTab.setSize(400, 40);
    buttonTab.setPosition(m_window_size.x/2 - 200, 20);
    buttonTab.push_back("AVL Tree");
    buttonTab.push_back("Graph");
    buttonTab.push_back("Hash Table");
    buttonTab.push_back("Singly Linked List");
    buttonTab.setSelection(index);

    create_label.setText("Create");
    create_label.setPosition(0, 5);
    create_label.setSize(300, 30);

    create_button.setText("Create");
    create_button.setPosition(25, 50);
    create_button.setSize(200,40);

    create_box.setPosition(130, 0);
    create_box.setSize(310, 100);

    add_button.setPosition(210, 5);
    add_button.setSize(70,40);
    add_button.setText("Add");

    input_textbox.setPosition(5, 5);
    input_textbox.setSize(145,40);
    input_textbox.setAlignText(TextBox::Left | TextBox::Top);

    insert_box.setPosition(130, 45);
    insert_box.setSize(310, 50);

    update_textbox.setPosition(5, 5);
    update_textbox.setSize(145,40);
    update_textbox.setAlignText(TextBox::Left | TextBox::Top);

    update_button.setPosition(200, 5);
    update_button.setSize(100,40);
    update_button.setText("Update");

    update_box.setPosition(130, 90);
    update_box.setSize(310, 50);

    search_textbox.setPosition(5, 5);
    search_textbox.setSize(145,40);
    search_textbox.setAlignText(TextBox::Left | TextBox::Top);

    search_button.setPosition(205, 5);
    search_button.setSize(100,40);
    search_button.setText("Search");

    search_box.setPosition(130, 135);
    search_box.setSize(310, 50);

    remove_button.setPosition(150, 5);
    remove_button.setSize(120,40);
    remove_button.setText("Remove");

    remove_textbox.setPosition(5, 5);
    remove_textbox.setSize(145, 40);

    remove_box.setPosition(130, 180);
    remove_box.setSize(310, 50);

    play_button.setPosition(m_window_size.x / 2 - 25, m_window_size.y - 80);
    play_button.setSize(50, 50);
    play_button.setButtonStage(0, PlayButton, PlayButtonHovered);
    play_button.setButtonStage(1, PauseButton,PauseButtonHovered);
    play_button.setButtonStage(2, Replay, Replayhovered);

    skip_button.setSize(30, 30);
    skip_button.setButtonStage(0, SkipNormal, SkipHovered);
    skip_button.setPosition(play_button.getPosition().x - 50, play_button.getPosition().y + 5);
    skip_button.setSize(40, 40);
    skip_button.setButtonStage(0, SkipNormal, SkipHovered);

    restart_button.setPosition(40, 270);
    restart_button.setSize(30, 30);
    restart_button.setButtonStage(0, Replay, Replayhovered);
    restart_button.setPosition(play_button.getPosition().x + 60, play_button.getPosition().y + 5);
    restart_button.setSize(40, 40);
    restart_button.setButtonStage(0, SkipNormal, SkipHovered);
    
    speed_scroll.setPosition(m_window_size.x - 100, 10);
    speed_scroll.setSize(70, m_window_size.y - 160);
    stringstream s;
    s << 0.2 << "x";
    for (float i = 0.4; i<=5; i+=0.2) s<<endl<< i<<"x";
    speed_scroll.select(4);
    speed_scroll.setText(s.str());

    back_button.setPosition(30, 30);
    back_button.setSize(40, 40);
    back_button.setButtonStage(0, back_normal, back_hovered);

    m_workspace.x = 10;
    m_workspace.y = 70;
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
    option_box.setSize(200, m_window_size.y/2-30);
    option_box.setVisible(false);

    track_hover.setText("");
    track_hover.setPosition(0, option_box.getPosition().y);
    track_hover.setSize(10, option_box.getAutoSize().y);

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
        if (buttonTab.isChanged()) {
            return 3 + buttonTab.GetSelection();
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
    if (!m_workspace_focus && workspace_hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            m_workspace_focus = true;
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
            m_workspace_focus = false;
    if (!speed_scroll.isHovered() && workspace_hover && m_workspace_focus && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
            m_camera.offset = m_camera.offset + GetMouseDelta();
    if (workspace_hover && !option_box.isHovered() && !speed_scroll.isHovered()) 
            m_camera.zoom += GetMouseWheelMove() / 10;

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
    if (track_hover.isHovered()) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 pos = track_hover.getPosition();
            pos.y += GetMouseDelta().y;
            track_hover.setPosition(pos.x, pos.y);
            option_box.setPosition(option_box.getPosition().x, pos.y);
        } 
        if (option_box.getVertexDone()==0) {
            option_box.setVisible(true);
            option_box.next();
        }
    } else if (!track_hover.isHovered() && !option_box.isHovered()) {
        if (option_box.getVertexDone() == 1) {
            option_box.next();
            option_box.select(-1);
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
    if (speed_scroll.isChanged()) 
        setSpeed(5.0f/(speed_scroll.getChoiceIndex()+1));
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
Form::~Form() {

}