#include "CC.h"
#include "DFS.h"

CC::CC(Graph& g) : m_Graph(g), m_Components(g.getSize()), m_Count(0)
{
    int i = 0;
    DFS dfs(m_Graph, i, this);
    do {
        while(i != m_Graph.getSize() && dfs.isReachable(++i));
        if (i == m_Graph.getSize()) break;
        m_Count++;
        dfs.continueAgain(i);
    } while (i < m_Graph.getSize());        
}

void CC::vertexMarked(int v)
{
    m_Components[v] = m_Count;
}

bool CC::isConnected(int v, int w)
{
    if (component(v) == component(w)) return true;
    return false;
}

int CC::count()
{
    return m_Count + 1;
}

int CC::component(int v)
{
    assert(v < m_Graph.getSize());
    return m_Components[v];
}
