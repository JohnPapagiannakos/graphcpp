#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <algorithm>
#include <vector>
#include <list>
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


template <typename T>
class BFS
{
    public:

    BFS(AbstractGraph<T> graph) : Graph(graph) {}

    AbstractGraph<T> Graph;

    std::vector<Vertex<T> *> Visited;

    std::list<Vertex<T> *> Queue;

    void MakeUnvisited(void)
    {
        for (auto &vertex : Visited)
        {
            vertex = NULL;
        }
        Visited.clear();

        for (auto &queue : Queue)
        {
            queue = NULL;
        }
        Queue.clear();
    }

    void Iterate(Vertex<T> rootVertex)
    {
        MakeUnvisited();
        std::cout << "Starting BFS using vertex : " << rootVertex.Value << " as root" << std::endl;
        IterativeBFS(rootVertex);
        for(auto &v: Visited)
        {
            std::cout << v->Value << "\t";
        }
        std::cout << std::endl;
    }

    void IterativeBFS(Vertex<T> &rootVertex)
    {
        Visited.push_back(&rootVertex);
        Queue.push_back(&rootVertex);

        while(!Queue.empty())
        {
            Vertex<T> *v = Queue.front();

            Queue.pop_front();

            for (auto &neighbor : v->Neighbors)
            {
                bool check = true;
                for (auto &el : Visited)
                {
                    // std::cout << el->Value << "\t" << neighbor->Value << std::endl;
                    check = (check && (el->Value != neighbor->Value));
                }
                if (check)
                {
                    Visited.push_back(neighbor);
                    Queue.push_back(neighbor);
                }
            }
        }
    }
};

#endif