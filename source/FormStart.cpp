#include "../include/FormStart.h"
#include "../include/Colors.h"
#include "../include/include.h"
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
        ColorScheme currentTheme = DarkTheme;
        ClearBackground(currentTheme.background);
        
        const char* text = "DATA STRUCTURE VISUALIZATION";
        int fontSize = 40;
        // Calculate the position to center the text
        int textWidth = MeasureText(text, fontSize);
        int posX = (m_windowSize.x - textWidth) / 2;
        DrawText(text, posX, 100, fontSize, currentTheme.text);

        draw();
        EndDrawing();
        if (Start.isPressed()) return 1;
        if (Setting.isPressed()) {
            setting_box.open();
        };
        if (Exit.isPressed()) return -1;
    };
    return 0;
};
void MenuStart::init() {
    form_setting.font = LoadFont(font_link);
    children.push_back(&Start);
    children.push_back(&Setting);
    children.push_back(&Exit);
    children.push_back(&setting_box);
    for (auto i : children) i->init();

    // BSTForm.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    Start.button_setting = &form_setting;
    Start.text_setting = &form_setting;
    Start.setSize(main_button_width, main_button_height);
    Start.setText("Start");
    Start.setPosition(m_windowSize.x / 2 - Start.getSize().x / 2, m_windowSize.y / 2 - Start.getSize().y / 2 - 100);

    Setting.button_setting = &form_setting;
    Setting.text_setting = &form_setting;
    Setting.setSize(main_button_width, main_button_height);
    Setting.setText("Setting");
    Setting.setPosition(m_windowSize.x / 2 - Setting.getSize().x / 2, m_windowSize.y / 2 - Setting.getSize().y / 2);

    setting_box.button_setting = &form_setting;
    setting_box.setSize(500, 600);
    setting_box.setPosition(m_windowSize.x/2-setting_box.getSize().x/2, m_windowSize.y/2-setting_box.getSize().y/2);
    setting_box.setDuration(0.2);
    setting_box.setBackgroundColor({255,255,255,240});
    
    Exit.button_setting = &form_setting;
    Exit.text_setting = &form_setting;
    Exit.setSize(main_button_width, main_button_height);
    Exit.setText("Exit");
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