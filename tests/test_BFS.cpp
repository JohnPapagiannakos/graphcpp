#include "GraphsLib.hpp"
#include <cassert>

int main()
{
    // Example #1
    Vertex<int> S0(0);
    Vertex<int> S1(1);
    Vertex<int> S2(2);
    Vertex<int> S3(3);

    DirectedGraph<int> testGraph;
    testGraph.AddPair(S0, S1);
    testGraph.AddPair(S0, S2);
    testGraph.AddPair(S1, S2);
    testGraph.AddPair(S2, S0);
    testGraph.AddPair(S2, S3);
    testGraph.AddPair(S3, S3);

    // Show Graph
    testGraph.Print();
    
    BFS<int> testBFS(testGraph);
    testBFS.Iterate(S2);

    // Example #2
    Vertex<int> S4(4);
    Vertex<int> S5(5);

    UndirectedGraph<int> testGraph2;
    testGraph2.AddPair(S0, S1);
    testGraph2.AddPair(S0, S2);
    testGraph2.AddPair(S1, S3);
    testGraph2.AddPair(S1, S4);
    testGraph2.AddPair(S2, S4);
    testGraph2.AddPair(S3, S4);
    testGraph2.AddPair(S3, S5);
    testGraph2.AddPair(S4, S5);

    // Show Graph
    testGraph2.Print();

    // Example #1
    BFS<int> testBFS2(testGraph2);
    testBFS2.Iterate(S0);
}