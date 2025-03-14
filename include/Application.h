#ifndef APPLICATION_H
#define APPLICATION_H

#include "Form.h"
#include "Graph.h"
#include "Menu.h"
#include "BinaryTree.h"
#include "FormStart.h"
#include "Graph.h"
#include "StringTreeForm.h"
class Application {
public:
    Application();
    void    run();
    ~Application();
private:
    int     m_width = 1000,
            m_height = 700;
    Menu    menu;
    MenuStart menuStart;
    BinaryTreeForm  BSTForm;
    Graph           GraphForm;
    Ex::NameTree        StrTreeForm;
};

#endif