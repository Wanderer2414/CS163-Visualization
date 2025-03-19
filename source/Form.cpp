#include "../include/Form.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/Colors.h"

Form::Form(const Vector2& window_size) :m_window_size(window_size) {
    m_workspace_focus = false;
}
void Form::init() {
    form_setting.font = GetFontDefault();
    CommandList::init();
    children.push_back(&console);
    children.push_back(&add_button);
    children.push_back(&input_textbox);
    children.push_back(&m_drop_box);
    children.push_back(&m_progress);
    children.push_back(&remove_textbox);
    children.push_back(&remove_button);
    children.push_back(&back_button);
    children.push_back(&home_button);
    for (auto i : children) i->init();
    Vector2 center = 0.5f * m_window_size;

    console.button_setting = &form_setting;
    console.text_setting = &form_setting;
    console.setPosition(Console_x, Console_y);
    console.setSize(Console_width, Console_height);
    console.setTextOrigin({ 10,10 });

    add_button.text_setting = &form_setting;
    add_button.button_setting = &form_setting;
    add_button.setPosition(Console_x, Console_y + Console_height + 10);
    add_button.setSize(Control_width, Control_height);
    add_button.setText("Add");

    back_button.button_setting = &form_setting;
    back_button.text_setting  = &form_setting;
    back_button.setPosition(10, 10);
    back_button.setSize(Control_width, Control_height);
    back_button.setText("Back");

    remove_button.button_setting = &form_setting;
    remove_button.text_setting = &form_setting;
    remove_button.setPosition(Console_x, Console_y + Console_height + Control_height + 20);
    remove_button.setSize(Control_width, Control_height);
    remove_button.setText("Remove");

    input_textbox.text_setting = &form_setting;
    input_textbox.button_setting = &form_setting;
    input_textbox.setPosition(Console_x + Control_width + 10, add_button.getPosition().y);
    input_textbox.setSize(TextInput_Width, Control_height);

    remove_textbox.button_setting = &form_setting;
    remove_textbox.text_setting = &form_setting;
    remove_textbox.setPosition(Console_x + Control_width + 10, remove_button.getPosition().y);
    remove_textbox.setSize(TextInput_Width, Control_height);

    m_workspace.x = Console_width + Console_x + 10;
    m_workspace.y = Console_y;
    m_workspace.width = m_window_size.x - m_workspace.x;
    m_workspace.height = m_window_size.y - m_workspace.y - 50;

    m_drop_box.text_setting = &form_setting;
    m_drop_box.button_setting = &form_setting;
    m_drop_box.setPosition(Console_x, Console_y + Console_height + Control_height * 3);
    m_drop_box.setSize(Console_width, Console_height);
    m_drop_box.setText("Drop file here");

    m_camera.offset = { m_window_size.x / 2, 100 };
    m_camera.zoom = 1;
    m_camera.rotation = 0;
    m_camera.target = { 0, 0 };

    m_progress.setPosition(10, m_window_size.y - 20);
    m_progress.setSize(m_window_size.x - 20, 20);
    m_progress.setThick(3);

    home_button.button_setting = &form_setting;
    home_button.setPosition(m_window_size.x - 90, 10);
    home_button.setSize(60, 50);

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
            add(*input_textbox.getText());
            input_textbox.clear();
        }
        if (remove_button.isPressed() || remove_textbox.isEnter()) {
            remove(*remove_textbox.getText());
            remove_textbox.clear();
        }
        if (back_button.isPressed()) return 1;
        //Home button handle
        if (home_button.isPressed()) {
            return 0;
        }

        if (m_drop_box.IsFileAdd()) {
            add_from_file(m_drop_box.getFiles()[0]);
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
    m_progress.setSplitCount(getCommandCount());
    if (m_progress.isChanged()) {
        //PProgress drag and drop
        GotoCommandLine(m_progress.getProgress());
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_progress.setProgresss(getProgress());
    }
    else {
        //Progress go next and go back
        if (IsKeyReleased(KEY_RIGHT)) goNext();
        else if (IsKeyReleased(KEY_LEFT)) goBack();
        //Reshow progress
        m_progress.setProgresss(getProgress());
    }
}
void Form::draw() {
    for (auto i : children) i->draw();
}
void Form::add(const std::string& x) {

}
void Form::add_from_file(const std::string& x) {

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
void Form::setButtonRoundness(const float& roundness) {
    m_roundness = roundness;
}
void Form::setBackgroundImage(const std::string& str) {
    UnloadTexture(m_background_image);
    m_background_image = LoadTexture(str.c_str());
}
void Form::setBackgroundColor(const Color& color) {
    m_background_color = color;
}
void Form::setFont(const Font& font) {
    m_font = font;
}
void Form::setFontSize(const int& size) {
    m_font_size = size;
}
Form::~Form() {

}