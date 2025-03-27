#include "../include/Graph.h"
#include "../include/Vertex.h"
#include "../include/General.h"
#include "../include/IncludePath.h"
#include <algorithm>

Graph::Graph(const int& index, FormSetting f_setting, const Vector2& window_size):
    Form(index, f_setting, window_size),
    track_graph_hover(&form_setting, &form_setting),
    graph_setting(&form_setting),
    setting_box(&form_setting),
    fixed_choice(&form_setting, 0, m_mode),
    drag_choice(&form_setting, 1, m_mode),
    collision_choice(&form_setting, 2, m_mode),
    weight_choice(&form_setting, 0, m_weight),
    unweight_choice(&form_setting, 1,m_weight),
    direct_choice(&form_setting, 0, m_type),
    undirect_choice(&form_setting, 1, m_type),

    dfs_choice(&form_setting, 0, search_type),
    bfs_choice(&form_setting, 1, search_type),

    search_graph_box(&form_setting),
    tools_box(&form_setting)
    
{
    children.push_back(&track_graph_hover);
    children.push_back(&graph_setting); 

    setting_box.push_back(&fixed_choice);
    setting_box.push_back(&drag_choice);
    setting_box.push_back(&collision_choice);

    setting_box.push_back(&weight_choice);
    setting_box.push_back(&unweight_choice);

    setting_box.push_back(&direct_choice);
    setting_box.push_back(&undirect_choice);

    tools_box.push_back(&match_tool);

    fixed_choice.setPosition(10, 5);
    fixed_choice.setSize(100, 30);
    fixed_choice.setText("Fixed");

    drag_choice.setPosition(10, 40);
    drag_choice.setSize(100, 30);
    drag_choice.setText("Drag");

    collision_choice.setPosition(10, 75);
    collision_choice.setSize(100, 30);
    collision_choice.setText("Collision");

    weight_choice.setPosition(170, 5);
    weight_choice.setSize(100, 30);
    weight_choice.setText("Weight");

    unweight_choice.setPosition(170, 40);
    unweight_choice.setSize(100, 30);
    unweight_choice.setText("Unweight");

    direct_choice.setPosition(170, 85);
    direct_choice.setSize(100, 30);
    direct_choice.setText("Direct");

    undirect_choice.setPosition(170, 120);
    undirect_choice.setSize(100, 30);
    undirect_choice.setText("Undirect");

    match_tool.setButtonStage(0, match_icon, match_filled_icon);
    match_tool.setPosition(5, 5);
    match_tool.setSize(40, 40);

    graph_setting.setPosition(-300, 100);
    graph_setting.setSize(300, 500);
    graph_setting.setText(0, "Settings");
    graph_setting.setText(1, "Tools");
    graph_setting.setText(2, "Algotithms");
    graph_setting.setText(3,"Extract");
    graph_setting.add_vertex({-300, 100});
    graph_setting.add_vertex({10, 100});
    graph_setting.setVisible(false);
    graph_setting.select(-1);

    setting_box.setSize(340, 170);
    setting_box.setPosition(graph_setting.getAutoSize().x + 15, 0);

    tools_box.setSize(200, 50);
    tools_box.setPosition(graph_setting.getAutoSize().x + 15, 45);

    graph_setting.push_back(0, &setting_box);   
    graph_setting.push_back(1, &tools_box);   

    track_graph_hover.setSize(10, graph_setting.getAutoSize().y);
    track_graph_hover.setPosition(0, 100);
    track_graph_hover.setText("");

    search_graph_box.push_back(&dfs_choice);
    search_graph_box.push_back(&bfs_choice);

    dfs_choice.setSize(100, 30);
    dfs_choice.setPosition(15, 5);
    dfs_choice.setText("Depth first search");

    bfs_choice.setSize(200, 30);
    bfs_choice.setPosition(15, 50);
    bfs_choice.setText("Breath first search");

    search_graph_box.setPosition(option_box.getAutoSize().x + 15, 30);
    search_graph_box.setSize(search_box.getSize().x, 100);
    option_box.push_back(3, &search_graph_box);

    console_setting.font = LoadFont(font_link);
    console_setting.font_size = 20;
    console_setting.spacing = 2;
    console_setting.color = BLACK;
    console.text_setting = &console_setting;

    chosen = -1;
    m_mode = 2;
    m_weight = 1;
    m_type = 1;
    m_tool = -1;
    m_is_lock = false;
    search_type = 0;
};
string Graph::RandomCreate() const {
    srand(time(0));
    int n = rand()%20 + 1;
    string ans = to_string(n) + '\n';
    vector<vector<bool>> matrix(n, vector<bool>(n, 0));
    for (int i = rand()%20; i>=0; i--) {
        int row = rand()%n;
        int col = rand()%n;
        matrix[row][col] = 1;
        matrix[col][row] = 1;
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            ans += to_string(matrix[i][j])+" ";
        }
        ans += '\n';
    }
    return ans;
}
void Graph::search(const string& val) {
    int value = to_int(val);
    float i = 0;
    while (i<vertices.size() && vertices[i]->getValue() != value) i++;
    if (i<vertices.size()) {
        if (search_type == 0)
            console.PushBackMainCommand("Search " + to_string(value) + " with DFS");
        else console.PushBackMainCommand("Search " + to_string(value) + " with BFS");
        InsertNextMainCommand({search_code, 1.0f*search_type, i, 0});
    }
}
void Graph::add(const vector<std::string>& str) {
    if (str.size()>1) {
        free();
        int n = to_int(str[0]);
        for (int i = 0; i<n; i++) {
            vertices.push_back(new Vertex(&form_setting, vertices.size()));
            float x = 1.0f*rand()/RAND_MAX*m_window_size.x;
            float y = 1.0f*rand()/RAND_MAX*m_window_size.y;
            vertices.back()->setPosition(x, y);
            vertices.back()->setSize(50, 50);;
            vertices.back()->setValue(i);
        }
        matrix = vector<vector<int>>(n, vector<int>(n, -1));
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<n; j++) {
                int weight = to_int(str[i*n+j+1]);
                if (weight && i != j) {
                    if (i<j) {
                        matrix[i][j] = true_edges.size();
                        true_edges.push_back(new Edge(vertices[i], vertices[j], &form_setting));
                        true_edges.back()->setWeight(weight);
                        true_edges.back()->setType(m_type == 0);
                    } else {
                        matrix[i][j] = reverse_edge.size();
                        reverse_edge.push_back(new Edge(vertices[i], vertices[j], &form_setting));
                        reverse_edge.back()->setWeight(weight);
                        reverse_edge.back()->setType(true);
                    }
                }
            }
        }
        random_subGraphColor();
        for (int i = 0; i<true_edges.size(); i++) true_edges[i]->start(false);
        for (int i = 0; i<reverse_edge.size(); i++) reverse_edge[i]->start(false);
    } else {
        vertices.push_back(new Vertex(&form_setting, vertices.size()));
        vertices.back()->setPosition(m_workspace.width/2, m_workspace.height/2);
        vertices.back()->setSize(50, 50);;
        vertices.back()->setValue(to_int(str[0]));
        vertices.back()->setColor(colors[rand()%6]);
        for (int i =0; i<matrix.size() ;i++) matrix[i].push_back(-1);
        matrix.push_back(vector<int>(matrix.size()+1, -1));
    }
}

