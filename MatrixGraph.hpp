#pragma once

#include <iostream>

#include "Array.hpp"
#include "Edge.hpp"

#define RST  "\x1B[0m"
#define KRED  "\x1B[41m"
#define KBLU  "\x1B[44m"

typedef Array<long long> NodeMatrix;
typedef Array<NodeMatrix> IncidenceMatrix;

class MatrixGraph {
    IncidenceMatrix matrix;
    bool isDirected;

public:
    MatrixGraph(bool isDirected = true) : isDirected(isDirected) { }

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
            if (i == from)
                matrix[i].push_back(isDirected ? -weight : weight);
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

    const size_t getEdgesCount() const
    {
        if (matrix.size() != 0)
            return matrix[0].size();
        else
            return 0;
    }

    size_t findFirstVertexOfEdge(const size_t &edge) const
    {
        // FIXME: nie jest przygotowane na dwukierunkowe grafy bo sprawdza ujemną, wywala -1
        auto count = getEdgesCount();
        for (size_t i = 0; i < count; i++) {
            if (matrix[i][edge] < 0)
                return i;
        }

        // Unreachable case
        return -1;
    }

    void print() const
    {
        const auto &count = getEdgesCount();
        const auto &vertices = getVertexCount();

        std::cout << "   " << KRED;
        for (size_t j = 0; j < count; j++) {
            std::cout << j << "  ";

            if (j < 10)
                std::cout << " ";
        }
        std::cout << RST << std::endl;

        for (size_t i = 0; i < vertices; i++) {
            std::cout << KBLU << i << RST << " ";
            if (i < 10)
                std::cout << " ";

            for (size_t j = 0; j < count; j++) {
                std::cout << matrix[i][j] << " ";

                if (matrix[i][j] < 10 && matrix[i][j] > -1)
                    std::cout << "  ";
                else if (matrix[i][j] > -10)
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
};