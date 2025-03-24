#ifndef GRAPH_H
#define GRAPH_H

#include "Form.h"
#include "GUI.h"
#include <vector>
#include <map>

class Graph: public Form {
public:
    Graph(const int& index, FormSetting form_setting, const Vector2& window_size);
    ~Graph();
private:
};
#endif