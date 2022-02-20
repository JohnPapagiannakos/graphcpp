#ifndef ABSTRACTGRAPH_HPP
#define ABSTRACTGRAPH_HPP

#include <iostream>
#include <vector>
#include "Vertex.hpp"

template <typename T>
class AbstractGraph
{
    public:
    AbstractGraph() {}

    AbstractGraph(std::vector<Vertex<T>> vertices) : Vertices(vertices) {}

    std::vector<Vertex<T> *> Vertices;
    std::vector<Vertex<T> *> Visited;

    int VerticesCount(void)
    {
        return Vertices.size();
    }

    bool operator==(const Vertex<T> &v2) const
    {
        return (this->Value == v2.Value);
    }

    typename std::vector<Vertex<T>*>::iterator FindVertex(const Vertex<T> &vertex)
    {
        return std::find(Vertices.begin(), Vertices.end(), &vertex);
    }

    bool ContainsVertex(const Vertex<T> &vertex)
    {
        typename std::vector<Vertex<T>*>::iterator idx = FindVertex(vertex);
        return (idx != Vertices.end());
    }

    void AddVertex(Vertex<T> &vertex)
    {
        if (!ContainsVertex(vertex))
        {
            Vertices.push_back(&vertex);
        }
    }
    
    void AddNeighbor(Vertex<T> &first, Vertex<T> &second)
    {
        if(!first.ContainsEdge(second))
        {
            first.AddEdge(second);
        }
    }

    void RemoveNeighbor(Vertex<T> &first, Vertex<T> &second)
    {
        if(first.ContainsEdge(second))
        {
            first.RemoveEdge(second);
        }
    }

    void Print(void)
    {
        std::cout << "Graph contains : " << VerticesCount() << " vertices" << std::endl;

        std::cout << std::endl;
        for (auto &v : Vertices)
        {
            std::cout << "vertex: " << v->Value << " (" << v->NeighborCount() << ")" << std::endl;
            for (auto &neighbor : v->Neighbors)
            {
                std::cout << neighbor->Value << "\t";
            }
            std::cout << std::endl;
        }
    }

    ~AbstractGraph() {}
};

template <typename T>
class UndirectedGraph : public AbstractGraph<T>
{
    public:
    UndirectedGraph() {}
    UndirectedGraph(std::vector<Vertex<T>> vertices) : AbstractGraph<T>(vertices) {}

    void AddPair(Vertex<T> &first, Vertex<T> &second)
    {
        AddNeighbors(first, second);
        AbstractGraph<T>::AddVertex(first);
        AbstractGraph<T> ::AddVertex(second);
    }

    void RemovePair(Vertex<T> &first, Vertex<T> &second)
    {
        RemoveNeighbors(first, second);
    }

    void AddNeighbors(Vertex<T> &first, Vertex<T> &second)
    {
        AbstractGraph<T>::AddNeighbor(first, second);
        AbstractGraph<T>::AddNeighbor(second, first);
    }

    void RemoveNeighbors(Vertex<T> &first, Vertex<T> &second)
    {
        AbstractGraph<T>::RemoveNeighbor(first, second);
        AbstractGraph<T>::RemoveNeighbor(second, first);
    }

    ~UndirectedGraph() {}
};

template <typename T>
class DirectedGraph : public AbstractGraph<T>
{
    public:
    DirectedGraph() {}

    DirectedGraph(std::vector<Vertex<T>> vertices) : AbstractGraph<T>(vertices) {}

    void AddPair(Vertex<T> &first, Vertex<T> &second)
    {
        AddNeighbors(first, second);
        AbstractGraph<T>::AddVertex(first);
        AbstractGraph<T>::AddVertex(second);
    }

    void RemovePair(Vertex<T> &first, Vertex<T> &second)
    {
        RemoveNeighbors(first, second);
    }

    void AddNeighbors(Vertex<T> &first, Vertex<T> &second)
    {
        AbstractGraph<T>::AddNeighbor(first, second);
    }

    void RemoveNeighbors(Vertex<T> &first, Vertex<T> &second)
    {
        RemoveNeighbor(first, second);
    }

    ~DirectedGraph() {}
};

#endif