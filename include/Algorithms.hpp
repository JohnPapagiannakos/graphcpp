#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>
#include <bits/stdc++.h>

#include "Constants.hpp"
#include "Vertex.hpp"
#include "AbstractGraph.hpp"
#include "AbstractWeightedGraph.hpp"
#include "Utils.hpp"

template <typename T>
class DFS
{
    public:

    DFS(AbstractGraph<T> graph) : Graph(graph) {}

    AbstractGraph<T> Graph;

    std::vector<Vertex<T> *> Visited;

    void Print(void)
    {
        for (auto &v : Visited)
        {
            std::cout << v->Value << "\t";
        }
        std::cout << std::endl;
    }

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
        Print();
    }

    void IterateAll(void)
    {
        MakeUnvisited();
        for (auto &rootVertex : Graph.Vertices)
        {
            std::cout << "Starting DFS using vertex : " << rootVertex->Value << " as root" << std::endl;
            RecursiveDFS(Visited, *rootVertex);
            Print();
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

    void Print(void)
    {
        for (auto &v : Visited)
        {
            std::cout << v->Value << "\t";
        }
        std::cout << std::endl;
    }

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
        Print();
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

template <typename T, typename W>
class ShortestPath
{
    public:
    
    ShortestPath(AbstractWeightedGraph<T,W> graph) : Graph(graph) {}
    
    AbstractWeightedGraph<T,W> Graph;

    std::set<std::pair<W, WeightedVertex<T, W> *>> setOfPairs;

    // Store distances in a vector and initialize all distances as infinite (POSINF)
    std::vector<W> Distance;

    void Print(WeightedVertex<T, W> rootVertex)
    {
        // Print shortest distances stored in Distance[]
        std::cout << "Vertex\tDistance from Source " << rootVertex.Value << std::endl;
        for (int i = 0; i < Graph.VerticesCount(); ++i)
            std::cout << (Graph.Vertices[i])->Value << "\t" << Distance[i] << std::endl;
    }

    void DijkstraShortestPath(WeightedVertex<T,W> rootVertex)
    {
        // Clean
        setOfPairs.clear();
        Distance.clear();

        for (auto &vertex : Graph.Vertices)
        {
            if (rootVertex.Value == vertex->Value)
            {
                Distance.push_back(0);
            }
            else
            {
                Distance.push_back(POSINF);
            }
        }

        // Insert source vertex in Set and initialize its distance as 0.
        setOfPairs.insert(std::make_pair(0, &rootVertex));

        // Loop until all shortest distance are finalized
        while (!setOfPairs.empty())
        {
            std::pair<W, WeightedVertex<T, W> *> current_pair = *(setOfPairs.begin());
            setOfPairs.erase(setOfPairs.begin());

            WeightedVertex<T, W> *current_vertex = current_pair.second;

            size_t curr_vertex_idx = graphcpp::find(Graph.Vertices, current_vertex);

            typename std::vector<WeightedVertex<T, W> *>::iterator neighbor;
            typename std::vector<W>::iterator weight;
            for (neighbor = current_vertex->Neighbors.begin(), weight = current_vertex->Weight.begin(); neighbor != current_vertex->Neighbors.end(); ++neighbor, ++weight)
            {
                size_t neighbor_idx = graphcpp::find(Graph.Vertices, *neighbor);

                // If there is shorter path to neighbor through current_vertex.
                if (Distance[neighbor_idx] > Distance[curr_vertex_idx] + *weight)
                {
                    // If distance of neighbor is not +INF then it must be inserted in our set
                    if (Distance[neighbor_idx] != POSINF)
                        setOfPairs.erase(setOfPairs.find(std::make_pair(Distance[neighbor_idx], *neighbor)));

                    // Updating distance of neighbor
                    Distance[neighbor_idx] = Distance[curr_vertex_idx] + *weight;
                    setOfPairs.insert(std::make_pair(Distance[neighbor_idx], *neighbor));
                }
            }
        }

        Print(rootVertex);
    }
};

#endif