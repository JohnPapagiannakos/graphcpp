#include "GraphCpp.hpp"
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

    ShortestPath<int,int> testDijstra(testWeightedGraph);
    testDijstra.DijkstraShortestPath(S0);

    std::cout << std::endl << std::endl;

    // Example #2
    WeightedVertex<int, double> E0(0);
    WeightedVertex<int, double> E1(1);
    WeightedVertex<int, double> E2(2);
    WeightedVertex<int, double> E3(3);
    WeightedVertex<int, double> E4(4);

    Matrix<double> M(5, 5);
    double M2[5][5] = {{0, 2, 3, 0, 0}, {2, 0, 15, 2, 0}, {3, 15, 0, 0, 13}, {0, 2, 0, 0, 9}, {0, 0, 13, 9, 0}};
    M.CopyData(M2[0], 5, 5);

    std::vector<WeightedVertex<int, double> *> V = {&E0, &E1, &E2, &E3, &E4};

    UndirectedWeightedGraphAdj<int, double> testWeightedGraph2(V, M);

    // Show Graph
    testWeightedGraph2.Print();

    std::cout << std::endl << std::endl;

    ShortestPath<int, double> testDijstra2(testWeightedGraph2);
    testDijstra2.DijkstraShortestPath(E0);

    std::cout << std::endl << std::endl;

    // Example #3 -- Directed Weighted Graph
    WeightedVertex<char, double> A('A');
    WeightedVertex<char, double> B('B');
    WeightedVertex<char, double> C('C');
    WeightedVertex<char, double> S('S');
    WeightedVertex<char, double> T('T');
    WeightedVertex<char, double> F('F');

    UndirectedWeightedGraph<char, double> testWeightedGraph3;
    testWeightedGraph3.AddPair(S, A, 3);
    testWeightedGraph3.AddPair(S, B, 4);
    testWeightedGraph3.AddPair(B, F, 5);
    testWeightedGraph3.AddPair(A, B, 6);
    testWeightedGraph3.AddPair(A, F, 7);
    testWeightedGraph3.AddPair(A, C, 2);
    testWeightedGraph3.AddPair(C, F, 1);
    testWeightedGraph3.AddPair(C, T, 8);
    testWeightedGraph3.AddPair(F, T, 4);

    // Show Graph
    testWeightedGraph3.Print();

    std::cout << std::endl << std::endl;

    ShortestPath<char, double> testDijstra3(testWeightedGraph3);
    testDijstra3.DijkstraShortestPath(S);

    std::cout << std::endl << std::endl;
}