#ifndef ABSTRACTWEIGHTEDGRAPH_HPP
#define ABSTRACTWEIGHTEDGRAPH_HPP

#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "Matrix.hpp"
#include "Utils.hpp"

template <typename T, typename W>
class AbstractWeightedGraph
{
public:
    AbstractWeightedGraph() {}

    AbstractWeightedGraph(std::vector<WeightedVertex<T,W> *> vertices) : Vertices(vertices) {}

    std::vector<WeightedVertex<T,W> *> Vertices;

    int VerticesCount(void)
    {
        return Vertices.size();
    }

    bool operator==(const WeightedVertex<T, W> &v2) const
    {
        return (this->Value == v2.Value);
    }

    typename std::vector<WeightedVertex<T, W> *>::iterator FindVertex(const WeightedVertex<T, W> &vertex)
    {
        return std::find(Vertices.begin(), Vertices.end(), &vertex);
    }

    bool ContainsVertex(const WeightedVertex<T, W> &vertex)
    {
        typename std::vector<WeightedVertex<T,W> *>::iterator idx = FindVertex(vertex);
        return (idx != Vertices.end());
    }

    void AddVertex(WeightedVertex<T,W> &vertex)
    {
        if (!ContainsVertex(vertex))
        {
            Vertices.push_back(&vertex);
        }
    }

    void AddNeighbor(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second, W weight)
    {
        if (!first.ContainsEdge(second))
        {
            first.AddEdge(second, weight);
        }
    }

    void RemoveNeighbor(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second)
    {
        if (first.ContainsEdge(second))
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
            for (auto &w : v->Weight)
            {
                std::cout << "{" << w << "}" << "\t";
            }
            std::cout << std::endl;
        }
    }

    Matrix<W> getAdjacencyMatrix(void)
    {
        size_t V = VerticesCount();
        Matrix<W> Adj(V,V);
        Adj.setConstant(0);
        for (auto &v : Vertices)
        {
            size_t row = graphcpp::find(Vertices, v);
            typename std::vector<W>::iterator weight = v->Weight.begin();
            for (auto &neighbor : v->Neighbors)
            {
                size_t col = graphcpp::find(Vertices, neighbor);
                Adj(row,col) = *weight;
                weight++;
            }
        }
        return Adj;
    }

    ~AbstractWeightedGraph() {}
};

template <typename T, typename W>
class UndirectedWeightedGraph : public AbstractWeightedGraph<T, W>
{
    public:
    UndirectedWeightedGraph() {}
    UndirectedWeightedGraph(std::vector<WeightedVertex<T,W>*> vertices) : AbstractWeightedGraph<T,W>(vertices) {}

    void AddPair(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second, W weight)
    {
        AddNeighbors(first, second, weight);
        AbstractWeightedGraph<T,W>::AddVertex(first);
        AbstractWeightedGraph<T,W>::AddVertex(second);
    }

    void RemovePair(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second)
    {
        RemoveNeighbors(first, second);
    }

    void AddNeighbors(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second, W weight)
    {
        AbstractWeightedGraph<T,W>::AddNeighbor(first, second, weight);
        AbstractWeightedGraph<T,W>::AddNeighbor(second, first, weight);
    }

    void RemoveNeighbors(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second)
    {
        AbstractWeightedGraph<T,W>::RemoveNeighbor(first, second);
        AbstractWeightedGraph<T,W>::RemoveNeighbor(second, first);
    }

    ~UndirectedWeightedGraph() {}
};

template <typename T, typename W>
class UndirectedWeightedGraphAdj : public UndirectedWeightedGraph<T,W>
{
    public:
    UndirectedWeightedGraphAdj(std::vector<WeightedVertex<T,W>*> vertices, Matrix<W> adj) : UndirectedWeightedGraph<T,W>(vertices), A(adj) { CreateGraph();}

    Matrix<W> A;

    void CreateGraph(void)
    {
        if(!A.isSymmetric())
        {
            std::cerr << "Adjacency matrix should be symmetric! " << std::endl;
            return;
        }
        size_t v_idx = 0; // row of upper triangular of A (symmetric)
        for (auto &v : UndirectedWeightedGraph<T,W>::Vertices)
        {
            // iterate over
            for (size_t col=v_idx; col<A.Cols(); col++)
            {
                if(A(v_idx,col) != 0)
                {
                    UndirectedWeightedGraph<T,W>::AddPair(*v, *UndirectedWeightedGraph<T,W>::Vertices[col], A(v_idx, col));
                }
            }
            v_idx++;
        }
    }

    Matrix<W> getAdjacencyMatrix(void)
    {
        return this->A;
    }
};

template <typename T, typename W>
class DirectedWeightedGraph : public AbstractWeightedGraph<T, W>
{
    public:
    DirectedWeightedGraph() {}

    DirectedWeightedGraph(std::vector<WeightedVertex<T,W>*> vertices) : AbstractWeightedGraph<T,W>(vertices) {}

    void AddPair(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second, W weight)
    {
        AddNeighbors(first, second);
        AbstractWeightedGraph<T,W>::AddVertex(first);
        AbstractWeightedGraph<T,W>::AddVertex(second);
    }

    void RemovePair(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second)
    {
        RemoveNeighbors(first, second);
    }

    void AddNeighbors(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second, W weight)
    {
        AbstractWeightedGraph<T,W>::AddNeighbor(first, second, weight);
    }

    void RemoveNeighbors(WeightedVertex<T,W> &first, WeightedVertex<T,W> &second)
    {
        RemoveNeighbor(first, second);
    }

    ~DirectedWeightedGraph() {}
};

template <typename T, typename W>
class DirectedWeightedGraphAdj : public DirectedWeightedGraph<T,W>
{
public:
    DirectedWeightedGraphAdj(std::vector<WeightedVertex<T, W> *> vertices, Matrix<W> adj) : DirectedWeightedGraph<T,W>(vertices), A(adj) { CreateGraph(); }

    Matrix<W> A;

    void CreateGraph(void)
    {
        size_t v_idx = 0;
        for (auto &v : DirectedWeightedGraph<T,W>::Vertices)
        {
            // iterate over
            for (size_t col = 0; col < A.Cols(); col++)
            {
                if (A(v_idx, col) != 0)
                {
                    DirectedWeightedGraph<T,W>::AddPair(*v, *DirectedWeightedGraph<T,W>::Vertices[col], A(v_idx, col));
                }
            }
            v_idx++;
        }
    }
    
    Matrix<W> getAdjacencyMatrix(void)
    {
        return this->A;
    }
};
#endif