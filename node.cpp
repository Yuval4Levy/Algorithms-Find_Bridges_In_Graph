
#include "node.h"

Node::Node(int _data) : data(_data), color(Color::WHITE), num_edges(0) {}

void Node::addEdge(int neighbor, int valid, EdgeColor edgeColor)
{
    edges.push_back(Edge(data, neighbor, valid));
    edges.back().color = edgeColor;
}