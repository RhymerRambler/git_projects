// Topological sort using BFS style traversal, while maintaining a
// map of node->in-degrees
//
// Assumes a directed acyclic graph

#include <map>
#include <queue>
#include <vector>
#include <cassert>

class InDegreesUpdater
{
  Graph& m_Graph;
  std::queue<int>& m_Q;
  std::map<int, int> m_InDegrees;
  public:
    InDegreesUpdater(Graph& g, std::queue<int>& q) : m_Graph(g), m_Q(q) {
      for (auto* n : m_Graph.nodes()) {
        m_InDegrees[n->id] = 0;
      }
      for (auto* n : m_Graph.nodes()) {
        for (auto& e : *(m_Graph.adj(n->id))) {
          m_InDegrees[e.first->id] ++;
        }
      }
      for (auto& p : m_InDegrees) {
        if (p.second == 0) m_Q.push(p.first);
      }
    }
    void decrDegree(int id) {
      assert(m_InDegrees[id] > 0);
      m_InDegrees[id] --;
      if (m_InDegrees[id] == 0) m_Q.push(id);
    }
};

class TopologicalSort
{
  Graph& m_Graph;
  std::queue<int> m_Q;
  std::vector<int> m_Result;
  InDegreesUpdater m_IDU;
  public:
    TopologicalSort(Graph& g) : m_Graph(g), m_IDU(g, m_Q) {
    }
    void start() {
      while(!m_Q.empty()) {
        int id = m_Q.front();
        m_Q.pop();
        for (auto& e : *(m_Graph.adj(id))) {
          m_IDU.decrDegree(e.first->id);
        }
        m_Result.push_back(id);
      }
    }
    std::vector<int> getResult() {
      return m_Result;
    }
};
