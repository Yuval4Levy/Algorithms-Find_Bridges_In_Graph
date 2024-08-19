#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H
#include <algorithm> 
#include "node.h"

class DirectedGraph {
private:
    int vertices;
    std::vector<Node> nodes;
    std::vector<std::vector<int>> child;
    std::vector<std::pair<int, int>> bridges; // Store bridges as pairs of vertices
public:
    DirectedGraph(int v);

    void addEdge(int u, int v, int valid, EdgeColor color);
    int getvertices() { return vertices; }
    void printGraph();
    void visit(int u);
    void DFS(std::vector<int>& blackOrder);
    void reverseEdges(DirectedGraph& transposedGraph);
    std::vector<std::pair<int, int>> getbridges() { return bridges; }
};

#endif
