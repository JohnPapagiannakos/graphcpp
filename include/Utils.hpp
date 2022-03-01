#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>
#include <bits/stdc++.h>

#include "Constants.hpp"
#include "Vertex.hpp"

namespace graphcpp
{
    template <typename T, typename W>
    size_t find(std::vector<WeightedVertex<T, W> *> &vec, WeightedVertex<T, W> *current_vertex)
    {
        typename std::vector<WeightedVertex<T, W> *>::iterator u_itr = vec.begin();
        for (; u_itr != vec.end(); ++u_itr)
        {
            if (current_vertex->Value == (*u_itr)->Value)
                break;
            else
                continue;
        }
        size_t curr_vertex_idx = std::distance(vec.begin(), u_itr);
        assert(curr_vertex_idx >= 0);
        return curr_vertex_idx;
    }

    template <typename T>
    size_t find(std::vector<Vertex<T> *> &vec, Vertex<T> *current_vertex)
    {
        typename std::vector<Vertex<T> *>::iterator u_itr = vec.begin();
        for (; u_itr != vec.end(); ++u_itr)
        {
            if (current_vertex->Value == (*u_itr)->Value)
                break;
            else
                continue;
        }
        size_t curr_vertex_idx = std::distance(vec.begin(), u_itr);
        assert(curr_vertex_idx >= 0);
        return curr_vertex_idx;
    }
}

#endif