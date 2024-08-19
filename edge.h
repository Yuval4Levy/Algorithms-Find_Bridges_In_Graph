#ifndef EDGE_H
#define EDGE_H
enum class EdgeColor {
    NONE,
    GREEN,   // Tree Edge
    RED,     // Back Edge
    BLUE,    // Forward Edge
    PURPLE   // Cross Edge
};

class Edge {
public:
    int from;
    int to;
    int valid;
    EdgeColor color;
    int twin_place;

    Edge(int _from, int _to, int valid) : from(_from), to(_to),valid(valid), color(EdgeColor::NONE) {}
};

#endif