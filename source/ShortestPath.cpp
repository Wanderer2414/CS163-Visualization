#include "../include/ShortestPath.h"
#include "../include/Global.h"

struct TreeNode {
    TreeNode *left, *right;
    int val;
};

const int INF = numeric_limits<int>::max();

void dijsktra(vector<vector<pair<int, int>>>& graph, vector<int>& dist, vector<int>& pre, int start) {
    int n = graph.size();
    dist.resize(n, INF);
    pre.resize(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    dist[start] = 0;
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto& v : graph[u]) {
            int w = v.first;
            int weight = v.second;
            if(dist[u] + weight < dist[w]) {
                dist[w] = dist[u] + weight;
                pre[w] = u;
                pq.push({dist[w], w});
            } 
        }
    }
}

vector<int> Dijkstra(vector<vector<pair<int, int>>>& graph, int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distance(graph.size(), numeric_limits<int>::max());
    vector<int> previous(graph.size(), -1);
    distance[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        int curNode = pq.top().second;
        int curDistance = pq.top().first;
        pq.pop();
        if (curNode == end) {
            vector<int> path;
            int tempNode = end;
            while (tempNode != -1) {
                path.push_back(tempNode);
                tempNode = previous[tempNode];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        if (curDistance > distance[curNode]) continue;
        for (int i = 0; i < graph[curNode].size(); ++i) {
            int neighbor = graph[curNode][i].first;
            int weight = graph[curNode][i].second;
            int newDistance = curNode + weight;
            if (newDistance < distance[neighbor]) {
                distance[neighbor] = newDistance;
                previous[neighbor] = curNode;
                pq.emplace(distance, neighbor);
            }
        }
    }
    return;
}

void localDijsktra(vector<vector<pair<int, int>>>& graph, vector<int>& dist, vector<int>& pre, int start, int radius) {
    int n = graph.size();
    dist.resize(n, INF);
    pre.resize(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    dist[start] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto& v : graph[u]) {
            int w = v.first;
            int weight = v.second;
            if (dist[w] > dist[u] + weight) {
                dist[w] = dist[u] + weight;
                pre[w] = u;
                pq.push({dist[w], w});
            }
        }
        if (dist[u] > radius) break;
    }
}

void dfs(const vector<vector<int>>& matrix, vector<bool>& visited, int vertex, vector<int>& component) {
    visited[vertex] = true;
    component.push_back(vertex);
    for (int neighbor = 0; neighbor < matrix.size(); ++neighbor) if (matrix[vertex][neighbor] == 1 && !visited[neighbor]) dfs(matrix, visited, neighbor, component);
}

void findConnectedComponents(const vector<vector<int>>& matrix, vector<vector<int>>& components) {
    int numVertices = matrix.size();
    vector<bool> visited(numVertices, false);
    for (int vertex = 0; vertex < numVertices; ++vertex) {
        if (!visited[vertex]) {
            vector<int> component;
            dfs(matrix, visited, vertex, component);
            components.push_back(component);
        }
    }
}

void output(const string& filename, vector<vector<int>>& components) {
    ofstream file(filename);
    file << components.size() << endl;
    for (int i = 0; i < components.size(); ++i) {
        for (int j = 0; j < components[i].size(); ++j) {
            file << components[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void ConnectedSubgraph(int** a, int n) {
    vector<vector<int>> res;
    queue<int> q;
    int cnt = 0;
    bool* visited = new bool[n]{0};
    for (int i = 0; i < n; ++i) {
        vector<int> sub;
        if(visited[i]) continue;
        q.push(i);
        sub.push_back(i);
        visited[i] = 1;
        
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for (int j = 0; j < n; ++j) {
                if(visited[j] || !a[u][j]) continue;
                sub.push_back(j);
                visited[j] = 1;
                q.push(j);
            }
        }
        res.push_back(sub);
        ++cnt;
    }
}

/*int parent(vector<int>& a, int n, int i) {
    if (i == 0) return -1;
    return (i - 1) / 2;
}

int left(vector<int>& a, int n, int i) {
    int left_child = 2*i + 1;
    if (left_child >= n) return -1;
    return left_child;
}

int right(vector<int>& a, int n, int i) {
    int right_child = 2*i + 2;
    if (right_child >= n) return -1;
    return right_child;
}

void swap(vector<int>& a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}*/

//Testing
int main() {
    
    return 0;
}