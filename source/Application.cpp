#include "../include/Application.h"
#include "../raylib/raylib.h"
#include "../include/IncludePath.h"
Application::Application() :
    menu            ({ 1.0f * m_width, 1.0f * m_height }),
    BSTForm         ({ 1.0f * m_width, 1.0f * m_height }),
    GraphForm       ({ 1.0f * m_width, 1.0f * m_height }),
    menuStart       ({ 1.0f * m_width, 1.0f * m_height }),
    HashTableForm   ({ 1.0f * m_width, 1.0f * m_height}),
    SLLForm         ({ 1.0f * m_width, 1.0f * m_height })
{
    InitWindow(m_width, m_height, "Visualization");
    SetTargetFPS(60);
    LightTheme.font = LoadFont(font_link);
    DarkTheme.font = LoadFont(font_link);
    NeonTheme.font = LoadFont(font_link);
}
void Application::setMode(const int& index, FormSetting& setting) {
    switch (index) {
        case 0: {
            setting = LightTheme;
        }
        break;
        case 1: {
            setting = DarkTheme;
        }
        break;
        case 2: {
            setting = NeonTheme;
        }
        break;
    
    }
}
void Application::run() {
    int form_index = 0;
    int mode = 1;
    while (!WindowShouldClose()) {
        switch (form_index) {
        case 0: {
            setMode(mode, menuStart.form_setting);
            menuStart.init();
            menuStart.setMode(mode);
            form_index = menuStart.run();
            mode = menuStart.getMode();
            menuStart.close();
        }
              break;
        case 1: {
            setMode(mode, menu.form_setting);
            menu.init();
            form_index = menu.run();
            menu.close();
        }
              break;
        case 3: {
            setMode(mode, BSTForm.form_setting);
            BSTForm.init();
            form_index = BSTForm.run();
            BSTForm.close();
        }
              break;
        case 4: {
            setMode(mode, GraphForm.form_setting);
            GraphForm.init();
            form_index = GraphForm.run();
            GraphForm.close();
        }
              break;
        case 5: {
            setMode(mode, HashTableForm.form_setting);
            HashTableForm.init();
            form_index = HashTableForm.run();
            HashTableForm.close();
        }
            break;
        case 6: {
            setMode(mode, SLLForm.form_setting);
            SLLForm.init();
            form_index = SLLForm.run();
            SLLForm.close();
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