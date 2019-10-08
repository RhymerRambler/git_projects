#include "graph.h"

#include <iostream>
#include <fstream>

void Graph::addNodes(int count)
{
    for (int i = 0; i < count; i++) {
        Node *n = new Node();
        n->id = i;
        m_Nodes.push_back(n);
    }
    m_Size = count;
}

void Graph::addEdge(int id1, int id2, Edge* e)
{
    Node* n1 = m_Nodes[id1];
    Node* n2 = m_Nodes[id2];
    Node::NE ne1(n2, e);
    (n1->nlist).push_back(ne1);
    if (!m_IsDirected) {
        Node::NE ne2(n1, e);
        (n2->nlist).push_back(ne2);
    }
}

void Graph::addEdge(int id1, int id2)
{
    addEdge(id1, id2, new Edge());
}

void Graph::addEdge(int id1, int id2, int label)
{
    Edge *e = new Edge();
    e->label = label;
    e->label_set = true;
    addEdge(id1, id2, e);
}

void Graph::printDot(std::string name) const
{
    std::ofstream fout((name + ".dot").c_str(), std::ofstream::out);
    std::string sep;
    if (m_IsDirected) {
        fout << "digraph G {\n";
        sep = "->";
    } else {
        fout << "graph G {\n";
        sep = "--";
    }

    fout << "\tgraph [fontname=\"fixed\"];\n"
            "\tnode [fontname=\"fixed\"];\n"
            "\tedge [fontname=\"fixed\"];\n";
    std::map<Edge*, bool> visited_edge_map;
    for (auto i = 0; i < m_Size; i++)
    {
        std::vector<Node::NE>& nlist = m_Nodes[i]->nlist;
        for (auto it = nlist.begin(); it != nlist.end(); ++it) {
            if (visited_edge_map[it->second]) continue;
            visited_edge_map[it->second] = true;
            fout << "\t" << i << " " << sep << " " << it->first->id;
            
            if (it->second->label_set) { // label of the edge if present
                fout << " [label = \"" << it->second->label << "\"]";
            }
            fout << ";\n";
        }
    }
    fout << "}";
    fout.close();
}

void Graph::print() const
{
    for (auto i = 0; i < m_Size; i++)
    {
        std::cout << i << " ==> ";
        std::vector<Node::NE>& nlist = m_Nodes[i]->nlist;
        for (auto it = nlist.begin(); it != nlist.end(); ++it) {
            std::cout << it->first->id << ", ";
        }
        std::cout <<"\n";
    }
}

std::vector<Node::NE>* Graph::adj(int id) const
{
    return &m_Nodes[id]->nlist;    
}

int Graph::getSize() const
{
    return m_Size;
}
