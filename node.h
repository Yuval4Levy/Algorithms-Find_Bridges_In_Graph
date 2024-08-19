#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include <set>
#include "edge.h"

enum class Color {
    WHITE,
    GRAY,
    BLACK
};

class Node {
public:
    int data;
    Color color;
    int num_edges;
    std::vector<Edge> edges;

    Node(int _data);

    void addEdge(int neighbor, int valid, EdgeColor edgeColor);

};

#endif