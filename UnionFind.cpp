#include "UnionFind.hpp"

UnionFind::UnionFind(const size_t &size)
{
    if (size == SIZE_MAX)
        throw std::invalid_argument("Limit reached!");

    table = Array<Node>(size);
}

const size_t &UnionFind::findNode(const size_t &node)
{
    if (table[node].parent == SIZE_MAX)
        return node;

    table[node].parent = findNode(table[node].parent);
    return table[node].parent;
}

void UnionFind::unionNodes(const size_t &a, const size_t &b)
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
