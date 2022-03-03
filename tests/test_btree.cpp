#include "GraphCpp.hpp"
#include "Trees/BTree.hpp"

int main()
{
    BTree<int> btree;

    btree.insert(4);
    btree.insert(18);
    btree.insert(5);

    btree.insert(20);
    btree.insert(32);
    btree.insert(19);
    btree.insert(10);

    std::cout << "size = " << btree.size() << std::endl;
    std::cout << "max depth = " << btree.maxDepth() << std::endl;
}