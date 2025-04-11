/*#ifndef SHORTESTPATH_H
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

    int findParent(vector<int>& parent, int node);
    void unionNode(vector<int>& parent, vector<int>& rank, int u, int v);
    int getVertexIndex(Vertex* node);
    void addVertex(Vertex* node);
    void addVertex();
    int addEdge(int from, int to, int weight);
    void random(int vertexCount, int maxX, int maxY);
    void startFromFile(const std::string filename);
    void drawGraph(Font font, std::vector<Color> color = {});
    void updatePosition();
    void resetHighlight();

    private:
    vector<Vertex*> nodes;
    int frameCount = 0;

};

class GraphVisual {
    public:
    void random();
    int loadFile(const std::string filename);
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

#endif*/