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
    const Vector2 window_sizes[3] = {
        Vector2({1366, 700}), 
        Vector2({1820, 980}), 
        Vector2({1024, 600}),
    };
    int window_size_index = 0;
};

#endif