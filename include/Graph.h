#ifndef GRAPH_H
#define GRAPH_H

#include "Container.h"
#include "Edge.h"
#include "Form.h"
#include "GUI.h"
#include "Label.h"
#include "OptionBox.h"
#include "Global.h"
#include "SettingPackage.h"
#include "TextBox.h"
#include "TextureButton.h"
#include <vector>

class Graph: public Form {
public:
    enum CommandCode {
        search_code = 0,
        choose_vertex = 1,
        choose_edge = 3,
        unchoose = 2,
        check = 4,
        uncheck = 5,
        goUp = 6,
        goDown = 7,
        choosev2_vertex = 8,
        choosev2_edge = 9,
        reset_color = 10,
        fill_edge = 11,
        fill_vertex = 12,
        unlock = 13,
        fill = 14,
        add_code = 15
    };
    Graph(const int& index, FormSetting form_setting, const Vector2& window_size);
    
    virtual void        add(const vector<std::string>& value) override,
                        handle()                              override,
                        draw()                                override,

                        search(const std::string& val)        override,
                        
                        FetchNextCommand(const vector<float>& codes) override;
    virtual string      RandomCreate() const override;
    ~Graph();
private:
    bool                m_is_physics,
                        m_is_lock;
    int                 chosen,
                        m_mode,
                        m_type,
                        m_weight,
                        m_tool,
                        search_type;

    Label               edge_label, vertex_label;
    TextBox             edge_textbox, vertex_textbox;
    TextureButton       random_edge_button, random_vertex_button;
    OptionBox           bfs_choice, dfs_choice;
    TextButton          track_graph_hover,
                        pull_matrix_button;
    TabBox              graph_setting;

    vector<Vertex*>     vertices;
    vector<Edge*>       true_edges, reverse_edge;

    Container           setting_box, tools_box, extract_box;

    TextBox             extract_text_bx;

    Container           search_graph_box;
    TextureButton       match_tool;
    OptionBox           fixed_choice, drag_choice, collision_choice, 
                        weight_choice, unweight_choice, 
                        direct_choice, undirect_choice;

    int                 color_pointer;
    Color               colors[6] = {RED, GREEN, BLUE, YELLOW, BROWN, GRAY};
    Color               tmp_color;
    vector<vector<int>> matrix;
    void                free(),
                        add_edge(const int& start, const int& end, const int& weight);
    Texture2D           cursor_icon;
    TextSetting         console_setting;


    void                insert(const int& value),
                        dfs(const int& vertex),
                        dfs(vector<bool>& visited, const int& vertex);

    void                pull_matrix(),
                        random_subGraphColor(),
                        setSubGraphColor(const int& row, const Color& color),
                        setSubGraphColor(const int& row, vector<bool>& visited, const Color& color);
};
string to_string(const vector<vector<int>>& matrix);
vector<vector<int>> to_matrix(const vector<string>& str);
vector<vector<int>> create_graph(const int& vertex, const int& edge, const bool& is_direct, const bool& is_weight);
#endif //GRAPH_H