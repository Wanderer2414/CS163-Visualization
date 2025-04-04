#ifndef GRAPH_H
#define GRAPH_H

#include "ColorBox.h"
#include "ColorPointer.h"
#include "Container.h"
#include "Dijikstra_margin.h"
#include "Edge.h"
#include "Form.h"
#include "GUI.h"
#include "HeapVisual.h"
#include "Label.h"
#include "NotationBox.h"
#include "OptionBox.h"
#include "Global.h"
#include "SettingPackage.h"
#include "TextBox.h"
#include "TextureButton.h"
#include <vector>

class Graph: public Form {
public:
    enum CommandCode {
        search_code,
        search_end_code,

        choose_vertex,
        choose_edge,
        unchoose,

        goUp,
        goDown,
        choosev2_vertex,
        choosev2_edge,
        reset_color,
        fill_edge,
        fill_vertex,
        
        fill,
        add_code,
        
        remove_edge,
        remove_vertex,

        add_heap,
        pop_heap,

        prim_code,
        prim_end_code,

        kruskal_code,
        kruskal_end_code,

        dijikstra_code,
        dijkstra_end_code,

        set_cost,
        update_code,
        match_code,
        
        wait
    };
    Graph(const int& index, FormSetting form_setting, const Vector2& window_size);
    
    virtual void        add(const vector<std::string>& value) override,
                        remove(const std::string &str)        override,
                        handle()                              override,
                        draw()                                override,

                        search(const std::string& val)        override,
                        update(const std::string &old_value, const std::string &new_value) override,
                        prim(const std::string& val),
                        kruskal(const string& str),
                        dijikstra(const string& str),
                        FetchNextCommand(const vector<float>& codes) override,
                        FetchPrevCommand(const vector<float>& codes) override;
                        
    virtual string      RandomCreate() const override,
                        RandomSearch() const override;
    void clearGraph();
    ~Graph();
  
private:
    bool                m_is_physics,
                        m_is_lock;
    int                 chosen,
                        m_mode,
                        m_type,
                        m_weight,
                        m_tool,
                        search_type,
                        color_pointer;

    Label               edge_label, vertex_label;
    TextBox             edge_textbox, vertex_textbox, extract_text_bx, prim_textbox, kruskal_textbox, pull_input_textbox,
                        dijikstra_textbox;

    TextureButton       random_edge_button, random_vertex_button, random_prim_button, random_kruskal_button,
                        random_dijikstra_button;

    OptionBox           bfs_choice, dfs_choice;

    TextButton          track_graph_hover,
                        pull_matrix_button,
                        prim_button, kruskal_button,
                        dijikstra_button;
    TabBox              graph_setting, algorithms_box;

    vector<Vertex*>     vertices;
    vector<Edge*>       edges;

    Container           setting_box, tools_box, extract_box, prim_box, kruskal_box, dijikstra_box;

    Container           search_graph_box;

    TextureButton       match_tool, filled_tool, scissors_tool;
    
    OptionBox           fixed_choice, drag_choice, collision_choice, 
                        weight_choice, unweight_choice, 
                        direct_choice, undirect_choice;

    Color               colors[6] = {RED, GREEN, BLUE, YELLOW, BROWN, GRAY};
    Color               tmp_color;
    vector<vector<int>> matrix;
    void                free(),
                        add_edge(const int& start, const int& end, const int& weight),
                        update(const int& index, const int& value);

    Texture2D           cursor_icon;
    TextSetting         console_setting;

    ColorPointer        color_box;
    HeapVisual          heap;
    NotationBox         notation_box;
    string              RandomVertex() const, RandomEdge() const;
    void                insert(const int& value),
                        remove(const int& index),
                        dfs(const int& vertex),
                        dfs(vector<bool>& visited, const int& vertex),
                        bfs(const int& vertex),
                        search_console_add(const int& vertex, const int& mode);

    void                pull_matrix(const int& graph),
                        complete_color(),
                        random_subGraphColor(),
                        setSubGraphColor(const int& row, const Color& color),
                        setSubGraphColor(const int& row, vector<bool>& visited, const Color& color);

    void                prim_console_add(),
                        prim_algorithms(const int& vertex),
                        prim_algorithms(vector<bool>& visited, MinHeap& q, const int& vertex),
                        
                        kruskal_console_add(),
                        kruskal_algorithms(const int& index),
                        
                        dijikstra_console_add(const int& val),
                        dijikstra_algorithms(const int& index),
                        dijikstra_algorithms(const int& index, MinHeap& heap, vector<bool>& visited, vector<int>& board),

                        create_Dmargin(),
                        free_Dmargin();
                        
    vector<vector<int>> pull(const int& index);
    vector<int>         getEdge(const int& graph),
                        getVertex(const int& graph);
    void                getVertex(const int& graph, vector<bool>& visited);
    int                 getVertexIndex(Vertex* node);
    
    int                 findParent(vector<int>& parent, int node);
    void                unionNode(vector<int>& parent, vector<int>& rank, int u, int v);
    void                addVertex(Vertex* node);
    void                addVertex();
    int                 addEdge(int from, int to, int weight);
    void                random(int vertexCount, int maxX, int maxY);
    void                startFromFile(const string filename);
    vector<Dijikstra_Margin*> DMargins;
    vector<Color>             true_color;

};
string to_string(const vector<vector<int>>& matrix);
vector<vector<int>> to_matrix(const vector<string>& str);
vector<vector<int>> create_graph(const int& vertex, const int& edge, const bool& is_direct, const bool& is_weight);
#endif //GRAPH_H