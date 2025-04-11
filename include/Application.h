#ifndef APPLICATION_H
#define APPLICATION_H

#include "Form.h"
#include "Graph.h"
#include "LinearHashTable.h"
#include "Menu.h"
#include "SinglyLinkedList.h"
#include "AVLTree.h"
#include "FormStart.h"
#include "Graph.h"

class Application {
public:
    Application();
    void    run();
    ~Application();
private:
    float   m_width = 1344,
            m_height = 700;
};

#endif