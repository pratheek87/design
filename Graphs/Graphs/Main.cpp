// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graph.h"

int main()
{
    Graph g(6, true);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(3, 5);

    //g.displayGraph();
    cout << "top sort" << endl;
    g.TopoSort(1);
    //g.TraverseDFS(5);
 


    return 1;
}
