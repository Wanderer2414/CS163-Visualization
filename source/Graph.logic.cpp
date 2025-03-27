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

void Graph::free() {
    for (int i = 0; i<vertices.size(); i++) delete vertices[i];
    for (int i = 0; i<true_edges.size(); i++) delete true_edges[i];
    for (int i = 0; i<reverse_edge.size(); i++) delete reverse_edge[i];
    vertices.clear();
    true_edges.clear();
    reverse_edge.clear();
    matrix.clear();
    console.clear();
    clear();
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
    for (int i = 0; i<visited.size(); i++) {
        if (!visited[i]) {
            setSubGraphColor(i, visited, colors[color_pointer]);
            color_pointer = (color_pointer+1)%6;
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
                if (m_type == 1 && matrix[i][row]!=-1) true_edges[matrix[i][row]]->setColor(color);
            }
        }
        if (matrix[row][i]!=-1 && !visited[i]) {
            setSubGraphColor(i, visited, color);
        }
    }
}
void Graph::pull_matrix() {
    string ans = to_string(matrix.size()) + '\n';
    for (int i = 0; i<matrix.size(); i++) {
        for (int j = 0; j<matrix.size(); j++) {
            if (matrix[i][j]!=-1) {
                if (i<j) ans += to_string(true_edges[matrix[i][j]]->getWeight());
                else if (i>j) ans += to_string(reverse_edge[matrix[i][j]]->getWeight());
                ans += " ";
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
vector<vector<int>> create_graph(const int& vertex, const int& edge, const bool& is_direct, const bool& is_weight) {
    vector<vector<int>> matrix(vertex, vector<int>(vertex, 0));
    if (!is_direct && !is_weight) {
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
            matrix[start][end] = matrix[end][start] = 1;
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
            matrix[start][end] = matrix[end][start] = 1;
            if (count[start]<vertex-2) {
                count[start]++;
                done.push(start);
            }
            if (count[end]<vertex-2) {
                count[end]++;
                done.push(end);
            }
        }
    }
    return matrix;
}