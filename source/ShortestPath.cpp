//#include "../raylib/raylib.h"
//#include "../include/ShortestPath.h"
//#include "../include/Global.h"
//#include "../include/Graph.h"
//const int INF = numeric_limits<int>::max();
//
//vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start, int end) {
//    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
//    vector<int> distance(graph.size(), numeric_limits<int>::max());
//    vector<int> previous(graph.size(), -1);
//    distance[start] = 0;
//    minHeap.emplace(0, start);
//    while (!minHeap.empty()) {
//        int currentNode = minHeap.top().second;
//        int currentDistance = minHeap.top().first;
//        minHeap.pop();
//        if (currentNode == end) {
//            vector<int> path;
//            for (int temp = end; temp != -1; temp = previous[temp]) {
//                path.push_back(temp);
//            }
//            reverse(path.begin(), path.end());
//            return path;
//        }
//        if (currentDistance > distance[currentNode]) continue;
//        for (auto& edge : graph[currentNode]) {
//            int neighbor = edge.first;
//            int weight = edge.second;
//            int newDistance = distance[currentNode] + weight;
//            if (newDistance < distance[neighbor]) {
//                distance[neighbor] = newDistance;
//                previous[neighbor] = currentNode;
//                minHeap.emplace(newDistance, neighbor);
//            }
//        }
//    }
//    return {};
//}
//
//void localDijsktra(vector<vector<pair<int, int>>>& graph, vector<int>& distance, vector<int>& previous, int start, int radius) {
//    int n = graph.size();
//    distance.resize(n, INF);
//    previous.resize(n, -1);
//    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
//    minHeap.push({0, start});
//    distance[start] = 0;
//    while (!minHeap.empty()) {
//        int u = minHeap.top().second;
//        minHeap.pop();
//        for (auto& v : graph[u]) {
//            int w = v.first;
//            int weight = v.second;
//            if (distance[w] > distance[u] + weight) {
//                distance[w] = distance[u] + weight;
//                previous[w] = u;
//                minHeap.push({distance[w], w});
//            }
//        }
//        if (distance[u] > radius) continue;
//    }
//}
//
//void ConnectedSubgraph(int** a, int n) {
//    vector<vector<int>> res;
//    queue<int> q;
//    int cnt = 0;
//    bool* visited = new bool[n]{0};
//    for (int i = 0; i < n; ++i) {
//        vector<int> sub;
//        if(visited[i]) continue;
//        q.push(i);
//        sub.push_back(i);
//        visited[i] = 1;
//        
//        while(!q.empty()) {
//            int u = q.front();
//            q.pop();
//            for (int j = 0; j < n; ++j) {
//                if(visited[j] || !a[u][j]) continue;
//                sub.push_back(j);
//                visited[j] = 1;
//                q.push(j);
//            }
//        }
//        res.push_back(sub);
//        ++cnt;
//    }
//}
//
//void dfs(const vector<vector<int>>& matrix, vector<bool>& visited, int vertex, vector<int>& component) {
//    visited[vertex] = true;
//    component.push_back(vertex);
//    for (int neighbor = 0; neighbor < matrix.size(); ++neighbor) 
//        if (matrix[vertex][neighbor] && !visited[neighbor]) dfs(matrix, visited, neighbor, component);
//}
//
//void GraphVisual::findConnectedComponents(const vector<vector<int>>& matrix, vector<vector<int>>& components) {
//    int numVertices = matrix.size();
//    vector<bool> visited(numVertices, false);
//    for (int vertex = 0; vertex < numVertices; ++vertex) {
//        if (!visited[vertex]) {
//            vector<int> component;
//            dfs(matrix, visited, vertex, component);
//            components.push_back(component);
//        }
//    }
//}
//
//void Graph::clearGraph() {
//    for (int i = 0; i < int(nodes.size()); ++i) {
//        delete nodes[i];
//    }
//    this->nodes.clear();
//    this->frameCount = 0;
//}
//
//Graph::~Graph() {
//    clearGraph();
//}
//
//int Graph::findParent(vector<int>& parent, int node) {
//    if (parent[node] != node) {
//        findParent(parent, parent[node]);
//    }
//    return parent[node];
//}
//
//void Graph::unionNode(vector<int>& parent, vector<int>& rank, int u, int v) {
//    int rootU = findParent(parent, u);
//    int rootV = findParent(parent, v);
//    if (rank[rootU] > rank[rootV]) {
//        parent[rootV] = rootU;
//    } else if (rank[rootU] < rank[rootV]) {
//        parent[rootU] = rootV;
//    } else {
//        parent[rootV] = rootU;
//        rank[rootU]++;
//    }
//}
//
//int Graph::getVertexIndex(Vertex* node) {
//    auto it = find(nodes.begin(), nodes.end(), node);
//    if (it != nodes.end()) {
//        return distance(nodes.begin(), it);
//    }
//    return -1;
//}
//
//void Graph::addVertex(Vertex* node) {
//    nodes.push_back(node);
//}
//
//void Graph::addVertex() {
//    auto* node = new Vertex();
//    node->pos = {500.f + rand() % 950, 100.f + rand() % 650};
//    addVertex(node);
//}
//
//int Graph::addEdge(int from, int to, int weight) {
//    if (from < nodes.size() && to < nodes.size() && from != to && weight != 0) {
//        bool existedEdge = false;
//        for (auto& edge : nodes[from]->neighbor) {
//            if (edge.nearVertex == nodes[to]) {
//                existedEdge = true;
//                edge.weight = weight;
//                break;
//            }
//        }
//        for (auto& edge : nodes[to]->neighbor) {
//            if (edge.nearVertex == nodes[from]) {
//                existedEdge = true;
//                edge.weight = weight;
//                break;
//            }
//        }
//        if (!existedEdge) {
//            nodes[from]->neighbor.push_back({nodes[to], weight, 0});
//            nodes[to]->neighbor.push_back({nodes[from], weight, 0});
//            return 1;
//        }
//    }
//    return 0;
//}
//
//void Graph::random(int vertexCount, int maxX, int maxY) {
//    clearGraph();
//
//}
//
//void Graph::startFromFile(const string filename) {
//    clearGraph();
//    ifstream file(filename);
//    int n;
//    file >> n;
//    for (int i = 0; i < n; ++i) {
//        Graph::addVertex();
//    }
//    
//    int weight;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            file >> weight;
//            addEdge(i, j, weight);
//        }
//    }
//    file.close();
//}