#pragma once

#include "Array.hpp"

using std::size_t;

class UnionFind {
    struct Node {
        size_t parent = SIZE_MAX;
        size_t rank = 0;
    };

    Array<Node> table;

public:
    // SIZE_MAX is reserved
    UnionFind(const size_t &size);
    const size_t &findNode(const size_t &node);
    void unionNodes(const size_t &a, const size_t &b);
};