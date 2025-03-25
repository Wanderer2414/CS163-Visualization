#ifndef GRAPH_H
#define GRAPH_H

#include "Form.h"
#include "GUI.h"
#include "Global.h"

class Graph: public Form {
public:
    Graph(const int& index, FormSetting form_setting, const Vector2& window_size);
    ~Graph();
private:
};
#endif //GRAPH_H