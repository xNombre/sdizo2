#pragma once

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

struct PathNode {
    size_t weight = SIZE_MAX;
    size_t prev = SIZE_MAX;

    PathNode(const size_t weight, const size_t &prev) : weight(weight), prev(prev) { }
    PathNode() { }

public:
    bool operator==(const PathNode &other) const
    {
        return weight == other.weight && prev == other.prev;
    }
};