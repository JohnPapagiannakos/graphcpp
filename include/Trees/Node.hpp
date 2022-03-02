#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node
{
    public:
    Node(T val) : key_value(val), left(NULL), right(NULL) {};

    ~Node(){};

    // protected:
    T key_value;
    Node<T> *left;
    Node<T> *right;
};

#endif