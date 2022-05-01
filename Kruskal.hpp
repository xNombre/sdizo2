#pragma once

#include "UnionFind.hpp"
#include "MinHeap.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"

using std::size_t;

class Kruskal {
public:
    static ListGraph generateMst(const ListGraph &graph);
    static MatrixGraph generateMst(const MatrixGraph &graph);
};