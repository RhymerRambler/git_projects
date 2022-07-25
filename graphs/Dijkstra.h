#pragma once
#include "graph.h"
#include <queue>
#include <vector>
#include <iostream>

using NC = std::pair<int, int>;
class CompareEdge
{
  public:
    bool operator () (const NC& e1, const NC& e2) const {
      return e1.second < e2.second;
    }
};

class Dijkstra
{
    Graph& m_Graph;
    std::priority_queue<NC, std::vector<NC>, CompareEdge> m_PQ;
    int m_Src;
    std::vector<int> m_SP; // holds the shortest path
    std::vector<unsigned int> m_Dist;
public:
    Dijkstra(Graph& g, int source) : m_Graph(g), m_PQ(CompareEdge()), m_Src(source) {
      m_SP.resize(g.getSize());
      m_Dist.resize(g.getSize());
      m_SP[m_Src] = m_Src;
      for (auto& e : m_Dist) {
        e = unsigned (-1);
      }
      m_Dist[m_Src] = 0;
    }

    void start() {
      update(m_Src);
      while(!m_PQ.empty()) {
        int next = m_PQ.top().first;
        m_PQ.pop();
        update(next);
      }
    }

    void update (int id) {
      auto* vec = m_Graph.adj(id);
      for (auto& ne : *vec) {
        int nid = ne.first->id;
        unsigned new_dist = m_Dist[id] + ne.second->label;
        if (new_dist < m_Dist[nid]) {
          m_Dist[nid] = new_dist;
          m_SP[nid] = id;
          m_PQ.push(std::make_pair(nid, new_dist));
        } 
      }
    }

    void print() {
      std::cout << std::endl;
      for (auto i = 0; i < m_Dist.size(); i++) {
        std::cout << "m_Dist[" << i << "] = " << m_Dist[i] << std::endl;
        std::cout << "Path: " << i << " <= ";
        int j = i;
        while (m_SP[j] != m_Src) {
          std::cout << m_SP[j] << " <= ";
          j = m_SP[j]; 
        }
        std::cout << m_Src << std::endl;
      }
    }
};
