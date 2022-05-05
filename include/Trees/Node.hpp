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

template <typename T, typename V>
class Node2
{
    public:
    Node2(T Key, V Val) : key(Key), value(Val), left(NULL), right(NULL){};

    ~Node2(){};

    // protected:
    T key;
    V value;
    Node2<T,V> *left;
    Node2<T,V> *right;
};

#endif