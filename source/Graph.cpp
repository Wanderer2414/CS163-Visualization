#include "../include/Graph.h"
#include "../include/Vertex.h"
#include "../include/General.h"
#include "../include/DSU.h"
#include <climits>
#include <queue>

void Graph::search(const string& val) {
    float i = to_int(val);
    if (i<vertices.size()) {
        int value = vertices[i]->getValue();
        if (search_type == 0)
            console.InsertNextMainCommand("Search " + to_string(value) + " with DFS");
        else console.InsertNextMainCommand("Search " + to_string(value) + " with BFS");
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
        for (int i = 0; i<edges.size(); i++) 
            if (edges[i]) edges[i]->start(false);
    } else {
        InsertNextMainCommand({add_code, 1.0f*to_int(str[0]),1});
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
            InsertNextSubCommand({choose_vertex, 1.0f*vertex, 1.0f*neighbor,  1});
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

void Graph::bfs(const int& vertex) {
    queue<pair<int,int>> q;
    vector<bool> visited(matrix.size(), 0);
    visited[vertex] = true;
    q.push({vertex, vertex});
    InsertNextSubCommand({goDown, 1, 0.2});
    while (q.size()) {
        InsertNextSubCommand({goDown, 1, 0.2});
        for (int i = 0; i<matrix.size(); i++) {
            if (matrix[q.front().second][i] != -1 && !visited[i]) {
                q.push({q.front().second, i});
                visited[i] = true;
            }
        }
        InsertNextSubCommand({goDown, 1, 0});
        if (q.front().first != q.front().second) {
            InsertNextSubCommand({choose_edge, 1.0f*q.front().first, 1.0f*q.front().second, 1});
        }
        InsertNextSubCommand({choose_vertex, 1.0f*q.front().first, 1.0f*q.front().second, 1});
        InsertNextSubCommand({goUp, 2, 0.2});
        q.pop();
    }
    InsertNextSubCommand({goDown, 3, 0.2});
}
void Graph::insert(const int& value) {
    vertices.push_back(new Vertex(&form_setting, vertices.size()));
    vertices.back()->setPosition(m_workspace.width/2, m_workspace.height/2);
    vertices.back()->setSize(50, 50);;
    vertices.back()->setValue(value);
    vertices.back()->setColor(colors[(++color_pointer)%6]);
    for (int i =0; i<matrix.size() ;i++) matrix[i].push_back(-1);
    matrix.push_back(vector<int>(matrix.size()+1, -1));
}
void Graph::remove(const int& i) {
    InsertNextMainCommand({remove_vertex, 1.0f*i, 1.0f*vertices[i]->getValue(), to_float(vertices[i]->getColor()), 1});
    for (int j = 0; j<edges.size(); j++) {
        if (edges[j]) {
            int start = edges[j]->m_start->getIndex();
            int end = edges[j]->m_end->getIndex();
            if (start == i || end == i) {
                InsertNextMainCommand({remove_edge,1.0f*j, 1.0f*start, 1.f*end, 1.0f*edges[j]->getWeight(), 1});
            }
        }
    }
}
void Graph::remove(const std::string& str) {
    int i = to_int(str);
    if (i<vertices.size()) {
        remove(i);
    }

}
void Graph::update(const int& index, const int& value) {
    vertices[index]->setValue(value);
}
void Graph::update(const std::string &old_value, const std::string &new_value) {
    int i = to_int(old_value);
    if (i<vertices.size()) {
        InsertNextMainCommand({update_code, 1.0f*i, 1.0f*vertices[i]->getValue(), 1.0f*to_int(new_value), 0.1});
    }
}
void Graph::prim(const std::string& str) {
    float i = to_int(str);
    if (i<vertices.size()) {
        console.InsertNextMainCommand("Prim: start at vertex = " + to_string(vertices[i]->getValue()));
        InsertNextMainCommand({prim_code, i, 1});
    }
}
void Graph::kruskal(const string& str) {
    float i = to_int(str);
    if (i<vertices.size()) {
        console.InsertNextMainCommand("Kruskal");
        InsertNextMainCommand({kruskal_code, i, 1});
    }
}
void Graph::dijikstra(const string& str) {
    float i = to_int(str);
    if (i<vertices.size()) {
        console.InsertNextMainCommand("Dijikstra at " + str);
        InsertNextMainCommand({dijikstra_code, i, 1});
    }
}
void Graph::create_Dmargin() {
    for (int i = 0; i<vertices.size(); i++) {
        DMargins.push_back(new Dijikstra_Margin(vertices[i]));
    }
}
void Graph::dijikstra_algorithms(const int& index) {
    InsertNextSubCommand({goDown, 1, 0.2});
    InsertNextSubCommand({choosev2_vertex, 1.0f*index, 1.0f*index, 0});
    InsertNextSubCommand({goDown, 1, 0.2});
    InsertNextSubCommand({set_cost, 1.0f*index, 0, 0.1});
    vector<int> board(vertices.size(), INT_MAX);
    vector<bool> visited(vertices.size(), 0);
    board[index] = 0;
    MinHeap q;
    InsertNextSubCommand({goDown, 1, 0.2});
    dijikstra_algorithms(index, q, visited, board);
};
void Graph::dijikstra_algorithms(const int& index, MinHeap& heap, vector<bool>& visited, vector<int>& board) {
    visited[index] = true;
    InsertNextSubCommand({goDown, 1, 0.2});
    for (int i = 0; i<matrix.size(); i++) {
        if (matrix[index][i]!=-1 && !visited[i]) {
            InsertNextSubCommand({goDown, 1, 0.2});
            int weight = edges[matrix[index][i]]->getWeight();
            InsertNextSubCommand({choose_edge, 1.0f*index, 1.0f*i, 1.0f*weight, 1});
            if (board[index] + weight < board[i]) {
                board[i] = board[index] + weight;
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({set_cost, 1.0f*i, 1.0f*board[i], 0.1});
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({add_heap, 1.0f*index, 1.0f*i, 1.0f*weight, 0});
                heap.Insert({index, i, weight});
                InsertNextSubCommand({goUp, 2, 0.2});;
            }
            InsertNextSubCommand({goUp, 1, 0.2});
        }
    }
    InsertNextSubCommand({goDown, 4, 0.2});
    InsertNextSubCommand({goDown, 1, 0.2});
    while (heap.size() && visited[heap.front().end]) {
        InsertNextSubCommand({pop_heap, 1.0f*heap.front().start, 1.0f*heap.front().end, 1.0f*heap.front().weight, 1});
        heap.pop();
    }

    InsertNextSubCommand({goDown, 1, 0.2});
    if (heap.size()) {
        Path q = heap.front();
        InsertNextSubCommand({goDown, 1, 0.2});
        InsertNextSubCommand({fill_vertex, 1.0f*q.start, to_float(vertices[q.end]->getColor()), 1});
        InsertNextSubCommand({choosev2_vertex, 1.0f*q.start, 1.0f*q.end,1});
        InsertNextSubCommand({choose_edge, 1.0f*q.start, 1.0f*q.end, 1});
        InsertNextSubCommand({pop_heap, 1.0f*q.start, 1.0f*q.end, 1.0f*q.weight, 1});
        heap.pop();
        InsertNextSubCommand({goUp, 8, 0.2});
        dijikstra_algorithms(q.end, heap, visited, board);
    }
}
void Graph::free_Dmargin() {
    for (int i = 0; i<vertices.size(); i++) {
        delete DMargins[i];
    }
    DMargins.clear();
}
void Graph::FetchNextCommand(const vector<float>& codes) {
    int code = codes[0];
    switch (code) {
        case add_code: {
            int val = codes[1];
            insert(val);
            setDuration(0.1);
        }
        break;
        case search_code: {
            int index = codes[2];
            int mode = codes[1];
            int value = vertices[index]->getValue();
            if (!mode) {
                InsertNextSubCommand({lock, 0});
                InsertNextSubCommand({reset_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                console.InsertNextSubCommand("Create visited[n]");
                console.InsertNextSubCommand("vertex = " + to_string(value));
                console.InsertNextSubCommand("f(vertex) {");
                console.InsertNextSubCommand("   visited[vertex] = true ");
                console.InsertNextSubCommand("   for i = first_des to last_des ");
                console.InsertNextSubCommand("      if this des didn't visited");
                console.InsertNextSubCommand("          f(i)");
                console.InsertNextSubCommand("}");
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({fill_vertex, 1.0f*index, to_float(vertices[index]->getColor()), 1});

                InsertNextSubCommand({goDown, 1, 0.2});
                
                dfs(index);
                InsertNextSubCommand({choosev2_vertex, 1.0f*index, 1.0f*index, 1});
                InsertNextSubCommand({goDown, 3, 2});
                InsertNextSubCommand({unlock, 0});
                InsertNextSubCommand({complete_color, 0});
                InsertNextSubCommand({fill, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                setDuration(0);
            }
            else {
                InsertNextSubCommand({lock, 0});
                InsertNextSubCommand({reset_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                console.InsertNextSubCommand("Create queue");
                console.InsertNextSubCommand("add vertex = " + to_string(value) + " to queue");
                console.InsertNextSubCommand("while queue not empty");
                console.InsertNextSubCommand("   Push all child to queue ");
                console.InsertNextSubCommand("   pop front of queue");
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({fill_vertex, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                
                InsertNextSubCommand({fill_vertex, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                bfs(index);
                
                InsertNextSubCommand({unlock, 0});
                InsertNextSubCommand({complete_color, 0});
                InsertNextSubCommand({fill, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                setDuration(0);
            }
        }
        break;
        case reset_color: {
            int n = codes[1];
            setSubGraphColor(n, PURPLE);
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
        case lock: {
            m_is_lock = true;
            setDuration(0);
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
            vertices[end]->start(arctan(delta), BROWN ,vertices[end]->getColor());
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
                if (edges[i]) {
                    if (edges[i]->m_start->getIndex() == index) {
                        edges[i]->setDuration(getSpeed()*codes.back());
                        edges[i]->start(false, false);
                    } else edges[i]->setDuration(0);
                }
            }
            setDuration(codes.back());
        }
        break;
        case complete_color: {
            for (int i = 0; i<vertices.size(); i++) 
                if (vertices[i]) vertices[i]->complete();
            for (int i = 0; i<edges.size(); i++) 
                if (edges[i]) edges[i]->complete();
            setDuration(codes.back());
        }
        break;
        case remove_edge: {
            int index = codes[1];
            int start = codes[2], end = codes[3];
            int weight = codes[4];
            delete edges[index];
            edges[index] = 0;
            matrix[start][end] = -1;
            setDuration(0);
        }
        break;
        case remove_vertex: {
            int index = codes[1];
            delete vertices[index];
            vertices[index] = 0;
            setDuration(0.1);
        }
        break;
        case prim_code: {
            int index = codes[1];
            heap.clear();
            console.InsertNextSubCommand("f(vertex)");
            console.InsertNextSubCommand("  Add all edge start at vertex to heap");
            console.InsertNextSubCommand("  Pop all edges with used end vertex from heap");
            console.InsertNextSubCommand("  while heap have element ");
            console.InsertNextSubCommand("      vertex = top heap -> end");
            console.InsertNextSubCommand("      Pop top heap");
            console.InsertNextSubCommand("      f(vertex)");
            console.goDown();
            InsertNextSubCommand({show_heap});
            InsertNextSubCommand({lock, 1});
            InsertNextSubCommand({reset_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            InsertNextSubCommand({fill_vertex, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            prim_algorithms(index);
            InsertNextSubCommand({unlock, 0});
            InsertNextSubCommand({complete_color, 0});
            InsertNextSubCommand({hide_heap});
            InsertNextSubCommand({goDown, 4, 0});
            InsertNextSubCommand({fill, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            setDuration(0);
        }
        break;
        case kruskal_code: {
            int index = codes[1];
            heap.clear();
            console.InsertNextSubCommand("f(vertex)");
            console.InsertNextSubCommand("  Add all edge to heap");
            console.InsertNextSubCommand("  while heap has element");
            console.InsertNextSubCommand("      Pop all next edge make cycle");
            console.InsertNextSubCommand("      Add top edges to DSU");
            console.InsertNextSubCommand("      Pop top edge");
            console.goDown();
            InsertNextSubCommand({show_heap, 1});
            InsertNextSubCommand({lock, 1});
            InsertNextSubCommand({reset_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            kruskal_algorithms(index);
            InsertNextSubCommand({unlock, 0});
            InsertNextSubCommand({complete_color, 0});
            InsertNextSubCommand({hide_heap});
            InsertNextSubCommand({goDown, 3, 0});
            InsertNextSubCommand({fill, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            setDuration(0);
        }
        break;
        case add_heap: {
            int start = vertices[codes[1]]->getValue(), end = vertices[codes[2]]->getValue(), weight = codes[3];
            heap.Insert({start, end, weight});
            setDuration(codes[4]);
        }
        break;
        case pop_heap: {
            heap.pop();
            setDuration(0);
        }
        break;
        case show_heap: {
            heap.setVisible(true);
            setDuration(0);
        }
        break;
        case hide_heap: {
            heap.setVisible(false);
            setDuration(0);
        }
        break;
        case dijikstra_code: {
            int index = codes[1];
            heap.clear();
            InsertNextSubCommand({prepare_dijikstra, 1});
            InsertNextSubCommand({show_heap, 1});
            InsertNextSubCommand({lock, 1});
            InsertNextSubCommand({reset_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            int value = vertices[index]->getValue();
            console.InsertNextSubCommand("Create min heap");
            console.InsertNextSubCommand("vertex = " + to_string(value));
            console.InsertNextSubCommand("Set cost at vertex = 0");
            console.InsertNextSubCommand("f(vertex)");
            console.InsertNextSubCommand("   for i = first edge to last edge");
            console.InsertNextSubCommand("      if cost[vertex] + cost[edge] < cost[end]");
            console.InsertNextSubCommand("         cost[end] = cost[vertex] + cost[edge]");
            console.InsertNextSubCommand("         add edge to min heap");
            console.InsertNextSubCommand("   Pop all next edges with used end");
            console.InsertNextSubCommand("   if heap has element: ");
            console.InsertNextSubCommand("         vertex = heap.pop()[end] ");
            console.InsertNextSubCommand("         f(vertex) ");
            InsertNextSubCommand({goDown, 1, 0.2});
            dijikstra_algorithms(index);
            InsertNextSubCommand({goDown, 2, 0.2});
            InsertNextSubCommand({unlock, 1});
            InsertNextSubCommand({complete_color, 0});
            InsertNextSubCommand({hide_heap, 1});
            InsertNextSubCommand({free_dijikstra, 1});
            InsertNextSubCommand({fill, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            setDuration(0);
        }
        break;
        case prepare_dijikstra: {
            create_Dmargin();
            setDuration(0);
        }
        break;
        case free_dijikstra: {
            free_Dmargin();
            setDuration(0);
        }
        break;
        case set_cost: {
            DMargins[codes[1]]->setValue(codes[2]);
            setDuration(codes.back());
        }
        break;
        case update_code: {
            update(codes[1], codes[3]);
            setDuration(codes.back());
        }
        break;
        case match_code: {
            console.goDown();
            int index = codes[1];
            int start = codes[2], end = codes[3];
            edges[index] = new Edge(vertices[start], vertices[end], &form_setting);
            edges[index]->start(false);
            edges[index]->setType(m_type == 0);
            edges[index]->setDuration(codes.back()*getSpeed());
            edges[index]->setWeight(codes[4]);
            matrix[start][end] = index;
            setDuration(codes.back());
        }
        break;
    }
}
void Graph::FetchPrevCommand(const vector<float>& codes) {
    int code = codes[0];
    switch (code) {
        case add_code: {
            int i = vertices.size()-1;
            while (i>=0 && (!vertices[i] || vertices[i]->getValue() != codes[1])) i--;
            if (i>=0) {
                delete vertices[i];
                vertices[i] = 0;
                color_pointer = (color_pointer-1 + 6)%6;
            }
            setDuration(0.1);
        }
        break;
        case search_code: {
            console.goUp();
            setDuration(1);
        }
        break;
        case reset_color: {
            int n = codes[1];
            setSubGraphColor(n, to_color(codes[2]));
            setDuration(0);
        }
        break;
        case goUp: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goDown();
            setDuration(codes.back());
        }
        break;
        case goDown: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goUp();
            setDuration(codes.back());
        }
        break;
        case choose_edge: {
            int start = codes[1], end = codes[2];
            if (start<end) {
                edges[matrix[start][end]]->setDuration(codes.back()*getSpeed());
                edges[matrix[start][end]]->start(true, false);
            }
            else {
                edges[matrix[end][start]]->setDuration(codes.back()*getSpeed());
                edges[matrix[end][start]]->start(false, false);
            }
            setDuration(codes.back());
        }
        break;
        case choose_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[end]->getCenter() - vertices[start]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->setDuration(codes.back()*getSpeed());
            vertices[end]->start(arctan(delta),PURPLE ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        case fill_vertex: {
            int index = codes[1];
            vertices[index]->setColor(to_color(codes[2]));
            setDuration(codes.back());
        }
        break;
        case choosev2_edge: {
            int start = codes[1], end = codes[2];
            if (start<end) {
                edges[matrix[start][end]]->setDuration(codes.back()*getSpeed());
                edges[matrix[start][end]]->start(true, false);
            }
            else {
                edges[matrix[end][start]]->setDuration(codes.back()*getSpeed());
                edges[matrix[end][start]]->start(false, false);
            }
            setDuration(codes.back());
        }
        break;
        case choosev2_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[end]->getCenter() - vertices[start]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->start(arctan(delta), BROWN ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        case unlock: {
            m_is_lock = true;
            setDuration(codes.back());
        }
        break;
        case fill: {
            int index = codes[1];
            setDuration(codes.back());
        }
        break;
        case spread_color: {
            int index = codes[1];
            setDuration(codes.back());
        }
        break;
        case complete_color: {
            setDuration(codes.back());
        }
        break;
        case remove_edge: {
            int index = codes[1];
            int start = codes[2], end = codes[3];
            int weight = codes[4];
            edges[index] = new Edge(vertices[start], vertices[end], &form_setting);
            edges[index]->setDuration(0.5);
            edges[index]->start(false);
            edges[index]->setWeight(weight);
            matrix[start][end] = index;
            setDuration(0.1);
        }
        break;
        case remove_vertex: {
            int index = codes[1];
            vertices[index] = new Vertex(&form_setting, index);
            vertices[index]->setValue(codes[2]);
            vertices[index]->setColor(to_color(codes[3]));
            vertices[index]->setSize(50, 50);
            setDuration(0.1);
        }
        break;
        case prim_code: {
            console.goUp();
            setDuration(0.5);
        }
        break;
        case kruskal_code: {
            console.goUp();
            setDuration(0.5);
        }
        break;
        case add_heap: {
            Path path;
            path.start = vertices[codes[1]]->getValue();
            path.end = vertices[codes[2]]->getValue();
            path.weight = codes[3];
            for (int i = 0; i<heap.size(); i++)
                if (heap[i] == path) {
                    heap.erase(i);
                    break;
                }
            setDuration(codes.back());
        }
        break;
        case pop_heap: {
            Path path;
            path.start = vertices[codes[1]]->getValue();
            path.end = vertices[codes[2]]->getValue();
            path.weight = codes[3];
            heap.Insert(path);
            setDuration(0);
        }
        break;
        case show_heap: {
            heap.setVisible(false);
            setDuration(0);
        }
        break;
        case hide_heap: {
            heap.setVisible(true);
            setDuration(0);
        }
        break;
        case update_code: {
            update(codes[1], codes[2]);
            setDuration(codes.back());
        }
        break;
        case match_code: {
            int index = codes[1];
            int start = codes[2], end = codes[3];
            delete edges[index];
            edges[index] = 0;
            matrix[start][end] = -1;
            console.goUp();
            setDuration(codes.back());
        }
        break;
    }
}
void Graph::prim_algorithms(const int& vertex) {
    vector<bool> visited(matrix.size(), 0);
    visited[vertex] =true;
    MinHeap q;
    prim_algorithms(visited, q, vertex);
}

void Graph::prim_algorithms(vector<bool>& visited, MinHeap& q, const int& vertex) {
    InsertNextSubCommand({goDown, 1, 0.5});
    for (int i = 0; i<matrix.size(); i++) {
        if (matrix[vertex][i] != -1 && !visited[i]) { 
            int weight = edges[matrix[vertex][i]]->getWeight();
            InsertNextSubCommand({add_heap, 1.0f*vertex, 1.0f*i, 1.0f*weight, 0});
            q.Insert({vertex, i, weight});
        }
    }
    InsertNextSubCommand({goDown, 1, 0.5});
    while (q.size() && visited[q.front().end]) {
        InsertNextSubCommand({pop_heap, 1.0f*q.front().start, 1.0f*q.front().end, 1.0f*q.front().weight});
        q.pop();
    }
    InsertNextSubCommand({goDown, 1, 0.5});
    if (q.size()) {
        InsertNextSubCommand({goDown, 1, 0});
        visited[q.front().end] = true;
        InsertNextSubCommand({choose_edge, 1.0f*q.front().start, 1.0f*q.front().end, 1});
        InsertNextSubCommand({choose_vertex, 1.0f*q.front().start, 1.0f*q.front().end, 1});
        InsertNextSubCommand({goDown, 1, 0.5});
        InsertNextSubCommand({pop_heap, 1.0f*q.front().start, 1.0f*q.front().end, 1.0f*q.front().weight});
        int end = q.front().end;
        q.pop();
        InsertNextSubCommand({goDown, 1, 0.5});
        InsertNextSubCommand({goUp, 6, 0.5});
        prim_algorithms(visited, q, end);
    }
}

void Graph::kruskal_algorithms(const int& index) {
    MinHeap q;
    DSU dsu(matrix.size());
    vector<int> edges_index = getEdge(index);
    InsertNextSubCommand({goDown, 1, 0.5});
    for (int i = 0; i<edges_index.size(); i++) {
        int index = edges_index[i];
        Path path = {edges[index]->m_start->getIndex(), edges[index]->m_end->getIndex(), edges[index]->getWeight()};
        if (path.start < path.end) {
            q.Insert(path);
            InsertNextSubCommand({add_heap, 1.0f*path.start, 1.0f*path.end, 1.0f*path.weight, 0});
        }
    }
    InsertNextSubCommand({goDown, 1, 0.5});
    InsertNextSubCommand({goDown, 1, 0.5});
    while (q.size()) {
        if (dsu.check(q.front().start, q.front().end)) {
            q.pop();
            InsertNextSubCommand({pop_heap, 1.0f*q.front().start, 1.0f*q.front().end, 1.0f*q.front().weight, 0});
        } else {
            InsertNextSubCommand({goDown, 1, 0.5});
            InsertNextSubCommand({fill_vertex, 1.0f*q.front().start, to_float(vertices[q.front().start]->getColor()),  1});
            InsertNextSubCommand({choose_edge, 1.0f*q.front().start, 1.0f*q.front().end, 1.0f*q.front().weight, 1});
            InsertNextSubCommand({choose_vertex, 1.0f*q.front().start, 1.0f*q.front().end,  1});
            dsu.join(q.front().start, q.front().end);
            InsertNextSubCommand({goDown, 1, 0.5});
            InsertNextSubCommand({pop_heap, 0});
            q.pop();
            InsertNextSubCommand({goUp, 3, 0.5});
            InsertNextSubCommand({goDown, 1, 0.5});
        }
    }
}

Graph::~Graph() {
    free();
}