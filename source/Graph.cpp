#include "../include/Graph.h"
#include "../include/Vertex.h"
#include "../include/General.h"

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
        int n = to_int(str[0]);
        for (int i = 0; i<n; i++) {
            vertices.push_back(new Vertex(&form_setting, vertices.size()));
            float x = 1.0f*rand()/RAND_MAX*m_window_size.x;
            float y = 1.0f*rand()/RAND_MAX*m_window_size.y;
            vertices.back()->setPosition(x, y);
            vertices.back()->setSize(50, 50);;
            vertices.back()->setValue(matrix.size()+i);
        }
        int delta = n+matrix.size();

        matrix.resize(delta, {});
        for (int i = 0; i<matrix.size(); i++) matrix[i].resize(delta, -1);

        delta -= n;
        for (int i = delta; i<n+delta; i++) {
            for (int j = delta; j<n+delta; j++) {
                int weight = to_int(str[(i-delta)*n+(j-delta)+1]);
                if (weight && i != j) {
                    matrix[i][j] = edges.size();
                    edges.push_back(new Edge(vertices[i], vertices[j], &form_setting));
                    edges.back()->setWeight(weight);
                    if (i<j) edges.back()->setType(m_type == 0);
                }
            }
        }
        setSubGraphColor(delta, colors[(++color_pointer)%6]);
        for (int i = 0; i<edges.size(); i++) edges[i]->start(false);
    } else {
        InsertNextMainCommand({add_code, 1.0f*to_int(str[0])});
    }
}

void Graph::dfs(vector<bool>& visited, const int& vertex) {
    InsertNextSubCommand({goDown, 1, 0.2});
    visited[vertex] = true;
    for (int neighbor = 0; neighbor < matrix.size(); ++neighbor) {
        if (matrix[vertex][neighbor]==-1) continue;
        InsertNextSubCommand({goDown, 1, 0.2});
        if (matrix[vertex][neighbor]!=-1 && !visited[neighbor]) {
            InsertNextSubCommand({goDown, 1, 0});
            InsertNextSubCommand({choose_edge, 1.0f*vertex , 1.0f*neighbor, 1});
            InsertNextSubCommand({goUp, 3, 0});
            InsertNextSubCommand({choose_vertex, 1.0f*vertex, 1.0f*neighbor, 1});
            dfs(visited, neighbor);
            InsertNextSubCommand({choosev2_vertex, 1.0f*vertex, 1.0f*neighbor, 1});
            InsertNextSubCommand({choosev2_edge, 1.0f*neighbor,1.0f*vertex ,  1});
            InsertNextSubCommand({goUp, 1, 0.2});
        }
        InsertNextSubCommand({goUp, 1, 0.2});
    }
    InsertNextSubCommand({goDown, 3, 0.2});
    InsertNextSubCommand({goUp, 1, 0.2});
}
void Graph::dfs(const int& vertex) {
    vector<bool> visited(matrix.size(), 0);
    dfs(visited, vertex);
}
void Graph::insert(const int& value) {
    vertices.push_back(new Vertex(&form_setting, vertices.size()));
    vertices.back()->setPosition(m_workspace.width/2, m_workspace.height/2);
    vertices.back()->setSize(50, 50);;
    vertices.back()->setValue(value);
    vertices.back()->setColor(colors[color_pointer]);
    color_pointer = (color_pointer+1)%6;
    for (int i =0; i<matrix.size() ;i++) matrix[i].push_back(-1);
    matrix.push_back(vector<int>(matrix.size()+1, -1));
}
void Graph::FetchNextCommand(const vector<float>& codes) {
    int code = codes[0];
    switch (code) {
        case add_code: {
            int val = codes[1];
            insert(val);
            setDuration(0);
        }
        break;
        case search_code: {
            int index = codes[2];
            int mode = codes[1];
            int value = vertices[index]->getValue();
            if (!mode) {
                InsertNextSubCommand({reset_color, 1.0f*index, to_float(WHITE), 1});
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

                InsertNextSubCommand({goDown, 1, 0.2});
                
                m_is_lock = true;
                dfs(index);
                InsertNextSubCommand({choosev2_vertex, 1.0f*index, 1.0f*index, 1});
                InsertNextSubCommand({goDown, 2, 2});
                InsertNextSubCommand({unlock, 0});
                InsertNextSubCommand({complete_color, 0});
                InsertNextSubCommand({fill, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                setDuration(0);
            }
            else {
                setDuration(0);
            }
        }
        break;
        case reset_color: {
            int n = codes[1];
            setSubGraphColor(n, to_color(codes[2]));
            setDuration(codes.back());
        }
        break;
        case goUp: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goUp();
            setDuration(codes.back());
        }
        break;
        case goDown: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goDown();
            setDuration(codes.back());
        }
        break;
        case choose_edge: {
            int start = codes[1], end = codes[2];
            if (start<end) {
                edges[matrix[start][end]]->setDuration(codes.back()*getSpeed());
                edges[matrix[start][end]]->start(false, false);
            }
            else {
                edges[matrix[end][start]]->setDuration(codes.back()*getSpeed());
                edges[matrix[end][start]]->start(true, false);
            }
            setDuration(codes.back());
        }
        break;
        case choose_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[start]->getCenter()-vertices[end]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->setDuration(codes.back()*getSpeed());
            vertices[end]->start(arctan(delta),vertices[start]->getColor() ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        case fill_vertex: {
            int index = codes[1];
            vertices[index]->setColor(ORANGE);
            setDuration(codes.back());
        }
        break;
        case choosev2_edge: {
            int start = codes[1], end = codes[2];
            if (start<end) {
                edges[matrix[start][end]]->setDuration(codes.back()*getSpeed());
                edges[matrix[start][end]]->start(false, false);
            }
            else {
                edges[matrix[end][start]]->setDuration(codes.back()*getSpeed());
                edges[matrix[end][start]]->start(true, false);
            }
            setDuration(codes.back());
        }
        break;
        case choosev2_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[start]->getCenter()-vertices[end]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->start(-arctan(delta), BROWN ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        case check: {
            console.goDown();
            int vertex = codes[1];
            tmp_color = vertices[vertex]->getColor();
            vertices[vertex]->setColor(WHITE);
            setDuration(codes.back());
        }
        break;
        case uncheck: {
            int vertex = codes[1];
            vertices[vertex]->setColor(tmp_color);
            setDuration(codes.back());
        }
        break;
        case unlock: {
            m_is_lock = false;
            setDuration(codes.back());
        }
        break;
        case fill: {
            int index = codes[1];
            vertices[index]->setDuration(codes.back()*getSpeed());
            vertices[index]->start(0, to_color(codes[2]), vertices[index]->getColor());
            setDuration(codes.back());
        }
        break;
        case spread_color: {
            int index = codes[1];
            for (int i = 0; i<edges.size(); i++) {
                if (edges[i]->m_start->getIndex() == index) {
                    edges[i]->setDuration(getSpeed()*codes.back());
                    edges[i]->start(false, false);
                } else edges[i]->setDuration(0);
            }
            setDuration(codes.back());
        }
        break;
        case complete_color: {
            for (int i = 0; i<vertices.size(); i++) vertices[i]->complete();
            for (int i = 0; i<edges.size(); i++) edges[i]->complete();
            setDuration(codes.back());
        }
        break;
    }
}

Graph::~Graph() {
    free();
}