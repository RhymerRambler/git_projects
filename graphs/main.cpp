#include <graph.h>

#include <iostream>

int main()
{
    Graph g;
    g.addNode(1, new NodeInfo());
    g.addNode(2, new NodeInfo());
    g.addNode(3, new NodeInfo());
    g.addNode(4, new NodeInfo());
    g.addNode(5, new NodeInfo());
    g.addNode(6, new NodeInfo());
    g.addNode(7, new NodeInfo());
    g.addNode(8, new NodeInfo());
    g.addNode(9, new NodeInfo());

    g.addEdge(1, 4, NULL);
    g.addEdge(1, 5, NULL);
    g.addEdge(1, 6, NULL);

    g.addEdge(2, 4, NULL);
    g.addEdge(2, 5, NULL);
    g.addEdge(2, 6, NULL);
    
    g.addEdge(3, 4, NULL);
    g.addEdge(3, 5, NULL);
    g.addEdge(3, 6, NULL);
    
    g.addEdge(8, 9, NULL);
    
    g.print();
    g.printDot();

    DFS *dfs = g.doDFS();
    for (auto c : dfs->components) {
        std::cout << "Component: \n";
        for (auto n : c) {
            std::cout << n->id << ", ";
        }
        std::cout << "\n";
    }
    return 0;
}
