#include "../include/Application.h"
#include "../raylib/raylib.h"

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
}
#include <iostream>
using namespace std;

void Application::run() {
    int form_index = 0;
    while (!WindowShouldClose()) {
        switch (form_index) {
        case 0: {
            menuStart.init();
            form_index = menuStart.run();
            menuStart.close();
        }
              break;
        case 1: {
            menu.init();
            form_index = menu.run();
            menu.close();
        }
              break;
        case 3: {
            BSTForm.init();
            form_index = BSTForm.run();
            BSTForm.close();
        }
              break;
        case 4: {
            GraphForm.init();
            form_index = GraphForm.run();
            GraphForm.close();
        }
              break;
        case 5: {
            HashTableForm.init();
            form_index = HashTableForm.run();
            HashTableForm.close();
        }
            break;
        case 6: {
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