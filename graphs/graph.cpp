#include <graph.h>

#include <iostream>

void Graph::addNode(int id, NodeInfo *ni)
{
    Node *n = new Node();
    n->id = id;
    assert(m_nodes.find(id) == m_nodes.end());
    m_nodes[id] = n;
    n->info = ni;
}

void Graph::addEdge(int id1, int id2, EdgeInfo* ei)
{
    assert(m_nodes.find(id1) != m_nodes.end());
    assert(m_nodes.find(id2) != m_nodes.end());
    Node* n1 = m_nodes[id1];
    Node* n2 = m_nodes[id2];
    Node::NE ne1(ei, n2);
    Node::NE ne2(ei, n1);
    (n1->nlist).push_back(ne1);
    (n2->nlist).push_back(ne2);
}

void Graph::print()
{
    for (auto it = m_nodes.begin(); it != m_nodes.end(); it++)
    {
        std::cout << it->first << " ==> ";
        std::vector<Node::NE>& nlist = (it->second)->nlist;
        for (auto it2 = nlist.begin(); it2 != nlist.end(); ++it2) {
            std::cout << it2->second->id << ", ";
        }
        std::cout <<"\n";
    }
}

void Graph::dfsHelper(Node* v, std::vector<Node*>& t)
{
    if (v->info->visited == false) {
        v->info->visited = true;
        t.push_back(v);
        for (auto ne : v->nlist) {
            dfsHelper(ne.second, t);
        }
    }
}

DFS* Graph::doDFS()
{
    auto it = m_nodes.begin();
    DFS *dfs = new DFS();
    while (1) {
        std::vector<Node*> dfs_trav;
        dfsHelper(it->second, dfs_trav);
        (dfs->components).push_back(dfs_trav);
        ++it;
        while ((it != m_nodes.end()) && (it->second->info)->visited) it++;
        if (it == m_nodes.end()) break;
    }
    return dfs;
}
