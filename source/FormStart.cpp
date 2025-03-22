#include "../include/FormStart.h"
#include <cmath>
#include <string>
MenuStart::MenuStart(const Vector2& windowSize) :
    m_windowSize(windowSize)
{
    
}
int MenuStart::getMode() const {
    return setting_box.getMode();
}
int MenuStart::run() {
    while (!WindowShouldClose()) {
        handle();
        for (auto i : children) i->handle();
        BeginDrawing();
            ClearBackground(form_setting.background_color);
            // Draw Title
            const char* text = "DATA STRUCTURE VISUALIZATION";
            int fontSize = 40;
            // Calculate the position to center the text
            Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 2.0f);
            float posX = (m_windowSize.x - textSize.x) / 2;
            DrawTextEx(GetFontDefault(), text, {posX, 100}, fontSize, 2.0f, form_setting.color);

            draw();
        EndDrawing();
        if (!setting_box.isHovered() && Start.isPressed()) return 1;
        if (!setting_box.isHovered() && Setting.isPressed()) setting_box.open();
        if (!setting_box.isHovered() && Exit.isPressed()) return -1;
    };
    return 0;
};
void MenuStart::init() {
    children.push_back(&Start);
    children.push_back(&Setting);
    children.push_back(&Exit);
    children.push_back(&AboutUs);
    children.push_back(&setting_box);

    Start.button_setting = &form_setting;
    Start.text_setting = &form_setting;
    Setting.button_setting = &form_setting;
    Setting.text_setting = &form_setting;
    AboutUs.button_setting = &form_setting;
    AboutUs.text_setting = &form_setting;
    Exit.button_setting = &form_setting;
    Exit.text_setting = &form_setting;

    for (auto i : children) i->init();

    // BSTForm.setPosition(center.x - 0.5f*main_button_width, center.y - main_button_height);
    Start.setSize(400, 60);
    Start.setText("Start");
    Start.setPosition(m_windowSize.x / 2 - Start.getSize().x / 2, m_windowSize.y / 2 - Start.getSize().y / 2 - 120);

    Setting.setSize(400, 60);
    Setting.setText("Setting");
    Setting.setPosition(m_windowSize.x / 2 - Setting.getSize().x / 2, m_windowSize.y / 2 - Setting.getSize().y / 2 - 30);

    setting_box.setSize(500, 600);
    setting_box.setPosition(m_windowSize.x/2-setting_box.getSize().x/2, m_windowSize.y/2-setting_box.getSize().y/2);
    setting_box.setDuration(0.2);

    AboutUs.setSize(400,60);
    AboutUs.setText("About Us");
    AboutUs.setPosition(m_windowSize.x / 2 - Start.getSize().x / 2, m_windowSize.y / 2 - AboutUs.getSize().y / 2 + 60);
    
    Exit.setSize(400, 60);
    Exit.setText("Exit");
    Exit.setPosition(m_windowSize.x / 2 - Exit.getSize().x / 2, m_windowSize.y / 2 - Exit.getSize().y / 2 + 150);
}
void MenuStart::handle() {
    if (old_mode != setting_box.getMode()) {
        old_mode = setting_box.getMode();
        if (old_mode) form_setting = DarkTheme;
        else form_setting = LightTheme;
    }
}
void MenuStart::draw() {
    for (auto i : children) i->draw();
}
void MenuStart::close() {
    for (auto& i:children) i->close();
    children.clear();
}
void MenuStart::setMode(const int& mode) {
    setting_box.setMode(mode);
}