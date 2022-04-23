#pragma once

#include "Array.hpp"

typedef Array<long long> NodeMatrix;
typedef Array<NodeMatrix> IncidenceMatrix;

class MatrixGraph {
    IncidenceMatrix matrix;

public:
    void addEdge(const size_t &from, const size_t &to, const long long &weight)
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
            //matrix[i].resize(edgesCount + 1);
            if (i == from)
                matrix[i].push_back(-weight);
            else if (i == to)
                matrix[i].push_back(weight);
            else
                matrix[i].push_back(0);
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