#include "GraphsLib.hpp"
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
}