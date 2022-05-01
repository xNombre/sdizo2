#pragma once

#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "TotalPathCost.hpp"
#include "PathNode.hpp"

class BellmanFord {

public:
    static Array<PathNode> getShortestPath(const ListGraph &graph, const size_t &from = 0);

    static Array<PathNode> getShortestPath(const MatrixGraph &graph, const size_t &from = 0);

    template<typename T>
    static TotalPathCost getShortestPathFromTo(const T &graph,
                                               const size_t &from,
                                               const size_t &to);
};