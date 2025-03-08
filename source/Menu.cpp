#include "../include/Menu.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/General.h"
#include <cmath>
#include <string>

Menu::Menu(const Vector2& windowSize):
        Form(windowSize), m_windowSize(windowSize) 
{
}

int Menu::run() {
    while (!WindowShouldClose()) {
        handle();
        for (auto i:children) i->handle();
        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
        if (start.isPressed()) return 1;
    };
    return 0;
};
void Menu::init() {
    children.push_back(&start);
    for (auto i:children) i->init();

    Vector2 center = m_windowSize/2;
    start.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    start.setSize(main_button_width,main_button_height);
    start.setText("Start");
    start.setRoundness(0.3);

}
void Menu::loadAsset() {
    
}
void Menu::handle() {
    
}
void Menu::draw() {
    start.draw();
}
void Menu::unloadAsset() {

}
void Menu::close() {

}
void Menu::add(const int& x) {

}
void Menu::add(std::vector<int>& x) {

}
void Menu::remove() {

}
void Menu::update(const int& x) {

}
void Menu::search(const int& x) {

}