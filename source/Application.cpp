#include "../include/Application.h"
#include "../include/IncludePath.h"
#include "../include/Global.h"

Vector2 WindowSize;
Application::Application()
{
    InitWindow(window_sizes[window_size_index].x, window_sizes[window_size_index].y, "Visualization");
    SetTargetFPS(60);
    WindowSize = window_sizes[window_size_index];
    LightTheme.font = LoadFont(font_link);
    DarkTheme.font = LoadFont(font_link);
}
void Application::run() {
    int form_index = 0;
    int mode = 1;
    FormSetting* form_setting = &DarkTheme;
    while (!WindowShouldClose()) {
        switch (form_index) {
        case 0: {
            MenuStart menuStart(form_setting, window_sizes[window_size_index]);
            menuStart.setMode(mode);
            menuStart.setSizeIndex(window_size_index);
            form_index = menuStart.run();
            mode = menuStart.getMode();
            if (mode == 0) form_setting = &LightTheme;
            else form_setting = &DarkTheme;
            int wsize_index = menuStart.getWindowSizeIndex();
            if (wsize_index != window_size_index) {
                window_size_index = wsize_index;
                WindowSize = window_sizes[window_size_index];
                SetWindowSize(window_sizes[window_size_index].x,window_sizes[window_size_index].y);
            }
        }
            break;
        case 1: {
            Menu menu(*form_setting, window_sizes[window_size_index]);
            form_index = menu.run();
        }
            break;
        case 3: {
            AVLTreeForm AVLtreeForm(0, *form_setting, window_sizes[window_size_index]);
            form_index = AVLtreeForm.run();
        }
            break;
        case 4: {
            Graph GraphForm(1,*form_setting, window_sizes[window_size_index]);
            form_index = GraphForm.run();
        }
            break;
        case 5: {
            HT::HashTable HashTableForm(2, *form_setting, window_sizes[window_size_index]);
            form_index = HashTableForm.run();
        }
            break;
        case 6: {
            SLL::SLLForm SLLForm(3, *form_setting, window_sizes[window_size_index]);
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