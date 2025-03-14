#ifndef GRAPH_H
#define GRAPH_H

#include "Form.h"
#include "GUI.h"
#include <vector>
#include <map>

class Graph: public Form {
public:
    Graph(const Vector2& window_size);
    void            add(const std::string& x)   override,
                    remove()                    override,
                    update(const int& x)        override,
                    search(const int& x)        override,
                    FetchCommandQueue()         override,
                    draw()                      override,
                    handle()                    override;
    ~Graph();
private:
};
#endif