void Graph::dfs(vector<bool>& visited, const int& vertex) {
    InsertNextSubCommand({goDown, 1});
    visited[vertex] = true;
    // InsertNextSubCommand({goDown, 1});
    for (int neighbor = 0; neighbor < matrix.size(); ++neighbor) {
        if (matrix[vertex][neighbor]==-1) continue;
        InsertNextSubCommand({goDown, 1});
        if (matrix[vertex][neighbor]!=-1 && !visited[neighbor]) {
            InsertNextSubCommand({goDown, 1});
            InsertNextSubCommand({choose_edge, 1.0f*vertex , 1.0f*neighbor, 1});
            InsertNextSubCommand({goUp, 3});
            InsertNextSubCommand({choose_vertex, 1.0f*vertex, 1.0f*neighbor, 1});
            dfs(visited, neighbor);
            InsertNextSubCommand({choosev2_vertex, 1.0f*vertex, 1.0f*neighbor, 1});
            InsertNextSubCommand({choosev2_edge, 1.0f*neighbor,1.0f*vertex ,  1});
            InsertNextSubCommand({goUp, 1});
        }
        InsertNextSubCommand({goUp, 1});
    }
    InsertNextSubCommand({goDown, 3});
    InsertNextSubCommand({goUp, 1});
}
void Graph::dfs(const int& vertex) {
    vector<bool> visited(matrix.size(), 0);
    dfs(visited, vertex);
}
void Graph::FetchNextCommand(const vector<float>& codes) {
    int code = codes[0];
    switch (code) {
        case search_code: {
            int index = codes[2];
            int mode = codes[1];
            int value = vertices[index]->getValue();
            InsertNextSubCommand({reset_color, 1.0f*index, 1});
            console.goDown();
            console.InsertNextSubCommand("Create visited[n]");
            console.InsertNextSubCommand("vertex = " + to_string(value));
            console.InsertNextSubCommand("f(vertex) {");
            console.InsertNextSubCommand("   visited[vertex] = true ");
            console.InsertNextSubCommand("   for i = first_des to last_des ");
            console.InsertNextSubCommand("      if this des didn't visited");
            console.InsertNextSubCommand("          f(i)");
            console.InsertNextSubCommand("}");
            console.goDown();
            InsertNextSubCommand({check, 1.0f*value, 1});
            InsertNextSubCommand({uncheck, 1.0f*value, 1});
            InsertNextSubCommand({fill_vertex, 1.0f*index, 1});

            InsertNextSubCommand({goDown, 1});
            
            m_is_lock = true;
            if (mode==0) dfs(index);
            InsertNextSubCommand({choosev2_vertex, 1.0f*index, 1.0f*index, 1});
            InsertNextSubCommand({goDown, 2});
            InsertNextSubCommand({unlock});
            setDuration(0);
        }
        break;
        case reset_color: {
            int n = codes[1];
            setSubGraphColor(n, WHITE);
            setDuration(2);
        }
        break;
        case goUp: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goUp();;
            setDuration(0.3);
        }
        break;
        case goDown: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goDown();
            setDuration(0.3);
        }
        break;
        case choose_edge: {
            int start = codes[1], end = codes[2];
            if (start<end) {
                true_edges[matrix[start][end]]->start(false, false);
            }
            else {
                true_edges[matrix[end][start]]->start(true, false);
            }
            setDuration(1);
        }
        break;
        case choose_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[start]->getCenter()-vertices[end]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->start(arctan(delta),vertices[start]->getColor() ,vertices[end]->getColor());
            setDuration(1);
        }
        break;
        case fill_vertex: {
            int index = codes[1];
            vertices[index]->setColor(ORANGE);
            setDuration(0);
        }
        break;
        case choosev2_edge: {
            int start = codes[1], end = codes[2];
            if (start<end) true_edges[matrix[start][end]]->start(false, false);
            else true_edges[matrix[end][start]]->start(true, false);
            setDuration(1);
        }
        break;
        case choosev2_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[start]->getCenter()-vertices[end]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->start(-arctan(delta), BROWN ,vertices[end]->getColor());
            setDuration(1);
        }
        break;
        case check: {
            console.goDown();
            int vertex = codes[1];
            tmp_color = vertices[vertex]->getColor();
            vertices[vertex]->setColor(WHITE);
            setDuration(0.25);
        }
        break;
        case uncheck: {
            int vertex = codes[1];
            vertices[vertex]->setColor(tmp_color);
            setDuration(0.25);
        }
        break;
        case unlock: {
            m_is_lock = false;
            setDuration(0);
        }
        break;
    }
}
void Graph::draw() {
    for (int i = 0; i<true_edges.size(); i++) {
        true_edges[i]->draw();
    }
    if (m_type == 0) {
        for (int i = 0; i<reverse_edge.size(); i++) reverse_edge[i]->draw();
    }
    for (int i =0 ;i <vertices.size(); i++) vertices[i]->draw();
    Form::draw();

    if (m_tool!=-1) 
        DrawTexture(cursor_icon, GetMousePosition().x, GetMousePosition().y-cursor_icon.height, WHITE);
}
void Graph::handle() {
    Form::handle();
    for (int i = 0; i<true_edges.size(); i++) {
        true_edges[i]->handle();
        true_edges[i]->setMode(m_weight == 0);
        //Check edge color change 
        if (true_edges[i]->IsColorChange() && !m_is_lock) {
            if (!true_edges[i]->IsReverse()) {
                float angular = arctan(true_edges[i]->m_start->getCenter() - true_edges[i]->m_end->getCenter());
                true_edges[i]->m_end->start(angular, true_edges[i]->start_color, true_edges[i]->m_end->getColor());
            } else {
                float angular = arctan(true_edges[i]->m_end->getCenter() - true_edges[i]->m_start->getCenter());
                true_edges[i]->m_start->start(angular, true_edges[i]->end_color, true_edges[i]->m_start->getColor());
            }
        }
        //Vertex color change
        if (!m_is_lock && true_edges[i]->m_start->IsColorChange() && (true_edges[i]->m_start->getColor() != true_edges[i]->start_color)) {
            true_edges[i]->start(false, false);
        }
        if (m_type == 1) {
            if (!m_is_lock && true_edges[i]->m_end->IsColorChange() && (true_edges[i]->m_end->getColor() != true_edges[i]->start_color)) {
                true_edges[i]->start(true, false);
            }
        }
    }
    //Check reverse color change
    if (m_type == 0) {
        for (int i = 0; i<reverse_edge.size(); i++) {
            reverse_edge[i]->handle();
            reverse_edge[i]->setMode(m_weight == 0);
            if (!m_is_lock && reverse_edge[i]->IsColorChange()) {
                if (!reverse_edge[i]->IsReverse()) {
                    float angular = arctan(reverse_edge[i]->m_start->getCenter() - reverse_edge[i]->m_end->getCenter());
                    reverse_edge[i]->m_end->start(angular, reverse_edge[i]->start_color, reverse_edge[i]->m_end->getColor());
                }
            }
            //Check vertex change color
            if (!m_is_lock && reverse_edge[i]->m_start->IsColorChange() && (reverse_edge[i]->m_start->getColor() != reverse_edge[i]->start_color)) {
                reverse_edge[i]->start(false, false);
            }
        }
    }
    bool isFocus = false;
    for (int i = 0; i<vertices.size(); i++) {
        vertices[i]->handle();
        vertices[i]->setFixed(m_mode == 0);
        vertices[i]->setDragable(m_mode == 1);

        //Match vertex
        if (vertices[i]->isFocused()) {
            isFocus = true;
            if (chosen == -1) chosen = i;
            else if (chosen != i) {
                if (m_tool == 0) add_edge(chosen, i, 1);
                chosen = i;
            }
        }
        //Check out window
        if (m_mode != 0) {
            Vector2 pos = vertices[i]->getCenter();
            float radius = vertices[i]->getRadius();
            Vector2 velocity = {0, 0}, acceleration = {0, 0};
            if (pos.x-radius<m_workspace.x)                             {
                acceleration.x = -vertices[i]->getVelocity().x*1.8;
                vertices[i]->setPosition(m_workspace.x + radius, pos.y);
            }
            else if (pos.x+radius>m_workspace.x + m_workspace.width)    {
                acceleration.x = - vertices[i]->getVelocity().x*1.8;
                vertices[i]->setPosition(m_workspace.x + m_workspace.width - radius, pos.y);
            }
            if (pos.y - radius<m_workspace.y)                           {
                acceleration.y = -vertices[i]->getVelocity().y*1.8;
                vertices[i]->setPosition(pos.x, m_workspace.y + radius);
            }
            else if (pos.y+radius > m_workspace.y + m_workspace.height) {
                acceleration.y = -vertices[i]->getVelocity().y*1.8;
                vertices[i]->setPosition(pos.x, m_workspace.y + m_workspace.height - radius);
            }
            vertices[i]->add_acceleration(acceleration);
            //Check collision
            for (int j = i+1; j<vertices.size(); j++) {
                if (abs(vertices[i]->getCenter()-vertices[j]->getCenter()) < vertices[i]->getRadius() + vertices[j]->getRadius()) {
                    Vector2 delta = vertices[j]->getCenter() - vertices[i]->getCenter();
                    delta = delta/abs(delta)*(vertices[i]->getRadius() + vertices[j]->getRadius() - abs(delta));
                    if (m_mode == 2) {
                        Vector2 velocityA = vertices[i]->getVelocity();
                        Vector2 velocityB = vertices[j]->getVelocity();
                        vertices[i]->setVelocity(velocityB - delta/10);
                        vertices[j]->setVelocity(velocityA + delta/10);
                    } else {
                        Vector2 posA = vertices[i]->getPosition() - delta*1.1;
                        Vector2 posB = vertices[j]->getPosition() + delta*1.1;
                        vertices[i]->setPosition(posA.x, posA.y);
                        vertices[j]->setPosition(posB.x, posB.y);
                    }
                }
            }
        }
    }

    //Change type
    if (direct_choice.isChanged() && direct_choice.isPressed()) {
        for (int i = 0; i<true_edges.size(); i++) {
            true_edges[i]->setType(true);
        }
        for (int i = 0; i<reverse_edge.size(); i++) {
            int row = reverse_edge[i]->m_start->getIndex();
            int col = reverse_edge[i]->m_end->getIndex();
            if (matrix[col][row]!=-1)
                reverse_edge[i]->setColor(true_edges[matrix[col][row]]->start_color);
        }
    } else if (undirect_choice.isChanged() && undirect_choice.isPressed()) {
        for (int i = 0; i<true_edges.size(); i++) {
            true_edges[i]->setType(false);
            if (true_edges[i]->start_color != true_edges[i]->m_end->getColor()) 
                true_edges[i]->start(true, false);
        }
    }
    if (!isFocus) chosen = -1;
    //Graph box show
    if (track_graph_hover.isHovered()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = track_graph_hover.getPosition();
            pos.y += GetMouseDelta().y;
            track_graph_hover.setPosition(pos.x, pos.y);
            pos = graph_setting.getPosition();
            pos.y += GetMouseDelta().y;
            graph_setting.setPosition(pos.x, pos.y);
        }
        if (graph_setting.getVertexDone() == 0) {
            graph_setting.setVisible(true);
            graph_setting.next();
        }
    }
    else if (!graph_setting.isHovered()) {
        if (graph_setting.getVertexDone() == 0)
            graph_setting.setVisible(false);
        else if (graph_setting.getVertexDone() == 1) {
            graph_setting.next();
            graph_setting.select(-1);
        }
    }
    //Insert edge/ Match tool press
    if (match_tool.isPressed()) {
        if (m_tool == -1) {
            m_tool = 0;
            HideCursor();
            cursor_icon = LoadTexture(match_cursor_icon);
            cursor_icon.width = cursor_icon.height = 30;
        }
        else {
            ShowCursor();
            UnloadTexture(cursor_icon);
            m_tool = -1;
        }
    }
}
void Graph::free() {
    for (int i = 0; i<vertices.size(); i++) delete vertices[i];
    for (int i = 0; i<true_edges.size(); i++) delete true_edges[i];
    for (int i = 0; i<reverse_edge.size(); i++) delete reverse_edge[i];
    vertices.clear();
    true_edges.clear();
    reverse_edge.clear();
    matrix.clear();
}
void Graph::add_edge(const int& start, const int& end, const int& weight) {
    if (start == end) return;
    if (matrix[start][end]==-1) {
        if (start<end) {
            matrix[start][end] = true_edges.size();
            true_edges.push_back(new Edge(vertices[start], vertices[end], &form_setting));
            true_edges.back()->start(false);
            true_edges.back()->setWeight(weight);
            true_edges.back()->setType(m_type == 0);
        } else {
            matrix[start][end] = reverse_edge.size();
            reverse_edge.push_back(new Edge(vertices[start], vertices[end], &form_setting));
            reverse_edge.back()->setType(true);
            reverse_edge.back()->setWeight(weight);
            if (m_type==0) reverse_edge.back()->start(false);
            else reverse_edge.back()->setColor(vertices[start]->getColor());
        }
    }
    if (m_type == 1) {
        if (matrix[end][start]==-1) {
            if (start>end) {
                matrix[end][start] = true_edges.size();
                true_edges.push_back(new Edge(vertices[end], vertices[start], &form_setting));
                true_edges.back()->start(true);
                true_edges.back()->setWeight(weight);
                true_edges.back()->setType(false);
            } else {
                matrix[end][start] = reverse_edge.size();
                reverse_edge.push_back(new Edge(vertices[end], vertices[start], &form_setting));
                reverse_edge.back()->setColor(vertices[start]->getColor());
                reverse_edge.back()->setType(true);
                reverse_edge.back()->setWeight(weight);
            }
        }
    }
}
void Graph::random_subGraphColor() {
    vector<bool> visited(matrix.size(), 0);
    int color = 0;
    for (int i = 0; i<visited.size(); i++) {
        if (!visited[i]) {
            setSubGraphColor(i, visited, colors[color]);
            color = (color+1)%6;
        }
    }
}
void Graph::setSubGraphColor(const int& row, const Color& color) {
    vector<bool> visited(matrix.size(), 0);
    setSubGraphColor(row, visited, color);
}
void Graph::setSubGraphColor(const int& row, vector<bool>& visited, const Color& color) {
    visited[row] = true;
    vertices[row]->setColor(color);
    for (int i = 0; i<matrix.size(); i++) {
        if (matrix[row][i] != -1) {
            if (row<i) true_edges[matrix[row][i]]->setColor(color);
            else {
                reverse_edge[matrix[i][row]]->setColor(color);
                if (m_type == 1) true_edges[matrix[i][row]]->setColor(color);
            }
        }
        if (matrix[row][i]!=-1 && !visited[i]) {
            setSubGraphColor(i, visited, color);
        }
    }
}
Graph::~Graph() {
    
}