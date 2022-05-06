#ifndef HTREE_HPP
#define HTREE_HPP

#include <math.h>
#include <utility>
#include "Node.hpp"
#include "../HashingFunctions.hpp"

template <typename T, typename V>
class HTree
{
    public:
    HTree() : _root(NULL) {};

    // void insert(T key, T value)
    // {
    //     if (_root != NULL)
    //         insert(key, value, _root);
    //     else
    //     {
    //         _root = new Node2<T>(key, value);
    //         _root->left = NULL;
    //         _root->right = NULL;
    //     }
    // }

    void construct_tree(std::vector<std::pair<T,V>> &datablocks)
    {
        int size = datablocks.size();
        if(size < 1) return;

        int height = static_cast<int>(std::ceil(std::log2(size)) + 1);

        // sort blocks first
        std::sort(datablocks.begin(), datablocks.end());

        int non_leafs_num = std::pow(2, height-1) - 1;
        std::cout << non_leafs_num << std::endl;

        // Create non-leaf nodes & initialize their values to 0.
        for (int n = datablocks[size - 1].first + 1; n < datablocks[size - 1].first + 1 + non_leafs_num; n++)
        {
            if (_root != NULL)
                insert(n, 0, _root);
            else
            {
                _root = new Node2<T,V>(n, 0);
                _root->left = NULL;
                _root->right = NULL;
            }
        }

        // Insert leafs
        for (int n = 0; n < size; n++)
        {
            if (_root != NULL)
                insert(datablocks[n].first, datablocks[n].second, _root);
            else
            {
                _root = new Node2<T, V>(datablocks[n].first, datablocks[n].second);
                _root->left = NULL;
                _root->right = NULL;
            }
        }
    }

    int compute_hash(void)
    {
        compute_hash(_root);
        return _root->value;
    }

    void topview(void)
    {
        topView(_root);
        std::cout << std::endl;
    }

    void destroy_tree(void)
    {
        destroy_tree(_root);
    }

    /*
        Compute the number of nodes in a tree.
    */
    size_t size(void)
    {
        return size(_root);
    }

    /*
        Compute the maxDepth of a BST.
    */
    size_t maxDepth(void)
    {
        return maxDepth(_root);
    }

    ~HTree() {destroy_tree();};

    private:
    Node2<T,V> *_root;

    void insert(T key, V value, Node2<T,V> *leaf)
    {
        std::queue<Node2<T,V>*> waitingNodes;

        waitingNodes.push(leaf);

        while (!waitingNodes.empty())
        {
            Node2<T,V> *firstNode = waitingNodes.front();
            waitingNodes.pop();

            if (firstNode->left != NULL)
            {
                waitingNodes.push(firstNode->left);
            }
            else
            {
                firstNode->left = new Node2<T,V>(key, value);
                firstNode->left->left = NULL;
                firstNode->left->right = NULL;
                return;
            }

            if (firstNode->right != NULL)
            {
                waitingNodes.push(firstNode->right);
            }
            else
            {
                firstNode->right = new Node2<T,V>(key, value);
                firstNode->right->left = NULL;
                firstNode->right->right = NULL;
                return;
            }
        }
    }

    int compute_hash(Node2<T,V> *leaf)
    {
        // Compute hashes recursively
        if (leaf == NULL)
        {
            return 0;
        }
        else
        {
            int l_hash = compute_hash(leaf->left);
            int r_hash = compute_hash(leaf->right);
            if(!(l_hash == r_hash && l_hash == 0))
            {
                leaf->value = pseudo_hash(l_hash, r_hash);
            }
            return leaf->value;
            // return hash(leaf->value) + concat(l_hash, r_hash)
        }
    }

    void topView(Node2<T, V> *leaf)
    {
        if (leaf != NULL)
        {
            topView(leaf->left);
            topView(leaf->right);
            std::cout << "<" << leaf->key << "," << leaf->value << ">\t";
        }
    }

    void destroy_tree(Node2<T,V> *leaf)
    {
        if (leaf != NULL)
        {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
        }
    }

    size_t size(Node2<T,V> *leaf)
    {
        if (leaf == NULL)
        {
            return 0;
        }
        else
        {
            return (size(leaf->left) + 1 + size(leaf->right));
        }
    }

    size_t maxDepth(Node2<T,V> *leaf)
    {
        if (leaf == NULL)
        {
            return 0;
        }
        else
        {
            size_t lMaxDepth = maxDepth(leaf->left);
            size_t rMaxDepth = maxDepth(leaf->right);

            return std::max(lMaxDepth, rMaxDepth) + 1;
        }
    }
};

#endif
