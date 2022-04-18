#pragma once

#include "Array.hpp"

typedef Array<size_t> NodeMatrix;
typedef Array<NodeMatrix> IncidenceMatrix;

class MatrixGraph {
    IncidenceMatrix matrix;

public:
    void addEdge(const size_t &from, const size_t &to, const size_t &weight)
    {
        // Add new vertices if necessary
        auto newSize = std::max(from, to) + 1;
        auto oldSize = matrix.size();
        if (newSize > oldSize) {
            matrix.resize(newSize);

            auto &edgesCount = matrix[0].size();
            for (size_t i = oldSize; i < newSize; i++) {
                matrix[i].resize(edgesCount);
            }
        }

        // Add new edge
        auto &edgesCount = matrix[0].size();
        for (size_t i = 0; i < matrix.size(); i++) {
            matrix[i].resize(edgesCount + 1);
            if (i == from)
                matrix[i] = -weight;
            else if (i == to)
                matrix[i] = weight;
        }
    }

    const IncidenceMatrix &getMatrix() const
    {
        return matrix;
    }

    const size_t &getVertexCount() const
    {
        return matrix.size();
    }

    const size_t &getEdgesCount() const
    {
        if (matrix.size() != 0)
            return matrix[0].size();
        else
            return 0;
    }
};