#include "../include/Form.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
Form::Form(const Vector2& window_size):m_window_size(window_size) {

}

float Form::PullCommand() {
    if (CommandQueue.empty()) return -1;
    float ans = CommandQueue.front();
    CommandQueue.pop_front();
    return ans;
}

void Form::init() {
    children.push_back(&home_button);
    children.push_back(&console);
    children.push_back(&add_button);
    children.push_back(&input_textbox);
    children.push_back(&m_drop_box);
    children.push_back(&remove_textbox);
    children.push_back(&remove_button);
    children.push_back(&back_button);
    for (auto i: children) i->init();
    Vector2 center = 0.5f*m_window_size;

    home_button.setPosition(center.x-0.5f*Home_width, 10);
    home_button.setSize(Home_width, Home_height);
    home_button.setText("Home");
    home_button.setRoundness(m_roundness);

    console.setPosition(Console_x, Console_y);
    console.setSize(Console_width, Console_height);
    console.setTextOrigin({10,10});
    console.m_normal_color = {150,150,150,100};

    add_button.setPosition(Console_x, Console_y + Console_height + 10);
    add_button.setSize(Control_width,Control_height);
    add_button.setText("Add");
    add_button.setRoundness(m_roundness);
    add_button.m_normal_color = WHITE;
    add_button.m_hover_color = {200, 200, 200, 255};
    add_button.setTextColor(BLACK);

    back_button.setPosition(10, 10);
    back_button.setSize(Control_width, Control_height);
    back_button.setText("Back");
    back_button.setRoundness(m_roundness);
    back_button.m_normal_color = WHITE;
    back_button.m_hover_color = { 200, 200, 200, 255 };
    back_button.setTextColor(BLACK);

    remove_button.setPosition(Console_x, Console_y + Console_height + Control_height + 20);
    remove_button.setSize(Control_width, Control_height);
    remove_button.setText("Remove");
    remove_button.setRoundness(m_roundness);
    remove_button.setTextColor(BLACK);

    input_textbox.setPosition(Console_x+Control_width + 10, add_button.getPosition().y);
    input_textbox.setSize(TextInput_Width, Control_height);
    input_textbox.m_normal_color = WHITE;
    input_textbox.m_hover_color = {200, 200, 200, 255};
    input_textbox.setRoundness(m_roundness);
    input_textbox.setTextColor(BLACK);

    remove_textbox.setPosition(Console_x + Control_width + 10, remove_button.getPosition().y);
    remove_textbox.setSize(TextInput_Width, Control_height);
    remove_button.m_hover_color = {200, 200, 200, 255};
    remove_button.setRoundness(m_roundness);
    remove_button.setTextColor(BLACK);

    m_workspace.x = Console_width + Console_x + 10;
    m_workspace.y = Console_y;
    m_workspace.width = m_window_size.x - m_workspace.x;
    m_workspace.height = m_window_size.y - m_workspace.y;

    m_drop_box.setPosition(Console_x,Console_y+ Console_height+ Control_height*3);
    m_drop_box.setSize(Console_width, Console_height);
    m_drop_box.setText("Drop file here");
    m_drop_box.m_normal_color = m_drop_box.m_hover_color = LIGHTGRAY;

    m_camera.offset = {m_window_size.x/2, 100};
    m_camera.zoom = 1;
    m_camera.rotation = 0;
    m_camera.target = {0, 0};
    setSpeed(0.5);
}
int Form::run() {
    while (!WindowShouldClose()) {
        handle();
        BeginDrawing();
            ClearBackground(BLACK);
            draw();
        EndDrawing();
        if (add_button.isPressed() || input_textbox.isEnter()) {
            add(*input_textbox.getString());
            input_textbox.clear();
        }
        if (back_button.isPressed()) return 1;
        if (home_button.isPressed()) return 0;
        if (m_drop_box.IsFileAdd()) {
            add_from_file(m_drop_box.getFiles()[0]);
        }
    }
    return 0;
}
void Form::handle() {
    for (auto i:children) i->handle();
    if (m_clock.get() && CommandQueue.size()) FetchCommandQueue();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_camera.offset = m_camera.offset + GetMouseDelta();
    if (CheckCollisionPointRec(GetMousePosition(), m_workspace)) m_camera.zoom += GetMouseWheelMove()/10;
}
void Form::draw() {
    for (auto i:children) i->draw();
}
void Form::FetchCommandQueue() {
    
}
void Form::PushCommand(const std::vector<float>& list) {
    for (float i:list) CommandQueue.push_back(i);
}
void Form::setSpeed(const float& duration) {
    m_speed = duration;
    m_clock.setDuration(duration);
}
void Form::add(const std::string& x) {

}
void Form::add_from_file(const std::string& x) {

}
void Form::remove() {

}
void Form::update(const int& x) {

}
void Form::search(const int& x) {

}
void Form::close() {
    children.clear();
    CommandQueue.clear();
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