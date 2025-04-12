// #include "../include/ShortestPath.h"
// #include "../include/Global.h"

// vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start, int end) {
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
//     vector<int> distance(graph.size(), numeric_limits<int>::max());
//     vector<int> previous(graph.size(), -1);
//     distance[start] = 0;
//     minHeap.emplace(0, start);
//     while (!minHeap.empty()) {
//         int currentNode = minHeap.top().second;
//         int currentDistance = minHeap.top().first;
//         minHeap.pop();
//         if (currentNode == end) {
//             vector<int> path;
//             for (int temp = end; temp != -1; temp = previous[temp]) {
//                 path.push_back(temp);
//             }
//             reverse(path.begin(), path.end());
//             return path;
//         }
//         if (currentDistance > distance[currentNode]) continue;
//         for (auto& edge : graph[currentNode]) {
//             int neighbor = edge.first;
//             int weight = edge.second;
//             int newDistance = distance[currentNode] + weight;
//             if (newDistance < distance[neighbor]) {
//                 distance[neighbor] = newDistance;
//                 previous[neighbor] = currentNode;
//                 minHeap.emplace(newDistance, neighbor);
//             }
//         }
//     }
//     return {};
// }

// void localDijsktra(vector<vector<pair<int, int>>>& graph, vector<int>& distance, vector<int>& previous, int start, int radius) {
//     distance.assign(graph.size(), numeric_limits<int>::max());
//     previous.assign(graph.size(), -1);
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
//     minHeap.push({0, start});
//     distance[start] = 0;
//     while (!minHeap.empty()) {
//         int u = minHeap.top().second;
//         minHeap.pop();
//         if (distance[u] > radius) break;
//         for (auto& v : graph[u]) {
//             int w = v.first;
//             int weight = v.second;
//             if (distance[w] > distance[u] + weight) {
//                 distance[w] = distance[u] + weight;
//                 previous[w] = u;
//                 minHeap.push({distance[w], w});
//             }
//         }   
//     }
// }

// void dfs(const vector<vector<int>>& matrix, vector<bool>& visited, vector<int>& component, int vertex) {
//     visited[vertex] = true;
//     component.push_back(vertex);
//     for (int neighbor = 0; neighbor < matrix.size(); ++neighbor) {
//         if (matrix[vertex][neighbor] == 1 && !visited[neighbor]) {
//             dfs(matrix, visited, component, neighbor);
//         }
//     }
// }

// int Graph::findParent(vector<int>& parent, int node) {
//     if (parent[node] != node) {
//         parent[node] = findParent(parent, parent[node]);
//     }
//     return parent[node];
// }

// void Graph::unionNode(vector<int>& parent, vector<int>& rank, int u, int v) {
//     int rootU = findParent(parent, u);
//     int rootV = findParent(parent, v);
//     if (rank[rootU] > rank[rootV]) {
//         parent[rootV] = rootU;
//     } else if (rank[rootU] < rank[rootV]) {
//         parent[rootU] = rootV;
//     } else {
//         parent[rootV] = rootU;
//         rank[rootU]++;
//     }
// }

// int Graph::getVertexIndex(Vertex* node) {
//     auto it = find(nodes.begin(), nodes.end(), node);
//     if (it != nodes.end()) {
//         return distance(nodes.begin(), it);
//     }
//     return -1;
// }

// void Graph::addVertex(Vertex* node) {
//     nodes.push_back(node);
// }

// void Graph::addVertex() {
//     auto* node = new Vertex();
//     node->pos = {500.f + rand() % 950, 100.f + rand() % 650};
//     addVertex(node);
// }

// int Graph::addEdge(int from, int to, int weight) {
//     if (from < nodes.size() && to < nodes.size() && from != to && weight != 0) {
//         bool existedEdge = false;
//         for (auto& edge : nodes[from]->neighbor) {
//             if (edge.nearVertex == nodes[to]) {
//                 existedEdge = true;
//                 edge.weight = weight;
//                 break;
//             }
//         }
//         for (auto& edge : nodes[to]->neighbor) {
//             if (edge.nearVertex == nodes[from]) {
//                 existedEdge = true;
//                 edge.weight = weight;
//                 break;
//             }
//         }
//         if (!existedEdge) {
//             nodes[from]->neighbor.push_back({nodes[to], weight, 0});
//             nodes[to]->neighbor.push_back({nodes[from], weight, 0});
//             return 1;
//         }
//     }
//     return 0;
// }

// void Graph::random(int vertexCount, int maxX, int maxY) {
//     for (int i = 0; i < vertexCount; ++i) {
//         addVertex();
//     }
//     for (int i = 0; i < vertexCount; ++i) {
//         for (int j = i + 1; j < vertexCount; ++j) {
//             if (rand() % 3 == 0) {
//                 int weight = 1 + rand() % 10;
//                 addEdge(i, j, weight);
//             }
//         }
//     }
// }

// void Graph::startFromFile(const string filename) {
//     ifstream file(filename);
//     if (!file) {
//         cerr << "Error: Cannot open file!" << endl;
//         return;
//     }
//     int n;
//     file >> n;
//     for (int i = 0; i < n; ++i) {
//         Graph::addVertex();
//     }
    
//     int weight;
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             file >> weight;
//             if (i != j && weight > 0) {
//                 addEdge(i, j, weight);
//             }
//         }
//     }
//     file.close();
// }

// void Graph::resetHighlight() {
//     for (auto node : nodes) {
//         for (auto& edge : node->neighbor) {
//             edge.highlight = false;
//         }
//         node->color = false;
//     }
// }

