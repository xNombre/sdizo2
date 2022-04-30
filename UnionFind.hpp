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
    UnionFind(const size_t &size)
    {
        if (size == SIZE_MAX)
            throw std::invalid_argument("Limit reached!");

        table = Array<Node>(size);
    }

    const size_t &findNode(const size_t &node)
    {
        if (table[node].parent == SIZE_MAX)
            return node;

        table[node].parent = findNode(table[node].parent);
        return table[node].parent;
    }

    void unionNodes(const size_t &a, const size_t &b)
    {
        const auto &aParent = findNode(a);
        const auto &bParent = findNode(b);

        if (table[aParent].rank < table[bParent].rank)
            table[aParent].parent = bParent;
        else if (table[aParent].rank > table[bParent].rank)
            table[bParent].parent = aParent;
        else if (aParent != bParent) {
            table[bParent].parent = aParent;
            table[aParent].rank += 1;
        }
    }
};