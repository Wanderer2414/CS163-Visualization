#ifndef APPLICATION_H
#define APPLICATION_H

#include "Form.h"
#include "Graph.h"
#include "Menu.h"
#include "BinaryTree.h"
#include "Graph.h"
#include "StringTreeForm.h"
class Application {
public:
    Application();
    void    run();
    ~Application();
private:
    int     m_width = 800,
            m_height = 600;
    Menu    menu;
    BinaryTreeForm  BSTForm;
    Graph           GraphForm;
    StringTreeForm  StrTreeForm;
};

#endif