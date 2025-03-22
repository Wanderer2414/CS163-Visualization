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
    DarkTheme.font = GetFontDefault();
    NeonTheme.font = GetFontDefault();
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
            menuStart.init();
            setMode(mode, menuStart.form_setting);
            menuStart.setMode(mode);
            form_index = menuStart.run();
            mode = menuStart.getMode();
            menuStart.close();
        }
              break;
        case 1: {
            menu.init();
            setMode(mode, menu.form_setting);
            form_index = menu.run();
            menu.close();
        }
              break;
        case 3: {
            BSTForm.init();
            setMode(mode, BSTForm.form_setting);
            form_index = BSTForm.run();
            BSTForm.close();
        }
              break;
        case 4: {
            GraphForm.init();
            setMode(mode, GraphForm.form_setting);
            form_index = GraphForm.run();
            GraphForm.close();
        }
              break;
        case 5: {
            HashTableForm.init();
            setMode(mode, HashTableForm.form_setting);
            form_index = HashTableForm.run();
            HashTableForm.close();
        }
            break;
        case 6: {
            SLLForm.init();
            setMode(mode, SLLForm.form_setting);
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