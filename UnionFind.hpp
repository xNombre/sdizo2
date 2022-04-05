#pragma once

#include "Array.hpp"

using std::size_t;

class UnionFind {

    struct Node {
        size_t parent = 0;
        size_t rank = 0;
    };
    
    Array<Node> table;

public:
    // Nodes are counted from 1
    UnionFind(const size_t &size) : table(size + 1)
    {
    }

    const size_t &findNode(const size_t &node)
    {
        if (node == 0)
            throw std::invalid_argument("Using node 0 is not allowed!");
        
        if (table[node].parent == 0)
            return node;

        table[node].parent = findNode(table[node].parent);
        return table[node].parent;
    }

    void unionNodes(const size_t &a, const size_t &b)
    {
        if (a == 0 || b == 0)
            throw std::invalid_argument("Using node 0 is not allowed!");
        
        auto aParent = findNode(a);
        auto bParent = findNode(b);

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