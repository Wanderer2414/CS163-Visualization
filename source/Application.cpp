#include "../include/Application.h"
#include "../raylib/raylib.h"

Application::Application(): 
            menu({1.0f*m_width, 1.0f*m_height}),
            BSTForm({1.0f*m_width, 1.0f*m_height}) ,
            GraphForm({1.0f*m_width, 1.0f*m_height}),
            StrTreeForm({1.0f*m_width, 1.0f*m_height})
{
    InitWindow(m_width, m_height, "Visualization");
    SetTargetFPS(60);
}
void Application::run() {
    int form_index = 0;
    while (!WindowShouldClose()) {
        switch (form_index) {
            case 0: {
                menu.init();
                form_index = menu.run();
                menu.close();
            }
                break;
            case 1: {
                BSTForm.init();
                form_index = BSTForm.run();
                BSTForm.close();
            }
                break;
            case 2: {
                GraphForm.init();
                form_index = GraphForm.run();
                GraphForm.close();
            }
                break;
            case 3: {
                StrTreeForm.init();
                form_index = StrTreeForm.run();
                StrTreeForm.close();
            }
                break;
            default: {
                return ;
            }
                break;
        }
    }
}
Application::~Application() {
    CloseWindow();
}