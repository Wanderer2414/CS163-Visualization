#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Global.h"
#include "ProgressBar.h"
#include "Button.h"

struct Vertex {
    struct Edge {
        Vertex* nearVertex;
        int weight;
        bool highlight = 0;
    };
    vector<Edge> neighbor;
    Vector2 pos;
    int color = 0; 
};

class Graph {
    public:
    Graph() {};



    int findParent(vector<int>& parent, int node);
    void unionNode(vector<int>& parent, vector<int>& rank, int u, int v);
    int getVertexIndex(Vertex* node);

    void clearGraph();
    void addVertex(Vertex* node);
    void addVertex();
    int addEdge(int from, int to, int weight);
    void random(int vertexCount, int maxX, int maxY);
    void startFromFile(const string filename);
    void drawGraph(Font font, vector<Color> color = {});
    void updatePosition();

    ~Graph();
    private:
    vector<Vertex*> nodes;
    int frameCount = 0;

};

class GraphVisual {
    public:
    GraphVisual(Font font = {});
    void random();
    int loadFile();
    void findConnectedComponents(const vector<vector<int>>& matrix, vector<vector<int>>& components);
    void drawGraph();
    void drawButton();


    private:
    Graph graph;
    int numComponent;
    vector<Color> colorComponent;
    ProgressBar bar;
    Button createButton;
    Button randomButton;
    Button loadFileButton;
    bool isChosen;

    Font font;
    
};

#endif //SHORTESTPATH_H