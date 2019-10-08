#pragma once
#include "graph.h"

class DFSObserver;

class DFS
{
    Graph& m_Graph;
    std::vector<bool> m_Marked;
    std::vector<int> m_EdgeTo;
    std::vector<DFSObserver*> m_ObsVec;
    int m_Start;
    void dfs(int);
public:
    DFS(Graph& g, int start, DFSObserver* ob=nullptr);
    void reset(int start);
    void continueAgain(int start);
    void registerObs(DFSObserver* obs);
    bool isReachable(int nid);
    std::vector<int> pathTo(int nid);
};

class DFSObserver
{
public:
    virtual void vertexMarked(int v) = 0;
};
