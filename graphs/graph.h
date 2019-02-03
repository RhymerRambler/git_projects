#pragma once

#include <map>
#include <vector>

#include <assert.h>
struct EdgeInfo
{
  int cost;
};


struct NodeInfo
{
  bool visited;
  NodeInfo() : visited(false) { }
  NodeInfo(bool v) : visited(v) { }
};

struct Node
{
  int id;
  typedef std::pair<EdgeInfo*, Node*> NE;
  std::vector<Node::NE> nlist;
  NodeInfo* info;
};

struct Edge
{
  Node *n1, *n2;
  EdgeInfo *info;  
};

struct DFS
{
    std::vector<std::vector<Node*>> components;
};

class Graph
{
    std::map<int, Node*> m_nodes;
    void dfsHelper(Node*, std::vector<Node*>&);    
public:
    void addNode(int id, NodeInfo *ni);
    void addEdge(int id1, int id2, EdgeInfo* ei);
    void print();
    void printDot();
    DFS* doDFS();
};

