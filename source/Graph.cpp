#include "../include/Graph.h"
#include "../include/Vertex.h"
#include "../include/General.h"
#include "../include/DSU.h"

void Graph::dfs(const int& vertex) {
    vector<bool> visited(vertices.size(), 0);
    dfs(visited, vertex);
}
void Graph::dfs(vector<bool>& visited, const int& vertex) {
    InsertNextSubCommand({goDown, 1, 0.2});
    visited[vertex] = true;
    for (auto edge:vertices[vertex]->edges) {
        if (edge) {
            int neighbor = edge->m_end->getIndex();
            InsertNextSubCommand({goDown, 1, 0.2});
            if (!visited[neighbor]) {
                InsertNextSubCommand({goDown, 1, 0});
                InsertNextSubCommand({choose_edge, 1.0f*edge->getGlobalIndex(), 1});
                InsertNextSubCommand({goUp, 3, 0});
                InsertNextSubCommand({choose_vertex, 1.0f*vertex, 1.0f*neighbor,  1});
                dfs(visited, neighbor);
                InsertNextSubCommand({choosev2_vertex, 1.0f*vertex, 1.0f*neighbor, 1});
                InsertNextSubCommand({choose_edge, 1.0f*edge->reverse->getGlobalIndex() ,  1});
                InsertNextSubCommand({goUp, 1, 0.2});
            }
            InsertNextSubCommand({goUp, 1, 0.2});
        }
    }
    InsertNextSubCommand({goDown, 3, 0.2});
    InsertNextSubCommand({goUp, 1, 0.2});
}