// void Graph::drawGraph(Font font, std::vector<Color> color) {
//     if(!color.empty()) {
//         for (auto node : nodes) {
//             for (auto edge : node->neighbor) {
//                 DrawLineEx(node->pos, edge.nearVertex->pos, 2, color[node->color]);
//                 Vector2 mid = { (node->pos.x + edge.nearVertex->pos.x) / 2, (node->pos.y + edge.nearVertex->pos.y) / 2 };
//                 DrawTextEx(font, TextFormat("%d", edge.weight), {mid.x, mid.y}, 15, 2, NeonTheme.color);
//             }
//         }
//         for (int i = 0; i < nodes.size(); ++i) {
//             Vector2 size = MeasureTextEx(font, TextFormat("%d", i), 15, 2);
//             DrawCircleV(nodes[i]->pos, 15, color[nodes[i]->color]);
//             printf("Color: (%d, %d, %d, %d)\n", color[nodes[i]->color].r, color[nodes[i]->color].g, color[nodes[i]->color].b, color[nodes[i]->color].a);
//             DrawTextEx(font, TextFormat("%d", i), {nodes[i]->pos.x - size.x/2, nodes[i]->pos.y - size.y/2}, 15, 2, BLACK);
//         }
//     } else {
//         for (auto node : nodes) {
//             for (auto edge : node->neighbor) {
//                 DrawLineEx(node->pos, edge.nearVertex->pos, 2, edge.highlight ? RED : NeonTheme.color);
//                 Vector2 mid = { (node->pos.x + edge.nearVertex->pos.x) / 2, (node->pos.y + edge.nearVertex->pos.y) / 2 };
//                 DrawTextEx(font, TextFormat("%d", edge.weight), {mid.x, mid.y}, 15, 2, NeonTheme.color);
//             }
//         }
//         for (int i = 0; i < nodes.size(); ++i) {
//             Vector2 size = MeasureTextEx(font, TextFormat("%d", i), 15, 2);
//             DrawCircleV(nodes[i]->pos, 15, nodes[i]->color ? RED : NeonTheme.color);
//             DrawTextEx(font, TextFormat("%d", i), {nodes[i]->pos.x - size.x/2, nodes[i]->pos.y - size.y/2}, 15, 2, BLACK);
//         }
//     }
// }

// void Graph::updatePosition() {
//     for (auto node : nodes) {
//         Vector2 force = {0, 0};
//         for (auto other : nodes) {
//             if (node != other) {
//                 float dx = node->pos.x - other->pos.x;
//                 float dy = node->pos.y - other->pos.y;
//                 float distance = sqrt(dx * dx + dy * dy);
//                 if (distance < 1.0f) continue; 
//                 if (distance > 0) {
//                     float repulsion = 500000.0f / (distance * distance);
//                     force.x += repulsion * dx / distance;
//                     force.y += repulsion * dy / distance;
//                 }
//             }
//         }
//         //Spring Force
//         for (auto& edge : node->neighbor) {
//             float dx = node->pos.x - edge.nearVertex->pos.x;
//             float dy = node->pos.y - edge.nearVertex->pos.y;
//             float distance = sqrt(dx * dx + dy * dy);
//             if (distance > 0) {
//                 float attraction = 0.1f * (distance - edge.weight);
//                 force.x -= attraction * dx / distance;
//                 force.y -= attraction * dy / distance;
//             }
//         }
//         if (this->frameCount > 2000) continue;
//         node->pos.x += force.x;
//         node->pos.y += force.y;
//         node->pos.x = max(min(1200.f, node->pos.x), 380.f);
//         node->pos.y = max(min(650.f, node->pos.y), 150.f);
//         frameCount++;
//     }
// }

<<<<<<< HEAD
//GraphVisual::GraphVisual(Font font) : font(font), isChosen(false), numComponent(0), graph(Graph()) {
//    
//}
=======
// // GraphVisual::GraphVisual(Font font) : font(font), isChosen(false), numComponent(0), graph(Graph()) {
    
// // }
>>>>>>> origin/Vile

// void GraphVisual::random() {
//     int vertexCount = rand() % 10 + 5;
//     graph = Graph();
//     for (int i = 0; i < vertexCount; ++i) {
//         graph.addVertex();
//     }
//     for (int i = 0; i < vertexCount; ++i) {
//         for (int j = i + 1; j < vertexCount; ++j) {
//             if (rand() % 3 == 0) {
//                 int weight = rand() % 10 + 1;
//                 graph.addEdge(i, j, weight);
//             }
//         }
//     }
//     numComponent = 0;
//     colorComponent.clear();
// }

// void GraphVisual::drawButton() {
//     this->createButton.draw();
//     if(this->isChosen) {
//         DrawLineEx({126, 501}, {297, 501}, 1.3, NeonTheme.color);
//         this->randomButton.draw();
//         this->loadFileButton.draw();
//     }
// }

// void GraphVisual::drawGraph() {
//     return this->graph.drawGraph(this->font, this->colorComponent);
// }

// int GraphVisual::loadFile(const std::string filename) {
//     ifstream inputFile(filename);
//     if (!inputFile) {
//         cerr << "Error: Cannot open file!" << endl;
//         return 0;
//     }
//     int n;
//     inputFile >> n;
//     this->graph = Graph();
//     for (int i = 0; i < n; ++i) {
//         graph.addVertex();
//     }
//     int weight;
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             inputFile >> weight;
//             if (weight > 0) {
//                 graph.addEdge(i, j, weight);
//             }
//         }
//     }
//     inputFile.close();
//     return 1;
// }
