#define _CRT_SECURE_NO_WARNINGS
#include"UnDirected_Graph.h"


int main() {
    try {
        int vertices, edges;
        std::cin >> vertices;
        if (vertices <= 0 )
            throw std::invalid_argument("invalid input");

        UndirectedGraph undirectedGraph(vertices);
        std::vector<int> blackOrder;
        std::cin >> edges;
        if (edges < 0 )
            throw std::invalid_argument("invalid input");

        for (int i = 0; i < edges; ++i) {
            int u, v;
            std::cin >> u >> v;
            if (u > vertices || v > vertices || u <= 0 || v <= 0)
                throw std::invalid_argument("invalid input");
            undirectedGraph.addEdge(u, v, 0);
        }

        if (undirectedGraph.isConnected()) {
            undirectedGraph.init();
            DirectedGraph directedGraph(vertices);

            undirectedGraph.createDirectedGraphFromUndirected(directedGraph, blackOrder);

            reverse(blackOrder.begin(), blackOrder.end()); // Reverse the order

            DirectedGraph transposedGraph(vertices);
            directedGraph.reverseEdges(transposedGraph);

            transposedGraph.DFS(blackOrder);

            if (transposedGraph.getbridges().empty())
                std::cout << "No bridges in graph" << std::endl;
            else {
                for (const std::pair<int, int> &bridge: transposedGraph.getbridges()) {
                    std::cout << bridge.second << " " << bridge.first << std::endl;
                }
            }
        }
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}








