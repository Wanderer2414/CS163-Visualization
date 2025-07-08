#include "Application.h"
#include "General.h"
#include "IncludePath.h"
#include "Global.h"
#include "RedBlackForm.h"

Vector2 WindowSize;

const vector<string> form_name {
    "AVL Tree",
    "Graph",
    "Hash Table",
    "Singly Linked List",
    "Red black tree"
};
FormSetting* setting = 0;
Application::Application()
{
    window_sizes.push_back(MyBase::getWindowSize());
    window_size_index = window_sizes.size()-1;
    InitWindow(window_sizes[window_size_index].x, window_sizes[window_size_index].y, "Visualization");
    InitAudioDevice();
    SetTargetFPS(60);
    WindowSize = window_sizes[window_size_index];
    LightTheme.font = LoadFont(font_link);
    DarkTheme.font = LoadFont(font_link);
}
void Application::run() {
    int form_index = 0;
    int mode = 1;
    setting = &DarkTheme;
    while (!WindowShouldClose()) {
        switch (form_index) {
        case 0: {
            MenuStart menuStart(setting, window_sizes[window_size_index], window_sizes);
            menuStart.setMode(mode);
            menuStart.setSizeIndex(window_size_index);
            form_index = menuStart.run();
            mode = menuStart.getMode();
            if (mode == 0) setting = &LightTheme;
            else setting = &DarkTheme;
            int wsize_index = menuStart.getWindowSizeIndex();
            if (wsize_index != window_size_index) {
                window_size_index = wsize_index;
                WindowSize = window_sizes[window_size_index];
                SetWindowSize(window_sizes[window_size_index].x,window_sizes[window_size_index].y);
            }
        }
            break;
        case 1: {
            Menu menu(*setting, window_sizes[window_size_index]);
            form_index = menu.run();
        }
            break;
        case 2: {
            AboutUsForm aboutus(*setting, window_sizes[window_size_index]);
            form_index = aboutus.run();
        }
            break;
        case 3: {
            AVLTreeForm AVLtreeForm(0);
            form_index = AVLtreeForm.run();
        }
            break;
        case 4: {
            Graph GraphForm(1);
            form_index = GraphForm.run();
        }
            break;
        case 5: {
            HT::HashTable HashTableForm(2);
            form_index = HashTableForm.run();
        }
            break;
        case 6: {
            SLL::SLLForm SLLForm(3);
            form_index = SLLForm.run();
        }
            break;
        case 7: {
            RedBlackForm RBForm(4);
            form_index = RBForm.run();
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
    CloseAudioDevice();
}