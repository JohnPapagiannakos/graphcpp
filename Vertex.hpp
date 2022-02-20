#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

template<typename T>
class Vertex
{
    public:
   
    Vertex(T value) : Value(value){}
    
    Vertex(T value, std::vector<Vertex<T>> neighbors) : Value(value), Neighbors(neighbors){}

    T Value;

    std::vector<Vertex<T> *> Neighbors;

    bool operator==(const Vertex<T> &v2) const
    {
        return (this->Value == v2.Value);
    }

    typename std::vector<Vertex<T>*>::iterator FindEdge(const Vertex<T> &vertex)
    {
        return std::find(Neighbors.begin(), Neighbors.end(), &vertex);
    }

    bool ContainsEdge(const Vertex<T> &vertex)
    {
        typename std::vector<Vertex<T>*>::iterator idx = FindEdge(vertex);
        return (idx != Neighbors.end());
    }

    int NeighborCount(void)
    {
        return Neighbors.size();
    }

    void AddEdge(Vertex<T> &newVertex)
    {
        // Neighbors.push_back(&newVertex);
        if (!ContainsEdge(newVertex))
        {
            Neighbors.push_back(&newVertex);
        }
        // std::cout << "{" << Value << "} add edge : {" << newVertex.Value << "}: -> new size is "  << NeighborCount() << std::endl;
        // for(auto &it: Neighbors)
        // {
        //     std::cout << it->Value << "\t";
        // }
        // std::cout << std::endl;
    }

    // void AddEdges(std::vector<Vertex<T>> newVertices)
    // {
    //     Neighbors.insert(Neighbors.end(), newVertices.begin(), newVertices.end());
    // }

    void RemoveEdge(Vertex<T> unusedVertex)
    {
        typename std::vector<Vertex<T>>::iterator idx = FindEdge(unusedVertex);
        if(idx != Neighbors.end())
        {
            Neighbors.erase(idx);
        }
    }

    ~Vertex()
    {
        // for (auto &element : Neighbors)
        // {
        //     delete element;
        // }
        // Neighbors.clear();
    };
};

#endif