#pragma once

#include "Form.h"
#include "Menu.h"
class Application {
public:
    Application();
    void    run();
    ~Application();
private:
    int     m_width = 800,
            m_height = 600;
    Menu    menu;
    Form    form;
};
