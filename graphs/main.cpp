#include "graph.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "Topological_sort.h"

#include <iostream>

int main()
{
    Graph g(false);
    g.addNodes(9);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(0, 5);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(7, 8);
    // g.print();
    g.printDot("g");

    Graph g2(false);
    g2.addNodes(6);
    g2.addEdge(0, 1, 3);
    g2.addEdge(0, 2, 9);
    g2.addEdge(1, 2, 4);
    g2.addEdge(1, 3, 11);
    g2.addEdge(2, 3, 4);
    g2.addEdge(2, 4, 6);
    g2.addEdge(3, 4, 1);
    g2.addEdge(3, 5, 8);
    g2.addEdge(4, 5, 6);
    // g2.print();
    g2.printDot("g2");

    Graph g3(false);
    g3.addNodes(7);
    g3.addEdge(0, 1, 5);
    g3.addEdge(0, 2, 6);
    g3.addEdge(1, 3, 7);
    g3.addEdge(2, 3, 3);
    g3.addEdge(1, 4, 3);
    g3.addEdge(2, 5, 7);
    g3.addEdge(4, 6, 22);
    g3.addEdge(3, 6, 15);
    g3.addEdge(5, 6, 4);
    // g3.print();
    g3.printDot("g3");

    Graph g4(true);
    g4.addNodes(8);
    g4.addEdge(0, 2);
    g4.addEdge(0, 3);
    g4.addEdge(0, 4);
    g4.addEdge(1, 3);
    g4.addEdge(1, 4);
    g4.addEdge(2, 5);
    g4.addEdge(3, 5);
    g4.addEdge(3, 4);
    g4.addEdge(4, 6);
    g4.addEdge(5, 6);
    g4.addEdge(5, 7);
    g4.addEdge(6, 7);
    g4.printDot("g4");

    std::cout << "/////////// DFS ///////////" << std::endl;
    DFS dfs(g, 0);
    std::cout << "path to 5: ";
    auto p = dfs.pathTo(5);
    for (auto e : p) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;

    std::cout << "/////////// Dijkstra ///////////\n";
    Dijkstra djk(g2, 0);
    djk.start();
    djk.print();

    Dijkstra djk2(g3, 0);
    djk2.start();
    djk2.print();
    std::cout << std::endl;

    std::cout << "/////////// Topological sort ///////////\n";
    TopologicalSort ts(g4);
    ts.start();
    for (auto n : ts.getResult()) {
      std::cout << n << " => ";
    }
    std::cout << std::endl;
    return 0;
}
