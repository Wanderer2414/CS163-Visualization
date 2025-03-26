#include "../include/Application.h"
#include "../include/IncludePath.h"

Application::Application()
{
    InitWindow(m_width, m_height, "Visualization");
    SetTargetFPS(60);
    LightTheme.font = LoadFont(font_link);
    DarkTheme.font = LoadFont(font_link);
    NeonTheme.font = LoadFont(font_link);
}
void Application::run() {
    int form_index = 0;
    int mode = 1;
    FormSetting* form_setting = &DarkTheme;
    while (!WindowShouldClose()) {
        switch (form_index) {
        case 0: {
            MenuStart menuStart(*form_setting, {m_width, m_height});
            menuStart.setMode(mode);
            form_index = menuStart.run();
            mode = menuStart.getMode();
            if (mode == 0) form_setting = &LightTheme;
            else form_setting = &DarkTheme;
        }
              break;
        case 1: {
            Menu menu(*form_setting, {m_width, m_height});
            form_index = menu.run();
        }
              break;
        case 3: {
            BinaryTreeForm  BSTForm(0, *form_setting, {m_width, m_height});
            form_index = BSTForm.run();
        }
            break;
        case 4: {
            Graph GraphForm(1,*form_setting, {m_width, m_height});
            form_index = GraphForm.run();
        }
              break;
        case 5: {
            HT::HashTable HashTableForm(2, *form_setting, {m_width, m_height});
            form_index = HashTableForm.run();
        }
            break;
        case 6: {
            SLL::SLLForm SLLForm(3, *form_setting, {m_width, m_height});
            form_index = SLLForm.run();
        }
              break;
        default: {
            return;
        }
               break;
        }
    }
}
Application::~Application() {
    CloseWindow();
}