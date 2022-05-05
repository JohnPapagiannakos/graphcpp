#include "GraphCpp.hpp"
#include "Trees/HashTree.hpp"

int main()
{
    HTree<int, int> HT;

    std::vector<std::pair<int, int>> datablocks;
    std::pair<int, double> tmp;

    const int blocks_num = 7;

    // srand(0);
    srand(time(0));
    for(int l=0; l<blocks_num; l++)
    {
        int hash = rand() % 10;
        tmp = std::make_pair(l, hash);
        datablocks.push_back(tmp);
    }
    HT.construct_tree(datablocks);
    std::cout << HT.compute_hash() << std::endl;
    HT.topview();

    // for (int l = 0; l < blocks_num; l++)
    // {
    //     std::cout << datablocks[l].first << " " << datablocks[l].second << std::endl;
    // }

    // test hashing
    int pair_01, pair_23, pair_45, pair_67;
    int pair_0123, pair_4567;
    int pair_root;

    pair_01 = pseudo_hash(datablocks[0].second, datablocks[1].second);
    pair_23 = pseudo_hash(datablocks[2].second, datablocks[3].second);
    pair_45 = pseudo_hash(datablocks[4].second, datablocks[5].second);
    pair_67 = pseudo_hash(datablocks[6].second, 0);

    pair_0123 = pseudo_hash(pair_01, pair_23);
    pair_4567 = pseudo_hash(pair_45, pair_67);

    pair_root = pseudo_hash(pair_0123, pair_4567);

    std::cout << pair_root << std::endl;

    if(pair_root == HT.compute_hash())
        std::cout << "test succeed!" << std::endl;
    else
        std::cout << "test failed!" << std::endl;
    return 0;
}
