#include "../include/Graph.h"
#include "../include/General.h"

string Graph::RandomCreate() const {
    srand(time(0));
    int vertex = to_int(vertex_textbox.getText());
    int edge = to_int(edge_textbox.getText());
    if (vertex && edge) {
        auto matrix = create_graph(vertex, edge, m_type == 0, m_weight == 0);
        return to_string(matrix);
    }
    return "";
}
string Graph::RandomSearch() const {
    if (vertices.empty()) return "";
    srand(clock());
    int index = rand()%vertices.size();
    return to_string(index);
}
string Graph::RandomInsert() const {
    srand(clock());
    int value = rand()%1000;
    return to_string(value);
};
string Graph::RandomNewValue() const {
    if (vertices.empty()) return "";
    srand(clock());
    int value;
    do value = rand()%1000;
    while (value == vertices[to_int(update_textbox_choice.getText())]->getValue());
    return to_string(value);
}
string Graph::RandomOldValue() const {
    if (vertices.empty()) return "";
    srand(clock());
    int index = rand()%vertices.size();
    return to_string(index);
}
string Graph::RandomRemove() const {
    if (vertices.empty()) return "";
    srand(clock());
    int index = rand()%vertices.size();
    return to_string(index);
}
string Graph::RandomEdge() const {
    srand(clock());
    int vertex = to_int(vertex_textbox.getText());
    return to_string(rand()%(vertex*(vertex-1)/2 - vertex + 1) + vertex - 1);
}
string Graph::RandomVertex() const {
    srand(clock());
    return to_string(rand()%8+5);
}
void Graph::free() {
    for (int i = 0; i<vertices.size(); i++) 
        if (vertices[i]) delete vertices[i];
    for (int i = 0; i<edges.size(); i++) 
        if (edges[i]) delete edges[i];
    vertices.clear();
    edges.clear();
    console.clear();
    clear();
}
void Graph::add_edge(const int& globalIndex, const int& localIndex, const int& start, const int& end, const int& weight) {
    if (start == end) return;
    for (Edge* edge:vertices[start]->edges)
        if (edge && edge->m_end->getIndex() == end) return;
    int iend = -1;
    for (Edge* edge:vertices[end]->edges) 
        if (edge && edge->m_end->getIndex() == start) {
            iend = edge->getGlobalIndex();
            break ;
        }
    edges[globalIndex] = new Edge(vertices[start], vertices[end], globalIndex, localIndex, &form_setting);
    vertices[start]->edges[localIndex] = edges[globalIndex];
    edges[globalIndex]->start(false);
    edges[globalIndex]->setWeight(weight);
    edges[globalIndex]->setType(m_type == 0);
    if (iend!=-1) {
        edges[globalIndex]->reverse = edges[iend];
        edges[iend]->reverse = edges[globalIndex];
    }
}
void Graph::pull_matrix(const int& graph) {
    auto vertices_index = getVertex(graph);
    vector<vector<int>> ans(vertices.size(), vector<int>(vertices.size(), 0));
    for (auto i: vertices_index) {
        for (Edge* edge:vertices[i]->edges) {
            if (edge) ans[edge->m_start->getIndex()][edge->m_end->getIndex()] = edge->getWeight();
            if (edge->reverse) ans[edge->m_end->getIndex()][edge->m_start->getIndex()] = edge->reverse->getWeight();
        }
    }
    extract_text_bx.setText(to_string(ans));
}
string to_string(const vector<vector<int>>& matrix) {
    string ans = to_string(matrix.size()) + '\n';
    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix.size(); j++) {
            ans+= to_string(matrix[i][j])+" ";
        }
        ans += '\n';
    }
    return ans;
}
vector<vector<int>> to_matrix(const vector<string>& str){
    int n = to_int(str[0]);
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            ans[i][j] = to_int(str[i*n+j+1]);
        }
    }
    return ans;
}
vector<int> Graph::getEdge(const int& graph) {
    vector<bool> visited(edges.size(), 0);
    getEdge(graph, visited);
    vector<int> ans;
    for (int i = 0; i<edges.size(); i++)
        if (visited[i]) ans.push_back(i);
    return ans;
}
void Graph::getEdge(const int& graph, vector<bool>& visited) {
    for (Edge* edge:vertices[graph]->edges)
        if (edge && !visited[edge->getGlobalIndex()]) {
            visited[edge->getGlobalIndex()] = true;
            getEdge(edge->m_end->getIndex(), visited);
        }
}
vector<int> Graph::getVertex(const int& graph) {
    if (vertices.empty()) return {};
    vector<bool> visited(vertices.size(), 0);
    getVertex(graph, visited);
    vector<int> ans;
    for (int i = 0; i<visited.size(); i++) 
        if (visited[i]) ans.push_back(i);
    return ans;
}
void Graph::getVertex(const int& graph, vector<bool>& visited) {
    visited[graph] = true;
    for (Edge* edge:vertices[graph]->edges)
        if (edge && !visited[edge->m_end->getIndex()]) {
            getVertex(edge->m_end->getIndex(), visited);
        }
}
void Graph::Dijkstra_console_add(const int& value) {
    console.InsertNextSubCommand("Create MinHeap");
    console.InsertNextSubCommand("add " + to_string(value) + " to heap");
    console.InsertNextSubCommand("while heap is not empty");
    console.InsertNextSubCommand("   vertex = heap.top()");
    console.InsertNextSubCommand("   Pop heap");
    console.InsertNextSubCommand("   if  !visited[vertex]");
    console.InsertNextSubCommand("      for first edge to last edge");
    console.InsertNextSubCommand("          if cost[vertex] + cost[edge] < cost[end]");
    console.InsertNextSubCommand("              cost[end] = cost[vertex] + cost[edge]");
    console.InsertNextSubCommand("              add end to min heap");
    console.InsertNextSubCommand("}");
}
void Graph::kruskal_console_add() {
    console.InsertNextSubCommand("f(vertex)");
    console.InsertNextSubCommand("  Add all edges to heap");
    console.InsertNextSubCommand("  while heap has element");
    console.InsertNextSubCommand("      Pop all next edges make cycle");
    console.InsertNextSubCommand("      Add top edge to DSU");
    console.InsertNextSubCommand("      Pop top edge");
}
void Graph::prim_console_add() {
    console.InsertNextSubCommand("f(vertex) ");
    console.InsertNextSubCommand("  Push vertex to heap");
    console.InsertNextSubCommand("  while heap has element {");
    console.InsertNextSubCommand("      vertex = topHeap -> end");
    console.InsertNextSubCommand("      Pop topHeap");
    console.InsertNextSubCommand("      if !visited[vertex]");
    console.InsertNextSubCommand("          visited[vertex] = true");
    console.InsertNextSubCommand("          Push all edges to heap");
    console.InsertNextSubCommand("  }");
}
void Graph::search_console_add(const int& vertex, const int& mode) {
    int value = vertices[vertex]->getValue();
    if (mode) {
        console.InsertNextSubCommand("Create queue");
        console.InsertNextSubCommand("add vertex = " + to_string(value) + " to queue");
        console.InsertNextSubCommand("while queue is not empty");
        console.InsertNextSubCommand("   Pop front of queue");
        console.InsertNextSubCommand("   Push all unvisited child to queue ");
    } else {
        console.InsertNextSubCommand("Create visited[n]");
        console.InsertNextSubCommand("vertex = " + to_string(value));
        console.InsertNextSubCommand("f(vertex) {");
        console.InsertNextSubCommand("   visited[vertex] = true ");
        console.InsertNextSubCommand("   for i = first_des to last_des ");
        console.InsertNextSubCommand("      if this des was not visited");
        console.InsertNextSubCommand("          f(i)");
        console.InsertNextSubCommand("}");
    }
}
void Graph::complete_color() {
    for (int i = 0; i<vertices.size(); i++) 
        if (vertices[i]) vertices[i]->complete();
    for (int i = 0; i<edges.size(); i++) 
        if (edges[i]) edges[i]->complete();
}
vector<vector<int>> create_graph_undir(const int& vertex, const int& edge) {
    srand(clock());
    vector<vector<int>> matrix(vertex, vector<int>(vertex, 0));
    queue<int> done;
    queue<int> q;
    done.push(0);
    vector<int> count(vertex, 0);
    for (int i = 1; i<vertex; i++) q.push(i);
    for (int i = 0; i<vertex-1; i++) {
        int start = rand()%done.size();
        for (int i = 0; i<start; i++) {
            done.push(done.front());
            done.pop();
        }
        start = done.front();
        int end = rand()%q.size();
        for (int i = 0; i<end; i++) {
            q.push(q.front());
            q.pop();
        }
        end = q.front();
        q.pop();
        count[start]++;
        count[end]++;
        if (count[end]<vertex-1) done.push(end);
        matrix[start][end] = matrix[end][start] = rand()%100 + 1;
    }
    for (int i = vertex-1; i<edge && done.size()>1; i++) {
        int start = rand()%done.size();
        for (int i = 0; i<start;i ++) {
            done.push(done.front());
            done.pop();
        }
        start = done.front();
        done.pop();
        int end = rand()%done.size();
        for (int i = 0; i<end || matrix[start][done.front()];i ++) {
            done.push(done.front());
            done.pop();
        }
        end = done.front();
        done.pop();
        matrix[start][end] = matrix[end][start] = rand()%100+1;
        if (count[start]<vertex-2) {
            count[start]++;
            done.push(start);
        }
        if (count[end]<vertex-2) {
            count[end]++;
            done.push(end);
        }
    }
    return matrix;
}
vector<vector<int>> create_graph(const int& vertex, const int& edge, const bool& is_direct, const bool& is_weight) {
    if (!is_direct) {
        return create_graph_undir(vertex, edge);
    }
    return {};
}