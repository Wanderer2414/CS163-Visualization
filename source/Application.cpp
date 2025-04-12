#include "../include/Application.h"
#include "../include/IncludePath.h"

Vector2 windowSize = {1366, 700};

Application::Application()
{
    InitWindow(windowSize.x, windowSize.y, "Visualization");
    SetTargetFPS(60);
    LightTheme.font = LoadFont(font_link);
    DarkTheme.font = LoadFont(font_link);
}
void Application::run() {
    int form_index = 0;
    int mode = 1;
    int size_index = 0;
    FormSetting* form_setting = &DarkTheme;
    while (!WindowShouldClose()) {
        switch (form_index) {
        case 0: {
            MenuStart menuStart(*form_setting, windowSize);
            menuStart.setMode(mode);
            menuStart.setSizeIndex(size_index);
            form_index = menuStart.run();
            mode = menuStart.getMode();
            if (mode == 0) form_setting = &LightTheme;
            else form_setting = &DarkTheme;
            int wsize_index = menuStart.getWindowSizeIndex();
            if (wsize_index != size_index) {
                size_index = wsize_index;
                windowSize = window_sizes[size_index];
                SetWindowSize(windowSize.x,windowSize.y);
            }
        }
              break;
        case 1: {
            Menu menu(*form_setting, windowSize);
            form_index = menu.run();
        }
              break;
        case 3: {
            AVLTreeForm AVLtreeForm(0, *form_setting, windowSize);
            form_index = AVLtreeForm.run();
        }
            break;
        case 4: {
            Graph GraphForm(1,*form_setting, windowSize);
            form_index = GraphForm.run();
        }
              break;
        case 5: {
            HT::HashTable HashTableForm(2, *form_setting, windowSize);
            form_index = HashTableForm.run();
        }
            break;
        case 6: {
            SLL::SLLForm SLLForm(3, *form_setting, windowSize);
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