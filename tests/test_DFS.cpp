#include "GraphCpp.hpp"
#include <cassert>

int main()
{
    /*--- Example #1 --- */
    Vertex<std::string> A("A");
    Vertex<std::string> B("B");
    Vertex<std::string> C("C");
    Vertex<std::string> D("D");
    Vertex<std::string> E("E");
    Vertex<std::string> F("F");

    UndirectedGraph<std::string> testGraph;

    testGraph.AddPair(A, B);
    testGraph.AddPair(A, C);
    testGraph.AddPair(A, F);
    testGraph.AddPair(B, D);
    testGraph.AddPair(B, F);
    testGraph.AddPair(C, E);
    testGraph.AddPair(D, F);


    /*--- Example #2 --- */
    Vertex<int> E0(0);
    Vertex<int> E1(1);
    Vertex<int> E2(2);
    Vertex<int> E3(3);
    Vertex<int> E4(4);
    UndirectedGraph<int> testGraph2;
    testGraph2.AddPair(E0, E1);
    testGraph2.AddPair(E0, E2);
    testGraph2.AddPair(E0, E3);
    testGraph2.AddPair(E2, E1);
    testGraph2.AddPair(E2, E4);

    /*--- Example #3 --- */
    Vertex<int> S0(0);
    Vertex<int> S1(1);
    Vertex<int> S2(2);
    Vertex<int> S3(3);
    DirectedGraph<int> testGraph3;
    testGraph3.AddPair(S0, S1);
    testGraph3.AddPair(S0, S2);
    testGraph3.AddPair(S1, S2);
    testGraph3.AddPair(S2, S0);
    testGraph3.AddPair(S2, S3);
    testGraph3.AddPair(S3, S3);

    // Show Graph
    testGraph.Print();
    testGraph2.Print();
    testGraph3.Print();

    // Example #1
    // testGraph.DFS(A);
    DFS<std::string> testDFS(testGraph);
    testDFS.Iterate(A);  // Output: DFS from vertex A : A B D F C E
    std::array<std::string, 6> expected = {"A", "B", "D", "F", "C", "E"};
    size_t i = 0, check_sum = 0;
    for (auto &v : testDFS.Visited) 
    {
        check_sum += static_cast<size_t>(expected[i] == v->Value); i++;
    }
    assert(check_sum == testGraph.VerticesCount());

    // Example #2
    DFS<int> testDFS2(testGraph2);
    testDFS2.Iterate(E0); // Output: DFS from vertex 0 : 0 1 2 4 3
    // testGraph2.DFS(E0);
    // testGraph2.DFS();

    // Example #3
    DFS<int> testDFS3(testGraph3);
    testDFS3.Iterate(S1); // Output: DFS from vertex 1 : 1 2 0 3
    testDFS3.Iterate(S2); // Output: DFS from vertex 2 : 2 0 1 3
    // testGraph3.DFS(S1);
    // testGraph3.DFS(S2);
}