
#include "Directed_Graph.h"

DirectedGraph::DirectedGraph(int v) : vertices(v), nodes(v, Node(-1)) {
    for (int i = 0; i < v; ++i) {
        nodes[i].data = i + 1;
    }
}

void DirectedGraph::addEdge(int u, int v, int valid, EdgeColor color) {
    for (Edge& edge : nodes[u-1].edges) {
        if (edge.to == v && edge.color == color) {
            return; // Edge already added
        }
    }
    nodes[u-1].addEdge(v, valid, color);
}

void DirectedGraph::printGraph() {
    for (int i = 0; i < vertices; ++i) {
        std::cout << "Node " << i + 1 << " has edges:";
        for (const Edge &edge: nodes[i].edges) {
            std::cout << " (" << edge.from << " -> " << edge.to << ", ";

            switch (edge.color) {
                case EdgeColor::GREEN:
                    std::cout << "Tree";
                    break;
                case EdgeColor::RED:
                    std::cout << "Back";
                    break;
                case EdgeColor::BLUE:
                    std::cout << "Forward";
                    break;
                case EdgeColor::PURPLE:
                    std::cout << "Cross";
                    break;
                default:
                    break;
            }

            std::cout << ")";
        }
        std::cout << std::endl;
    }
}
void DirectedGraph::visit(int u) {

    nodes[u - 1].color = Color::GRAY;

    for (Edge& edge : nodes[u - 1].edges) {
        if (edge.valid == 0) {
            if (nodes[edge.to - 1].color == Color::WHITE) {
                edge.color = EdgeColor::GREEN;
                child[u - 1].push_back(edge.to);
                visit(edge.to);
            }
            else if (nodes[edge.to - 1].color == Color::GRAY) {
                edge.color = EdgeColor::RED;
            }
            else if (nodes[edge.to - 1].color == Color::BLACK && nodes[u - 1].color == Color::GRAY) { // To avoid processing the same edge twice
                // Check if edge.to is a descendant of u
                bool isDescendant = false;
                for (int descendant : child[u - 1]) {
                    if (descendant == edge.to || find(child[descendant - 1].begin(), child[descendant - 1].end(), edge.to) != child[descendant - 1].end()) {
                        isDescendant = true;
                        break;
                    }
                }
                if (isDescendant) {
                    edge.color = EdgeColor::BLUE;
                }
                else {
                    edge.color = EdgeColor::PURPLE;
                    bridges.push_back(std::make_pair(u, edge.to)); // Add the bridge to the vector
                }
            }
        }
    }

    nodes[u - 1].color = Color::BLACK;
}

void DirectedGraph::DFS(std::vector<int>& blackOrder) {
    
    child.assign(vertices, std::vector<int>());

    for (int u : blackOrder) {
        if (nodes[u-1].color == Color::WHITE) 
            visit(u);
    }
}

void DirectedGraph::reverseEdges(DirectedGraph& transposedGraph)
{
    for (Node& node : nodes)
    {
        for (Edge& edge : node.edges) {
            transposedGraph.addEdge(edge.to, edge.from, 0, EdgeColor::NONE); 
        }
    }
}


