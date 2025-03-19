#ifndef APPLICATION_H
#define APPLICATION_H

#include "Form.h"
#include "Graph.h"
#include "LinearHashTable.h"
#include "Menu.h"
#include "SinglyLinkedList.h"
#include "BinaryTree.h"
#include "FormStart.h"
#include "Graph.h"

class Application {
public:
    Application();
    void    run();
    ~Application();
private:
    int     m_width = 1400,
            m_height = 1000;
    Menu            menu;
    MenuStart       menuStart;
    BinaryTreeForm  BSTForm;
    Graph           GraphForm;
    SLL::SLLForm    SLLForm;
    HT::HashTable   HashTableForm;
};

#endif