#pragma once

#include "MinHeap.hpp"
#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "TotalPathCost.hpp"
#include "PathNode.hpp"

class Dijkstra {
    struct HeapNode {
        size_t distance;
        size_t vertex;

        bool operator>(const HeapNode &other) const
        {
            return distance > other.distance;
        }
        bool operator<(const HeapNode &other) const
        {
            return distance < other.distance;
        }

        HeapNode(const size_t &vertex, const size_t &distance) :
            distance(distance), vertex(vertex)
        {
        }

        HeapNode() { }
    };

public:
    static Array<PathNode> getShortestPath(const ListGraph &graph, const size_t &from = 0);

    static Array<PathNode> getShortestPath(const MatrixGraph &graph, const size_t &from = 0);

    template<typename T>
    static TotalPathCost getShortestPathFromTo(const T &graph,
                                               const size_t &from,
                                               const size_t &to);
};