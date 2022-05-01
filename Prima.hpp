#pragma once

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "MinHeap.hpp"

class Prima {
public:
    static ListGraph generateMst(const ListGraph &graph);
    static MatrixGraph generateMst(const MatrixGraph &graph);
};