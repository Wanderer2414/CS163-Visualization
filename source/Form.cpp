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
    children.push_back(&add_button);
    children.push_back(&input_textbox);
    children.push_back(&console);
    for (auto i:children) i->init();

    console.setPosition(10, 10);
    console.setSize(300, 200);
    console.setTextOrigin({10,10});
    console.m_normal_color = {150,150,150,100};

    add_button.setPosition(10, 300);
    add_button.setSize(150, 50);
    add_button.setText("Add");
    add_button.m_normal_color = WHITE;
    add_button.m_hover_color = {200, 200, 200, 255};
    add_button.setTextColor(BLACK);

    input_textbox.setPosition(10, 240);
    input_textbox.setSize(150, 50);
    input_textbox.m_normal_color = WHITE;
    input_textbox.m_hover_color = {200, 200, 200, 255};
    input_textbox.setTextColor(BLACK);

    m_origin = {m_window_size.x/2, 50};
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
            add(to_int(*input_textbox.getString()));
            input_textbox.clear();
        }
    }
    return 0;
}
void Form::handle() {
    if (m_clock.get() && CommandQueue.size()) FetchCommandQueue();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) m_origin = m_origin + GetMouseDelta();
}
void Form::draw() {
    add_button.draw();
    input_textbox.draw();
    console.draw();
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
void Form::add(const int& x) {

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