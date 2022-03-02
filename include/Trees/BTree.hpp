#ifndef BTREE_HPP
#define BTREE_HPP

#include "Node.hpp"

template <typename T>
class BTree
{
    public:
    // BST();
    BTree() : _root(NULL) {};

    void insert(T key)
    {
        if (_root != NULL)
            insert(key, _root);
        else
        {
            _root = new Node<T>(key);
            _root->left = NULL;
            _root->right = NULL;
        }
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

    ~BTree() {destroy_tree();};

    private:
    Node<T> *_root;

    void insert(T key, Node<T> *leaf)
    {
        std::queue<Node<T>*> waitingNodes;

        waitingNodes.push(leaf);

        while (!waitingNodes.empty())
        {
            Node<T> *firstNode = waitingNodes.front();
            waitingNodes.pop();

            if (firstNode->left != NULL)
            {
                waitingNodes.push(firstNode->left);
            }
            else
            {
                firstNode->left = new Node<T>(key);
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
                firstNode->right = new Node<T>(key);
                firstNode->right->left = NULL;
                firstNode->right->right = NULL;
                return;
            }
        }
    }

    void destroy_tree(Node<T> *leaf)
    {
        if (leaf != NULL)
        {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
        }
    }

    size_t size(Node<T> *leaf)
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

    size_t maxDepth(Node<T> *leaf)
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