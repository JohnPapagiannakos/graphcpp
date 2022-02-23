#include "GraphsLib.hpp"
#include <cassert>

int main()
{
    // Example #1
    WeightedVertex<int, int> S0(0);
    WeightedVertex<int, int> S1(1);
    WeightedVertex<int, int> S2(2);
    WeightedVertex<int, int> S3(3);
    WeightedVertex<int, int> S4(4);

    UndirectedWeightedGraph<int, int> testWeightedGraph;
    testWeightedGraph.AddPair(S0, S1, 10);
    testWeightedGraph.AddPair(S0, S4, 20);
    testWeightedGraph.AddPair(S1, S2, 30);
    testWeightedGraph.AddPair(S1, S3, 40);
    testWeightedGraph.AddPair(S1, S4, 50);
    testWeightedGraph.AddPair(S2, S3, 60);
    testWeightedGraph.AddPair(S3, S4, 70);

    // Show Graph
    testWeightedGraph.Print();

    std::cout << std::endl << std::endl;

    // Example #2
    WeightedVertex<int, int> E0(0);
    WeightedVertex<int, int> E1(1);
    WeightedVertex<int, int> E2(2);
    WeightedVertex<int, int> E3(3);
    WeightedVertex<int, int> E4(4);

    Matrix<int> M(5, 5);
    int M2[5][5] = {{0,2,3,0,0}, {2,0,15,2,0}, {3,15,0,0,13}, {0,2,0,0,9}, {0,0,13,9,0}};
    M.CopyData(M2[0], 5, 5);

    std::vector<WeightedVertex<int, int> *> V = {&E0, &E1, &E2, &E3, &E4};

    UndirectedWeightedGraphAdj<int, int> testWeightedGraph2(V, M);

    // Show Graph
    testWeightedGraph2.Print();
}