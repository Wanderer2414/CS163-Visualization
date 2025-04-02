#include "../include/Graph.h"
#include "../include/General.h"
#include <ctime>

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
    srand(clock());
    int index = rand()%vertices.size();
    return to_string(vertices[index]->getValue());
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
    matrix.clear();
    console.clear();
    clear();
}
void Graph::add_edge(const int& start, const int& end, const int& weight) {
    if (start == end) return;
    if (matrix[start][end]==-1) {
        matrix[start][end] = edges.size();
        edges.push_back(new Edge(vertices[start], vertices[end], &form_setting));
        edges.back()->start(false);
        edges.back()->setWeight(weight);
        edges.back()->setType(m_type == 0);
    }
    if (m_type == 1) {
        if (matrix[end][start]==-1) {
            matrix[end][start] = edges.size();
            edges.push_back(new Edge(vertices[end], vertices[start], &form_setting));
            edges.back()->start(true);
            edges.back()->setWeight(weight);
            edges.back()->setType(m_type == 0);
        }
    }
}
void Graph::random_subGraphColor() {
    vector<bool> visited(matrix.size(), 0);
    for (int i = 0; i<visited.size(); i++) {
        if (!visited[i]) {
            setSubGraphColor(i, visited, colors[color_pointer]);
            color_pointer = (color_pointer+1)%6;
        }
    }
}
void Graph::setSubGraphColor(const int& row, const Color& color) {
    if (!vertices[row]) return;
    vector<bool> visited(matrix.size(), 0);
    setSubGraphColor(row, visited, color);
}
void Graph::setSubGraphColor(const int& row, vector<bool>& visited, const Color& color) {
    if (!vertices[row]) return;
    visited[row] = true;
    vertices[row]->setColor(color);
    for (int i = 0; i<matrix.size(); i++) {
        if (matrix[row][i] != -1) {
            edges[matrix[row][i]]->setColor(color);
            if (m_type == 1 && matrix[i][row]!=-1) edges[matrix[i][row]]->setColor(color);
        }
        if (matrix[row][i]!=-1 && !visited[i]) {
            setSubGraphColor(i, visited, color);
        }
    }
}
void Graph::pull_matrix(const int& graph) {
    auto vertices = getVertex(graph);
    string ans = to_string(vertices.size()) + '\n';
    for (auto i: vertices) {
        for (int j: vertices) {
            if (matrix[i][j]!=-1) {
                ans += to_string(edges[matrix[i][j]]->getWeight()) + " ";
            } else ans += "0 ";
        }
        ans += '\n';
    }
    extract_text_bx.setText(ans);
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
    int vertex = graph;
    vector<bool> visited(matrix.size(), 0);
    vector<int> ans;
    getVertex(graph, visited);
    for (int i = 0; i<edges.size(); i++) {
        int start = edges[i]->m_start->getIndex();
        int end = edges[i]->m_end->getIndex();
        if (start < end && visited[start]) {
            ans.push_back(i);
        }
    }
    return ans;
}
vector<int> Graph::getVertex(const int& graph) {
    vector<bool> visited(matrix.size(), 0);
    getVertex(graph, visited);
    vector<int> ans;
    for (int i = 0; i<visited.size(); i++) 
        if (visited[i]) ans.push_back(i);
    return ans;
}
void Graph::getVertex(const int& graph, vector<bool>& visited) {
    visited[graph] = true;
    for (int i = 0; i<matrix.size(); i++)
        if (matrix[graph][i]!=-1 && !visited[i]) {
            getVertex(i, visited);
        }
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