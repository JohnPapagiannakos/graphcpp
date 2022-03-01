#include "GraphCpp.hpp"
#include <assert.h>

int main()
{
    AdjacencyMatrix M(5, 2);
    M.setConstant(5);
    // std::cout << M(2, 1) << std::endl;
    M(2,1) = 4;
    M.Print();

    AdjacencyMatrix M_T(2, 5);
    M_T = M.transpose();
    M_T.Print();

    AdjacencyMatrix notS(5, 2);
    notS.setConstant(2);
    notS(2, 1) = 4;
    // std::cout << notS.isSymmetric() << std::endl;

    notS += M;
    notS.Print();

    AdjacencyMatrix S(3, 3);
    S.setConstant(2);
    S(2, 1) = 4;
    S(1, 2) = 4;
    S(0, 2) = 3;
    S(2, 0) = 3;
    std::cout << S.isSymmetric() << std::endl;
    S.Print();
}