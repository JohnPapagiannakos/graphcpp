#include "GraphCpp.hpp"
#include "Trees/BST.hpp"

int main()
{
    BST<int> bst;

    bst.insert(4);
    bst.insert(18);
    bst.insert(5);

    bst.insert(20);
    bst.insert(32);
    bst.insert(19);
    bst.insert(10);
    bst.insert(102);

    bst.search(12);

    std::cout << "size = " << bst.size() << std::endl;
    std::cout << "max depth = " << bst.maxDepth() << std::endl;
    std::cout << "min(value) = " << bst.minValue() << std::endl;
    std::cout << "max(value) = " << bst.maxValue() << std::endl;
    // bst.printIncrSorted();
    // bst.printDecrSorted();
    std::vector<int> path = bst.getPathOfSum(37);
    for (auto &el : path)
    {
        std::cout << el << "\t";
    }
    std::cout << std::endl;
}