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

    void addEdge(const size_t &from, const size_t &to, const long long &weight);
    const IncidenceMatrix &getMatrix() const;
    const size_t &getVertexCount() const;
    const size_t getEdgesCount() const;
    void print() const;
    void clear();
};