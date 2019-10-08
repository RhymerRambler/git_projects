#include "graph.h"
#include "DFS.h"

class CC : public DFSObserver
{
    Graph& m_Graph;
    std::vector<int> m_Components;
    int m_Count;
public:
    CC(Graph& g);
    bool isConnected(int v, int w);
    int count();
    int component(int v);
    void vertexMarked(int v);
};

