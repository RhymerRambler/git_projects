#pragma once

#include <map>
#include <vector>
#include <string>

#include <assert.h>
struct Edge
{
    int label;
    bool label_set = false;
};

struct Node
{
    int id;
    using NE = std::pair<Node*, Edge*>;
    std::vector<Node::NE> nlist;
};

class Graph
{
    bool m_IsDirected;
    int m_Size;
    std::vector<Node*> m_Nodes;
public:
    Graph(bool directed=false) : m_IsDirected(directed) { }
    void addNodes(int count);

    void addEdge(int id1, int id2, Edge* e);
    void addEdge(int id1, int id2);
    void addEdge(int id1, int id2, int label);

    int getSize() const;
    std::vector<Node::NE>* adj(int) const;

    void print() const;
    void printDot(std::string name) const;

    bool isDirected() const { return m_IsDirected; }
};

