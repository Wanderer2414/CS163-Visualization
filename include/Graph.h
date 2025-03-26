#ifndef GRAPH_H
#define GRAPH_H

#include "Container.h"
#include "Edge.h"
#include "Form.h"
#include "GUI.h"
#include "Label.h"
#include "OptionBox.h"
#include "Global.h"
#include "TextBox.h"

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
                        m_mode,
                        m_type,
                        m_weight,
                        m_tool,
                        is_spread_color;

    TextButton          track_graph_hover;
    TabBox              graph_setting;

    vector<Vertex*>     vertices;
    vector<Edge*>       true_edges, reverse_edge;

    Container           setting_box, tools_box;

    Container           search_graph_box;
    TextureButton       match_tool;
    OptionBox           fixed_choice, drag_choice, collision_choice, 
                        weight_choice, unweight_choice, 
                        direct_choice, undirect_choice;

    Color               colors[6] = {RED, GREEN, BLUE, YELLOW, BROWN, GRAY};

    vector<vector<int>> matrix;
    void                free(),
                        add_edge(const int& start, const int& end, const int& weight);
    Texture2D           cursor_icon;
};
#endif //GRAPH_H