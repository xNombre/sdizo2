#pragma once

#include "Array.hpp"

typedef Array<size_t> MatrixRow;
typedef Array<MatrixRow> MatrixArray;
class MatrixGraph {
    MatrixArray matrix;

public:
    void addEdge(const size_t &from, const size_t &to, const size_t &weight)
    {

    }

    const MatrixArray &getMatrix() const
    {
        return matrix;
    }

    const size_t &getVertexCount() const
    {
        
    }
};