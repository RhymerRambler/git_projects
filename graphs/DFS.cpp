#include "DFS.h"
#include <iostream>

DFS::DFS(Graph& g, int start, DFSObserver* ob) : m_Graph(g), 
                                                 m_Start(start),
                                                 m_Marked(g.getSize()),
                                                 m_EdgeTo(g.getSize())
{
    if (ob) m_ObsVec.push_back(ob);
    m_EdgeTo[start] = -1;
    dfs(start);
}

void DFS::dfs(int node)
{
    m_Marked[node] = true;
    for (auto* ob : m_ObsVec) {
        ob->vertexMarked(node);
    }
    auto* adj_nodes = m_Graph.adj(node);
    for(auto ne: *adj_nodes) {
        if (!m_Marked[ne.first->id]) {
            m_EdgeTo[ne.first->id] = node;
            dfs(ne.first->id);
        }
    }
}

void DFS::reset(int start)
{
    m_Start = start;
    m_EdgeTo[start] = -1;
    for (int i = 0; i < m_Graph.getSize(); i++) {
        m_Marked[i] = false;
        m_EdgeTo[i] = 0;
    }
    dfs(start);
}

void DFS::continueAgain(int start)
{
    m_Start = start;
    m_EdgeTo[start] = -1;
    dfs(start);
}

bool DFS::isReachable(int node) {
    assert(node < m_Graph.getSize());
    return m_Marked[node];
}

std::vector<int> DFS::pathTo(int node)
{
    assert(node < m_Graph.getSize());
    if (!isReachable(node)) return std::vector<int>();
    std::vector<int> path;
    int i;
    for (i = node; i != m_Start && i != -1; i = m_EdgeTo[i]) {
        path.push_back(i);
    }
    if (i == -1) {
        std::cerr << "No path found from node: " << m_Start << " to node: " << node << std::endl;
        return std::vector<int>();
    }
    return path;
}

void DFS::registerObs(DFSObserver* obs)
{
    m_ObsVec.push_back(obs);
}