void Graph::bfs(const int& vertex) {
    queue<pair<int,int>> q;
    vector<bool> visited(vertices.size(), 0);
    visited[vertex] = true;
    q.push({vertex, -1});
    InsertNextSubCommand({goDown, 1, 0.2});
    while (q.size()) {
        InsertNextSubCommand({goDown, 1, 0.2});
        auto [vertex, iedge] = q.front();
        q.pop();
        InsertNextSubCommand({goDown, 1, 0.2});
        for (Edge* edge:vertices[vertex]->edges) {
            if (edge) {
                int i = edge->m_end->getIndex();
                if (!visited[i]) {
                    q.push({i, edge->getGlobalIndex()});
                    InsertNextSubCommand({choose_edge, 1.0f*edge->getGlobalIndex(), 1});
                    InsertNextSubCommand({choose_vertex, 1.0f*vertex, 1.0f*i, 1});
                    visited[i] = true;
                }
            }
        }
        InsertNextSubCommand({goUp, 2, 0.2});
    }
}
void Graph::insert(const int& value) {
    vertices.push_back(new Vertex(&form_setting, vertices.size()));
    vertices.back()->setPosition(m_workspace.width/2, m_workspace.height/2);
    vertices.back()->setSize(50, 50);;
    vertices.back()->setValue(value);
    vertices.back()->setColor(colors[color_pointer]);
    color_pointer = (color_pointer+1)%6;
}
void Graph::remove(const int& i) {
    InsertNextMainCommand({remove_vertex, 1.0f*i, 1.0f*vertices[i]->getValue(), vertices[i]->getPosition().x, vertices[i]->getPosition().y, to_float(vertices[i]->getColor()), 0.2});
    for (Edge* edge: vertices[i]->edges) {
        if (edge) {
            int reverse = -1;
            if (edge->reverse) {
                reverse = edge->reverse->getGlobalIndex();
                InsertNextMainCommand({remove_edge,  1.0f*edge->m_end->getIndex(), 1.0f*i, 1.0f*edge->reverse->getLocalIndex(), 1.0f*reverse, 1.0f*edge->getGlobalIndex(), 1.0f*edge->reverse->getWeight(), 0.2});
            }
            InsertNextMainCommand({remove_edge,  1.0f*i, 1.0f*edge->m_end->getIndex(), 1.0f*edge->getLocalIndex(), 1.0f*edge->getGlobalIndex(), 1.0f*reverse, 1.0f*edge->getWeight(), 0.2});
        }
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
void Graph::Dijkstra(const string& str) {
    float i = to_int(str);
    if (i<vertices.size()) {
        console.InsertNextMainCommand("Dijkstra at " + str);
        InsertNextMainCommand({Dijkstra_code, i, 1});
    }
}
void Graph::create_Dmargin() {
    DMargins.clear();
    for (int i = 0; i<vertices.size(); i++) {
        DMargins.push_back(new Dijkstra_Margin(vertices[i]));
    }
}
void Graph::Dijkstra_algorithms(const int& index) {
    vector<float> board(vertices.size(), numeric_limits<float>::max());
    vector<bool> visited(vertices.size(), 0);
    board[index] = 0;
    MinHeap q;
    InsertNextSubCommand({goDown, 1, 0});
    InsertNextSubCommand({set_cost, 1.0f*index, 0, 1.0f*DMargins[index]->getValue(), 0.1});
    q.Insert({index, index, 0, -1});
    InsertNextSubCommand({add_heap, 1.0f*index, 1.0f*index, 0, 0});
    InsertNextSubCommand({goDown, 1, 0.2});
    
    while (q.size()) {
        InsertNextSubCommand({goDown, 1, 0.2});
        Path path = q.front();
        q.pop();
        InsertNextSubCommand({goDown, 1, 0.2});
        InsertNextSubCommand({pop_heap, 1.0f*path.start, 1.0f*path.end, 1.0f*path.weight, 0});
        InsertNextSubCommand({goDown, 1, 0.2});
        if (visited[path.end]) {
            InsertNextSubCommand({goDown, 5, 1});
            InsertNextSubCommand({goUp, 8, 1});
            continue;
        }
        InsertNextSubCommand({choose_vertex, 1.0f*path.start, 1.0f*path.end, 1 });
        if (path.index!=-1) InsertNextSubCommand({choose_edge, 1.0f*path.index, 1});
        visited[path.end] = true;
        InsertNextSubCommand({goDown, 1, 0.2});
        for (Edge* edge:vertices[path.end]->edges) {
            if (edge && !visited[edge->m_end->getIndex()]) {
                int weight = edge->getWeight();
                InsertNextSubCommand({choose_edge, 1.0f*edge->getGlobalIndex(), 1});
                if (path.weight + weight < board[edge->m_end->getIndex()]) {
                    InsertNextSubCommand({goDown, 1, 0.2});
                    board[edge->m_end->getIndex()] = weight+path.weight;
                    InsertNextSubCommand({goDown, 1, 0.2});
                    InsertNextSubCommand({set_cost, 1.0f*edge->m_end->getIndex(), 1.0f*board[edge->m_end->getIndex()], 1.0f*DMargins[edge->m_end->getIndex()]->getValue(), 0.1});
                    InsertNextSubCommand({goDown, 1, 0.2});
                    InsertNextSubCommand({add_heap, 1.0f*path.end, 1.0f*edge->m_end->getIndex(), 1.0f*board[edge->m_end->getIndex()], 0});
                    q.Insert({path.end, edge->m_end->getIndex(), int(board[edge->m_end->getIndex()]), edge->getGlobalIndex()});
                    InsertNextSubCommand({goDown, 1, 0.2});
                    InsertNextSubCommand({goUp, 4, 0.2});
                }
                else {
                    InsertNextSubCommand({goDown, 4, 0.2});
                    InsertNextSubCommand({goUp, 4, 0.2});
                } 
            }
        }
        InsertNextSubCommand({choosev2_vertex, 1.0f*path.start, 1.0f*path.end, 1});
        InsertNextSubCommand({goDown, 4, 0.2});
        InsertNextSubCommand({goUp, 8, 0.2});
    }
};
void Graph::free_Dmargin() {
    for (int i = 0; i<DMargins.size(); i++) {
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
                m_is_lock = true;
                InsertNextSubCommand({reset_color, 1.0f*index, 1});
                search_console_add(index, mode);
                console.goDown();
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({fill_vertex, 1.0f*index, 1});

                InsertNextSubCommand({goDown, 1, 0.2});
                
                dfs(index);
                InsertNextSubCommand({reback_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                InsertNextSubCommand({search_end_code,  1.0f*mode, 1.0f*index, 1});
                setDuration(0);
            }
            else {
                m_is_lock = true;
                InsertNextSubCommand({reset_color, 1.0f*index, 1});

                search_console_add(index, mode);
                console.goDown();
        
                InsertNextSubCommand({goDown, 1, 0.2});
                InsertNextSubCommand({fill_vertex, 1.0f*index, 1});
                
                bfs(index);
                InsertNextSubCommand({reback_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
                InsertNextSubCommand({search_end_code,  1.0f*mode, 1.0f*index, 1});
                
                setDuration(0);
            }
        }
        break;
        case search_end_code: {
            int index = codes[2];
            int mode = codes[1];
            if (!mode) {
                console.goDown();
                console.goDown();
                m_is_lock = false;
            } else {
                console.goDown();
                console.goDown();
                console.goDown();
                m_is_lock = false;
            }
            setDuration(codes.back());
        }
        break;
        case wait: {
            setDuration(codes.back());
        }
        break;
        case reset_color: {
            int n = codes[1];
            prevs.push(to_float(vertices[n]->getColor()));
            vector<int> vertices_index= getVertex(n);
            for (int i:vertices_index) vertices[i]->setColor(PURPLE);
            vector<int> edge_index = getEdge(n);
            for (int i:edge_index) edges[i]->setColor(PURPLE);
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
        case reback_color: {
            int n = codes[1];
            vector<int> vertices_index = getVertex(n), edges_index = getEdge(n);
            for (int i:vertices_index) {
                prevs.push(i);
                prevs.push(to_float(vertices[i]->getColor()));
            }
            prevs.push(vertices_index.size());
            for (int i:edges_index) {
                prevs.push(i);
                prevs.push(to_float(edges[i]->start_color));
            }
            prevs.push(edges_index.size());
            Color color = to_color(codes[2]);
            for (int i:vertices_index) vertices[i]->setColor(color);
            for (int i:edges_index) edges[i]->setColor(color);
            setDuration(codes.back());
        }
        break;
        case choose_edge: {
            int index = codes[1];
            if (edges[index]->m_start->getIndex()<edges[index]->m_end->getIndex()) {
                edges[index]->setDuration(codes.back()*getSpeed());
                edges[index]->start(false, false);
            } else {
                edges[index]->reverse->setDuration(codes.back()*getSpeed());
                edges[index]->reverse->start(true, false);
            }
            setDuration(codes.back());
        }
        break;
        case choose_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[start]->getCenter()-vertices[end]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->setDuration(codes.back()*getSpeed());
            vertices[end]->start(arctan(delta),ORANGE ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        case fill_vertex: {
            int index = codes[1];
            vertices[index]->setColor(ORANGE);
            setDuration(codes.back());
        }
        break;
        case choosev2_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[start]->getCenter()-vertices[end]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->start(arctan(delta), LIME ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        break;
        case fill: {
            int index = codes[1];
            vertices[index]->setDuration(codes.back()*getSpeed());
            vertices[index]->start(0, to_color(codes[2]), vertices[index]->getColor());
            setDuration(codes.back());
        }
        break;
        case remove_edge: {
            int globalIndex = codes[4], reverse = codes[5];
            int start = codes[1], end = codes[2], localIndex = codes[3];
            if (reverse!=-1 && edges[reverse]) edges[reverse]->reverse = 0;
            delete edges[globalIndex];
            edges[globalIndex] = 0;
            vertices[start]->edges[localIndex] = 0;
            setDuration(codes.back());
        }
        break;
        case remove_vertex: {
            int index = codes[1];
            if (notation_box.vertex == vertices[index]) notation_box.vertex = 0;
            delete vertices[index];
            vertices[index] = 0;
            setDuration(0.1);
        }
        break;
        case prim_code: {
            int index = codes[1];
            heap.clear();
            prim_console_add();
            heap.setVisible(true);
            m_is_lock = true;
            InsertNextSubCommand({reset_color, 1.0f*index, 1});
            console.goDown();
            InsertNextSubCommand({fill_vertex, 1.0f*index, 1});
            prim_algorithms(index);
            InsertNextSubCommand({reback_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            InsertNextSubCommand({prim_end_code, 1.0f*index, 1});
            setDuration(0.5);
        }
        break;
        case prim_end_code: {
            int index = codes[1];
            m_is_lock = false;
            heap.setVisible(false);
            for (int i = 0; i<7; i++) console.goDown();
            setDuration(codes.back());
        }
        break;
        case kruskal_code: {
            int index = codes[1];
            heap.clear();
            kruskal_console_add();
            console.goDown();
            heap.setVisible(true);
            m_is_lock = true;
            InsertNextSubCommand({reset_color, 1.0f*index, 1});
            kruskal_algorithms(index);
            InsertNextSubCommand({reback_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            InsertNextSubCommand({kruskal_end_code, 1.0f*index, 1});
            setDuration(0.5);
        }
        break;
        case kruskal_end_code: {
            int index = codes[1];
            heap.setVisible(false);
            for (int i = 0; i<3; i++) console.goDown();
            m_is_lock = false;
            setDuration(0.5);
        }
        break;
        case add_heap: {
            int start = vertices[codes[1]]->getValue(), end = vertices[codes[2]]->getValue(), weight = codes[3];
            heap.Insert({start, end, weight});
            setDuration(codes.back());
        }
        break;
        case pop_heap: {
            heap.pop();
            setDuration(0);
        }
        break;
        case Dijkstra_code: {
            int index = codes[1];
            heap.clear();
            create_Dmargin();
            heap.setVisible(true);
            m_is_lock = true;
            InsertNextSubCommand({reset_color, 1.0f*index, 1});
            int value = vertices[index]->getValue();
            Dijkstra_console_add(value);
            console.goDown();
            InsertNextSubCommand({fill_vertex, 1.0f*index, 1});
            Dijkstra_algorithms(index);
            InsertNextSubCommand({reback_color, 1.0f*index, to_float(vertices[index]->getColor()), 1});
            InsertNextSubCommand({dijkstra_end_code, 1.0f*index, 1});
            setDuration(0.5);
        }
        break;
        case dijkstra_end_code: {
            int index = codes[1];
            for (int i = 0; i<9; i++) console.goDown();
            m_is_lock = false;
            heap.setVisible(false);
            vector<int> vertices_index = getVertex(index);
            for (int i:vertices_index) {
                prevs.push(i);
                prevs.push(DMargins[i]->getValue());
            }
            prevs.push(vertices_index.size());
            free_Dmargin();
            setDuration(0.5);
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
            int globalIndex = codes[1], localIndex =codes[2];
            int start = codes[3], end = codes[4];
            add_edge(globalIndex, localIndex, start, end, 1);
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
            int index = codes[2];
            int mode = codes[1];
            int value = vertices[index]->getValue();
            if (!mode) {
                m_is_lock = false;
                console.goUp();
            }
            else {
                m_is_lock = true;
                console.goUp();
            }   
            setDuration(0);
        }
        break;
        case search_end_code: {
            int index = codes[2];
            int mode = codes[1];
            if (!mode) {
                console.goUp();
                search_console_add(index, mode);
                for (int i = 0;i < 7; i++) console.goDown();
                m_is_lock = true;
            } else {
                console.goUp();
                search_console_add(index, mode);
                for (int i = 0;i < 3; i++) console.goDown();
                m_is_lock = true;
            }
            setDuration(0.1);
        }
        break;
        case reset_color: {
            int n = codes[1];
            Color color = to_color(prevs.top());
            prevs.pop();
            vector<int> vertices_index= getVertex(n);
            for (int i:vertices_index) vertices[i]->setColor(color);
            vector<int> edge_index = getEdge(n);
            for (int i:edge_index) edges[i]->setColor(color);
            setDuration(0.5);
        }
        break;
        
        case goUp: {
            int n = codes[1];
            for (int i = 0; i<n; i++) console.goDown();
            setDuration(codes.back());
        }
        break;
        case reback_color: {
            int n = codes[1];
            int size, index;
            Color color;
            size = prevs.top();
            prevs.pop();
            for (int i = 0; i<size; i++) {
                color = to_color(prevs.top());
                prevs.pop();
                index = prevs.top();
                prevs.pop();
                edges[index]->setColor(color);
            }
            size = prevs.top();
            prevs.pop();
            for (int i = 0; i<size; i++) {
                color = to_color(prevs.top());
                prevs.pop();
                index = prevs.top();
                prevs.pop();
                vertices[index]->setColor(color);
            }
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
            int index = codes[1];
            if (edges[index]->m_start->getIndex()<edges[index]->m_end->getIndex()) {
                edges[index]->setDuration(codes.back()*getSpeed());
                edges[index]->start(true, false);
            } else {
                edges[index]->reverse->setDuration(codes.back()*getSpeed());
                edges[index]->reverse->start(false, false);
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
            vertices[index]->setColor(PURPLE);
            setDuration(codes.back());
        }
        break;
        case choosev2_vertex: {
            int start = codes[1], end = codes[2];
            Vector2 delta = vertices[end]->getCenter() - vertices[start]->getCenter();
            if (start == end) delta = vertices[start]->getCenter();
            vertices[end]->start(arctan(delta), ORANGE ,vertices[end]->getColor());
            setDuration(codes.back());
        }
        break;
        case set_cost: {
            int index = codes[1];
            DMargins[index]->setValue(codes[3]);
            setDuration(codes.back());
        }
        break;
        case fill: {
            int index = codes[1];
            setDuration(codes.back());
        }
        break;
        case remove_edge: {
            int globalIndex = codes[4], localIndex = codes[3];
            int start = codes[1], end = codes[2], reverse = codes[5];
            int weight = codes[6];
            edges[globalIndex] = new Edge(vertices[start], vertices[end], globalIndex, localIndex, &form_setting);
            edges[globalIndex]->setDuration(0.5);
            edges[globalIndex]->start(false);
            edges[globalIndex]->setWeight(weight);
            edges[globalIndex]->setType(m_type == 0);
            if (reverse != -1 && edges[reverse]) {
                edges[globalIndex]->reverse = edges[reverse];
                edges[reverse]->reverse = edges[globalIndex];
            }
            if (localIndex>=vertices[start]->edges.size()) vertices[start]->edges.resize(localIndex+1);
            vertices[start]->edges[localIndex] = edges[globalIndex];
            setDuration(0.1);
        }
        break;
        case remove_vertex: {
            int index = codes[1];
            vertices[index] = new Vertex(&form_setting, index);
            vertices[index]->setValue(codes[2]);
            vertices[index]->setColor(to_color(codes[5]));
            vertices[index]->setSize(50, 50);
            vertices[index]->setPosition(codes[3], codes[4]);
            setDuration(0.1);
        }
        break;
        case prim_code: {
            int index = codes[1];
            console.goUp();
            heap.setVisible(false);
            setDuration(0.5);
        }
        break;
        case prim_end_code: {
            m_is_lock = true;
            console.goUp();
            prim_console_add();
            heap.setVisible(true);
            for (int i = 0; i<3; i++) console.goDown();
            setDuration(0.5);
        }
        break;
        case kruskal_code: {
            int index = codes[1];
            console.goUp();
            heap.setVisible(false);
            m_is_lock = false;
            setDuration(0.5);
        }
        break;
        case kruskal_end_code: {
            int index = codes[1];
            console.goUp();
            kruskal_console_add();
            console.goDown();
            console.goDown();
            console.goDown();
            console.goDown();
            heap.setVisible(true);
            m_is_lock = true;
            setDuration(0.5);
        }
        break;
        case Dijkstra_code: {
            int index = codes[1];
            heap.setVisible(false);
            free_Dmargin();
            console.goUp();
            setDuration(0.5);
        }
        break;
        case dijkstra_end_code: {
            int index = codes[1];
            int value = vertices[index]->getValue();
            console.goUp();
            Dijkstra_console_add(index);
            for (int i = 0; i<3; i++) console.goDown();
            m_is_lock = true;
            heap.setVisible(true);
            create_Dmargin();
            int size = prevs.top();
            prevs.pop();
            for (int i = 0; i<size; i++) {
                int value = prevs.top();
                prevs.pop();
                int index = prevs.top();
                prevs.pop();
                DMargins[index]->setValue(value);
            }
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
        case update_code: {
            update(codes[1], codes[2]);
            setDuration(codes.back());
        }
        break;
        case match_code: {
            int globalIndex = codes[1], localINdex = codes[2];
            int start = codes[3], end = codes[4];
            if (edges[globalIndex]->reverse) {
                edges[globalIndex]->reverse->reverse = 0;
            }
            delete edges[globalIndex];
            edges[globalIndex] = 0;
            vertices[start]->edges[localINdex] = 0;
            console.goUp();
            setDuration(codes.back());
        }
        break;
    }
}
void Graph::prim_algorithms(const int& vertex) {
    vector<bool> visited(vertices.size(), 0);
    MinHeap q;
    InsertNextSubCommand({goDown, 1, 0.5});
    q.Insert({vertex, vertex, 0, -1});
    InsertNextSubCommand({add_heap, 1.0f*vertex, 1.0f*vertex, 0, 0});
    InsertNextSubCommand({goDown, 1, 0.5});
    while (q.size()) {
        InsertNextSubCommand({goDown, 1, 0.2});
        Path path = q.front();
        q.pop();
        InsertNextSubCommand({goDown, 1, 0.2});
        InsertNextSubCommand({pop_heap, 1.0f*path.start, 1.0f*path.end, 1.0f*path.weight});
        InsertNextSubCommand({goDown, 1, 0.2});
        if (visited[path.end]) {
            InsertNextSubCommand({goDown, 3, 0.2});
            InsertNextSubCommand({goUp, 6, 1});
            continue;
        }
        InsertNextSubCommand({goDown, 1, 0.2});
        if (path.index!=-1) InsertNextSubCommand({choose_edge, 1.0f*path.index, 1});
        InsertNextSubCommand({choose_vertex, 1.0f*path.start, 1.0f*path.end, 1});
        visited[path.end] = true;
        InsertNextSubCommand({goDown, 1, 0.2});
        for (Edge* edge: vertices[path.end]->edges) {
            if (edge && !visited[edge->m_end->getIndex()]) {
                q.Insert({path.end, edge->m_end->getIndex(), edge->getWeight(), edge->getGlobalIndex()});
                InsertNextSubCommand({add_heap, 1.0f*path.end, 1.0f*edge->m_end->getIndex(), 1.0f*edge->getWeight(), 0});
            }
        }

        InsertNextSubCommand({goDown, 1, 0.2});
        InsertNextSubCommand({goUp, 6, 1});
    }
}

void Graph::kruskal_algorithms(const int& index) {
    MinHeap q;
    DSU dsu(vertices.size());
    vector<int> edges_index = getEdge(index);
    InsertNextSubCommand({goDown, 1, 0.5});
    for (int i:edges_index) {
        Path path = {edges[i]->m_start->getIndex(), edges[i]->m_end->getIndex(), edges[i]->getWeight(), i};
        q.Insert(path);
        InsertNextSubCommand({add_heap, 1.0f*path.start, 1.0f*path.end, 1.0f*path.weight, 0});
    }
    InsertNextSubCommand({goDown, 1, 0.5});
    InsertNextSubCommand({goDown, 1, 0.5});
    while (q.size()) {
        if (dsu.check(q.front().start, q.front().end)) {
            q.pop();
            InsertNextSubCommand({pop_heap, 1.0f*q.front().start, 1.0f*q.front().end, 1.0f*q.front().weight, 0});
        } else {
            InsertNextSubCommand({goDown, 1, 0.5});
            InsertNextSubCommand({fill_vertex, 1.0f*q.front().start,  1});
            InsertNextSubCommand({choose_edge, 1.0f*q.front().index, 1});
            InsertNextSubCommand({choose_vertex, 1.0f*q.front().start, 1.0f*q.front().end,  1});
            dsu.join(q.front().start, q.front().end);
            InsertNextSubCommand({goDown, 1, 0.5});
            InsertNextSubCommand({pop_heap,  1.0f*q.front().start, 1.0f*q.front().end, 1.0f*q.front().weight, 0});
            q.pop();
            InsertNextSubCommand({goUp, 3, 0.5});
            InsertNextSubCommand({goDown, 1, 0.5});
        }
    }
}
