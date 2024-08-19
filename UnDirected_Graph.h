#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H
#include "Directed_Graph.h"


class UndirectedGraph {
private:
    int vertices;
    std::vector<Node> nodes;

public:
    UndirectedGraph(int v);

    void addEdge(int u, int v, int valid);

    void printGraph();

    void visit(int u);

    bool isConnected();

    void init();

    void createDirectedGraphDFS(int u, DirectedGraph& directedGraph, std::vector<int>& blackOrder);

    void createDirectedGraphFromUndirected(DirectedGraph& directedGraph, std::vector<int>& blackOrder);

    void ResetEdges();

    
};

#endif