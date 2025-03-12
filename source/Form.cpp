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

    input_textbox.setPosition(Console_x+Control_width + 10, add_button.getPosition().y);
    input_textbox.setSize(TextInput_Width, Control_height);
    input_textbox.m_normal_color = WHITE;
    input_textbox.m_hover_color = {200, 200, 200, 255};
    input_textbox.setRoundness(m_roundness);
    input_textbox.setTextColor(BLACK);

    m_workspace.x = Console_width + Console_x + 10;
    m_workspace.y = Console_y;
    m_workspace.width = m_window_size.x - m_workspace.x;
    m_workspace.height = m_window_size.y - m_workspace.y;

    m_origin = {m_window_size.x/2, 100};
    setSpeed(0.5);
}
void Form::loadAsset() {

}
int Form::run() {
    while (!WindowShouldClose()) {
        for (auto i:children) i->handle();
        handle();
        BeginDrawing();
            ClearBackground(BLACK);
            draw();
        EndDrawing();
        if (add_button.isPressed() || input_textbox.isEnter()) {
            add(*input_textbox.getString());
            input_textbox.clear();
        }
        if (home_button.isPressed()) return 0;
    }
    return 0;
}
void Form::handle() {
    if (m_clock.get() && CommandQueue.size()) FetchCommandQueue();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_origin = m_origin + GetMouseDelta();
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
void Form::add(std::vector<int>& x) {

}
void Form::remove() {

}
void Form::update(const int& x) {

}
void Form::search(const int& x) {

}
void Form::unloadAsset() {
    UnloadTexture(m_background_image);
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