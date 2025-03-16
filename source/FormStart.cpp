#include "../include/FormStart.h"
#include "../raylib/raylib.h"
#include "../include/General.h"
#include "../include/General.h"
#include <cmath>
#include <string>

MenuStart::MenuStart(const Vector2& windowSize) :
    m_windowSize(windowSize)
{
}

int MenuStart::run() {
    while (!WindowShouldClose()) {
        handle();
        for (auto i : children) i->handle();
        BeginDrawing();
        ClearBackground(BLACK);
        draw();

        const char* text = "DATA STRUCTURE VISUALIZATION";
        int fontSize = 40;
        int textWidth = MeasureText(text, fontSize);
        int textX = m_windowSize.x / 2 -  textWidth / 2; // Center horizontall
        DrawText(text, textX, 100, fontSize, WHITE);

        EndDrawing();
        if (Start.isPressed()) return 1;
        if (Setting.isPressed()) return 2;
        if (Exit.isPressed()) return -1;
    };
    return 0;
};
void MenuStart::init() {
    children.push_back(&Start);
    children.push_back(&Setting);
    children.push_back(&Exit);
    for (auto i : children) i->init();

    // BSTForm.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    Start.setSize(main_button_width, main_button_height);
    Start.setText("Start");
    Start.setRoundness(0.3);
    Start.setPosition(m_windowSize.x / 2 - Start.getSize().x / 2, m_windowSize.y / 2 - Start.getSize().y / 2 - 100);

    Setting.setSize(main_button_width, main_button_height);
    Setting.setText("Setting");
    Setting.setRoundness(0.3);
    Setting.setPosition(m_windowSize.x / 2 - Setting.getSize().x / 2, m_windowSize.y / 2 - Setting.getSize().y / 2);

    Exit.setSize(main_button_width, main_button_height);
    Exit.setText("Exit");
    Exit.setRoundness(0.3);
    Exit.setPosition(m_windowSize.x / 2 - Exit.getSize().x / 2, m_windowSize.y / 2 - Exit.getSize().y / 2 + 100);
}
void MenuStart::loadAsset() {

}
void MenuStart::handle() {

}
void MenuStart::draw() {
    for (auto i : children) i->draw();
}
void MenuStart::unloadAsset() {

}
void MenuStart::close() {
    children.clear();
}