
#include "UnDirected_Graph.h"

UndirectedGraph::UndirectedGraph(int v) : vertices(v), nodes(v, Node(-1)) {
    for (int i = 0; i < v; ++i) {
        nodes[i].data = i+1;
    }
}

void UndirectedGraph::addEdge(int u, int v ,int valid)
{
   nodes[u-1].addEdge(v, valid, EdgeColor::NONE);
   nodes[u-1].num_edges += 1;
   nodes[v-1].addEdge(u, valid, EdgeColor::NONE);
   nodes[v-1].num_edges += 1;

   nodes[u - 1].edges[nodes[u - 1].num_edges - 1].twin_place = nodes[v - 1].num_edges - 1;
   nodes[v - 1].edges[nodes[v - 1].num_edges - 1].twin_place = nodes[u - 1].num_edges - 1;
}

void UndirectedGraph::printGraph()
{
    for (int i = 0; i < vertices; ++i) {
        std::cout << "Node " << i+1 << " is connected to:";
        for (int j = 0;j <  nodes[i].num_edges; j++) {
            std::cout << " " << nodes[i].edges[j].to;
        }
        std::cout << std::endl;
    }
}

void UndirectedGraph::visit(int u)
{
    nodes[u-1].color = Color::GRAY;

    for (int j = 0; j < nodes[u-1].num_edges; j++ ) {
        if (nodes[nodes[u-1].edges[j].to - 1].color == Color::WHITE && nodes[u-1].edges[j].valid == 0) {
            nodes[u-1].edges[j].valid = 1;
            visit(nodes[u-1].edges[j].to);
        }
    }

    nodes[u-1].color = Color::BLACK;
}

bool UndirectedGraph::isConnected()
{
    // Reset colors for a new traversal
    for (int i = 0; i < vertices; ++i) {
        nodes[i].color = Color::WHITE;
    }

    // Perform DFS from the first node
    visit(1);

    // Check if all nodes have been visited
    for (int i = 0; i < vertices; ++i)
    {
        if (nodes[i].color == Color::WHITE)
        {
            std::cout << "Graph is not connected\n";
            return false;
        }

    }
    return true;
}

void UndirectedGraph::createDirectedGraphDFS(int u, DirectedGraph &directedGraph, std::vector<int>& blackOrder)
{
    nodes[u - 1].color = Color::GRAY;

    for (Edge& edge : nodes[u-1].edges) {
        if(edge.valid == 0) {
            if (nodes[edge.to - 1].color == Color::WHITE) {
                directedGraph.addEdge(u, edge.to, 1, EdgeColor::GREEN); // Tree Edge
                nodes[edge.to - 1].edges[edge.twin_place].valid = 1;

                createDirectedGraphDFS(edge.to, directedGraph, blackOrder);
            }
            else if (nodes[edge.to - 1].color == Color::GRAY) {
                directedGraph.addEdge(u, edge.to, 1, EdgeColor::RED); // Back Edge
                nodes[edge.to - 1].edges[edge.twin_place].valid = 1;
            }
            else if (nodes[edge.to - 1].color == Color::BLACK && nodes[u - 1].color == Color::GRAY) { // To avoid processing the same edge twice
                directedGraph.addEdge(u, edge.to, 1, EdgeColor::BLUE); // Forward Edge
                nodes[edge.to - 1].edges[edge.twin_place].valid = 1;
            } else {
                directedGraph.addEdge(u, edge.to, 1, EdgeColor::PURPLE); // Cross Edge
                nodes[edge.to - 1].edges[edge.twin_place].valid = 1;
            }
            
        }
    }

    nodes[u - 1].color = Color::BLACK;
    blackOrder.push_back(u);
}

void UndirectedGraph::createDirectedGraphFromUndirected(DirectedGraph &directedGraph, std::vector<int> &blackOrder)
{
    for (int u = 0; u < vertices; ++u) {
        if (nodes[u].color == Color::WHITE) {
            createDirectedGraphDFS(u+1, directedGraph, blackOrder);
        }
    }
}

void UndirectedGraph::init()
{
    // Reset graph for a new traversal
    for (int i = 0; i < vertices; ++i) {
        nodes[i].color = Color::WHITE;
        for (int j = 0; j < nodes[i].num_edges; j++)
        {
            nodes[i].edges[j].valid = 0;
        }
    }
}

void UndirectedGraph::ResetEdges()
{
    for(int i= 0; i<vertices; ++i)
    {
        for(int j=0; j<nodes[i].num_edges;j++)
        {
            nodes[i].edges[j].valid = 0;
        }

    }
}
