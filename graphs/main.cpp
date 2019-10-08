#include "graph.h"
#include "DFS.h"

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
    g.print();
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
    g2.print();
    g2.printDot("g2");

    DFS dfs(g, 0);
    std::cout << "path to 5: ";
    auto p = dfs.pathTo(5);
    for (auto e : p) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
    return 0;
}
