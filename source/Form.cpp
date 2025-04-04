#include "../include/Form.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include <string>
#include "../include/IncludePath.h"
#include <sstream>
#include <iostream>


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
    update_old_value_label(&form_setting),
    update_new_value_label(&form_setting),

    create_button(&form_setting, &form_setting),
    insert_button(&form_setting,&form_setting),
    search_button(&form_setting,&form_setting),
    update_button(&form_setting, &form_setting),
    remove_button(&form_setting, &form_setting),

    create_textbox(&form_setting, &form_setting),
    insert_textbox(&form_setting, &form_setting),
    search_textbox(&form_setting, &form_setting),
    update_textbox_choice(&form_setting, &form_setting),
    update_textbox_value(&form_setting, &form_setting),
    remove_textbox(&form_setting,&form_setting),

    speed_scroll(&form_setting),
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
    children.push_back(&small_skip_back_button);
    children.push_back(&small_skip_next_button);

    create_box.push_back(&create_label);
    create_box.push_back(&create_button);
    create_box.push_back(&create_textbox);
    create_box.push_back(&random_create);
    create_box.push_back(&m_drop_box);

    insert_box.push_back(&insert_textbox);
    insert_box.push_back(&random_insert);
    insert_box.push_back(&insert_button);

    update_box.push_back(&update_new_value_label);
    update_box.push_back(&update_old_value_label);
    update_box.push_back(&update_textbox_choice);
    update_box.push_back(&update_textbox_value);
    update_box.push_back(&random_update_choice);
    update_box.push_back(&random_update_value);
    update_box.push_back(&update_button);

    search_box.push_back(&search_textbox);
    search_box.push_back(&random_search);
    search_box.push_back(&search_button);

    remove_box.push_back(&remove_button);
    remove_box.push_back(&random_remove);
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

    console.setPosition(m_window_size.x - 510, m_window_size.y - 220);
    console.setSize(500, 200);
    console.setTextOrigin({ 10,10 });

    buttonTab.setSize(400, 40);
    buttonTab.setPosition(m_window_size.x/2 - 200, 10);
    buttonTab.push_back("AVL Tree");
    buttonTab.push_back("Graph");
    buttonTab.push_back("Hash Table");
    buttonTab.push_back("Singly Linked List");
    buttonTab.setSelection(index);

    create_label.setText("Create");
    create_label.setPosition(0, 5);
    create_label.setSize(310, 30);

    create_textbox.setPosition(5, 40);
    create_textbox.setSize(300, 100);
    create_textbox.setAlignText(TextBox::Left | TextBox::Top);
    create_textbox.margin = 5;

    create_button.setText("Create");
    create_button.setPosition(5, 145);
    create_button.setSize(300,40);

    random_create.setPosition(270, 5);
    random_create.setSize(30, 30);
    random_create.setButtonStage(0, Rand, Rand);

    m_drop_box.setVisible(false);
    m_drop_box.setPosition(create_textbox.getPosition().x,create_textbox.getPosition().y);
    m_drop_box.setSize(create_textbox.getSize().x, create_textbox.getSize().y);

    create_box.setPosition(130, 0);
    create_box.setSize(310, 190);

    insert_button.setPosition(200, 5);
    insert_button.setSize(70,40);
    insert_button.setText("Add");

    random_insert.setPosition(155, 5);
    random_insert.setSize(40, 40);
    random_insert.setButtonStage(0, Rand, Rand);

    insert_textbox.setPosition(5, 5);
    insert_textbox.setSize(145,40);
    insert_textbox.setAlignText(TextBox::Left | TextBox::Center);

    insert_box.setPosition(130, 45);
    insert_box.setSize(280, 50);
    //Update box
    update_old_value_label.setPosition(5, 5);
    update_old_value_label.setSize(150, 40);
    update_old_value_label.setText("Old value: ");
    update_old_value_label.setAlignText(Label::Left);

    update_textbox_choice.setPosition(155, 5);
    update_textbox_choice.setSize(145,40);
    update_textbox_choice.setAlignText(TextBox::Left | TextBox::Center);

    random_update_choice.setPosition(305, 5);
    random_update_choice.setSize(40, 40);
    random_update_choice.setButtonStage(0, Rand, Rand);

    update_new_value_label.setPosition(5, 50);
    update_new_value_label.setSize(150, 40);
    update_new_value_label.setText("New value: ");
    update_new_value_label.setAlignText(Label::Left);

    update_textbox_value.setPosition(155, 50);
    update_textbox_value.setSize(145,40);
    update_textbox_value.setAlignText(TextBox::Left | TextBox::Center);
    
    random_update_value.setPosition(305, 50);
    random_update_value.setSize(40, 40);
    random_update_value.setButtonStage(0, Rand, Rand);

    update_button.setPosition(5, 95);
    update_button.setSize(340,40);
    update_button.setText("Update");

    update_box.setPosition(130, 90);
    update_box.setSize(355, 140);
    //Search box
    search_textbox.setPosition(5, 5);
    search_textbox.setSize(145,40);
    search_textbox.setAlignText(TextBox::Left | TextBox::Center);

    random_search.setPosition(155, 5);
    random_search.setSize(40, 40);
    random_search.setButtonStage(0, Rand, Rand);

    search_button.setPosition(200, 5);
    search_button.setSize(145,40);
    search_button.setText("Search");

    search_box.setPosition(130, 135);
    search_box.setSize(350, 50);
    //Remove box
    remove_button.setPosition(200, 5);
    remove_button.setSize(145,40);
    remove_button.setText("Remove");

    random_remove.setPosition(155, 5);
    random_remove.setSize(40, 40);
    random_remove.setButtonStage(0, Rand, Rand);
    
    remove_textbox.setPosition(5, 5);
    remove_textbox.setSize(145, 40);

    remove_box.setPosition(130, 180);
    remove_box.setSize(350, 50);

    play_button.setPosition(m_window_size.x / 2 - 25, m_window_size.y - 80);
    play_button.setSize(50, 50);
    play_button.setButtonStage(0, PauseButton,PauseButtonHovered);
    play_button.setButtonStage(1, PlayButton, PlayButtonHovered);
    play_button.setButtonStage(2, Replay, Replayhovered);

    skip_button.setPosition(play_button.getPosition().x + 110, play_button.getPosition().y + 5);
    skip_button.setSize(40, 40);
    skip_button.setButtonStage(0, SkipNormal, SkipHovered);

    small_skip_next_button.setPosition(play_button.getPosition().x + 60, play_button.getPosition().y + 5);
    small_skip_next_button.setSize(40, 40);
    small_skip_next_button.setButtonStage(0, DoubleArrowRight, DoubleArrowRight_Hovered);

    //restart_button.setPosition(40, 270);
    restart_button.setPosition(play_button.getPosition().x - 100, play_button.getPosition().y + 5);
    restart_button.setSize(40, 40);
    restart_button.setButtonStage(0, SkipBackNormal, SkipBackHovered);
    
    //small_skip_back_button.setPosition(40, 270);
    small_skip_back_button.setPosition(play_button.getPosition().x - 50, play_button.getPosition().y + 5);
    small_skip_back_button.setSize(40, 40);
    small_skip_back_button.setButtonStage(0, DoubleArrowLeft, DoubleArrowLeft_Hovered);

    speed_scroll.setPosition(m_window_size.x - 100, 10);
    speed_scroll.setSize(70, m_window_size.y - 160);
    for (float i = 0.2; i<=5; i+=0.2) {
        stringstream s;
        s<< i <<"x";
        speed_scroll.push_back(i, s.str());
    }
    speed_scroll.select(4);

    back_button.setPosition(10, 10);
    back_button.setSize(40, 40);
    back_button.setButtonStage(0, back_normal, back_hovered);

    m_workspace.x = 10;
    m_workspace.y = 70;
    m_workspace.width = m_window_size.x - m_workspace.x - 120;
    m_workspace.height = m_window_size.y - m_workspace.y - 50;

    m_camera.offset = { m_window_size.x / 2, 100 };
    m_camera.zoom = 1;
    m_camera.rotation = 0;
    m_camera.target = { 0, 0 };

    m_progress.setPosition(10, m_window_size.y - 20);
    m_progress.setSize(m_window_size.x - 20, 20);
    m_progress.setThick(3);

    home_button.setPosition(m_window_size.x - 50, 10);
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
    setSpeed(1);
}
int Form::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();

        ClearBackground(form_setting.background_color);
        draw();
        EndDrawing();
        if (back_button.isPressed()) return 1;
        //Home button handle
        if (home_button.isPressed()) return 0;
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
        main_box_show();
    } else if (!track_hover.isHovered() && !option_box.isHovered()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            main_box_hide();
        }
        else if (option_box.getVertexDone() == 0) {
            option_box.setVisible(false);
        }
    }
    //Is file add
    if (m_drop_box.IsFileAdd()) {
        create_textbox.setText(readFromFile(m_drop_box.getFiles()[0]));
    }
    //Play button;
    //Stage 0: Pause, 1: Continue, 3:Replay
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
            setPause(true);
            GotoCommandLine(0);
        }
    } 
    else if (!isPause() && progress < 1) play_button.go(0);
    else if (isPause() && progress<1) play_button.go(1);
    else play_button.go(2);
    //Skip button
    if (skip_button.isPressed()) GotoCommandLine(1);
    if (restart_button.isPressed()) {
        setPause(true);
        GotoCommandLine(0);
    }
    //Speed
    if (speed_scroll.isChanged())
        setSpeed(1.0f/(speed_scroll.getValue()));
    //Button handle
    if (create_button.isPressed()) {
        add(split(create_textbox.getText()));
    }
    if (insert_button.isPressed() || insert_textbox.isEnter()) {
        add({insert_textbox.getText()});
        insert_textbox.clear();
    }
    if (search_button.isPressed() || search_textbox.isEnter()) {
        search(search_textbox.getText());
    }
    if (update_button.isPressed()) {
        update(update_textbox_choice.getText(), update_textbox_value.getText());
    }
    if (remove_button.isPressed() || remove_textbox.isEnter()) {
        remove(remove_textbox.getText());
        remove_textbox.clear();
    }
    //Random create
    if (random_create.isPressed()) create_textbox.setText(RandomCreate());
    if (random_insert.isPressed()) insert_textbox.setText(RandomInsert());
    if (random_update_choice.isPressed()) update_textbox_choice.setText(RandomOldValue());
    if (random_update_value.isPressed()) update_textbox_value.setText(RandomNewValue());
    if (random_remove.isPressed()) remove_textbox.setText(RandomRemove());
    if (random_search.isPressed()) search_textbox.setText(RandomSearch());
}
void Form::draw() {
    for (auto i : children) i->draw();
}
void Form::add(const vector<string>& x) {

}
void Form::remove(const std::string& str) {

}
void Form::update(const std::string& oldValue, const std::string& newValue) {

}
void Form::search(const std::string& x) {

}
void Form::main_box_show() {
    if (option_box.getVertexDone()==0) {
        option_box.setVisible(true);
        option_box.next();
    }
}
void Form::main_box_hide() {
    if (option_box.getVertexDone() == 1) {
        option_box.next();
        option_box.select(-1);
        insert_textbox.setFocus(false);
        remove_textbox.setFocus(false);
    }
}
string Form::RandomCreate() const {
    string ans;
    srand(time(0));
    for (int i = rand()%50; i>=0; i--) ans+=to_string(rand()%1000)+" ";
    return ans;
}
string Form::RandomInsert() const {
    srand(time(0));
    return to_string(rand());
}
string Form::RandomOldValue() const {
    srand(time(0));
    return to_string(rand());
}
string Form::RandomNewValue() const {
    srand(time(0));
    return to_string(rand());
}
string Form::RandomSearch() const {
    srand(time(0));
    return to_string(rand());
}
string Form::RandomRemove() const {
    srand(time(0));
    return to_string(rand());
}
Form::~Form() {

}