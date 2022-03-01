#ifndef ABSTRACTGRAPH_HPP
#define ABSTRACTGRAPH_HPP

#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "Matrix.hpp"

template <typename T>
class AbstractGraph
{
    public:
    AbstractGraph() {}

    AbstractGraph(std::vector<Vertex<T>*> vertices) : Vertices(vertices) {}

    std::vector<Vertex<T> *> Vertices;

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

    AdjacencyMatrix getAdjacencyMatrix(void)
    {
        size_t V = VerticesCount();
        AdjacencyMatrix Adj(V, V);
        Adj.setConstant(0);
        for (auto &v : Vertices)
        {
            size_t row = graphcpp::find(Vertices, v);
            for (auto &neighbor : v->Neighbors)
            {
                size_t col = graphcpp::find(Vertices, neighbor);
                Adj(row, col) = 1;
            }
        }
        return Adj;
    }

    ~AbstractGraph() {}
};

template <typename T>
class UndirectedGraph : public AbstractGraph<T>
{
    public:
    UndirectedGraph() {}
    UndirectedGraph(std::vector<Vertex<T>*> vertices) : AbstractGraph<T>(vertices) {}

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
class UndirectedGraphAdj : public UndirectedGraph<T>
{
    public:
    UndirectedGraphAdj(std::vector<Vertex<T>*> vertices, AdjacencyMatrix adj) : UndirectedGraph<T>(vertices), A(adj) { CreateGraph();}

    AdjacencyMatrix A;

    void CreateGraph(void)
    {
        if(!A.isSymmetric())
        {
            std::cerr << "Adjacency matrix should be symmetric! " << std::endl;
            return;
        }
        size_t v_idx = 0; // row of upper triangular of A (symmetric)
        for (auto &v : UndirectedGraph<T>::Vertices)
        {
            // iterate over 
            for (size_t col=v_idx; col<A.Cols(); col++)
            {
                if(A(v_idx,col) != 0)
                {
                    UndirectedGraph<T>::AddPair(*v, *UndirectedGraph<T>::Vertices[col]);
                }
            }
            v_idx++;
        }
    }

    AdjacencyMatrix getAdjacencyMatrix(void)
    {
        return this->A;
    }
};

template <typename T>
class DirectedGraph : public AbstractGraph<T>
{
    public:
    DirectedGraph() {}

    DirectedGraph(std::vector<Vertex<T>*> vertices) : AbstractGraph<T>(vertices) {}

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

template <typename T>
class DirectedGraphAdj : public DirectedGraph<T>
{
public:
    DirectedGraphAdj(std::vector<Vertex<T> *> vertices, AdjacencyMatrix adj) : DirectedGraph<T>(vertices), A(adj) { CreateGraph(); }

    AdjacencyMatrix A;

    void CreateGraph(void)
    {
        size_t v_idx = 0;
        for (auto &v : DirectedGraph<T>::Vertices)
        {
            // iterate over
            for (size_t col = 0; col < A.Cols(); col++)
            {
                if (A(v_idx, col) != 0)
                {
                    DirectedGraph<T>::AddPair(*v, *DirectedGraph<T>::Vertices[col]);
                }
            }
            v_idx++;
        }
    }

    AdjacencyMatrix getAdjacencyMatrix(void)
    {
        return this->A;
    }
};
#endif