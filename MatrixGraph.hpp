#pragma once

#include "Array.hpp"

typedef Array<Array<size_t>> MatrixArray;
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
};