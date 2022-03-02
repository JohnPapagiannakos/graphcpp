#ifndef BST_HPP
#define BST_HPP

#include "BTree.hpp"

template <typename T>
class BST : public BTree<T>
{
    public:
    // BST();
    BST() : _root(NULL) {};

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

    Node<T> *search(T key)
    {
        return search(key, _root);
    }

    /*
        Given a BST, return its minimum data <T> value.
    */
    T minValue(void)
    {
        return minValue(_root);
    }

    /*
        Given a BST, return its maximum data <T> value.
    */
    T maxValue(void)
    {
        return maxValue(_root);
    }

    /*
     Given a BST and a sum, return path as a vector from the root
     down to a leaf, such that adding up all the values along the path
     equals the given sum.
    */
    std::vector<T> getPathOfSum(T sum)
    {
        std::vector<T> path;
        bool found = false;
        getPathOfSum(sum, path, _root, found);
        return path;
    }

    /*
        Given a BST, print its elements <T> in increasing sorted order.
    */
    void printIncrSorted(void)
    {
        printIncrSorted(_root);
    }

    /*
        Given a BST, print its elements <T> in decreasing sorted order.
    */
    void printDecrSorted(void)
    {
        printDecrSorted(_root);
    }

    ~BST() {BTree<T>::destroy_tree();};

    private:
    Node<T> *_root;

    void insert(T key, Node<T> *leaf)
    {
        if (key < leaf->key_value)
        {
            if (leaf->left != NULL)
            {
                insert(key, leaf->left);
            }
            else
            {
                leaf->left = new Node<T>(key);
                leaf->left->left = NULL; 
                leaf->left->right = NULL; 
            }
        }
        else if (key >= leaf->key_value)
        {
            if (leaf->right != NULL)
            {
                insert(key, leaf->right);
            }
            else
            {
                leaf->right = new Node<T>(key);
                leaf->right->left = NULL; 
                leaf->right->right = NULL; 
            }
        }
    }

    Node<T> *search(int key, Node<T> *leaf)
    {
        if (leaf != NULL)
        {
            std::cout << leaf->key_value << std::endl;

            if (key == leaf->key_value)
            {
                return leaf;
            }
            if (key < leaf->key_value)
            {
                return search(key, leaf->left);
            }
            else
            {
                return search(key, leaf->right);
            }
        }
        else
        {
            return NULL;
        }
    }

    T minValue(Node<T> *leaf)
    {
        if(leaf->left == NULL)
        {
            return leaf->key_value;
        }
        else
        {
            return minValue(leaf->left);
        }
        
    }

    T maxValue(Node<T> *leaf)
    {
        if (leaf->right == NULL)
        {
            return leaf->key_value;
        }
        else
        {
            return maxValue(leaf->right);
        }
    }

    void getPathOfSum(T sum, std::vector<T> &path, Node<T> *leaf, bool &finished)
    {
        if (finished)
        {
            return;
        }
        if (leaf == NULL)
        {
            if (sum == 0)
            {
                finished = true;
                return;
            }
        }
        else
        {
            path.push_back(leaf->key_value);
            T remainder = sum - leaf->key_value;
            // std::cout << leaf->key_value << " " << remainder << std::endl;
            getPathOfSum(remainder, path, leaf->left,  finished);
            getPathOfSum(remainder, path, leaf->right, finished);
        }
    }

    void printIncrSorted(Node<T> *leaf)
    {
        if (leaf == NULL)
            return;
        else
        {
            printIncrSorted(leaf->left);
            std::cout << leaf->key_value << std::endl;
            printIncrSorted(leaf->right);
        }
    }

    void printDecrSorted(Node<T> *leaf)
    {
        if (leaf == NULL)
            return;
        else
        {
            printDecrSorted(leaf->right);
            std::cout << leaf->key_value << std::endl;
            printDecrSorted(leaf->left);
        }
    }
};

#endif