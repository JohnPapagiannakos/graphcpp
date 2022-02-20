#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <algorithm>
#include <vector>
#include <unordered_map>

#include "Vertex.hpp"
#include "AbstractGraph.hpp"

template <typename T>
class DFS
{
    public:

    DFS(AbstractGraph<T> graph) : Graph(graph) {}

    AbstractGraph<T> Graph;

    std::vector<Vertex<T> *> Visited;

    void MakeUnvisited(void)
    {
        for (auto &vertex : Visited)
        {
            vertex = NULL;
        }
        Visited.clear();
    }

    void Iterate(Vertex<T> rootVertex)
    {
        MakeUnvisited();
        std::cout << "Starting DFS using vertex : " << rootVertex.Value << " as root" << std::endl;
        RecursiveDFS(Visited, rootVertex);
        for(auto &v: Visited)
        {
            std::cout << v->Value << "\t";
        }
        std::cout << std::endl;
    }

    void IterateAll(void)
    {
        MakeUnvisited();
        for (auto &rootVertex : Graph.Vertices)
        {
            std::cout << "Starting DFS using vertex : " << rootVertex->Value << " as root" << std::endl;
            RecursiveDFS(Visited, *rootVertex);
            for (auto &v : Visited)
            {
                std::cout << v->Value << "\t";
            }
            std::cout << std::endl;
        }
    }

    // void RecursiveDFS(Vertex<T> &rootVertex)
    // {
    //     std::cout << rootVertex.Value << "\t" << rootVertex.IsVisited << "\t(" << rootVertex.NeighborCount() << ")" << std::endl;
    //     rootVertex.IsVisited = true;
    //     for (auto &neighbor : rootVertex.Neighbors)
    //     {
    //         // std::cout << "{" << neighbor->Value << "," << neighbor->IsVisited << "}" << std::endl;
    //         if (!neighbor->IsVisited)
    //         {
    //             RecursiveDFS(*neighbor);
    //         }
    //     }
    // }

    void RecursiveDFS(std::vector<Vertex<T> *> &IsVisited, Vertex<T> &rootVertex)
    {
        IsVisited.push_back(&rootVertex);
        // std::cout << rootVertex.Value << "\t" << IsVisited.size() << "\t(" << rootVertex.NeighborCount() << ")" << std::endl;
        for (auto &neighbor : rootVertex.Neighbors)
        {
            bool check = true;
            for (auto &el : IsVisited)
            {
                // std::cout << el->Value << "\t" << neighbor->Value << std::endl;
                check = (check && (el->Value != neighbor->Value));
            }
            if (check)
            {
                RecursiveDFS(IsVisited, *neighbor);
            }
        }
    }
};

#endif