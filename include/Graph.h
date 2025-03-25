#ifndef GRAPH_H
#define GRAPH_H

#include "Container.h"
#include "Edge.h"
#include "Form.h"
#include "GUI.h"
#include "Vertex.h"
#include "OptionBox.h"
#include <string>
#include <vector>
#include <map>
#include <vector>

class Graph: public Form {
public:
    Graph(const int& index, FormSetting form_setting, const Vector2& window_size);
    
    virtual void        add(const vector<std::string>& value) override,
                        handle()                              override,
                        draw()                                override;
    virtual string      RandomCreate() const override;
    ~Graph();
private:
    bool                m_is_physics;
    int                 chosen,
                        m_mode;
    TextButton          track_graph_hover;
    TabBox              graph_setting;
    vector<Vertex>      vertices;
    vector<Edge>        edges;
    Container           setting_box;
    OptionBox           fixed_box, drag_box, collision_box;
};
#endif