#include "GraphCpp.hpp"
#include <assert.h>

int main()
{
    AdjacencyMatrix M(5, 5);
   
    M(0,1) = 1; M(1,0) = 1;
    M(0,2) = 1; M(2,0) = 1;
    M(0,3) = 1; M(3,0) = 1;
    M(2,1) = 1; M(1,2) = 1;
    M(2,4) = 1; M(4,2) = 1;

    M.Print();

    Vertex<int> E0(0);
    Vertex<int> E1(1);
    Vertex<int> E2(2);
    Vertex<int> E3(3);
    Vertex<int> E4(4);

    std::vector<Vertex<int>*> V = {&E0, &E1, &E2, &E3, &E4};

    UndirectedGraphAdj<int> testGraph(V, M);

    testGraph.Print();

    DFS<int> testDFS(testGraph);
    testDFS.Iterate(E0);

    std::cout << std::endl << std::endl;

    /*--- Example #3 --- */
    AdjacencyMatrix M2(4, 4);
    M2(0,1) = 1;
    M2(0,2) = 1;
    M2(1,2) = 1;
    M2(2,0) = 1;
    M2(2,3) = 1;
    M2(3,3) = 1;

    M2.Print();

    Vertex<int> S0(0);
    Vertex<int> S1(1);
    Vertex<int> S2(2);
    Vertex<int> S3(3);

    std::vector<Vertex<int> *> V2 = {&S0, &S1, &S2, &S3};

    DirectedGraphAdj<int> testGraph2(V2,M2);

    testGraph2.Print();

    DFS<int> testDFS2(testGraph2);
    testDFS2.Iterate(S1); // Output: DFS from vertex 1 : 1 2 0 3
    testDFS2.Iterate(S2); // Output: DFS from vertex 2 : 2 0 1 3
}